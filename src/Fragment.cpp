//
// Created by isegal on 13.01.2022.
//

#include "Fragment.h"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------
// Class Fragment for description of fragment parameters
//--------------------------------------------------------------------

Fragment::Fragment()
    : TObject(),
      fFragmentId(-999),
      fPosition(-999, -999, -999),
      fMomentum(-999, -999, -999, -999),
      fEPsd(-999.),
      fAFrag(-999),
      fZFrag(-999),
      fPdgId(-999),
      fNucleusId(-999),
      fIniId(-999),
      fSpectatorId(-999)
{
    // Default constructor
}

Fragment::Fragment(const Fragment& newFragment)
    : TObject(newFragment),
      fFragmentId(newFragment.fFragmentId),
      fPosition(newFragment.fPosition),
      fMomentum(newFragment.fMomentum),
      fEPsd(newFragment.fEPsd),
      fAFrag(newFragment.fAFrag),
      fZFrag(newFragment.fZFrag),
      fPdgId(newFragment.fPdgId),
      fNucleusId(newFragment.fNucleusId),
      fIniId(newFragment.fIniId),
      fSpectatorId(newFragment.fSpectatorId)
{
    // Constructor
}

Fragment::Fragment(Int_t FragmentId,
                   Double_t x, Double_t y, Double_t z,
                   Double_t Px, Double_t Py, Double_t Pz, Double_t E,
                   Double_t EPsd,
                   Int_t AFrag ,
                   Int_t ZFrag,
                   Int_t Na,
                   Int_t PdgId,
                   Int_t NucleusId,
                   Int_t IniId,
                   Int_t SpectatorId)
        : TObject(),
          fFragmentId(FragmentId),
          fPosition(x, y, z),
          fMomentum(Px, Py, Pz, E),
          fEPsd(EPsd),
          fAFrag(AFrag),
          fZFrag(ZFrag),
          fPdgId(PdgId),
          fNucleusId(NucleusId),
          fIniId(IniId),
          fSpectatorId(SpectatorId)
{
    // Class parameters initialization
}

Fragment& Fragment::operator = (const Fragment& newFragment) {
    // Assignment operator
    TObject::operator=(newFragment);
    fFragmentId = newFragment.fFragmentId;
    fPosition = newFragment.fPosition;
    fMomentum = newFragment.fMomentum;
    fEPsd = newFragment.fEPsd;
    fAFrag = newFragment.fAFrag;
    fZFrag = newFragment.fZFrag;
    fPdgId = newFragment.fPdgId;
    fNucleusId = newFragment.fNucleusId;
    fIniId = newFragment.fIniId;
    fSpectatorId = newFragment.fSpectatorId;
}

Bool_t Fragment::operator == (const Fragment& newFragment) const {
    // If equal operator
    return (
        fFragmentId == newFragment.fFragmentId &&
        fAFrag == newFragment.fAFrag &&
        fZFrag == newFragment.fZFrag &&
        fPdgId == newFragment.fPdgId &&
        fNucleusId == newFragment.fNucleusId &&
        fIniId == newFragment.fIniId &&
        fSpectatorId == newFragment.fSpectatorId &&
        ((TMath::Abs((fMomentum.Px()-newFragment.fMomentum.Px())/fMomentum.Px())<0.0001) ||
        (TMath::Abs(fMomentum.Px())<1e-16&&TMath::Abs(newFragment.fMomentum.Px())<1e-16)) &&
        ((TMath::Abs((fMomentum.Py()-newFragment.fMomentum.Py())/fMomentum.Py())<0.0001) ||
        (TMath::Abs(fMomentum.Py())<1e-16&&TMath::Abs(newFragment.fMomentum.Py())<1e-16)) &&
        ((TMath::Abs((fMomentum.Pz()-newFragment.fMomentum.Pz())/fMomentum.Pz())<0.0001) ||
        (TMath::Abs(fMomentum.Pz())<1e-16&&TMath::Abs(newFragment.fMomentum.Pz())<1e-16)) &&
        ((TMath::Abs((fMomentum.E()-newFragment.fMomentum.E())/fMomentum.E())<0.0001) ||
        (TMath::Abs(fMomentum.E())<1e-16&&TMath::Abs(newFragment.fMomentum.E())<1e-16)) &&
        ((TMath::Abs((fPosition.X()-newFragment.fPosition.X())/fPosition.X())<0.0001) ||
        (TMath::Abs(fPosition.X())<1e-16&&TMath::Abs(newFragment.fPosition.X())<1e-16)) &&
        ((TMath::Abs((fPosition.Y()-newFragment.fPosition.Y())/fPosition.Y())<0.0001) ||
        (TMath::Abs(fPosition.Y())<1e-16&&TMath::Abs(newFragment.fPosition.Y())<1e-16)) &&
        ((TMath::Abs((fPosition.Z()-newFragment.fPosition.Z())/fPosition.Z())<0.0001) ||
        (TMath::Abs(fPosition.Z())<1e-16&&TMath::Abs(newFragment.fPosition.Z())<1e-16))
    );
}

Bool_t Fragment::IsProjectile() const {
    // Checking if fragment (or initial nucleon) belongs to projectile nucleus (return 1 for projectile, 0 for target or error)
    if (fNucleusId == 0) return kTRUE;
    else if (fNucleusId == 1) return kFALSE;
    else {
        cout << "WARNING: Invalid fNucleusId value" << endl;
        return kFALSE;
    }
}

Bool_t Fragment::IsTarget() const {
    // Checking if fragment (or initial nucleon) belongs to target nucleus (return 1 for target, 0 for projectile or error)
    if (fNucleusId == 1) return kTRUE;
    else if (fNucleusId == 0) return kFALSE;
    else {
        cout << "WARNING: Invalid fNucleusId value" << endl;
        return kFALSE;
    }
}

Bool_t Fragment::IsInitialNucleon() const {
    // Checking if it is an initial nucleon (return 1 for initial nucleon, 0 for fragment (or produced particle) or error)
    if (fIniId == 0) return kTRUE;
    else if (fIniId == 1) return kFALSE;
    else {
        cout << "WARNING: Invalid fIniId value" << endl;
        return kFALSE;
    }
}

Bool_t Fragment::IsFragment() const {
    // Checking if it is a fragment (or produced particle) (return 1 for fragment (or produced particle), 0 for initial nucleon or error)
    if (fIniId == 1) return kTRUE;
    else if (fIniId == 0) return kFALSE;
    else {
        cout << "WARNING: Invalid fIniId value" << endl;
        return kFALSE;
    }
}
Bool_t Fragment::IsSpectator() const {
    // Checking if fragment (or initial nucleon) belongs to spectators region
    // (return 1 for spectator fragments (or initial spectators), 0 for produced particles (or participants) or error)
    if (fSpectatorId == 0) return kTRUE;
    else if (fSpectatorId == 1) return kFALSE;
    else {
        cout << "WARNING: Invalid fSpectatorId value" << endl;
        return kFALSE;
    }
}

Bool_t Fragment::IsParticipant() const {
    // Checking if fragment (or initial nucleon) belongs to participants region
    // (return 1 for produced particles (or participants), 0 for spectator fragments (or initial spectators) or error)
    if (fSpectatorId == 1) return kTRUE;
    else if (fSpectatorId == 0) return kFALSE;
    else {
        cout << "WARNING: Invalid fSpectatorId value" << endl;
        return kFALSE;
    }
}

ClassImp(Fragment);