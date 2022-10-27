#include "generator.hh"

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

    sps->GetEneDist()->SetEnergyDisType("Bbody"); // Mono, Lin, Pow, Exp, Gaus, Brem, BBody, Cdg (cosmic diffuse gamma), User, Arb, Epn (energy per nucleon)
    sps->GetEneDist()->SetEmin(0.1*keV);
    sps->GetEneDist()->SetEmax(200*keV);
    sps->GetEneDist()->SetTemp(2E7);
}

generator::~generator() {
    delete fGeneralParticleSource;
}

void generator::GeneratePrimaries(G4Event *anEvent) {
    fGeneralParticleSource->GeneratePrimaryVertex(anEvent);
}
