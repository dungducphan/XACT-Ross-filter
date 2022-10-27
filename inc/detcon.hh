#pragma once

#include <utility>
#include <tuple>
#include <fstream>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SDManager.hh"

#include "TMath.h"

#include "gammasd.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class detcon : public G4VUserDetectorConstruction {
  public:
    detcon();
    virtual ~detcon();

    virtual G4VPhysicalVolume* Construct();
    virtual G4VPhysicalVolume* BuildRossFilter();

    virtual void ConstructSDandField();
private:

    G4LogicalVolume *logicWorld;

    G4Material* worldMat;
    G4Material* ross_Pair0_0;
    G4Material* ross_Pair0_1;
    G4Material* ross_Pair2_1;
    G4Material* ross_Pair2_0;
    G4Material* ross_Pair1_0;
    G4Material* ross_Pair1_1;

    G4double rossThickness_Pair0_0;
    G4double rossThickness_Pair0_1;
    G4double rossThickness_Pair1_0;
    G4double rossThickness_Pair1_1;
    G4double rossThickness_Pair2_0;
    G4double rossThickness_Pair2_1;

    G4Tubs* solidRoss_Pair0_0;
    G4Tubs* solidRoss_Pair0_1;
    G4Tubs* solidRoss_Pair1_0;
    G4Tubs* solidRoss_Pair1_1;
    G4Tubs* solidRoss_Pair2_0;
    G4Tubs* solidRoss_Pair2_1;

    G4LogicalVolume* logicRoss_Pair0_0;
    G4LogicalVolume* logicRoss_Pair0_1;
    G4LogicalVolume* logicRoss_Pair1_0;
    G4LogicalVolume* logicRoss_Pair1_1;
    G4LogicalVolume* logicRoss_Pair2_0;
    G4LogicalVolume* logicRoss_Pair2_1;

    G4Tubs* solidRossFilter;
    G4LogicalVolume* logicRossFilter;
    G4VPhysicalVolume* physRossFilter;

    G4Tubs* solidDet;
    G4Tubs* solidDetTotal;
    G4LogicalVolume* logicDet;
    G4LogicalVolume* logicDetTotal;
};
