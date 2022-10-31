#include "generator.hh"
#include <Math/SpecFuncMathMore.h>

generator::generator() {
    fGeneralParticleSource = new G4GeneralParticleSource();

    G4SingleParticleSource *sps = fGeneralParticleSource->GetCurrentSource();
    G4ParticleDefinition *particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");

    sps->SetParticleDefinition(particle);
    sps->SetNumberOfParticles(1);

    sps->GetPosDist()->SetPosDisType("Plane"); // Point, Beam, Plane, Surface, Volume
    sps->GetPosDist()->SetPosDisShape("Circle");
    sps->GetPosDist()->SetRadius(1 * cm);
    sps->GetPosDist()->SetCentreCoords(G4ThreeVector(0., 0., 2 * cm));
    sps->GetPosDist()->ConfineSourceToVolume("NULL");

    sps->GetAngDist()->SetAngDistType("planar"); // Isotropic, Cosine-law, Beam, User-defined
/*
    // Black-body distribution
    sps->GetEneDist()->SetEnergyDisType("Bbody"); // Mono, Lin, Pow, Exp, Gaus, Brem, BBody, Cdg (cosmic diffuse gamma), User, Arb, Epn (energy per nucleon)
    sps->GetEneDist()->SetEmin(0.1*keV);
    sps->GetEneDist()->SetEmax(200*keV);
    sps->GetEneDist()->SetTemp(2E7);
*/

    sps->GetEneDist()->SetEnergyDisType("User");
    double E_emax = 100E6; // eV
    double Ecrit = 2000.; // eV
    double electron_mass = 0.511E6; // eV
    double gammaFactor = E_emax / electron_mass; // relativistic gamma factor
    double Nbet = 3; // number of oscillations of electrons
    double qe = 1.602E-19; // electron charge in Coulomb
    double hbarJ = 1.055E-16; // hbar in J*s
    double epsilon0 = 8.854E-12; // permitivity of free space (F/m)
    double c0 = 2.998E8; // m/s
    double constant = 3 * Nbet * TMath::Power(qe, 2) / (2*TMath::Power(TMath::Pi(), 3) * hbarJ * c0 * epsilon0);
    for (unsigned int i = 1; i < 1024; i++) {
        double ehi = 20. * i; // in eV
        double CSI = (ehi - 10.) / Ecrit;
        double val = constant * TMath::Power(gammaFactor * CSI * ROOT::Math::cyl_bessel_k(2./3., CSI), 2);
        sps->GetEneDist()->UserEnergyHisto(G4ThreeVector((ehi - 10.) * eV, val, 0));
    }
}

generator::~generator() {
    delete fGeneralParticleSource;
}

void generator::GeneratePrimaries(G4Event *anEvent) {
    fGeneralParticleSource->GeneratePrimaryVertex(anEvent);
}
