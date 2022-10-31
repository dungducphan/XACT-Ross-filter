#include "detcon.hh"

detcon::detcon() : G4VUserDetectorConstruction(),
                   // FIXME: change thickness here
                   rossThickness_Pair0_0( 3.0*um),
                   rossThickness_Pair0_1( 1.5*um),
                   rossThickness_Pair1_0( 6.0*um),
                   rossThickness_Pair1_1( 4.0*um),
                   rossThickness_Pair2_0(15.0*um),
                   rossThickness_Pair2_1(14.0*um) {}

detcon::~detcon() {}

G4VPhysicalVolume *detcon::BuildRossFilter() {
    solidRoss_Pair0_0 = new G4Tubs("solidRoss_Pair0_0", 0, 1*cm, rossThickness_Pair0_0 / 2., 0., TMath::TwoPi()/6.);
    solidRoss_Pair0_1 = new G4Tubs("solidRoss_Pair0_1", 0, 1*cm, rossThickness_Pair0_1 / 2., 0., TMath::TwoPi()/6.);
    solidRoss_Pair1_0 = new G4Tubs("solidRoss_Pair1_0", 0, 1*cm, rossThickness_Pair1_0 / 2., 0., TMath::TwoPi()/6.);
    solidRoss_Pair1_1 = new G4Tubs("solidRoss_Pair1_1", 0, 1*cm, rossThickness_Pair1_1 / 2., 0., TMath::TwoPi()/6.);
    solidRoss_Pair2_0 = new G4Tubs("solidRoss_Pair2_0", 0, 1*cm, rossThickness_Pair2_0 / 2., 0., TMath::TwoPi()/6.);
    solidRoss_Pair2_1 = new G4Tubs("solidRoss_Pair2_1", 0, 1*cm, rossThickness_Pair2_1 / 2., 0., TMath::TwoPi()/6.);

    logicRoss_Pair0_0 = new G4LogicalVolume(solidRoss_Pair0_0, ross_Pair0_0, "logicRoss_Pair0_0");
    logicRoss_Pair0_1 = new G4LogicalVolume(solidRoss_Pair0_1, ross_Pair0_1, "logicRoss_Pair0_1");
    logicRoss_Pair1_0 = new G4LogicalVolume(solidRoss_Pair1_0, ross_Pair1_0, "logicRoss_Pair1_0");
    logicRoss_Pair1_1 = new G4LogicalVolume(solidRoss_Pair1_1, ross_Pair1_1, "logicRoss_Pair1_1");
    logicRoss_Pair2_0 = new G4LogicalVolume(solidRoss_Pair2_0, ross_Pair2_0, "logicRoss_Pair2_0");
    logicRoss_Pair2_1 = new G4LogicalVolume(solidRoss_Pair2_1, ross_Pair2_1, "logicRoss_Pair2_1");

    solidRossFilter = new G4Tubs("solidRossFilter", 0, 1*cm, 100*um / 2., 0, TMath::TwoPi());
    logicRossFilter = new G4LogicalVolume(solidRossFilter, worldMat, "logicRossFilter");
    physRossFilter = new G4PVPlacement(0, G4ThreeVector(), logicRossFilter, "physRossFilter", logicWorld, false, 1000, true);
    G4RotationMatrix *rot = nullptr;
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Pair0_0, "physRoss_Pair0_0", logicRossFilter, false, 1001, true);
    rot = new G4RotationMatrix(TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Pair0_1, "physRoss_Pair0_1", logicRossFilter, false, 1002, true);
    rot = new G4RotationMatrix(2 * TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Pair1_0, "physRoss_Pair1_0", logicRossFilter, false, 1003, true);
    rot = new G4RotationMatrix(3 * TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Pair1_1, "physRoss_Pair1_1", logicRossFilter, false, 1004, true);
    rot = new G4RotationMatrix(4 * TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Pair2_0, "physRoss_Pair2_0", logicRossFilter, false, 1005, true);
    rot = new G4RotationMatrix(5 * TMath::TwoPi()/6., 0, 0);
    new G4PVPlacement(rot, G4ThreeVector(), logicRoss_Pair2_1, "physRoss_Pair2_1", logicRossFilter, false, 1006, true);

    return physRossFilter;
}

G4VPhysicalVolume *detcon::Construct() {
    G4NistManager *nist = G4NistManager::Instance();
    G4bool checkOverlaps = true;

    // Ross filter materials
    // FIXME: change material here
    ross_Pair0_0 = nist->FindOrBuildMaterial("G4_Mg");
    ross_Pair0_1 = nist->FindOrBuildMaterial("G4_Al");
    ross_Pair1_0 = nist->FindOrBuildMaterial("G4_Ti");
    ross_Pair1_1 = nist->FindOrBuildMaterial("G4_V");
    ross_Pair2_0 = nist->FindOrBuildMaterial("G4_Ni");
    ross_Pair2_1 = nist->FindOrBuildMaterial("G4_Cu");

    G4Material* mylar = nist->FindOrBuildMaterial("G4_MYLAR");

    // World
    G4double worldSize = 5 * cm;
    worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * worldSize, 0.5 * worldSize, 0.5 * worldSize);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0,
                                                     checkOverlaps);

    // Ross-Filter
    // FIXME: Adding Ross filters here
    // BuildRossFilter();

    // Mylar window
    G4Tubs* solidWindow = new G4Tubs("solidWindow", 0, 1*cm, 50*um, 0, TMath::TwoPi());
    G4LogicalVolume* logicWindow = new G4LogicalVolume(solidWindow, mylar, "logicWindow");
    // FIXME: Adding mylar window here
    // G4VPhysicalVolume* physWindow = new G4PVPlacement(0, G4ThreeVector(0, 0, 1*mm), logicWindow, "physWindow", logicWorld, false, 0, checkOverlaps);

    // X-ray detector
    solidDet = new G4Tubs("solidDet", 0, 1*cm, 10*um, 0, TMath::TwoPi()/6.);
    solidDetTotal = new G4Tubs("solidDetTotal", 0, 1*cm, 10*um, 0, TMath::TwoPi());
    logicDet = new G4LogicalVolume(solidDet, worldMat, "logicDet");
    logicDetTotal = new G4LogicalVolume(solidDetTotal, worldMat, "logicDetTotal");
    G4VPhysicalVolume* physDetTotal = new G4PVPlacement(0, G4ThreeVector(0, 0, -1*mm), logicDetTotal, "physDetTotal", logicWorld, false, 5000, checkOverlaps);

    G4VPhysicalVolume* physDet_Pair0_0 = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicDet, "physDet_Pair0_0", logicDetTotal, false, 5001, checkOverlaps);
    G4RotationMatrix *rot = new G4RotationMatrix(TMath::TwoPi()/6., 0, 0);
    G4VPhysicalVolume* physDet_Pair0_1 = new G4PVPlacement(rot, G4ThreeVector(0, 0, 0), logicDet, "physDet_Pair0_1", logicDetTotal, false, 5002, checkOverlaps);
    rot = new G4RotationMatrix(2 * TMath::TwoPi()/6., 0, 0);
    G4VPhysicalVolume* physDet_Pair1_0 = new G4PVPlacement(rot, G4ThreeVector(0, 0, 0), logicDet, "physDet_Pair1_0", logicDetTotal, false, 5003, checkOverlaps);
    rot = new G4RotationMatrix(3 * TMath::TwoPi()/6., 0, 0);
    G4VPhysicalVolume* physDet_Pair1_1 = new G4PVPlacement(rot, G4ThreeVector(0, 0, 0), logicDet, "physDet_Pair1_1", logicDetTotal, false, 5004, checkOverlaps);
    rot = new G4RotationMatrix(4 * TMath::TwoPi()/6., 0, 0);
    G4VPhysicalVolume* physDet_Pair2_0 = new G4PVPlacement(rot, G4ThreeVector(0, 0, 0), logicDet, "physDet_Pair2_0", logicDetTotal, false, 5005, checkOverlaps);
    rot = new G4RotationMatrix(5 * TMath::TwoPi()/6., 0, 0);
    G4VPhysicalVolume* physDet_Pair2_1 = new G4PVPlacement(rot, G4ThreeVector(0, 0, 0), logicDet, "physDet_Pair2_1", logicDetTotal, false, 5006, checkOverlaps);

    return physWorld;
}

void detcon::ConstructSDandField() {
    const G4String name = "GammaSD";
    GammaSD *sd = new GammaSD(name);
    G4SDManager::GetSDMpointer()->AddNewDetector(sd);
    SetSensitiveDetector(logicDet, sd);
}

