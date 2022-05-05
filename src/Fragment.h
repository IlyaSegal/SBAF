//
// Created by isegal on 13.01.2022.
//

#ifndef SBAF_FRAGMENT_H
#define SBAF_FRAGMENT_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"


class Fragment : public TObject {

private:
    Int_t fFragmentId;        // Fragment Id
    TVector3 fPosition;       // Position of the fragment
    TLorentzVector fMomentum; // 4-dimensional momentum of the fragment
    Double_t fEPsd;           // Energy of the fragment registered with PSD
    Int_t fAFrag;             // Mass number of the fragment (0 for neutrons)
    Int_t fZFrag;             // Charge number of the fragment
    Int_t fPdgId;             // PDG code of the fragment
    Int_t fNucleusId;         // 0 - fragment from projectile, 1 - fragment from target
    Int_t fIniId;             // 0 - initial nucleon, 1 - produced fragment
    Int_t fSpectatorId;       // 0 - spectator, 1 - participant

public:
    Fragment();
    Fragment(const Fragment& newFragment);
    explicit Fragment(Int_t FragmentId,
             Double_t x, Double_t y, Double_t z,
             Double_t Px, Double_t Py, Double_t Pz, Double_t E,
             Double_t EPsd,
             Int_t AFrag,
             Int_t ZFrag,
             Int_t Na,
             Int_t PdgId,
             Int_t NucleusId,
             Int_t IniId,
             Int_t SpectatorId);
    virtual ~Fragment() = default;
    Fragment& operator = (const Fragment& newFragment);
    Bool_t operator == (const Fragment& newFragment) const;
    Int_t GetFragmentId() const {return fFragmentId;}
    TVector3 GetPosition() const {return fPosition;}
    TLorentzVector GetMomentum() const {return fMomentum;}
    Double_t GetEPsd() const {return fEPsd;}
    Int_t GetAFrag() const {return fAFrag;}
    Int_t GetZFrag() const {return fZFrag;}
    Int_t GetPdgId() const {return fPdgId;}
    Int_t GetNucleusId() const {return fNucleusId;}
    Int_t GetIniId() const {return fIniId;}
    Int_t GetSpectatorId() const {return fSpectatorId;}
    Bool_t IsProjectile() const;
    Bool_t IsTarget() const;
    Bool_t IsInitialNucleon() const;
    Bool_t IsFragment() const;
    Bool_t IsSpectator() const;
    Bool_t IsParticipant() const;
    void SetFragmentId(Int_t FragmentId) {fFragmentId = FragmentId;}
    void SetPosition(const TVector3 &Position) {fPosition = Position;}
    void SetMomentum(const TLorentzVector &Momentum) {fMomentum = Momentum;}
    void SetEPsd(Double_t EPsd) {fEPsd = EPsd;}
    void SetAFrag(Int_t AFrag) {fAFrag = AFrag;}
    void SetZFrag(Int_t ZFrag) {fZFrag = ZFrag;}
    void SetPdgId(Int_t PdgId) {fPdgId = PdgId;}
    void SetNucleusId(Int_t NucleusId) {fNucleusId = NucleusId;}
    void SetIniId(Int_t IniId) {fIniId = IniId;}
    void SetSpectatorId(Int_t SpectatorId) {fSpectatorId = SpectatorId;}

ClassDef(Fragment, 1);
};

#endif //SBAF_FRAGMENT_H