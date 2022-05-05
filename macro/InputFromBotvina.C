#include "TFile.h"
#include "TMath.h"
#include "TString.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TVector3.h"
#include "UEvent.h"
#include "UParticle.h"
#include "Nucleon.h"
#include "EventInitialState.h"

#include "src/Event.h"
#include "src/Fragment.h"

#include <iostream>

using namespace std;

void InputFromBotvina(const TString &input_botvina_dirname, const TString &input_glauber_dirname, const TString &output_dirname, Int_t AProj, Int_t ZProj, Int_t ATarg, Int_t ZTarg, Double_t PProjBeam, Double_t PTargBeam)
{
    auto* fChain=new TChain("events");
    auto* fChain_glauber=new TChain("events");
        fChain->Add(input_botvina_dirname);
        fChain_glauber->Add(input_glauber_dirname);
    cout<<"Numer of entries equal "<<fChain->GetEntries()<<endl;
    auto* fEvent = new UEvent;
    UParticle* fParticle;
    std::vector<Nucleon> fNucleons;
    auto* fIniState = new EventInitialState;
    auto* fIniState_glauber = new EventInitialState;
    fChain->AddFriend(fChain_glauber, "glauber");
    fChain->SetBranchAddress("event", &fEvent);
    fChain->SetBranchAddress("iniState", &fIniState);
    fChain->SetBranchAddress("glauber.iniState", &fIniState_glauber);

    auto* fSBAFEvent = new Event(0, AProj, ZProj, ATarg, ZTarg);
    Fragment fSBAFFragment(0, 0., 0., 0., 0., 0., 0., 0., 0., 0, 0, 0, 0, 0, 0, 0);

    Long64_t lNEvents = fChain->GetEntries();
    Long64_t fNpa;

    Double_t px_beam, py_beam, pz_beam, E_beam;
    if (PProjBeam > 3. && PProjBeam < 3.5) px_beam=0., py_beam=0., pz_beam=3.300000, E_beam=3.430721;
    else if (PProjBeam > 11.9 && PProjBeam < 12.1) px_beam=0., py_beam=0., pz_beam=12.0, E_beam=12.036604;
    else px_beam=0., py_beam=0., pz_beam=0.0, E_beam=0.0;
    TLorentzVector Beam(px_beam, py_beam, pz_beam, E_beam);
    TLorentzVector Target(0., 0., 0, 0.938);
    TLorentzRotation rTransform;
    rTransform.Boost((Beam + Target).BoostVector());

    auto* tree = new TTree ("SBAFTree", "SBAFTree");
    tree->Branch("event", "Event", fSBAFEvent);

    for (long i = 0; i < lNEvents; i++)
    {
        if (i%1000==0) cout << "\r" << 100.*i/lNEvents << "% done" << flush;
        fChain->GetEntry(i);
        fNpa = fEvent->GetNpa();
//        if (fIniState_glauber->getNPart() == 0) continue;

        fSBAFEvent->Clear();
        fSBAFEvent->SetEventId(i);
        fSBAFEvent->SetAProj(AProj);
        fSBAFEvent->SetZProj(ZProj);
        fSBAFEvent->SetATarg(ATarg);
        fSBAFEvent->SetZTarg(ZTarg);
        fSBAFEvent->SetB(fEvent->GetB());
        fSBAFEvent->SetBx(fEvent->GetBx());
        fSBAFEvent->SetBy(fEvent->GetBy());
        fSBAFEvent->SetNPartProj(fIniState_glauber->getNPartA());
        fSBAFEvent->SetNPartTarg(fIniState_glauber->getNPartB());
        fSBAFEvent->SetNColl(fIniState_glauber->getNColl());

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
            fSBAFFragment.SetFragmentId(j + AProj);
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

        for (int j=0;j<fNpa;j++) {
            fParticle = fEvent->GetParticle(j);
            TLorentzVector fMomentum = (fParticle->GetMomentum()).Transform(rTransform);
            TVector3 fPosition = TVector3(fParticle->X(), fParticle->Y(), fParticle->Z());

            if (fParticle->T() == 1 || fParticle->T() == -1) {
                fSBAFFragment.SetFragmentId(j);
                fSBAFFragment.SetPosition(fPosition);
                fSBAFFragment.SetMomentum(fMomentum);
                fSBAFFragment.SetEPsd(0);
                if (fParticle->T() == 1) fSBAFFragment.SetNucleusId(0);
                else fSBAFFragment.SetNucleusId(1);
                fSBAFFragment.SetIniId(1);
                fSBAFFragment.SetSpectatorId(0);
                if (fParticle->GetPdg() > 1e9) {
                    fSBAFFragment.SetAFrag(fParticle->GetPdg() / 10 % 1000);
                    fSBAFFragment.SetZFrag(fParticle->GetPdg() / 10000 % 1000);
                    fSBAFFragment.SetPdgId(fParticle->GetPdg());
                } else if (fParticle->GetPdg() == 2212) {
                    fSBAFFragment.SetAFrag(1);
                    fSBAFFragment.SetZFrag(1);
                    fSBAFFragment.SetPdgId(fParticle->GetPdg());
                } else if (fParticle->GetPdg() == 2112) {
                    fSBAFFragment.SetAFrag(0);
                    fSBAFFragment.SetZFrag(0);
                    fSBAFFragment.SetPdgId(fParticle->GetPdg());
                }
                fSBAFEvent->AddFragment(fSBAFFragment);
            }
        }

        Int_t ATotProj = 0;
        Int_t ATotTarg = 0;
        Int_t ZTotProj = 0;
        Int_t ZTotTarg = 0;
        Double_t ETotProj = 0.;
        Double_t ETotTarg = 0.;
        Int_t NFragProj = 0;
        Int_t NFragTarg = 0;
        Int_t NaProj[AProj+1];
        for (int j=0; j<AProj+1; j++) NaProj[j] = 0;
        Int_t NaTarg[ATarg+1];
        for (int j=0; j<ATarg+1; j++) NaTarg[j] = 0;

        for (int j=AProj+ATarg; j<fSBAFEvent->GetNFragments(); j++) {
            if (fSBAFEvent->GetFragment(j).GetNucleusId() == 0) {
                if (fSBAFEvent->GetFragment(j).GetPdgId() == 2112) ATotProj = ATotProj + 1;
                else ATotProj = ATotProj + fSBAFEvent->GetFragment(j).GetAFrag();
                ZTotProj = ZTotProj + fSBAFEvent->GetFragment(j).GetZFrag();
                ETotProj = ETotProj + fSBAFEvent->GetFragment(j).GetMomentum().E();
                NFragProj = NFragProj + 1;
                NaProj[fSBAFEvent->GetFragment(j).GetAFrag()] = NaProj[fSBAFEvent->GetFragment(j).GetAFrag()] + 1;
            }
            else if (fSBAFEvent->GetFragment(j).GetNucleusId() == 1) {
                if (fSBAFEvent->GetFragment(j).GetPdgId() == 2112) ATotTarg = ATotTarg+ 1;
                else ATotTarg = ATotTarg + fSBAFEvent->GetFragment(j).GetAFrag();
                ZTotTarg = ZTotTarg + fSBAFEvent->GetFragment(j).GetZFrag();
                ETotTarg = ETotTarg + fSBAFEvent->GetFragment(j).GetMomentum().E();
                NFragTarg = NFragTarg + 1;
                NaTarg[fSBAFEvent->GetFragment(j).GetAFrag()] = NaTarg[fSBAFEvent->GetFragment(j).GetAFrag()] + 1;
            }
        }

        Int_t NuProj = 0;
        for (int j=0; j<AProj+1; j++) if (NaProj[j] > 0) NuProj = NuProj + 1;
        Int_t NuTarg = 0;
        for (int j=0; j<ATarg+1; j++) if (NaTarg[j] > 0) NuTarg = NuTarg + 1;

        fSBAFEvent->SetATotProj(ATotProj);
        fSBAFEvent->SetATotTarg(ATotTarg);
        fSBAFEvent->SetZTotProj(ZTotProj);
        fSBAFEvent->SetZTotTarg(ZTotTarg);
        fSBAFEvent->SetETotProj(ETotProj);
        fSBAFEvent->SetETotTarg(ETotTarg);
        fSBAFEvent->SetEPsdProj(0.);
        fSBAFEvent->SetEPsdTarg(0.);
        fSBAFEvent->SetNFragProj(NFragProj);
        fSBAFEvent->SetNFragTarg(NFragTarg);
        for (int j=0; j<AProj+1; j++) fSBAFEvent->SetNaProj(NaProj[j], j);
        for (int j=0; j<ATarg+1; j++) fSBAFEvent->SetNaTarg(NaTarg[j], j);
        fSBAFEvent->SetNuProj(NuProj);
        fSBAFEvent->SetNuTarg(NuTarg);
//        fSBAFEvent->SetNAniVectors(NAniVectors);

        tree->Fill();
    }

    auto *fout = new TFile(output_dirname, "recreate");
    tree->Write();
    fout->Close();
}