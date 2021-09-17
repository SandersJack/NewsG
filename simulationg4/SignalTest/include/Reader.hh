//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 14 15:37:02 2019 by ROOT version 6.16/00
// from TTree simul/energy
// found on file: output_proton_1+MeV_All.root
//////////////////////////////////////////////////////////

#ifndef Reader_h
#define Reader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class Reader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   std::vector<int>     *InitialParticleType;
   std::vector<double>  *InitialParticleEnergy;
   std::vector<double>  *InitialParticleRadius;
   std::vector<double>  *InitialParticleCosTheta;
   std::vector<double>  *InitialParticlePhi;
   std::vector<double>  *InitialParticleTime;
   std::vector<double>  *InitialParticleDirRad;
   std::vector<double>  *InitialParticleDirCosTheta;
   std::vector<double>  *InitialParticleDirPhi;
   std::vector<double>  *InitialParticleDirX;
   std::vector<double>  *InitialParticleDirY;
   std::vector<double>  *InitialParticleDirZ;
   std::vector<double>  *InitElecRadius;
   std::vector<double>  *InitElecPhi;
   std::vector<double>  *InitElecCosTheta;
   std::vector<double>  *InitElecTime;
   std::vector<double>  *InitIonRadius;
   std::vector<double>  *InitIonPhi;
   std::vector<double>  *InitIonCosTheta;
   std::vector<double>  *InitIonTime;
   std::vector<double>  *FinElecRadius;
   std::vector<double>  *FinElecPhi;
   std::vector<double>  *FinElecCosTheta;
   std::vector<double>  *FinElecTime;
   std::vector<double>  *FinIonRadius;
   std::vector<double>  *FinIonPhi;
   std::vector<double>  *FinIonCosTheta;
   std::vector<double>  *FinIonTime;
   std::vector<double>  *IonCharge;
   std::vector<int>     *AvalancheSize;
   std::vector<double>  *Signal;
   std::vector<double>  *Signalt;
   std::vector<double>  *Pulse;
   std::vector<double>  *Pulset;
   std::vector<double>  *ElecDriftTime;
   std::vector<double>  *IonDriftTime;
   std::vector<int>     *NumInitElecs;
   std::vector<double>  *AverageGain;
   std::vector<double>  *IntegratedTownsend;
   std::vector<int>     *PrimaryProcess;
   std::vector<double>  *PrimaryDeltaEnergy;
   std::vector<double>  *PrimaryRadius;
   std::vector<double>  *PrimaryCosTheta;
   std::vector<double>  *PrimaryPhi;
   std::vector<double>  *PrimaryEnergy;
   std::vector<double>  *PrimaryDeposit;
   std::vector<int>     *SecondaryProcess;
   std::vector<int>     *SecondaryParent;
   std::vector<int>     *SecondaryID;
   std::vector<double>  *SecondaryDeltaEnergy;
   std::vector<double>  *SecondaryRadius;
   std::vector<double>  *SecondaryCosTheta;
   std::vector<double>  *SecondaryPhi;

   // List of branches
   TBranch        *b_InitialParticleType;   //!
   TBranch        *b_InitialParticleEnergy;   //!
   TBranch        *b_InitialParticleRadius;   //!
   TBranch        *b_InitialParticleCosTheta;   //!
   TBranch        *b_InitialParticlePhi;   //!
   TBranch        *b_InitialParticleTime;   //!
   TBranch        *b_InitialParticleDirRad;   //!
   TBranch        *b_InitialParticleDirCosTheta;   //!
   TBranch        *b_InitialParticleDirPhi;   //!
   TBranch        *b_InitialParticleDirX;   //!
   TBranch        *b_InitialParticleDirY;   //!
   TBranch        *b_InitialParticleDirZ;   //!
   TBranch        *b_InitElecRadius;   //!
   TBranch        *b_InitElecPhi;   //!
   TBranch        *b_InitElecCosTheta;   //!
   TBranch        *b_InitElecTime;   //!
   TBranch        *b_InitIonRadius;   //!
   TBranch        *b_InitIonPhi;   //!
   TBranch        *b_InitIonCosTheta;   //!
   TBranch        *b_InitIonTime;   //!
   TBranch        *b_FinElecRadius;   //!
   TBranch        *b_FinElecPhi;   //!
   TBranch        *b_FinElecCosTheta;   //!
   TBranch        *b_FinElecTime;   //!
   TBranch        *b_FinIonRadius;   //!
   TBranch        *b_FinIonPhi;   //!
   TBranch        *b_FinIonCosTheta;   //!
   TBranch        *b_FinIonTime;   //!
   TBranch        *b_IonCharge;   //!
   TBranch        *b_AvalancheSize;   //!
   TBranch        *b_Signal;   //!
   TBranch        *b_Signalt;   //!
   TBranch        *b_Pulse;   //!
   TBranch        *b_Pulset;   //!
   TBranch        *b_ElecDriftTime;   //!
   TBranch        *b_IonDriftTime;   //!
   TBranch        *b_NumInitElecs;   //!
   TBranch        *b_AverageGain;   //!
   TBranch        *b_IntegratedTownsend;   //!
   TBranch        *b_PrimaryProcess;   //!
   TBranch        *b_PrimaryDeltaEnergy;   //!
   TBranch        *b_PrimaryRadius;   //!
   TBranch        *b_PrimaryCosTheta;   //!
   TBranch        *b_PrimaryPhi;   //!
   TBranch        *b_PrimaryEnergy;   //!
   TBranch        *b_PrimaryDeposit;   //!
   TBranch        *b_SecondaryProcess;   //!
   TBranch        *b_SecondaryParent;   //!
   TBranch        *b_SecondaryID;   //!
   TBranch        *b_SecondaryDeltaEnergy;   //!
   TBranch        *b_SecondaryRadius;   //!
   TBranch        *b_SecondaryCosTheta;   //!
   TBranch        *b_SecondaryPhi;   //!

   Reader(TTree *tree=0);
   virtual ~Reader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Reader_cxx
Reader::Reader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output_proton_1+MeV_All.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("output_proton_1+MeV_All.root");
      }
      f->GetObject("simul",tree);

   }
   Init(tree);
}

Reader::~Reader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Reader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Reader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Reader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   InitialParticleType = 0;
   InitialParticleEnergy = 0;
   InitialParticleRadius = 0;
   InitialParticleCosTheta = 0;
   InitialParticlePhi = 0;
   InitialParticleTime = 0;
   InitialParticleDirRad = 0;
   InitialParticleDirCosTheta = 0;
   InitialParticleDirPhi = 0;
   InitialParticleDirX = 0;
   InitialParticleDirY = 0;
   InitialParticleDirZ = 0;
   InitElecRadius = 0;
   InitElecPhi = 0;
   InitElecCosTheta = 0;
   InitElecTime = 0;
   InitIonRadius = 0;
   InitIonPhi = 0;
   InitIonCosTheta = 0;
   InitIonTime = 0;
   FinElecRadius = 0;
   FinElecPhi = 0;
   FinElecCosTheta = 0;
   FinElecTime = 0;
   FinIonRadius = 0;
   FinIonPhi = 0;
   FinIonCosTheta = 0;
   FinIonTime = 0;
   IonCharge = 0;
   AvalancheSize = 0;
   Signal = 0;
   Signalt = 0;
   Pulse = 0;
   Pulset = 0;
   ElecDriftTime = 0;
   IonDriftTime = 0;
   NumInitElecs = 0;
   AverageGain = 0;
   IntegratedTownsend = 0;
   PrimaryProcess = 0;
   PrimaryDeltaEnergy = 0;
   PrimaryRadius = 0;
   PrimaryCosTheta = 0;
   PrimaryPhi = 0;
   PrimaryEnergy = 0;
   PrimaryDeposit = 0;
   SecondaryProcess = 0;
   SecondaryParent = 0;
   SecondaryID = 0;
   SecondaryDeltaEnergy = 0;
   SecondaryRadius = 0;
   SecondaryCosTheta = 0;
   SecondaryPhi = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("InitialParticleType", &InitialParticleType, &b_InitialParticleType);
   fChain->SetBranchAddress("InitialParticleEnergy", &InitialParticleEnergy, &b_InitialParticleEnergy);
   fChain->SetBranchAddress("InitialParticleRadius", &InitialParticleRadius, &b_InitialParticleRadius);
   fChain->SetBranchAddress("InitialParticleCosTheta", &InitialParticleCosTheta, &b_InitialParticleCosTheta);
   fChain->SetBranchAddress("InitialParticlePhi", &InitialParticlePhi, &b_InitialParticlePhi);
   fChain->SetBranchAddress("InitialParticleTime", &InitialParticleTime, &b_InitialParticleTime);
   fChain->SetBranchAddress("InitialParticleDirRad", &InitialParticleDirRad, &b_InitialParticleDirRad);
   fChain->SetBranchAddress("InitialParticleDirCosTheta", &InitialParticleDirCosTheta, &b_InitialParticleDirCosTheta);
   fChain->SetBranchAddress("InitialParticleDirPhi", &InitialParticleDirPhi, &b_InitialParticleDirPhi);
   fChain->SetBranchAddress("InitialParticleDirX", &InitialParticleDirX, &b_InitialParticleDirX);
   fChain->SetBranchAddress("InitialParticleDirY", &InitialParticleDirY, &b_InitialParticleDirY);
   fChain->SetBranchAddress("InitialParticleDirZ", &InitialParticleDirZ, &b_InitialParticleDirZ);
   fChain->SetBranchAddress("InitElecRadius", &InitElecRadius, &b_InitElecRadius);
   fChain->SetBranchAddress("InitElecPhi", &InitElecPhi, &b_InitElecPhi);
   fChain->SetBranchAddress("InitElecCosTheta", &InitElecCosTheta, &b_InitElecCosTheta);
   fChain->SetBranchAddress("InitElecTime", &InitElecTime, &b_InitElecTime);
   fChain->SetBranchAddress("InitIonRadius", &InitIonRadius, &b_InitIonRadius);
   fChain->SetBranchAddress("InitIonPhi", &InitIonPhi, &b_InitIonPhi);
   fChain->SetBranchAddress("InitIonCosTheta", &InitIonCosTheta, &b_InitIonCosTheta);
   fChain->SetBranchAddress("InitIonTime", &InitIonTime, &b_InitIonTime);
   fChain->SetBranchAddress("FinElecRadius", &FinElecRadius, &b_FinElecRadius);
   fChain->SetBranchAddress("FinElecPhi", &FinElecPhi, &b_FinElecPhi);
   fChain->SetBranchAddress("FinElecCosTheta", &FinElecCosTheta, &b_FinElecCosTheta);
   fChain->SetBranchAddress("FinElecTime", &FinElecTime, &b_FinElecTime);
   fChain->SetBranchAddress("FinIonRadius", &FinIonRadius, &b_FinIonRadius);
   fChain->SetBranchAddress("FinIonPhi", &FinIonPhi, &b_FinIonPhi);
   fChain->SetBranchAddress("FinIonCosTheta", &FinIonCosTheta, &b_FinIonCosTheta);
   fChain->SetBranchAddress("FinIonTime", &FinIonTime, &b_FinIonTime);
   fChain->SetBranchAddress("IonCharge", &IonCharge, &b_IonCharge);
   fChain->SetBranchAddress("AvalancheSize", &AvalancheSize, &b_AvalancheSize);
   fChain->SetBranchAddress("Signal", &Signal, &b_Signal);
   fChain->SetBranchAddress("Signalt", &Signalt, &b_Signalt);
   fChain->SetBranchAddress("Pulse", &Pulse, &b_Pulse);
   fChain->SetBranchAddress("Pulset", &Pulset, &b_Pulset);
   fChain->SetBranchAddress("ElecDriftTime", &ElecDriftTime, &b_ElecDriftTime);
   fChain->SetBranchAddress("IonDriftTime", &IonDriftTime, &b_IonDriftTime);
   fChain->SetBranchAddress("NumInitElecs", &NumInitElecs, &b_NumInitElecs);
   fChain->SetBranchAddress("AverageGain", &AverageGain, &b_AverageGain);
   fChain->SetBranchAddress("IntegratedTownsend", &IntegratedTownsend, &b_IntegratedTownsend);
   fChain->SetBranchAddress("PrimaryProcess", &PrimaryProcess, &b_PrimaryProcess);
   fChain->SetBranchAddress("PrimaryDeltaEnergy", &PrimaryDeltaEnergy, &b_PrimaryDeltaEnergy);
   fChain->SetBranchAddress("PrimaryRadius", &PrimaryRadius, &b_PrimaryRadius);
   fChain->SetBranchAddress("PrimaryCosTheta", &PrimaryCosTheta, &b_PrimaryCosTheta);
   fChain->SetBranchAddress("PrimaryPhi", &PrimaryPhi, &b_PrimaryPhi);
   fChain->SetBranchAddress("PrimaryEnergy", &PrimaryEnergy, &b_PrimaryEnergy);
   fChain->SetBranchAddress("PrimaryDeposit", &PrimaryDeposit, &b_PrimaryDeposit);
   fChain->SetBranchAddress("SecondaryProcess", &SecondaryProcess, &b_SecondaryProcess);
   fChain->SetBranchAddress("SecondaryParent", &SecondaryParent, &b_SecondaryParent);
   fChain->SetBranchAddress("SecondaryID", &SecondaryID, &b_SecondaryID);
   fChain->SetBranchAddress("SecondaryDeltaEnergy", &SecondaryDeltaEnergy, &b_SecondaryDeltaEnergy);
   fChain->SetBranchAddress("SecondaryRadius", &SecondaryRadius, &b_SecondaryRadius);
   fChain->SetBranchAddress("SecondaryCosTheta", &SecondaryCosTheta, &b_SecondaryCosTheta);
   fChain->SetBranchAddress("SecondaryPhi", &SecondaryPhi, &b_SecondaryPhi);
   Notify();
}

Bool_t Reader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Reader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Reader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Reader_cxx