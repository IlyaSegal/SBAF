//
// Created by isegal on 14.01.2022.
//

#include <vector>
#include <map>
#include <iostream>
#include "Event.h"
#include "Fragment.h"
#include "QA.h"
#include "AnisotropyVector.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "THnSparse.h"
using namespace std;

//--------------------------------------------------------------------
// Class QA for working with QA histograms
//--------------------------------------------------------------------

QA::QA()
        : TObject(),
          fAProj(-99),
          fZProj(-99),
          fATarg(-99),
          fZTarg(-99),
          fPBeamProj(-99.),
          fPBeamTarg(-99.),
          fCollisionType("fixed-target")
{
    // Default constructor
}

QA::QA(TString CollisionType, Int_t AProj, Int_t ZProj, Int_t ATarg, Int_t ZTarg, Double_t PBeamProj, Double_t PBeamTarg)
        : TObject(),
          fAProj(AProj),
          fZProj(ZProj),
          fATarg(ATarg),
          fZTarg(ZTarg),
          fPBeamProj(PBeamProj),
          fPBeamTarg(PBeamTarg),
          fCollisionType(CollisionType)
{
    // Class parameters initialization
}

TH1D* QA::GetOneDHisto(const TString &name) {
    // Return 1D histogram with certain name
    for (TH1D* histo : hOneDHistos) if (histo->GetName() == name) return histo;
    cout << "WARNING: There no histogram " << name << endl;
    return nullptr;
}

TH2D* QA::GetTwoDHisto(const TString &name) {
    // Return 2D histogram with certain name
    for (TH2D* histo : hTwoDHistos) if (histo->GetName() == name) return histo;
    cout << "WARNING: There no histogram " << name << endl;
    return nullptr;
}

TH3D* QA::GetThreeDHisto(const TString &name) {
    // Return 3D histogram with certain name
    for (TH3D* histo : hThreeDHistos) if (histo->GetName() == name) return histo;
    cout << "WARNING: There no histogram " << name << endl;
    return nullptr;
}

THnSparseD* QA::GetNDHisto(const TString &name) {
    // Return ND histogram with certain name
    for (THnSparseD* histo : hNDHistos) if (histo->GetName() == name) return histo;
    cout << "WARNING: There no histogram " << name << endl;
    return nullptr;
}

void QA::DeleteOneDHisto(const TString &name) {
    // Delete 1D histogram with certain name
    for (Int_t i = 0; i < hOneDHistos.size(); i++) if (hOneDHistos.at(i)->GetName() == name) hOneDHistos.erase(hOneDHistos.begin() + i);
}

void QA::DeleteTwoDHisto(const TString &name) {
    // Delete 2D histogram with certain name
    for (Int_t i = 0; i < hTwoDHistos.size(); i++) if (hTwoDHistos.at(i)->GetName() == name) hTwoDHistos.erase(hTwoDHistos.begin() + i);
}

void QA::DeleteThreeDHisto(const TString &name) {
    // Delete 3D histogram with certain name
    for (Int_t i = 0; i < hThreeDHistos.size(); i++) if (hThreeDHistos.at(i)->GetName() == name) hThreeDHistos.erase(hThreeDHistos.begin() + i);
}

void QA::DeleteNDHisto(const TString &name) {
    // Delete ND histogram with certain name
    for (Int_t i = 0; i < hNDHistos.size(); i++) if (hNDHistos.at(i)->GetName() == name) hNDHistos.erase(hNDHistos.begin() + i);
}

void QA::AddOneDHisto(Int_t parameterX) {
    // Add new 1D histogram to vector of 1D histograms
    auto* histo = new TH1D(
            gQAParameters[parameterX].name,
            Form("%s;%s;counts", gQAParameters[parameterX].title.Data(), gQAParameters[parameterX].axis_title.Data()),
            (int) ((gQAParameters[parameterX].max_value - gQAParameters[parameterX].min_value) / gQAParameters[parameterX].bin_value),
            gQAParameters[parameterX].min_value,
            gQAParameters[parameterX].max_value
    );
    hOneDHistos.push_back(histo);
}

void QA::AddTwoDHisto(Int_t parameterX, Int_t parameterY) {
    // Add new 2D histogram to vector of 2D histograms
    TH2D* histo = new TH2D(
            Form("%s_%s", gQAParameters[parameterX].name.Data(), gQAParameters[parameterY].name.Data()),
            Form("%s VS %s;%s;%s;counts", gQAParameters[parameterY].title.Data(), gQAParameters[parameterX].title.Data(), gQAParameters[parameterX].axis_title.Data(), gQAParameters[parameterY].axis_title.Data()),
            (int) ((gQAParameters[parameterX].max_value - gQAParameters[parameterX].min_value) / gQAParameters[parameterX].bin_value),
            gQAParameters[parameterX].min_value,
            gQAParameters[parameterX].max_value,
            (int) ((gQAParameters[parameterY].max_value - gQAParameters[parameterY].min_value) / gQAParameters[parameterY].bin_value),
            gQAParameters[parameterY].min_value,
            gQAParameters[parameterY].max_value
    );
    cout<<histo->GetName()<<endl;
    hTwoDHistos.push_back(histo);
}

void QA::AddThreeDHisto(Int_t parameterX, Int_t parameterY, Int_t parameterZ) {
    // Add new 3D histogram to vector of 3D histograms
    auto* histo = new TH3D(
            Form("%s_%s_%s", gQAParameters[parameterX].name.Data(), gQAParameters[parameterY].name.Data(), gQAParameters[parameterZ].name.Data()),
            Form("%s VS %s VS %s;%s;%s;%s", gQAParameters[parameterZ].title.Data(), gQAParameters[parameterY].title.Data(), gQAParameters[parameterX].title.Data(), gQAParameters[parameterX].axis_title.Data(), gQAParameters[parameterY].axis_title.Data(), gQAParameters[parameterZ].axis_title.Data()),
            (int) ((gQAParameters[parameterX].max_value - gQAParameters[parameterX].min_value) / gQAParameters[parameterX].bin_value),
            gQAParameters[parameterX].min_value,
            gQAParameters[parameterX].max_value,
            (int) ((gQAParameters[parameterY].max_value - gQAParameters[parameterY].min_value) / gQAParameters[parameterY].bin_value),
            gQAParameters[parameterY].min_value,
            gQAParameters[parameterY].max_value,
            (int) ((gQAParameters[parameterZ].max_value - gQAParameters[parameterZ].min_value) / gQAParameters[parameterZ].bin_value),
            gQAParameters[parameterZ].min_value,
            gQAParameters[parameterZ].max_value
    );
    hThreeDHistos.push_back(histo);
}

void QA::AddNDHisto(Int_t dimensions, Int_t* parameters) {
    // Add new ND histogram to vector of ND histograms
    TString name = gQAParameters[parameters[0]].name;
    for (Int_t i = 1; i < dimensions; i++) name = name + "_" + gQAParameters[parameters[i]].name;
    TString title = gQAParameters[parameters[dimensions-1]].title;
    for (Int_t i = 2; i <= dimensions; i++) title = title + " VS " + gQAParameters[parameters[dimensions-i]].title;
    Int_t bins[dimensions];
    Double_t min[dimensions];
    Double_t max[dimensions];
    for (Int_t i = 0; i < dimensions; i++) {
        bins[i] = (int) ((gQAParameters[parameters[i]].max_value - gQAParameters[parameters[i]].min_value) / gQAParameters[parameters[i]].bin_value);
        min[i] = gQAParameters[parameters[i]].min_value;
        max[i] = gQAParameters[parameters[i]].max_value;
    }
    auto* histo = new THnSparseD(name, title, dimensions, bins, min, max);
    for (Int_t i = 0; i < dimensions; i++) histo->GetAxis(i)->SetTitle(gQAParameters[parameters[i]].axis_title);
    hNDHistos.push_back(histo);
}

Double_t QA::GetParameterValue(Event* event, const TString &axis_name, Int_t fragmentId) {
    // Return value of parameter
    Fragment fragment = event->GetFragment(fragmentId);
    if (axis_name == "b, fm") return event->GetB();
    else if (axis_name == "N_{coll}") return event->GetNColl();
    else if (axis_name == "N_{part}") return (event->GetNPartProj() + event->GetNPartTarg());
    else if (axis_name == "N_{spec}") return (event->GetAProj() - event->GetNPartProj() + event->GetATarg() - event->GetNPartTarg());
    else if (axis_name == "A_{tot}") return (event->GetATotProj() + event->GetATotTarg());
    else if (axis_name == "Z_{tot}") return (event->GetZTotProj() + event->GetZTotTarg());
    else if (axis_name == "E_{tot}") return (event->GetETotProj() + event->GetETotTarg());
    else if (axis_name == "E_{PSD}") return (event->GetEPsdProj() + event->GetEPsdTarg());
    else if (axis_name == "N_{frag}") return (event->GetNFragProj() + event->GetNFragTarg());
    else if (axis_name == "N_{u}") return (event->GetNuProj() + event->GetNuTarg());
    else if (axis_name == "N_{part}^{proj}") return event->GetNPartProj();
    else if (axis_name == "N_{spec}^{proj}") return (event->GetAProj() - event->GetNPartProj());
    else if (axis_name == "A_{tot}^{proj}") return event->GetATotProj();
    else if (axis_name == "Z_{tot}^{proj}") return event->GetZTotProj();
    else if (axis_name == "E_{tot}^{proj}") return event->GetETotProj();
    else if (axis_name == "E_{PSD}^{proj}") return event->GetEPsdProj();
    else if (axis_name == "N_{frag}^{proj}") return (event->GetNFragProj());
    else if (axis_name == "N_{u}^{proj}") return event->GetNuProj();
    else if (axis_name == "N_{part}^{targ}") return event->GetNPartTarg();
    else if (axis_name == "N_{spec}^{targ}") return (event->GetATarg() - event->GetNPartTarg());
    else if (axis_name == "A_{tot}^{targ}") return event->GetATotTarg();
    else if (axis_name == "Z_{tot}^{targ}") return event->GetZTotTarg();
    else if (axis_name == "E_{tot}^{targ}") return event->GetETotTarg();
    else if (axis_name == "E_{PSD}^{targ}") return event->GetEPsdTarg();
    else if (axis_name == "N_{frag}^{targ}") return (event->GetNFragTarg());
    else if (axis_name == "N_{u}^{targ}") return event->GetNuTarg();
    else if ((axis_name == "A_{frag}" && fragment.IsFragment()) ||
             (axis_name == "A_{frag}^{proj}" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "A_{frag}^{targ}" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetAFrag();
    else if ((axis_name == "Z_{frag}" && fragment.IsFragment()) ||
             (axis_name == "Z_{frag}^{proj}" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "Z_{frag}^{targ}" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetZFrag();
    else if ((axis_name == "N_{a}" && fragment.IsFragment()) ||
             (axis_name == "N_{a}^{proj}" && fragment.IsFragment() && fragment.IsProjectile())
            )
        return event->GetNaProj(fragment.GetAFrag());
    else if ((axis_name == "N_{a}" && fragment.IsFragment()) ||
             (axis_name == "N_{a}^{targ}" && fragment.IsFragment() && fragment.IsTarget())
            )
        return event->GetNaTarg(fragment.GetAFrag());
    else if ((axis_name == "E, GeV" && fragment.IsFragment()) ||
             (axis_name == "E^{proj}, GeV" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "E^{targ}, GeV" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetMomentum().E();
    else if ((axis_name == "E_{frag,PSD}, GeV" && fragment.IsFragment()) ||
             (axis_name == "E_{frag,PSD}^{proj}, GeV" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "E_{frag,PSD}^{targ}, GeV" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetEPsd();
    else if ((axis_name == "p, GeV/c" && fragment.IsFragment()) ||
             (axis_name == "p^{proj}, GeV/c" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "p^{targ}, GeV/c" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetMomentum().P();
    else if ((axis_name == "p_{x}, GeV/c" && fragment.IsFragment()) ||
             (axis_name == "p_{x}^{proj}, GeV/c" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "p_{x}^{targ}, GeV/c" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetMomentum().Px();
    else if ((axis_name == "p_{y}, GeV/c" && fragment.IsFragment()) ||
             (axis_name == "p_{y}^{proj}, GeV/c" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "p_{y}^{targ}, GeV/c" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetMomentum().Py();
    else if ((axis_name == "p_{z}, GeV/c" && fragment.IsFragment()) ||
             (axis_name == "p_{z}^{proj}, GeV/c" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "p_{z}^{targ}, GeV/c" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetMomentum().Pz();
    else if ((axis_name == "p_{t}, GeV/c" && fragment.IsFragment()) ||
             (axis_name == "p_{t}^{proj}, GeV/c" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "p_{t}^{targ}, GeV/c" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetMomentum().Pt();
    else if ((axis_name == "Rapidity" && fragment.IsFragment()) ||
             (axis_name == "Rapidity^{proj}" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "Rapidity^{targ}" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetMomentum().Rapidity();
    else if ((axis_name == "#Theta" && fragment.IsFragment()) ||
             (axis_name == "#Theta^{proj}" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "#Theta^{targ}" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetMomentum().Theta();
    else if ((axis_name == "#eta" && fragment.IsFragment())||
             (axis_name == "#eta^{proj}" && fragment.IsFragment() && fragment.IsProjectile()) ||
             (axis_name == "#eta^{targ}" && fragment.IsFragment() && fragment.IsTarget())
            )
        return fragment.GetMomentum().Eta();
    else if ((axis_name == "X, fm" && fragment.IsInitialNucleon()) ||
             (axis_name == "X^{proj}, fm" && fragment.IsInitialNucleon() && fragment.IsProjectile()) ||
             (axis_name == "X^{targ}, fm" && fragment.IsInitialNucleon() && fragment.IsTarget())
            )
        return fragment.GetPosition().X();
    else if ((axis_name == "Y, fm" && fragment.IsInitialNucleon()) ||
             (axis_name == "Y^{proj}, fm" && fragment.IsInitialNucleon() && fragment.IsProjectile()) ||
             (axis_name == "Y^{targ}, fm" && fragment.IsInitialNucleon() && fragment.IsTarget())
            )
        return fragment.GetPosition().Y();
    else if ((axis_name == "Z, fm" && fragment.IsInitialNucleon()) ||
             (axis_name == "Z^{proj}, fm" && fragment.IsInitialNucleon() && fragment.IsProjectile()) ||
             (axis_name == "Z^{targ}, fm" && fragment.IsInitialNucleon() && fragment.IsTarget())
            )
        return fragment.GetPosition().Z();
    else if ((axis_name == "r, fm" && fragment.IsInitialNucleon()) ||
             (axis_name == "r^{proj}, fm" && fragment.IsInitialNucleon() && fragment.IsProjectile()) ||
             (axis_name == "r^{targ}, fm" && fragment.IsInitialNucleon() && fragment.IsTarget())
            )
        return fragment.GetPosition().Mag();
    else if ((axis_name == "#phi, rad" && fragment.IsInitialNucleon()) ||
             (axis_name == "#phi^{proj}, rad" && fragment.IsInitialNucleon() && fragment.IsProjectile()) ||
             (axis_name == "#phi^{targ}, rad" && fragment.IsInitialNucleon() && fragment.IsTarget())
            )
        return fragment.GetPosition().Phi();
    else if ((axis_name == "#theta, rad" && fragment.IsInitialNucleon()) ||
             (axis_name == "#theta^{proj}, rad" && fragment.IsInitialNucleon() && fragment.IsProjectile()) ||
             (axis_name == "#theta^{targ}, rad" && fragment.IsInitialNucleon() && fragment.IsTarget())
            )
        return fragment.GetPosition().Theta();
    return -9999.;
}

void QA::FillOneDHisto(TH1D *&histo, Event* event, Int_t fragmentId) {
    // Fill 1D histogram
    Double_t weight = 1;
    if (strcmp(histo->GetXaxis()->GetTitle(), "N_{a}") == 0 || strcmp(histo->GetXaxis()->GetTitle(), "N_{a}^{proj}") == 0 || strcmp(histo->GetXaxis()->GetTitle(), "N_{a}^{targ}") == 0)
        weight = 1/GetParameterValue(event, histo->GetXaxis()->GetTitle(), fragmentId);
    histo->Fill(GetParameterValue(event, histo->GetXaxis()->GetTitle(), fragmentId), weight);
}

void QA::FillTwoDHisto(TH2D *&histo, Event* event, Int_t fragmentId) {
    // Fill 2D histogram
    Double_t weight = 1;
    if (strcmp(histo->GetXaxis()->GetTitle(), "N_{a}") == 0 || strcmp(histo->GetXaxis()->GetTitle(), "N_{a}^{proj}") == 0 || strcmp(histo->GetXaxis()->GetTitle(), "N_{a}^{targ}") == 0)
        weight = 1/GetParameterValue(event, histo->GetXaxis()->GetTitle(), fragmentId);
    else if (strcmp(histo->GetYaxis()->GetTitle(), "N_{a}") == 0 || strcmp(histo->GetYaxis()->GetTitle(), "N_{a}^{proj}") == 0 || strcmp(histo->GetYaxis()->GetTitle(), "N_{a}^{targ}") == 0)
        weight = 1/GetParameterValue(event, histo->GetYaxis()->GetTitle(), fragmentId);
    histo->Fill(
        GetParameterValue(event, histo->GetXaxis()->GetTitle(), fragmentId),
        GetParameterValue(event, histo->GetYaxis()->GetTitle(), fragmentId),
        weight
    );
}

void QA::FillThreeDHisto(TH3D *&histo, Event* event, Int_t fragmentId) {
    // Fill 3D histogram
    Double_t weight = 1;
    if (strcmp(histo->GetXaxis()->GetTitle(), "N_{a}") == 0 || strcmp(histo->GetXaxis()->GetTitle(), "N_{a}^{proj}") == 0 || strcmp(histo->GetXaxis()->GetTitle(), "N_{a}^{targ}") == 0)
        weight = 1/GetParameterValue(event, histo->GetXaxis()->GetTitle(), fragmentId);
    else if (strcmp(histo->GetYaxis()->GetTitle(), "N_{a}") == 0 || strcmp(histo->GetYaxis()->GetTitle(), "N_{a}^{proj}") == 0 || strcmp(histo->GetYaxis()->GetTitle(), "N_{a}^{targ}") == 0)
        weight = 1/GetParameterValue(event, histo->GetYaxis()->GetTitle(), fragmentId);
    else if (strcmp(histo->GetZaxis()->GetTitle(), "N_{a}") == 0 || strcmp(histo->GetZaxis()->GetTitle(), "N_{a}^{proj}") == 0 || strcmp(histo->GetZaxis()->GetTitle(), "N_{a}^{targ}") == 0)
        weight = 1/GetParameterValue(event, histo->GetZaxis()->GetTitle(), fragmentId);
    histo->Fill(
        GetParameterValue(event, histo->GetXaxis()->GetTitle(), fragmentId),
        GetParameterValue(event, histo->GetYaxis()->GetTitle(), fragmentId),
        GetParameterValue(event, histo->GetZaxis()->GetTitle(), fragmentId),
        weight
    );
}

void QA::FillNDHisto(THnSparseD *&histo, Event* event, Int_t fragmentId) {
    // Fill ND histogram
    Double_t par[histo->GetNdimensions()];
    Double_t weight = 1;
    for (Int_t i = 0; i < histo->GetNdimensions(); i++) par[i] = GetParameterValue(event, histo->GetAxis(i)->GetTitle(), fragmentId);
    for (Int_t i = 0; i < histo->GetNdimensions(); i++) {
        if (strcmp(histo->GetAxis(i)->GetTitle(), "N_{a}") == 0 ||
            strcmp(histo->GetAxis(i)->GetTitle(), "N_{a}^{proj}") == 0 ||
            strcmp(histo->GetAxis(i)->GetTitle(), "N_{a}^{targ}") == 0) {
            weight = 1 / GetParameterValue(event, histo->GetAxis(i)->GetTitle(), fragmentId);
            break;
        }
    }
    histo->Fill(par, weight);
}

Bool_t QA::IsOneDFromEvent(TH1D* histo) {
    // Return 1 if parameter of 1D hist is event parameter, return 0 otherwise
    for (const QAParameters& i : gQAParameters)
        if (histo->GetXaxis()->GetTitle() == i.axis_title) {
            if (i.level_id == 0) return kTRUE;
            else return kFALSE;
        }
    return kFALSE;
}

Bool_t QA::IsTwoDFromEvent(TH2D* histo) {
    // Return 1 if all parameters of 2D hist are event parameters, return 0 otherwise
    for (const QAParameters& i : gQAParameters) {
        if (histo->GetXaxis()->GetTitle() == i.axis_title) {
            if (i.level_id == 1) return kFALSE;
            break;
        }
    }
    for (const QAParameters& i : gQAParameters) {
        if (histo->GetYaxis()->GetTitle() == i.axis_title) {
            if (i.level_id != 0) return kFALSE;
            break;
        }
    }
    return kTRUE;
}
Bool_t QA::IsThreeDFromEvent(TH3D* histo) {
    // Return 1 if all parameters of 3D hist are event parameters, return 0 otherwise
    for (const QAParameters& i : gQAParameters) {
        if (histo->GetXaxis()->GetTitle() == i.axis_title) {
            if (i.level_id != 0) return kFALSE;
            break;
        }
    }
    for (const QAParameters& i : gQAParameters) {
        if (histo->GetYaxis()->GetTitle() == i.axis_title) {
            if (i.level_id != 0) return kFALSE;
            break;
        }
    }
    for (const QAParameters& i : gQAParameters) {
        if (histo->GetZaxis()->GetTitle() == i.axis_title) {
            if (i.level_id != 0) return kFALSE;
            break;
        }
    }
    return kTRUE;
}

Bool_t QA::IsNDFromEvent(THnSparseD* histo) {
    // Return 1 if all parameters of ND hist are event parameters, return 0 otherwise
    for (Int_t j = 0; j < histo->GetNdimensions(); j++) {
        for (const QAParameters &i: gQAParameters) {
            if (histo->GetAxis(j)->GetTitle() == i.axis_title) {
                if (i.level_id != 0) return kFALSE;
                break;
            }
        }
    }
    return kTRUE;
}

void QA::Fill(Event* event) {
    // Fill all histograms
    for (TH1D* histo : hOneDHistos) if (IsOneDFromEvent(histo)) FillOneDHisto(histo, event);
    for (TH2D* histo : hTwoDHistos) if (IsTwoDFromEvent(histo)) FillTwoDHisto(histo, event);
    for (TH3D* histo : hThreeDHistos) if (IsThreeDFromEvent(histo)) FillThreeDHisto(histo, event);
    for (THnSparseD* histo : hNDHistos) if (IsNDFromEvent(histo)) FillNDHisto(histo, event);
    for (Int_t j = 0; j < event->GetNFragments(); j++) {
        for (TH1D* histo : hOneDHistos) if (!IsOneDFromEvent(histo)) FillOneDHisto(histo, event, j);
        for (TH2D* histo : hTwoDHistos) if (!IsTwoDFromEvent(histo)) FillTwoDHisto(histo, event, j);
        for (TH3D* histo : hThreeDHistos) if (!IsThreeDFromEvent(histo)) FillThreeDHisto(histo, event, j);
        for (THnSparseD* histo : hNDHistos) if (!IsNDFromEvent(histo)) FillNDHisto(histo, event, j);
    }
}

void QA::Write() {
    // Write all histograms
    for (TH1D* histo : hOneDHistos) histo->Write();
    for (TH2D* histo : hTwoDHistos) histo->Write();
    for (TH3D* histo : hThreeDHistos) histo->Write();
    for (THnSparseD* histo : hNDHistos) histo->Write();
}

void QA::Clear() {
    // Clear QA
    hOneDHistos.clear();
    hTwoDHistos.clear();
    hThreeDHistos.clear();
    hNDHistos.clear();
}

ClassImp(QA);
