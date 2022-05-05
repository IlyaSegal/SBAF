//
// Created by isegal on 13.01.2022.
//

#ifndef SBAF_EVENT_H
#define SBAF_EVENT_H

#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "THnSparse.h"
#include "TObject.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"

class Fragment;
class AnisotropyVector;

using namespace std;

class Event : public TObject {

private:
    Int_t fEventId{0};                           // Event number
    Int_t fAProj{-999};                          // Mass number of projectile nucleus
    Int_t fZProj{-999};                          // Charge number of projectile nucleus
    Int_t fATarg{-999};                          // Mass number of target nucleus
    Int_t fZTarg{-999};                          // Charge number of target nucleus
    Double_t fB{-999.};                          // Impact parameter value (fm)
    Double_t fBx{-999.};                         // Impact parameter value along X axis (fm)
    Double_t fBy{-999.};                         // Impact parameter value along Y axis (fm)
    Int_t fNPartProj{-999};                      // Number of participants from projectile nucleus
    Int_t fNPartTarg{-999};                      // Number of participants from target nucleus
    Int_t fNColl{-999};                          // Number of binary nucleon-nucleon collisions
    Int_t fATotProj{-999};                       // Total mass number of spectator fragments from projectile nucleus
    Int_t fATotTarg{-999};                       // Total mass number of spectator fragments from target nucleus
    Int_t fZTotProj{-999};                       // Total charge number of spectator fragments from projectile nucleus
    Int_t fZTotTarg{-999};                       // Total charge number of spectator fragments from target nucleus
    Double_t fETotProj{-999.};                   // Total energy of spectator fragments from projectile nucleus
    Double_t fETotTarg{-999.};                   // Total energy of spectator fragments from target nucleus
    Double_t fEPsdProj{-999.};                   // Total PSD energy of spectator fragments from projectile nucleus
    Double_t fEPsdTarg{-999.};                   // Total PSD energy of spectator fragments from target nucleus
    Int_t fNFragProj{-999};                      // Total number of spectator fragments from projectile nucleus
    Int_t fNFragTarg{-999};                      // Total number of spectator fragments from target nucleus
    std::vector<Int_t> fNaProj;                  // Number of spectator fragments with certain mass number from projectile nucleus
    std::vector<Int_t> fNaTarg;                  // Number of spectator fragments with certain mass number from target nucleus
    Int_t fNuProj{-999};                         // Number of spectator fragments with unique mass number from projectile nucleus
    Int_t fNuTarg{-999};                         // Number of spectator fragments with unique mass number from target nucleus
    Int_t fNFragments{0};                        // Number of entries in fragments array
    vector<Fragment> fFragments;                 // Array of all fragments (including initial nucleons)
//    Int_t fNAniVectors{0};                       // Number of anisotropy vectors
//    vector<AnisotropyVector> fAnisotropyVectors; // Array of anisotropy vectors (eccentricities and flow coefficients)

public:
    Event() = default;
    Event(Int_t EventId, Int_t AProj, Int_t ZProj, Int_t ATarg, Int_t ZTarg);
    virtual ~Event();
    void Init(Int_t EventId, Int_t AProj, Int_t ZProj, Int_t ATarg, Int_t ZTarg);
    Int_t GetEventId() const {return fEventId;}
    Int_t GetAProj() const {return fAProj;}
    Int_t GetZProj() const {return fZProj;}
    Int_t GetATarg() const {return fATarg;}
    Int_t GetZTarg() const {return fZTarg;}
    Double_t GetB() const {return fB;}
    Double_t GetBx() const {return fBx;}
    Double_t GetBy() const {return fBy;}
    Int_t GetNPartProj() const {return fNPartProj;}
    Int_t GetNPartTarg() const {return fNPartTarg;}
    Int_t GetNColl() const {return fNColl;}
    Int_t GetATotProj() const {return fATotProj;}
    Int_t GetATotTarg() const {return fATotTarg;}
    Int_t GetZTotProj() const {return fZTotProj;}
    Int_t GetZTotTarg() const {return fZTotTarg;}
    Double_t GetETotProj() const {return fETotProj;}
    Double_t GetETotTarg() const {return fETotTarg;}
    Double_t GetEPsdProj() const {return fEPsdProj;}
    Double_t GetEPsdTarg() const {return fEPsdTarg;}
    Int_t GetNFragProj() const {return fNFragProj;}
    Int_t GetNFragTarg() const {return fNFragTarg;}
    Int_t GetNaProj(Int_t fA = 0) const {return fNaProj.at(fA);}
    Int_t GetNaTarg(Int_t fA = 0) const {return fNaTarg.at(fA);}
    Int_t GetNuProj() const {return fNuProj;}
    Int_t GetNuTarg() const {return fNuTarg;}
    Int_t GetNFragments() const {return fNFragments;}
    vector<Fragment> GetListOfFragments() const {return fFragments;}
    Fragment GetFragment(Int_t id) const;
//    Int_t GetNAniVectors() const {return fNAniVectors;}
//    vector<AnisotropyVector> GetListOfAnisotropyVectors() const {return fAnisotropyVectors;}
//    AnisotropyVector GetAnisotropyVector(Int_t id) const;
    void SetEventId(Int_t EventId) {fEventId = EventId;}
    void SetAProj(Int_t AProj) {
        fAProj = AProj;
        fNaProj.clear();
        for (int i = 0; i < AProj+1; i++) fNaProj.push_back(0);
    }
    void SetZProj(Int_t ZProj) {fZProj = ZProj;}
    void SetATarg(Int_t ATarg) {
        fATarg = ATarg;
        fNaTarg.clear();
        for (int i = 0; i < ATarg+1; i++) fNaTarg.push_back(0);
    }
    void SetZTarg(Int_t ZTarg) {fZTarg = ZTarg;}
    void SetB(Double_t B) {fB = B;}
    void SetBx(Double_t Bx) {fBx = Bx;}
    void SetBy(Double_t By) {fBy = By;}
    void SetNPartProj(Int_t NPartProj) {fNPartProj = NPartProj;}
    void SetNPartTarg(Int_t NPartTarg) {fNPartTarg = NPartTarg;}
    void SetNColl(Int_t NColl) {fNColl = NColl;}
    void SetATotProj(Int_t ATotProj) {fATotProj = ATotProj;}
    void SetATotTarg(Int_t ATotTarg) {fATotTarg = ATotTarg;}
    void SetZTotProj(Int_t ZTotProj) {fZTotProj = ZTotProj;}
    void SetZTotTarg(Int_t ZTotTarg) {fZTotTarg = ZTotTarg;}
    void SetETotProj(Double_t ETotProj) {fETotProj = ETotProj;}
    void SetETotTarg(Double_t ETotTarg) {fETotTarg = ETotTarg;}
    void SetEPsdProj(Double_t EPsdProj) {fEPsdProj = EPsdProj;}
    void SetEPsdTarg(Double_t EPsdTarg) {fEPsdTarg = EPsdTarg;}
    void SetNFragProj(Int_t NFragProj) {fNFragProj = NFragProj;}
    void SetNFragTarg(Int_t NFragTarg) {fNFragTarg = NFragTarg;}
    void SetNaProj(Int_t NaProj, Int_t fA) {fNaProj.at(fA) = NaProj;}
    void SetNaTarg(Int_t NaTarg, Int_t fA) {fNaTarg.at(fA) = NaTarg;}
    void SetNuProj(Int_t NuProj) {fNuProj = NuProj;}
    void SetNuTarg(Int_t NuTarg) {fNuTarg = NuTarg;}
    void SetNFragments(Int_t NFragments) {fNFragments = NFragments;}
    void AddFragment(const Fragment& newFragment);
//    void SetNAniVectors(Int_t NAniVectors) {fNAniVectors = NAniVectors;}
//    void AddAnisotropyVector(const AnisotropyVector& newAnisotropyVector);
    void Clear();
    Bool_t SampleEvent(Double_t a,
                     Double_t b,
                     Double_t c,
                     THnSparseD* ATotSampleHisto,
                     Bool_t ATotDependsOnB = false,
                     Bool_t ATotDependsOnNSpec = false,
                     Bool_t ProcedureMode = false,
                     THnSparseD* FragSampleHisto = nullptr,
                     THnSparseD* ChargeSampleHisto = nullptr,
                     Bool_t FragDependsOnB = false,
                     Bool_t FragDependsOnNSpec = false,
                     Bool_t FragDependsOnATot = false,
                     THnSparseD* EYSampleHisto = nullptr,
                     Bool_t EYDependsOnB = false,
                     Bool_t EYDependsOnNSpec = false,
                     Bool_t EYDependsOnATot = false,
                     Bool_t EYDependsAFrag = false);
    Bool_t SampleFragments(TH2D* FragSampleHisto, TH2D* ChargeSampleHisto);
    Bool_t SampleEY(Double_t a, Double_t b, Double_t c, THnSparse* EYSampleHisto, Bool_t EYDependsAFrag);
    void SampleLight(Double_t a, Double_t b);

ClassDef(Event, 1);
};

#endif //SBAF_EVENT_H