#include "runaction.hh"

runAction::runAction() : G4UserRunAction() {
  man = G4AnalysisManager::Instance();
  man->CreateNtuple("Gamma", "Gamma");
  man->CreateNtupleDColumn("E");
  man->CreateNtupleDColumn("CopyNo");
  man->FinishNtuple(0);
}

runAction::~runAction() {}

void runAction::BeginOfRunAction(const G4Run* run) {
  man = G4AnalysisManager::Instance();
  man->OpenFile(Form("Gamma_R%05i.root", (int) run->GetRunID()));
}

void runAction::EndOfRunAction(const G4Run*) {
  man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile();
}

