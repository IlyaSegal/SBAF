#include "TFile.h"
#include "TMath.h"
#include "TString.h"
#include "TChain.h"
#include "TLorentzRotation.h"

#include "src/Event.h"
#include "src/Fragment.h"
#include "src/QA.h"

#include <iostream>

using namespace std;

void FillQA(const TString &input_filename, const TString &output_filename, Int_t AProj, Int_t ZProj, Int_t ATarg, Int_t ZTarg, Double_t PProjBeam, Double_t PTargBeam, TString collision_type, Int_t WhichHistos = 0)
{
    auto* fChain=new TChain("SBAFTree");
    fChain->Add(input_filename);
    cout<<"Numer of entries equal "<<fChain->GetEntries()<<endl;
    auto* fSBAFEvent = new Event;
    fChain->SetBranchAddress("event", &fSBAFEvent);

    QA fSBAFQA(collision_type, AProj, ZProj, ATarg, ZTarg, PProjBeam, PTargBeam);

    if (WhichHistos < 2 ) {
        fSBAFQA.AddOneDHisto(kB);
        fSBAFQA.AddOneDHisto(kNColl);
        fSBAFQA.AddOneDHisto(kNPartProj);
        fSBAFQA.AddOneDHisto(kNPartTarg);
        fSBAFQA.AddOneDHisto(kATotProj);
        fSBAFQA.AddOneDHisto(kATotTarg);
        fSBAFQA.AddOneDHisto(kNFragProj);
        fSBAFQA.AddOneDHisto(kNFragTarg);
        fSBAFQA.AddOneDHisto(kETotProj);
        fSBAFQA.AddOneDHisto(kETotTarg);
        fSBAFQA.AddOneDHisto(kXProj);
        fSBAFQA.AddOneDHisto(kYProj);
        fSBAFQA.AddOneDHisto(kZProj);
        fSBAFQA.AddOneDHisto(kRhoProj);
        fSBAFQA.AddOneDHisto(kPhiProj);
        fSBAFQA.AddOneDHisto(kPosThetaProj);
        fSBAFQA.AddOneDHisto(kXTarg);
        fSBAFQA.AddOneDHisto(kYTarg);
        fSBAFQA.AddOneDHisto(kZTarg);
        fSBAFQA.AddOneDHisto(kRhoTarg);
        fSBAFQA.AddOneDHisto(kPhiTarg);
        fSBAFQA.AddOneDHisto(kPosThetaTarg);

        fSBAFQA.AddTwoDHisto(kNPart, kB);
        fSBAFQA.AddTwoDHisto(kNColl, kB);
        fSBAFQA.AddTwoDHisto(kNPart, kNColl);

        fSBAFQA.AddTwoDHisto(kATotProj, kNSpecProj);
        fSBAFQA.AddTwoDHisto(kATotTarg, kNSpecTarg);
        fSBAFQA.AddTwoDHisto(kATotProj, kB);
        fSBAFQA.AddTwoDHisto(kATotTarg, kB);
        fSBAFQA.AddTwoDHisto(kNFragProj, kB);
        fSBAFQA.AddTwoDHisto(kNFragTarg, kB);
        fSBAFQA.AddTwoDHisto(kETotProj, kB);
        fSBAFQA.AddTwoDHisto(kETotTarg, kB);
        fSBAFQA.AddTwoDHisto(kETotProj, kNColl);
        fSBAFQA.AddTwoDHisto(kETotTarg, kNColl);
        fSBAFQA.AddTwoDHisto(kETotProj, kATotProj);
        fSBAFQA.AddTwoDHisto(kETotTarg, kATotTarg);

        fSBAFQA.AddTwoDHisto(kX, kY);
        fSBAFQA.AddTwoDHisto(kXProj, kYProj);
        fSBAFQA.AddTwoDHisto(kXProj, kYProj);

        if (WhichHistos == 0) {
            Int_t THnSparse1[3] = {kB, kATotProj, kNSpecProj};
            Int_t THnSparse2[5] = {kB, kATotProj, kAFragProj, kNaProj, kNSpecProj};
            Int_t THnSparse3[5] = {kB, kATotProj, kAFragProj, kZFragProj, kNSpecProj};
            Int_t THnSparse4[5] = {kB, kATotProj, kAFragProj, kEProj, kRapidityProj};

            fSBAFQA.AddNDHisto(3, THnSparse1);
            fSBAFQA.AddNDHisto(5, THnSparse2);
            fSBAFQA.AddNDHisto(5, THnSparse3);
            fSBAFQA.AddNDHisto(5, THnSparse4);
        }
    }

    Long64_t lNEvents = fChain->GetEntries();

    for (long i = 0; i < lNEvents; i++)
    {
        if (i%1000==0) cout << "\r" << 100.*i/lNEvents << "% done" << flush;
        fChain->GetEntry(i);
        fSBAFQA.Fill(fSBAFEvent);
    }

    auto *fout = new TFile(output_filename, "recreate");
    fSBAFQA.Write();
    fout->Close();
}