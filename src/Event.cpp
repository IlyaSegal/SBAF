//
// Created by isegal on 13.01.2022.
//

#include <TRandom.h>
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "THnSparse.h"
#include "Event.h"
#include "Fragment.h"
#include "AnisotropyVector.h"
#include "TClonesArray.h"

#include <iostream>

using namespace std;

//--------------------------------------------------------------------
// Class Event for description of event parameters
//--------------------------------------------------------------------

Event::Event(Int_t EventId, Int_t AProj, Int_t ZProj, Int_t ATarg, Int_t ZTarg) {
    // Constructor
    Init(EventId, AProj, ZProj, ATarg, ZTarg);
}

Event::~Event() {
    // Destructor
    Clear();
    fFragments.clear();
}

void Event::Init(Int_t EventId, Int_t AProj, Int_t ZProj, Int_t ATarg, Int_t ZTarg) {
    // Initialization of event parameters
    fEventId = EventId;
    fAProj = AProj;
    fZProj = ZProj;
    fATarg = ATarg;
    fZTarg = ZTarg;
    fB = -999.;
    fBx = -999.;
    fBy = -999.;
    fNPartProj = -999;
    fNPartTarg = -999;
    fNColl = -999;
    fATotProj = -999;
    fATotTarg = -999;
    fZTotProj = -999;
    fZTotTarg = -999;
    fETotProj = -999.;
    fETotTarg = -999.;
    fEPsdProj = -999.;
    fEPsdTarg = -999.;
    fNFragProj = 0;
    fNFragTarg = 0;
    fNaProj.clear();
    fNaTarg.clear();
    for (int i = 0; i < AProj+1; i++) fNaProj.push_back(0);
    for (int i = 0; i < ATarg+1; i++) fNaTarg.push_back(0);
    fNuProj = -999;
    fNuTarg = -999;
    fNFragments = 0;
//    fNAniVectors = 0;
}

Fragment Event::GetFragment(Int_t id) const {
    // Return pointer to the fragment with id
    return fFragments.at(id);
}

//AnisotropyVector Event::GetAnisotropyVector(Int_t id) const {
    // Return pointer to the anisotropy vector with id
//        return fAnisotropyVectors.at(id);
//}

void Event::AddFragment(const Fragment &newFragment) {
    // Add new fragment to array of fragments
    fFragments.push_back(newFragment);
    fNFragments++;
}

//void Event::AddAnisotropyVector(const AnisotropyVector &newAnisotropyVector) {
    // Add new anisotropy vector to array of anisotropy vectors
//   fAnisotropyVectors.push_back(newAnisotropyVector);
//    fNAniVectors++;
//}

void Event::Clear() {
    // Clear information about event
    fFragments.clear();
    fNFragments=0;
//    fAnisotropyVectors.clear();
//    fNAniVectors=0;
    fNaProj.clear();
    fNaTarg.clear();
    Init(fEventId+1, fAProj, fZProj, fATarg, fZProj);
}

Bool_t Event::SampleEvent(Double_t a,
                          Double_t b,
                          Double_t c,
                          THnSparseD* ATotSampleHisto,
                          Bool_t ATotDependsOnB,
                          Bool_t ATotDependsOnNSpec,
                          Bool_t ProcedureMode,
                          THnSparseD* FragSampleHisto,
                          THnSparseD* ChargeSampleHisto,
                          Bool_t FragDependsOnB,
                          Bool_t FragDependsOnNSpec,
                          Bool_t FragDependsOnATot,
                          THnSparseD* EYSampleHisto,
                          Bool_t EYDependsOnB,
                          Bool_t EYDependsOnNSpec,
                          Bool_t EYDependsOnATot,
                          Bool_t EYDependsAFrag) {
    // Sample event parameters during centrality determination procedure
    // ProcedureMode is false for light mode, true - for full mode
    // Step depends on any parameter if corresponding flag is true
    Int_t iter=0;
    if (ATotDependsOnB) ATotSampleHisto->GetAxis(0)->SetRange(fB*10+1, fB*10+1);
    else ATotSampleHisto->GetAxis(0)->SetRange(0, 210);
    if (ATotDependsOnNSpec) ATotSampleHisto->GetAxis(2)->SetRange((fAProj-fNPartProj)+1, (fAProj-fNPartProj)+1);
    else ATotSampleHisto->GetAxis(2)->SetRange(0, 210);
    auto hAtot = (TH1D*)ATotSampleHisto->Projection(1);
    hAtot->SetName("Atot_temp");
    if (hAtot->Integral()==0)  return false;
    fATotProj = (int) hAtot->GetRandom();
    if (FragDependsOnB) FragSampleHisto->GetAxis(0)->SetRange(fB*10+1, fB*10+1);
    else FragSampleHisto->GetAxis(0)->SetRange(0, 210);
    if (FragDependsOnATot) FragSampleHisto->GetAxis(1)->SetRange(fATotProj+1, fATotProj+1);
    else FragSampleHisto->GetAxis(1)->SetRange(0, 210);
    if (FragDependsOnATot) FragSampleHisto->GetAxis(4)->SetRange((fAProj-fNPartProj)+1, (fAProj-fNPartProj)+1);
    else FragSampleHisto->GetAxis(4)->SetRange(0, 210);
    auto hFragHisto = (TH2D*)FragSampleHisto->Projection(3, 2);
    hFragHisto->SetName("Afrag_vs_NA_temp");
    if (fATotProj == 0) {
        fZTotProj = 0;
        fETotProj = 0.;
        fEPsdProj = 0.;
        fNFragProj = 0;
        for (Int_t i = 0; i <= fAProj; i++) { fNaProj.push_back(0); }
        fNuProj = 0;
        return true;
    }
    while(hFragHisto->Integral()==0)
    {
        fATotProj = (int) hAtot->GetRandom();
        if (FragDependsOnATot) FragSampleHisto->GetAxis(1)->SetRange(fATotProj+1, fATotProj+1);
        hFragHisto = (TH2D*)FragSampleHisto->Projection(3, 2);
        hFragHisto->SetName("Afrag_vs_NA_temp");
        iter++;
        if (iter == 1000) return false;
    }
    if (FragDependsOnB) ChargeSampleHisto->GetAxis(0)->SetRange(fB*10+1, fB*10+1);
    else ChargeSampleHisto->GetAxis(0)->SetRange(0, 210);
    if (FragDependsOnATot) ChargeSampleHisto->GetAxis(1)->SetRange(fATotProj+1, fATotProj+1);
    else ChargeSampleHisto->GetAxis(1)->SetRange(0, 210);
    if (FragDependsOnATot) ChargeSampleHisto->GetAxis(4)->SetRange((fAProj-fNPartProj)+1, (fAProj-fNPartProj)+1);
    else ChargeSampleHisto->GetAxis(4)->SetRange(0, 210);
    auto hChargeHisto = (TH2D*)ChargeSampleHisto->Projection(3, 2);
    hChargeHisto->SetName("Afrag_vs_NA_temp");
    if (hChargeHisto->Integral()==0)  return false;
    if (ProcedureMode) {
        if (!SampleFragments(hFragHisto, hChargeHisto)) return false;
    }
    if (EYDependsOnB) EYSampleHisto->GetAxis(0)->SetRange(fB*10+1, fB*10+1);
    else EYSampleHisto->GetAxis(0)->SetRange(0, 210);
    if (EYDependsOnATot) EYSampleHisto->GetAxis(1)->SetRange(fATotProj+1, fATotProj+1);
    else EYSampleHisto->GetAxis(1)->SetRange(0, 210);
    Int_t nProjection[3]={2,3,4};
    auto* hEYHisto = (THnSparse*)EYSampleHisto->Projection(3, nProjection);
    hEYHisto->SetName("Afrag_vs_Rapidity_vs_Energy_temp");
    if (ProcedureMode) {
        if (!SampleEY(a, b, c, hEYHisto, EYDependsAFrag)) return false;
    }
    else SampleLight(a, b);
    return true;
}

Bool_t Event::SampleFragments(TH2D* FragSampleHisto, TH2D* ChargeSampleHisto) {
    // Sample fragments and its masses and charges during centrality determination procedure
    Int_t counter = fATotProj;
    fZTotProj = 0;
    fNFragProj = 0;
    fNuProj = 0;
    fNFragments = fAProj + fATarg;
    fNaProj.clear();
    for (Int_t i = 0; i <= fAProj; i++) { fNaProj.push_back(0); }
    Int_t j = 0, NA = 0;
    Double_t double_j = 0, double_NA = 0;
    Int_t kk = 0;
    Int_t stopper = 0;

    while (counter != 0) {
        if (counter < 0 || kk == 20) {
            for (int i = 0; i <= fAProj; i++) fNaProj.at(i) = 0;
            counter = fATotProj;
            kk = 0;
            stopper++;
        }
        if (stopper == 1000) return false;
        FragSampleHisto->GetRandom2(double_j, double_NA);
        j = (int) double_j;
        NA = (int) double_NA;
        kk++;
        if (fNaProj.at(j) > 0) continue;
        fNaProj.at(j) = NA;
        if (j==0) counter = counter - fNaProj.at(j);
        else counter = counter - j * fNaProj.at(j);
    }

    for (int i = 0; i <= fAProj; i++) {
        auto hCharge = (TH1D *) ChargeSampleHisto->ProjectionY("ChargeHist", i+1, i+1);
        if (fNaProj.at(i) > 0) fNuProj++;
        for (int k = 0; k < fNaProj.at(i); k++) {
            Fragment fFragment;
            TVector3 fPosition(0., 0., 0.);
            fFragment.SetFragmentId(fNFragments);
            fFragment.SetPosition(fPosition);
            fFragment.SetAFrag(i);
            Int_t fCharge = (int) hCharge->GetRandom();
            fFragment.SetZFrag(fCharge);
            if (i == 0) fFragment.SetPdgId(2112);
            else if (i == 1) fFragment.SetPdgId(2212);
            else fFragment.SetPdgId(1000000000 + fCharge * 10000 + i * 10);
            fFragment.SetNucleusId(0);
            fFragment.SetIniId(1);
            fFragment.SetSpectatorId(0);
            fZTotProj = fZTotProj + fCharge;
            fNFragProj++;
            fFragments.push_back(fFragment);
            fNFragments++;
        }
    }
    return true;
}

Bool_t Event::SampleEY(Double_t a, Double_t b, Double_t c,THnSparse* EYSampleHisto, Bool_t EYDependsAFrag) {
    // Sample fragments' kinematics and PSD response during centrality determination procedure
    Double_t Phi=0, Pt=0, Px=0, Py=0, Pz=0;
    TLorentzVector fMomentum(0.,0.,0.,0.);
    fEPsdProj = 0;
    fETotProj = 0;
    Double_t EFrag, Rapidity, EPsdFrag, EPsdSigma;
    Int_t AFrag;
    for (int i = fAProj + fATarg; i < fNFragments; i++)
    {
        AFrag = fFragments.at(i).GetAFrag();
        if (EYDependsAFrag) EYSampleHisto->GetAxis(0)->SetRange(AFrag+1, AFrag+1);
        else EYSampleHisto->GetAxis(0)->SetRange(0, 210);
        auto hRapidity_vs_Energy_temp = (TH2D*)EYSampleHisto->Projection(2, 1);
        if (hRapidity_vs_Energy_temp->Integral()==0) return false;
        hRapidity_vs_Energy_temp->SetName("Rapidity_vs_Energy_temp");
        hRapidity_vs_Energy_temp->GetRandom2(EFrag,Rapidity);
        Phi = 2*TMath::Pi()*gRandom->Rndm();
        Pz = EFrag*(TMath::Exp(2*Rapidity)-1)/(TMath::Exp(2*Rapidity)+1);
        Pt = TMath::Sqrt(EFrag*EFrag-(AFrag+1)*(AFrag+1)*0.931*0.931-Pz*Pz);
        Px = Pt*TMath::Cos(Phi);
        Py = Pt*TMath::Sin(Phi);
        fMomentum.SetXYZT(Px,Py,Pz,EFrag);
        fETotProj = fETotProj + EFrag;
        EPsdSigma = EFrag * (TMath::Sqrt(a*a/EFrag+c*c/TMath::Sqrt(EFrag))+b);
        EPsdFrag = gRandom->Gaus(EFrag, EPsdSigma);
        fEPsdProj = fEPsdProj + EPsdFrag;
        fFragments.at(i).SetMomentum(fMomentum);
        fFragments.at(i).SetEPsd(EPsdFrag);
    }
    return true;
}

void Event::SampleLight(Double_t a, Double_t b) {
    // Sample fragments and PSD energy in light mode
    fZTotProj = 0;
    fNFragProj = fATotProj;
    fNuProj = 1;
    fEPsdProj = 0;
    fETotProj = 0;
    fNFragments = fAProj + fATarg;
    Double_t EPsdFrag;
    for (int i = 0; i <= fATotProj; i++) {
        Fragment fFragment;
        TVector3 fPosition(0., 0., 0.);
        fFragment.SetFragmentId(fNFragments);
        fFragment.SetPosition(fPosition);
        fFragment.SetAFrag(1);
        fFragment.SetZFrag(1);
        fFragment.SetPdgId(2212);
        fFragment.SetNucleusId(0);
        fFragment.SetIniId(1);
        fFragment.SetSpectatorId(0);
        EPsdFrag = gRandom->Gaus(a, b);
        fETotProj = fETotProj + EPsdFrag;
        fEPsdProj = fEPsdProj + EPsdFrag;
        fFragment.SetEPsd(EPsdFrag);
        TLorentzVector fMomentum(0.,0.,0.,EPsdFrag);
        fFragment.SetMomentum(fMomentum);
        fFragments.push_back(fFragment);
        fNFragments++;
    }
}

ClassImp(Event);