#include "detcon.hh"

detcon::detcon() : G4VUserDetectorConstruction(),
                   rossThickness_Ti(25*um),
                   rossThickness_Pd(8*um),
                   rossThickness_Ni(15*um),
                   rossThickness_Fe(25*um),
                   rossThickness_Al(6*um),
                   rossThickness_Mylar(63*um) {}

detcon::~detcon() {}

G4VPhysicalVolume *detcon::BuildRossFilter() {
    solidRoss = new G4Tubs("solidRoss", 0, 1*cm, rossThickness_Ti / 2., 0., TMath::TwoPi()/6.);

    logicRoss_Ti = new G4LogicalVolume(solidRoss, ross_Ti, "logicRoss_Ti");
    logicRoss_Pd = new G4LogicalVolume(solidRoss, ross_Pd, "logicRoss_Pd");
    logicRoss_Ni = new G4LogicalVolume(solidRoss, ross_Ni, "logicRoss_Ni");
    logicRoss_Fe = new G4LogicalVolume(solidRoss, ross_Fe, "logicRoss_Fe");
    logicRoss_Al = new G4LogicalVolume(solidRoss, ross_Al, "logicRoss_Al");
    logicRoss_Mylar = new G4LogicalVolume(solidRoss, ross_Mylar, "logicRoss_Mylar");

    solidRossFilter = new G4Tubs("solidRossFilter", 0, 1*cm, 100*um / 2., 0, TMath::TwoPi());
    logicRossFilter = new G4LogicalVolume(solidRossFilter, worldMat, "logicRossFilter");
    physRossFilter = new G4PVPlacement(0, G4ThreeVector(), logicRossFilter, "physRossFilter", logicWorld, false, 1000, true);
    new G4PVPlacement(0, G4ThreeVector(), logicRoss_Ti, "physRoss_Ti", logicRossFilter, false, 1001, true);
    G4RotationMatrix *rot = new G4RotationMatrix(TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Pd, "physRoss_Pd", logicRossFilter, false, 1002, true);
    rot = new G4RotationMatrix(2 * TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Ni, "physRoss_Ni", logicRossFilter, false, 1003, true);
    rot = new G4RotationMatrix(3 * TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Fe, "physRoss_Fe", logicRossFilter, false, 1004, true);
    rot = new G4RotationMatrix(4 * TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Al, "physRoss_Al", logicRossFilter, false, 1005, true);
    rot = new G4RotationMatrix(5 * TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Mylar, "physRoss_Mylar", logicRossFilter, false, 1006, true);

    return physRossFilter;
}

G4VPhysicalVolume *detcon::Construct() {
    G4NistManager *nist = G4NistManager::Instance();
    G4bool checkOverlaps = true;

    // Ross filter materials
    ross_Ti = nist->FindOrBuildMaterial("G4_Ti");
    ross_Pd = nist->FindOrBuildMaterial("G4_Pd");
    ross_Ni = nist->FindOrBuildMaterial("G4_Ni");
    ross_Fe = nist->FindOrBuildMaterial("G4_Fe");
    ross_Al = nist->FindOrBuildMaterial("G4_Al");
    ross_Mylar = nist->FindOrBuildMaterial("G4_MYLAR");

    // World
    G4double worldSize = 5 * cm;
    worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * worldSize, 0.5 * worldSize, 0.5 * worldSize);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0,
                                                     checkOverlaps);

    BuildRossFilter();

    return physWorld;
}

