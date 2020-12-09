//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: ExN02SteppingVerbose.cc 69899 2013-05-17 10:05:33Z gcosmo $
// 

#include "ExN02SteppingVerbose.hh"
#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

static FILE *fileOut = NULL;
static Float photonInitE = -1.f, photonLostE = -1.f;
static bool firstEventFound = false;

ExN02SteppingVerbose::ExN02SteppingVerbose()
{
	fileOut = fopen("events.dat", "w");	
}

ExN02SteppingVerbose::~ExN02SteppingVerbose()
{
	fclose(fileOut);
} 

void ExN02SteppingVerbose::StepInfo()
{
  CopyState();

  G4int prec = G4cout.precision(3);

  if ( fTrack->GetDefinition()->GetPDGEncoding() == 22 &&
       fTrack->GetTrackID() == 1 && photonInitE == -1.f) {
    photonInitE = fTrack->GetKineticEnergy();
  }

  if( fTrack->GetDefinition()->GetPDGEncoding() == 22 &&
      fTrack->GetVolume()->GetName() == "Target" &&
      fTrack->GetTrackID() == 1 && !firstEventFound) {

    firstEventFound = true;
    int eventType = 0;
    if( fStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()
        == "phot" ) { eventType = 1; }
    else if( fStep->GetPostStepPoint()->GetProcessDefinedStep()->
             GetProcessName() == "compt" ) { eventType = 2; }
    else if( fStep->GetPostStepPoint()->GetProcessDefinedStep()->
             GetProcessName() == "conv" ) { eventType = 3; }
    std::stringstream fileOutSS;
    fileOutSS
      << photonInitE << " "
      << eventType
      << G4endl;
    fprintf(fileOut, "%s", fileOutSS.str().c_str());

    G4cout << G4endl << "DEBUG: " << fileOutSS.str() << G4endl;
  }

  if( verboseLevel >= 1 ){
    if( verboseLevel >= 4 ) VerboseTrack();
    if( verboseLevel >= 3 ){
      G4cout
        << G4endl    
        << std::setw( 2) << "#"
        << std::setw(10) << "E"
        << std::setw(10) << "dE"
        << std::setw( 9) << "dx"
        << std::setw(17) << "dE/dx"
        << G4endl; 
    }

    G4cout
      << std::setw(2) << fTrack->GetCurrentStepNumber()
      << std::setw(6) << G4BestUnit(fTrack->GetKineticEnergy(),"Energy")
      << std::setw(6) << G4BestUnit(fStep->GetTotalEnergyDeposit(),"Energy")
      << std::setw(6) << G4BestUnit(fStep->GetStepLength(),"Length");

    const G4VProcess* process 
                      = fStep->GetPostStepPoint()->GetProcessDefinedStep();
    G4String procName = " UserLimit";
    if (process) procName = process->GetProcessName();
    if (fStepStatus == fWorldBoundary) procName = "OutOfWorld";
    G4cout << std::setw(15) << procName;
    G4cout << G4endl;

    if( verboseLevel == 2 ){
      G4int tN2ndariesTot = fN2ndariesAtRestDoIt +
                            fN2ndariesAlongStepDoIt +
                            fN2ndariesPostStepDoIt;
      if(tN2ndariesTot>0){
        G4cout << "\n    :----- List of secondaries ----------------"
               << G4endl;
        G4cout.precision(4);
        for(size_t lp1=(*fSecondary).size()-tN2ndariesTot; 
                        lp1<(*fSecondary).size(); lp1++){
          G4cout << "   "
                 << std::setw(13)                 
                 << (*fSecondary)[lp1]->GetDefinition()->GetParticleName()          
                 << ":  energy ="
                 << std::setw(6)
                 << G4BestUnit((*fSecondary)[lp1]->GetKineticEnergy(),"Energy")         
                 << "  time ="
                 << std::setw(6)
                 << G4BestUnit((*fSecondary)[lp1]->GetGlobalTime(),"Time");                                  
          G4cout << G4endl;
        }
              
        G4cout << "    :------------------------------------------\n"
               << G4endl;
      }
    }
    
  }
  G4cout.precision(prec);
}

void ExN02SteppingVerbose::TrackingStarted()
{
  CopyState();
  G4int prec = G4cout.precision(3);

  firstEventFound = false;
  photonInitE = -1.f;

  if( verboseLevel > 0 ){

    G4cout
      << std::setw( 2) << "#"
      << std::setw(10) << "E"
      << std::setw(10) << "dE"
      << std::setw( 9) << "dx"
      << std::setw(15) << "step"
      << G4endl;

    G4cout
      << std::setw( 2) << fTrack->GetCurrentStepNumber()
      << std::setw( 6) << G4BestUnit(fTrack->GetKineticEnergy(),"Energy")
      << std::setw( 6) << G4BestUnit(fStep->GetTotalEnergyDeposit(),"Energy")
      << std::setw( 6) << G4BestUnit(fStep->GetStepLength(),"Length")
      << std::setw(22) << "initStep"
      << G4endl;        
  }
  G4cout.precision(prec);
}

