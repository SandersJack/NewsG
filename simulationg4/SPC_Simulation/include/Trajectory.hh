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
 /// \file runAndEvent/RE04/include/RE04Trajectory.hh
 /// \brief Definition of the RE04Trajectory class
 //
 // $Id: $
 //
 #ifndef Trajectory_h
 #define Trajectory_h 1
 
 #include "G4VTrajectory.hh"
 #include "G4Allocator.hh"
 #include <stdlib.h>                 // Include from 'system'
 #include "G4ios.hh"                 // Include from 'system'
 #include <vector>                   // G4RWTValOrderedVector
 #include "globals.hh"               // Include from 'global'
 #include "G4ParticleDefinition.hh"  // Include from 'particle+matter'
 #include "TrajectoryPoint.hh"   // Include from 'tracking'
 #include "G4Track.hh"
 #include "G4Step.hh"
 
 class G4Polyline;                   // Forward declaration.
 
 typedef std::vector<G4VTrajectoryPoint*>  TrajectoryPointContainer;
 
 //
 /// User trajectory class
 ///
 /// - new, delete and "==" operators are overwritten
 ///
 /// - get functions
 ///     G4int GetTrackID() const, G4int GetParentID() const,
 ///     G4String GetParticleName() const, G4double GetCharge() const,
 ///     G4int GetPDGEncoding() const, G4double GetInitialKineticEnergy() const
 ///     and G4ThreeVector GetInitialMomentum() const
 ///
 /// - void ShowTrajectory(std::ostream& os=G4cout) const
 ///     invokes the default implementation
 ///
 /// - void DrawTrajectory() const
 ///     invokes the default implementation
 ///
 /// - void AppendStep(const G4Step* aStep)
 ///     adds a user trajectory point object, RE04TrajectoryPoint
 ///
 /// - int GetPointEntries() const
 ///     returns the number of point entries
 ///
 /// - G4VTrajectoryPoint* GetPoint(G4int i) const 
 ///     gets the i-th trajectory point
 ///
 /// - void MergeTrajectory(G4VTrajectory* secondTrajectory)
 ///     adds a trajectory to a TrajectoryPointContainer, fPositionRecord
 ///
 /// - G4ParticleDefinition* GetParticleDefinition()
 ///     get a particle definition from G4ParticleTable
 ///
 /// - const std::map<G4String,G4AttDef>* GetAttDefs() const
 ///    defines the track ID, the parent ID, the particle name, the charge,
 ///    the PDG encoding, the initial kinetic energy, the initial momentum,
 ///    the initial momentum magnitude and the number of points as attiributes 
 ///
 /// - std::vector<G4AttValue>* CreateAttValues() const
 ///    sets and returns the attributes
 //

class Trajectory : public G4VTrajectory
{ 
public: 
  
  // Constructor/Destrcutor
  
  Trajectory();
  explicit Trajectory(const G4Track* aTrack);
  explicit Trajectory(Trajectory &);
  virtual ~Trajectory();
 
  // Operators
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  inline int operator == (const Trajectory& right) const  {return (this==&right);} 
  
  // Get/Set functions 
  inline virtual G4int GetTrackID() const override                 {return fTrackID;}
  inline virtual G4int GetParentID() const override                {return fParentID;}
  inline virtual G4String GetParticleName() const override         {return fParticleName;}
  inline virtual G4double GetCharge() const override               {return fPDGCharge;}
  inline virtual G4int GetPDGEncoding() const override             {return fPDGEncoding;}
  inline virtual G4ThreeVector GetInitialMomentum() const override {return fInitialMomentum;}


  // Other member functions
  inline virtual int GetPointEntries() const override                 {return fPositionRecord->size();}
  inline virtual G4VTrajectoryPoint* GetPoint(G4int i) const override {return (*fPositionRecord)[i];}
 
  virtual void ShowTrajectory(std::ostream& os=G4cout) const override;
  //virtual void DrawTrajectory() const;
  virtual void DrawTrajectory() const override;
  virtual void AppendStep(const G4Step* aStep) override;
  virtual void MergeTrajectory(G4VTrajectory* secondTrajectory) override;
  
  virtual const std::map<G4String,G4AttDef>* GetAttDefs() const override;
  virtual std::vector<G4AttValue>* CreateAttValues() const override;
  
  // Non-override functions
  G4ParticleDefinition* GetParticleDefinition();
  inline virtual G4double GetInitialKineticEnergy() const {return fInitialKineticEnergy;}
  
private:
  TrajectoryPointContainer* fPositionRecord;
  G4int                     fTrackID;
  G4int                     fParentID;
  G4int                     fPDGEncoding;
  G4double                  fPDGCharge;
  G4String                  fParticleName;
  G4double                  fInitialKineticEnergy;
  G4ThreeVector             fInitialMomentum;
 };
 
extern G4ThreadLocal G4Allocator<Trajectory> * faTrajAllocator;

inline void* Trajectory::operator new(size_t)
{
  if(!faTrajAllocator) faTrajAllocator = new G4Allocator<Trajectory>;
  return (void*)faTrajAllocator->MallocSingle();
}

inline void Trajectory::operator delete(void* aTrajectory)
{
   faTrajAllocator->FreeSingle((Trajectory*)aTrajectory);
}

#endif