#include "gammasd.hh"

GammaSD::GammaSD(const G4String &name) : G4VSensitiveDetector(name) {}

GammaSD::~GammaSD() {}

G4bool GammaSD::ProcessHits(G4Step *aStep, G4TouchableHistory *) {
    G4Track *track = aStep->GetTrack();

    if (track->GetDefinition() != G4ParticleTable::GetParticleTable()->FindParticle("gamma")) {
        track->SetTrackStatus(fStopAndKill);
        return false;
    }

    auto prePoint = aStep->GetPreStepPoint();

    G4double energy = prePoint->GetTotalEnergy();
    G4double copyNo = prePoint->GetPhysicalVolume()->GetCopyNo();

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleDColumn(0, energy / keV);
    man->FillNtupleDColumn(1, copyNo);
    man->AddNtupleRow(0);

    track->SetTrackStatus(fStopAndKill);
    return true;
}