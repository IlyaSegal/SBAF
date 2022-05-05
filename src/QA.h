//
// Created by isegal on 14.01.2022.
//

#ifndef SBAF_QA_H
#define SBAF_QA_H

#include <vector>
#include <map>
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "THnSparse.h"
using namespace std;

class Event;
class Fragment;
class AnisotropyVector;

    enum eQAParameters {
        // Enumerator of possible QA parameters
        kB = 0, kNColl,
        kNPart, kNSpec, kATot, kZTot, kETot, kEPsd, kNFrag, kAFrag, kZFrag, kNa, kNu,
        kNPartProj, kNSpecProj, kATotProj, kZTotProj, kETotProj, kEPsdProj, kNFragProj, kAFragProj, kZFragProj, kNaProj, kNuProj,
        kNPartTarg, kNSpecTarg, kATotTarg, kZTotTarg, kETotTarg, kEPsdTarg, kNFragTarg, kAFragTarg, kZFragTarg, kNaTarg, kNuTarg,
        kE, kEFragPsd, kP, kPx, kPy, kPz, kPt, kRapidity, kEta, kTheta,
        kEProj, kEFragPsdProj, kPProj, kPxProj, kPyProj, kPzProj, kPtProj, kRapidityProj, kEtaProj, kThetaProj,
        kETarg, kEFragPsdTarg, kPTarg, kPxTarg, kPyTarg, kPzTarg, kPtTarg, kRapidityTarg, kEtaTarg, kThetaTarg,
        kX, kY, kZ, kPhi, kPosTheta, kRho,
        kXProj, kYProj, kZProj, kPhiProj, kPosThetaProj, kRhoProj,
        kXTarg, kYTarg, kZTarg, kPhiTarg, kPosThetaTarg, kRhoTarg,
        kQAP
    };

    const struct QAParameters {
        Int_t id;
        TString name;
        TString title;
        TString axis_title;
        Double_t bin_value;
        Double_t min_value;
        Double_t max_value;
        Int_t level_id;
    } gQAParameters[kQAP] = {
            // Initialization of QA parameters
            { .id = kB,            .name = "B",            .title = "Impact parameter",                                                    .axis_title = "b, fm",                     .bin_value = 0.1,  .min_value = 0,   .max_value = 20,      .level_id = 0},
            { .id = kNColl,        .name = "NColl",        .title = "Number of binary collisions",                                         .axis_title = "N_{coll}",                  .bin_value = 1,    .min_value = 0,   .max_value = 1200,    .level_id = 0},
            { .id = kNPart,        .name = "NPart",        .title = "Number of participating nucleons",                                    .axis_title = "N_{part}",                  .bin_value = 1,    .min_value = 0,   .max_value = 420,     .level_id = 0},
            { .id = kNSpec,        .name = "NSpec",        .title = "Number of spectator nucleons",                                        .axis_title = "N_{spec}",                  .bin_value = 1,    .min_value = 0,   .max_value = 420,     .level_id = 0},
            { .id = kATot,         .name = "ATot",         .title = "Total mass number of spectator fragments",                            .axis_title = "A_{tot}",                   .bin_value = 1,    .min_value = 0,   .max_value = 420,     .level_id = 0},
            { .id = kZTot,         .name = "ZTot",         .title = "Total charge number of spectator fragments",                          .axis_title = "Z_{tot}",                   .bin_value = 1,    .min_value = 0,   .max_value = 420,     .level_id = 0},
            { .id = kETot,         .name = "ETot",         .title = "Total energy of spectator fragments",                                 .axis_title = "E_{tot}, GeV",              .bin_value = 0.1,  .min_value = 0,   .max_value = 5000,    .level_id = 0},
            { .id = kEPsd,         .name = "EPsd",         .title = "Total PSD energy of spectator fragments",                             .axis_title = "E_{PSD}, GeV",              .bin_value = 0.1,  .min_value = 0,   .max_value = 5000,    .level_id = 0},
            { .id = kNFrag,        .name = "NFrag",        .title = "Number of the fragment",                                              .axis_title = "N_{frag}",                  .bin_value = 1,    .min_value = 0,   .max_value = 420,     .level_id = 0},
            { .id = kAFrag,        .name = "AFrag",        .title = "Mass number of the fragment",                                         .axis_title = "A_{frag}",                  .bin_value = 1,    .min_value = 0,   .max_value = 420,     .level_id = 1},
            { .id = kZFrag,        .name = "ZFrag",        .title = "Charge number of the fragment",                                       .axis_title = "Z_{frag}",                  .bin_value = 1,    .min_value = 0,   .max_value = 420,     .level_id = 1},
            { .id = kNa,           .name = "Na",           .title = "Number of spectator fragments with certain mass number",              .axis_title = "N_{a}",                     .bin_value = 1,    .min_value = 0,   .max_value = 420,     .level_id = 0},
            { .id = kNu,           .name = "Nu",           .title = "Number of spectator fragments with unique mass number",               .axis_title = "N_{u}",                     .bin_value = 1,    .min_value = 0,   .max_value = 420,     .level_id = 0},
            { .id = kNPartProj,    .name = "NPartProj",    .title = "Number of participating nucleons (projectile)",                       .axis_title = "N_{part}^{proj}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kNSpecProj,    .name = "NSpecProj",    .title = "Number of spectator nucleons (projectile)",                           .axis_title = "N_{spec}^{proj}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kATotProj,     .name = "ATotProj",     .title = "Total mass number of spectator fragments (projectile)",               .axis_title = "A_{tot}^{proj}",            .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kZTotProj,     .name = "ZTotProj",     .title = "Total charge number of spectator fragments (projectile)",             .axis_title = "Z_{tot}^{proj}",            .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kETotProj,     .name = "ETotProj",     .title = "Total energy of spectator fragments (projectile)",                    .axis_title = "E_{tot}^{proj}, GeV",       .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 0},
            { .id = kEPsdProj,     .name = "EPsdProj",     .title = "Total PSD energy of spectator fragments (projectile)",                .axis_title = "E_{PSD}^{proj}, GeV",       .bin_value = 5,    .min_value = 0,   .max_value = 4000,    .level_id = 0},
            { .id = kNFragProj,    .name = "NFragProj",    .title = "Number of the fragment (projectile)",                                 .axis_title = "N_{frag}^{proj}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kAFragProj,    .name = "AFragProj",    .title = "Mass number of the fragment (projectile)",                            .axis_title = "A_{frag}^{proj}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 1},
            { .id = kZFragProj,    .name = "ZFragProj",    .title = "Charge number of the fragment (projectile)",                          .axis_title = "Z_{frag}^{proj}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 1},
            { .id = kNaProj,       .name = "NaProj",       .title = "Number of spectator fragments with certain mass number (projectile)", .axis_title = "N_{a}^{proj}",              .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kNuProj,       .name = "NuProj",       .title = "Number of spectator fragments with unique mass number (projectile)",  .axis_title = "N_{u}^{proj}",              .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kNPartTarg,    .name = "NPartTarg",    .title = "Number of participating nucleons (target)",                           .axis_title = "N_{part}^{targ}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kNSpecTarg,    .name = "NSpecTarg",    .title = "Number of spectator nucleons (target)",                               .axis_title = "N_{spec}^{targ}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kATotTarg,     .name = "ATotTarg",     .title = "Total mass number of spectator fragments (target)",                   .axis_title = "A_{tot}^{targ}",            .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kZTotTarg,     .name = "ZTotTarg",     .title = "Total charge number of spectator fragments (target)",                 .axis_title = "Z_{tot}^{targ}",            .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kETotTarg,     .name = "ETotTarg",     .title = "Total energy of spectator fragments (target)",                        .axis_title = "E_{tot}^{targ}, GeV",       .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 0},
            { .id = kEPsdTarg,     .name = "EPsdTarg",     .title = "Total PSD energy of spectator fragments (target)",                    .axis_title = "E_{PSD}^{targ}, GeV",       .bin_value = 5,    .min_value = 0,   .max_value = 4000,    .level_id = 0},
            { .id = kNFragTarg,    .name = "NFragTarg",    .title = "Number of the fragment (target)",                                     .axis_title = "N_{frag}^{targ}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kAFragTarg,    .name = "AFragTarg",    .title = "Mass number of the fragment (target)",                                .axis_title = "A_{frag}^{targ}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 1},
            { .id = kZFragTarg,    .name = "ZFragTarg",    .title = "Charge number of the fragment (target)",                              .axis_title = "Z_{frag}^{targ}",           .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 1},
            { .id = kNaTarg,       .name = "NaTarg",       .title = "Number of spectator fragments with certain mass number (target)",     .axis_title = "N_{a}^{targ}",              .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kNuTarg,       .name = "NuTarg",       .title = "Number of spectator fragments with unique mass number (target)",      .axis_title = "N_{u}^{targ}",              .bin_value = 1,    .min_value = 0,   .max_value = 210,     .level_id = 0},
            { .id = kE,            .name = "E",            .title = "Energy of spectator fragments",                                       .axis_title = "E_{frag}, GeV",             .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 1},
            { .id = kEFragPsd,     .name = "EFragPsd",     .title = "PSD energy of spectator fragments",                                   .axis_title = "E_{frag,PSD}, GeV",         .bin_value = 5,    .min_value = 0,   .max_value = 4000,    .level_id = 1},
            { .id = kP,            .name = "P",            .title = "Momentum of spectator fragments",                                     .axis_title = "p_{frag}, GeV/c",           .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 1},
            { .id = kPx,           .name = "Px",           .title = "Momentum of spectator fragments along X axis",                        .axis_title = "p_{x, frag}, GeV/c",        .bin_value = 0.01, .min_value = -10, .max_value = 10,      .level_id = 1},
            { .id = kPy,           .name = "Py",           .title = "Momentum of spectator fragments along Y axis",                        .axis_title = "p_{y, frag}, GeV/c",        .bin_value = 0.01, .min_value = -10, .max_value = 10,      .level_id = 1},
            { .id = kPz,           .name = "Pz",           .title = "Momentum of spectator fragments along Z axis",                        .axis_title = "p_{z, frag}, GeV/c",        .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 1},
            { .id = kPt,           .name = "Pt",           .title = "Transverse momentum of spectator fragments",                          .axis_title = "p_{t, frag}, GeV/c",        .bin_value = 0.01, .min_value = 0,   .max_value = 10,      .level_id = 1},
            { .id = kRapidity,     .name = "Rapidity",     .title = "Rapidity of spectator fragments",                                     .axis_title = "Rapidity_{frag}",           .bin_value = 0.01, .min_value = 2.5, .max_value = 4,       .level_id = 1},
            { .id = kTheta,        .name = "Theta",        .title = "Theta of spectator fragments",                                        .axis_title = "#Theta_{frag}",             .bin_value = 0.01, .min_value = -4,  .max_value = 4,       .level_id = 1},
            { .id = kEta,          .name = "Eta",          .title = "Pseudorapidity of spectator fragments",                               .axis_title = "#eta_{frag}",               .bin_value = 0.01, .min_value = -5,  .max_value = 5,       .level_id = 1},
            { .id = kEProj,        .name = "EProj",        .title = "Energy of spectator fragments (projectile)",                          .axis_title = "E_{frag}^{proj}, GeV",      .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 1},
            { .id = kEFragPsdProj, .name = "EFragPsdProj", .title = "PSD energy of spectator fragments (projectile)",                      .axis_title = "E_{frag,PSD}^{proj}, GeV",  .bin_value = 5,    .min_value = 0,   .max_value = 4000,    .level_id = 1},
            { .id = kPProj,        .name = "PProj",        .title = "Momentum of spectator fragments (projectile)",                        .axis_title = "p_{frag}^{proj}, GeV/c",    .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 1},
            { .id = kPxProj,       .name = "PxProj",       .title = "Momentum of spectator fragments along X axis (projectile)",           .axis_title = "p_{x, frag}^{proj}, GeV/c", .bin_value = 0.01, .min_value = -10, .max_value = 10,      .level_id = 1},
            { .id = kPyProj,       .name = "PyProj",       .title = "Momentum of spectator fragments along Y axis (projectile)",           .axis_title = "p_{y, frag}^{proj}, GeV/c", .bin_value = 0.01, .min_value = -10, .max_value = 10,      .level_id = 1},
            { .id = kPzProj,       .name = "PzProj",       .title = "Momentum of spectator fragments along Z axis (projectile)",           .axis_title = "p_{z, frag}^{proj}, GeV/c", .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 1},
            { .id = kPtProj,       .name = "PtProj",       .title = "Transverse momentum of spectator fragments (projectile)",             .axis_title = "p_{t, frag}^{proj}, GeV/c", .bin_value = 0.01, .min_value = 0,   .max_value = 10,      .level_id = 1},
            { .id = kRapidityProj, .name = "RapidityProj", .title = "Rapidity of spectator fragments (projectile)",                        .axis_title = "Rapidity_{frag}^{proj}",    .bin_value = 0.01, .min_value = 2.5, .max_value = 4,       .level_id = 1},
            { .id = kThetaProj,    .name = "ThetaProj",    .title = "Theta of spectator fragments (projectile)",                           .axis_title = "#Theta_{frag}^{proj}",      .bin_value = 0.01, .min_value = -4,  .max_value = 4,       .level_id = 1},
            { .id = kEtaProj,      .name = "EtaProj",      .title = "Pseudorapidity of spectator fragments (projectile)",                  .axis_title = "#eta_{frag}^{proj}",        .bin_value = 0.01, .min_value = -5,  .max_value = 5,       .level_id = 1},
            { .id = kETarg,        .name = "ETarg",        .title = "Energy of spectator fragments (target)",                              .axis_title = "E_{frag}^{targ}, GeV",      .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 1},
            { .id = kEFragPsdTarg, .name = "EFragPsdTarg", .title = "PSD energy of spectator fragments (target)",                          .axis_title = "E_{frag,PSD}^{targ}, GeV",  .bin_value = 5,    .min_value = 0,   .max_value = 4000,    .level_id = 1},
            { .id = kPTarg,        .name = "PTarg",        .title = "Momentum of spectator fragments (target)",                            .axis_title = "p_{frag}^{targ}, GeV/c",    .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 1},
            { .id = kPxTarg,       .name = "PxTarg",       .title = "Momentum of spectator fragments along X axis (target)",               .axis_title = "p_{x, frag}^{targ}, GeV/c", .bin_value = 0.01, .min_value = -10, .max_value = 10,      .level_id = 1},
            { .id = kPyTarg,       .name = "PyTarg",       .title = "Momentum of spectator fragments along Y axis (target)",               .axis_title = "p_{y, frag}^{targ}, GeV/c", .bin_value = 0.01, .min_value = -10, .max_value = 10,      .level_id = 1},
            { .id = kPzTarg,       .name = "PzTarg",       .title = "Momentum of spectator fragments along Z axis (target)",               .axis_title = "p_{z, frag}^{targ}, GeV/c", .bin_value = 5,    .min_value = 0,   .max_value = 2500,    .level_id = 1},
            { .id = kPtTarg,       .name = "PtTarg",       .title = "Transverse momentum of spectator fragments (target)",                 .axis_title = "p_{t, frag}^{targ}, GeV/c", .bin_value = 0.01, .min_value = 0,   .max_value = 10,      .level_id = 1},
            { .id = kRapidityTarg, .name = "RapidityTarg", .title = "Rapidity of spectator fragments (target)",                            .axis_title = "Rapidity_{frag}^{targ}",    .bin_value = 0.01, .min_value = 2.5, .max_value = 4,       .level_id = 1},
            { .id = kThetaTarg,    .name = "ThetaTarg",    .title = "Theta of spectator fragments (target)",                               .axis_title = "#Theta_{frag}^{targ}",      .bin_value = 0.01, .min_value = -4,  .max_value = 4,       .level_id = 1},
            { .id = kEtaTarg,      .name = "EtaTarg",      .title = "Pseudorapidity of spectator fragments (target)",                      .axis_title = "#eta_{frag}^{targ}",        .bin_value = 0.01, .min_value = -5,  .max_value = 5,       .level_id = 1},
            { .id = kX,            .name = "X",            .title = "Position of initial nucleons along X axis",                           .axis_title = "X, fm",                     .bin_value = 0.1,  .min_value = -20, .max_value = 20,      .level_id = 1},
            { .id = kY,            .name = "Y",            .title = "Position of initial nucleons along Y axis",                           .axis_title = "Y, fm",                     .bin_value = 0.1,  .min_value = -20, .max_value = 20,      .level_id = 1},
            { .id = kZ,            .name = "Z",            .title = "Position of initial nucleons along Z axis",                           .axis_title = "Z, fm",                     .bin_value = 0.1,  .min_value = -20, .max_value = 20,      .level_id = 1},
            { .id = kRho,          .name = "Rho",          .title = "Position of initial nucleons along r axis",                           .axis_title = "r, fm",                     .bin_value = 0.1,  .min_value = 0,   .max_value = 20,      .level_id = 1},
            { .id = kPhi,          .name = "Phi",          .title = "Position of initial nucleons along #phi axis",                        .axis_title = "#phi, rad",                 .bin_value = 0.01, .min_value = -4,  .max_value = 4,       .level_id = 1},
            { .id = kPosTheta,     .name = "PosTheta",     .title = "Position of initial nucleons along #theta axis",                      .axis_title = "#theta, rad",               .bin_value = 0.01, .min_value = -4,  .max_value = 4,       .level_id = 1},
            { .id = kXProj,        .name = "XProj",        .title = "Position of initial nucleons along X axis (projectile)",              .axis_title = "X^{proj}, fm",              .bin_value = 0.1,  .min_value = -20, .max_value = 20,      .level_id = 1},
            { .id = kYProj,        .name = "YProj",        .title = "Position of initial nucleons along Y axis (projectile)",              .axis_title = "Y^{proj}, fm",              .bin_value = 0.1,  .min_value = -20, .max_value = 20,      .level_id = 1},
            { .id = kZProj,        .name = "ZProj",        .title = "Position of initial nucleons along Z axis (projectile)",              .axis_title = "Z^{proj}, fm",              .bin_value = 0.1,  .min_value = -20, .max_value = 20,      .level_id = 1},
            { .id = kRhoProj,      .name = "RhoProj",      .title = "Position of initial nucleons along r axis (projectile)",              .axis_title = "r^{proj}, fm",              .bin_value = 0.1,  .min_value = 0,   .max_value = 20,      .level_id = 1},
            { .id = kPhiProj,      .name = "PhiProj",      .title = "Position of initial nucleons along #phi axis (projectile)",           .axis_title = "#phi^{proj}, rad",          .bin_value = 0.01, .min_value = -4,  .max_value = 4,       .level_id = 1},
            { .id = kPosThetaProj, .name = "PosThetaProj", .title = "Position of initial nucleons along #theta axis (projectile)",         .axis_title = "#theta^{proj}, rad",        .bin_value = 0.01, .min_value = -4,  .max_value = 4,       .level_id = 1},
            { .id = kXTarg,        .name = "XTarg",        .title = "Position of initial nucleons along X axis (target)",                  .axis_title = "X^{targ}, fm",              .bin_value = 0.1,  .min_value = -20, .max_value = 20,      .level_id = 1},
            { .id = kYTarg,        .name = "YTarg",        .title = "Position of initial nucleons along Y axis (target)",                  .axis_title = "Y^{targ}, fm",              .bin_value = 0.1,  .min_value = -20, .max_value = 20,      .level_id = 1},
            { .id = kZTarg,        .name = "ZTarg",        .title = "Position of initial nucleons along Z axis (target)",                  .axis_title = "Z^{targ}, fm",              .bin_value = 0.1,  .min_value = -20, .max_value = 20,      .level_id = 1},
            { .id = kRhoTarg,      .name = "RhoTarg",      .title = "Position of initial nucleons along r axis (target)",                  .axis_title = "r^{targ}, fm",              .bin_value = 0.1,  .min_value = 0,   .max_value = 20,      .level_id = 1},
            { .id = kPhiTarg,      .name = "PhiTarg",      .title = "Position of initial nucleons along #phi axis (target)",               .axis_title = "#phi^{targ}, rad",          .bin_value = 0.01, .min_value = -4,  .max_value = 4,       .level_id = 1},
            { .id = kPosThetaTarg, .name = "PosThetaTarg", .title = "Position of initial nucleons along #theta axis (target)",             .axis_title = "#theta^{targ}, rad",        .bin_value = 0.01, .min_value = -4,  .max_value = 4,       .level_id = 1}
    };

class QA : public TObject {

private:
    Int_t fAProj;                      // Mass number of projectile nucleus
    Int_t fZProj;                      // Charge number of projectile nucleus
    Int_t fATarg;                      // Mass number of target nucleus
    Int_t fZTarg;                      // Charge number of target nucleus
    Double_t fPBeamProj;               // Beam momentum of projectile
    Double_t fPBeamTarg;               // Beam momentum of target
    TString fCollisionType;            // Type of collision (collider or fixed-target)
    vector<TH1D*> hOneDHistos;         // Vector of 1D histograms
    vector<TH2D*> hTwoDHistos;         // Vector of 2D histograms
    vector<TH3D*> hThreeDHistos;       // Vector of 3D histograms
    vector<THnSparseD*> hNDHistos;      // Vector of ND histograms

public:
    QA();
    QA(TString CollisionType, Int_t AProj, Int_t ZProj, Int_t ATarg, Int_t ZTarg, Double_t PBeamProj, Double_t PBeamTarg);
    virtual ~QA() = default;
    Int_t GetAProj() const {return fAProj;}
    Int_t GetZProj() const {return fZProj;}
    Int_t GetATarg() const {return fATarg;}
    Int_t GetZTarg() const {return fZTarg;}
    Double_t GetPProjBeam() const {return fPBeamProj;}
    Double_t GetPTargBeam() const {return fPBeamTarg;}
    TString GetCollisionType() const {return fCollisionType;}
    vector<TH1D*> GetOneDHistos() const {return hOneDHistos;}
    vector<TH2D*> GetTwoDHistos() const {return hTwoDHistos;}
    vector<TH3D*> GetThreeDHistos() const {return hThreeDHistos;}
    vector<THnSparseD*> GetNDHistos() const {return hNDHistos;}
    TH1D* GetOneDHisto(Int_t id)  {return hOneDHistos.at(id);}
    TH2D* GetTwoDHisto(Int_t id)  {return hTwoDHistos.at(id);}
    TH3D* GetThreeDHisto(Int_t id)  {return hThreeDHistos.at(id);}
    THnSparseD* GetNDHisto(Int_t id)  {return hNDHistos.at(id);}
    TH1D* GetOneDHisto(const TString &name);
    TH2D* GetTwoDHisto(const TString &name);
    TH3D* GetThreeDHisto(const TString &name);
    THnSparseD* GetNDHisto(const TString &name);
    void SetAProj(Int_t AProj) {fAProj = AProj;}
    void SetZProj(Int_t ZProj) {fZProj = ZProj;}
    void SetATarg(Int_t ATarg) {fATarg = ATarg;}
    void SetZTarg(Int_t ZTarg) {fZTarg = ZTarg;}
    void SetPProjBeam(Double_t PBeamProj) {fPBeamProj = PBeamProj;}
    void SetPTargBeam(Double_t PBeamTarg) {fPBeamTarg = PBeamTarg;}
    void SetCollisionType(TString CollisionType) {fCollisionType = CollisionType;}
    void DeleteOneDHisto(Int_t id)  {hOneDHistos.erase(hOneDHistos.begin() + id);}
    void DeleteTwoDHisto(Int_t id)  {hTwoDHistos.erase(hTwoDHistos.begin() + id);}
    void DeleteThreeDHisto(Int_t id)  {hThreeDHistos.erase(hThreeDHistos.begin() + id);}
    void DeleteNDHisto(Int_t id)  {hNDHistos.erase(hNDHistos.begin() + id);}
    void DeleteOneDHisto(const TString &name);
    void DeleteTwoDHisto(const TString &name);
    void DeleteThreeDHisto(const TString &name);
    void DeleteNDHisto(const TString &name);
    void AddOneDHisto(Int_t parameterX);
    void AddTwoDHisto(Int_t parameterX, Int_t parameterY);
    void AddThreeDHisto(Int_t parameterX, Int_t parameterY, Int_t parameterZ);
    void AddNDHisto(Int_t dimensions, Int_t* parameters);
    Double_t GetParameterValue(Event* event, const TString &axis_name, Int_t fragmentId = 0);
    void FillOneDHisto(TH1D* &histo, Event* event, Int_t fragmentId = 0);
    void FillTwoDHisto(TH2D* &histo, Event* event, Int_t fragmentId = 0);
    void FillThreeDHisto(TH3D* &histo, Event* event, Int_t fragmentId = 0);
    void FillNDHisto(THnSparseD* &histo, Event* event, Int_t fragmentId = 0);
    Bool_t IsOneDFromEvent(TH1D* histo);
    Bool_t IsTwoDFromEvent(TH2D* histo);
    Bool_t IsThreeDFromEvent(TH3D* histo);
    Bool_t IsNDFromEvent(THnSparseD* histo);
    void Fill(Event* event);
    void Write();
    void Clear();

ClassDef(QA, 1);
};

#endif //SBAF_QA_H
