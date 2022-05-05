#include "TFile.h"
#include "TRandom.h"
#include "TMath.h"
#include "TString.h"
#include "TChain.h"
#include "THnSparse.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "src/Fragment.h"
#include "src/Event.h"
#include <Nucleon.h>
#include <UEvent.h>
#include <EventInitialState.h>

#include <iostream>

using namespace std;

void SampleGlauberEvent(const TString &input_dirname,
                        const TString &input_filename,
                        const TString &output_dirname,
                        Int_t File,
                        Int_t Events,
                        Int_t AProj, Int_t ZProj, Int_t ATarg, Int_t ZTarg, Double_t PProjBeam, Double_t PTargBeam,
                        Double_t a,
                        Double_t b,
                        Double_t c,
                        Bool_t ATotDependsOnB = true,
                        Bool_t ATotDependsOnNSpec = true,
                        Bool_t ProcedureMode = false,
                        Bool_t FragDependsOnB = false,
                        Bool_t FragDependsOnNSpec = false,
                        Bool_t FragDependsOnATot = false,
                        Bool_t EYDependsOnB = false,
                        Bool_t EYDependsOnNSpec = false,
                        Bool_t EYDependsOnATot = false,
                        Bool_t EYDependsAFrag = false)
{
    gRandom->SetSeed(0);
    auto* fChain=new TChain("events");
    fChain->Add(input_dirname);
    Long64_t StartEvent = (File-1)*Events;
    Long64_t lNEvents = fChain->GetEntries();
    if (lNEvents>File*Events) lNEvents = File*Events;
    cout<<"Numer of entries equal "<<lNEvents-StartEvent<<endl;
    auto* fEvent = new UEvent;
    auto* fIniState = new EventInitialState;
    fChain->SetBranchAddress("event", &fEvent);
    fChain->SetBranchAddress("iniState", &fIniState);

    auto *fin = new TFile(input_filename);
    auto* ATotSampleHisto = (THnSparseD*)fin->Get("B_ATotProj_NSpecProj");
    auto* FragSampleHisto = (THnSparseD*)fin->Get("B_ATotProj_AFragProj_NaProj_NSpecProj");
    auto* ChargeSampleHisto = (THnSparseD*)fin->Get("B_ATotProj_AFragProj_ZFragProj_NSpecProj");
    auto* EYSampleHisto = (THnSparseD*)fin->Get("B_ATotProj_AFragProj_EProj_RapidityProj");
    fin->Close();
    ATotSampleHisto->SetName("B_ATotProj_NSpecProj_input");
    FragSampleHisto->SetName("B_ATotProj_AFragProj_NaProj_NSpecProj_input");
    ChargeSampleHisto->SetName("B_ATotProj_AFragProj_ZFragProj_NSpecProj_input");
    EYSampleHisto->SetName("B_ATotProj_AFragProj_EProj_RapidityProj_input");

    auto* fSBAFEvent = new Event(0, AProj, ZProj, ATarg, ZTarg);
    Fragment fSBAFFragment(0, 0., 0., 0., 0., 0., 0., 0., 0., 0, 0, 0, 0, 0, 0, 0);
    std::vector<Nucleon> fNucleons;

    auto *fout = new TFile(output_dirname, "recreate");
    auto *tree = new TTree ("SBAFTree", "SBAFTree");
    tree->Branch("event", "Event", fSBAFEvent);

    for (long i = StartEvent; i < lNEvents; i++)
    {
        cout << "\r" << 100.*(i-StartEvent+1)/(lNEvents-StartEvent) << "% done" << flush;
        fChain->GetEntry(i);

        fSBAFEvent->Clear();
        fSBAFEvent->SetEventId(i);
        fSBAFEvent->SetAProj(AProj);
        fSBAFEvent->SetZProj(ZProj);
        fSBAFEvent->SetATarg(ATarg);
        fSBAFEvent->SetZTarg(ZTarg);
        fSBAFEvent->SetB(fEvent->GetB());
        fSBAFEvent->SetBx(fEvent->GetBx());
        fSBAFEvent->SetBy(fEvent->GetBy());
        fSBAFEvent->SetNPartProj(fIniState->getNPartA());
        fSBAFEvent->SetNPartTarg(fIniState->getNPartB());
        fSBAFEvent->SetNColl(fIniState->getNColl());
        fSBAFEvent->SetATotTarg(0);
        fSBAFEvent->SetZTotTarg(0);
        fSBAFEvent->SetETotTarg(0.);
        fSBAFEvent->SetEPsdTarg(0.);
        fSBAFEvent->SetNFragTarg(0);
        for (int j=0; j<ATarg+1; j++) fSBAFEvent->SetNaTarg(0, j);
        fSBAFEvent->SetNuTarg(0);
//        fSBAFEvent->SetNAniVectors(NAniVectors);

        fNucleons = fIniState->getNucleons();
        for (int j=0; j<AProj; j++)
        {
            TLorentzVector fMomentum(0., 0., PProjBeam, TMath::Sqrt(PProjBeam*PProjBeam + 0.938*0.938));
            TVector3 fPosition(fNucleons.at(j).getPosition().X(), fNucleons.at(j).getPosition().Y(), fNucleons.at(j).getPosition().Z());
            fSBAFFragment.SetFragmentId(j);
            fSBAFFragment.SetPosition(fPosition);
            fSBAFFragment.SetMomentum(fMomentum);
            fSBAFFragment.SetEPsd(0);
            fSBAFFragment.SetAFrag(0);
            fSBAFFragment.SetZFrag(0);
            fSBAFFragment.SetPdgId(0);
            fSBAFFragment.SetNucleusId(0);
            fSBAFFragment.SetIniId(0);
            fSBAFFragment.SetSpectatorId(fNucleons.at(j).getSpectatorId());
            fSBAFEvent->AddFragment(fSBAFFragment);
        }

        for (int j=AProj; j<AProj + ATarg; j++)
        {
            TLorentzVector fMomentum(0., 0., 0., 0.938);
            TVector3 fPosition(fNucleons.at(j).getPosition().X(), fNucleons.at(j).getPosition().Y(), fNucleons.at(j).getPosition().Z());
            fSBAFFragment.SetFragmentId(j);
            fSBAFFragment.SetPosition(fPosition);
            fSBAFFragment.SetMomentum(fMomentum);
            fSBAFFragment.SetEPsd(0);
            fSBAFFragment.SetAFrag(0);
            fSBAFFragment.SetZFrag(0);
            fSBAFFragment.SetPdgId(0);
            fSBAFFragment.SetNucleusId(1);
            fSBAFFragment.SetIniId(0);
            fSBAFFragment.SetSpectatorId(fNucleons.at(j).getSpectatorId());
            fSBAFEvent->AddFragment(fSBAFFragment);
        }

        if (fSBAFEvent->SampleEvent(a, b, c,
                                    ATotSampleHisto, ATotDependsOnB, ATotDependsOnNSpec, ProcedureMode,
                                    FragSampleHisto,ChargeSampleHisto, FragDependsOnB, FragDependsOnNSpec, FragDependsOnATot,
                                    EYSampleHisto, EYDependsOnB, EYDependsOnNSpec, EYDependsOnATot, EYDependsAFrag))
            tree->Fill();


    }

    tree->Write();
    fout->Close();
}

