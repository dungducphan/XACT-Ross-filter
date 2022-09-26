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

class G4VPhysicalVolume;
class G4LogicalVolume;

class detcon : public G4VUserDetectorConstruction {
  public:
    detcon();
    virtual ~detcon();

    virtual G4VPhysicalVolume* Construct();
    virtual G4VPhysicalVolume* BuildRossFilter();
private:

    G4LogicalVolume *logicWorld;

    G4Material* worldMat;
    G4Material* ross_Ti;
    G4Material* ross_Pd;
    G4Material* ross_Mylar;
    G4Material* ross_Al;
    G4Material* ross_Ni;
    G4Material* ross_Fe;

    G4double rossThickness_Ti;
    G4double rossThickness_Pd;
    G4double rossThickness_Ni;
    G4double rossThickness_Fe;
    G4double rossThickness_Al;
    G4double rossThickness_Mylar;

    G4Tubs* solidRoss;

    G4LogicalVolume* logicRoss_Ti;
    G4LogicalVolume* logicRoss_Pd;
    G4LogicalVolume* logicRoss_Ni;
    G4LogicalVolume* logicRoss_Fe;
    G4LogicalVolume* logicRoss_Al;
    G4LogicalVolume* logicRoss_Mylar;

    G4Tubs* solidRossFilter;
    G4LogicalVolume* logicRossFilter;
    G4VPhysicalVolume* physRossFilter;
};
