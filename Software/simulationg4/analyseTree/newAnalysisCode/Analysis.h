//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 31 11:18:04 2019 by ROOT version 6.16/00
// from TTree simul/energy
// found on file: ./analyseTree/outputAnalysis.root
//////////////////////////////////////////////////////////

#ifndef Analysis_h
#define Analysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class Analysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<int>     *InitialParticleType;
   vector<double>  *InitialParticleEnergy;
   vector<double>  *InitialParticleRadius;
   vector<double>  *InitialParticleCosTheta;
   vector<double>  *InitialParticlePhi;
   vector<double>  *InitialParticleTime;
   vector<double>  *InitialParticleDirRad;
   vector<double>  *InitialParticleDirCosTheta;
   vector<double>  *InitialParticleDirPhi;
   vector<double>  *InitialParticleDirX;
   vector<double>  *InitialParticleDirY;
   vector<double>  *InitialParticleDirZ;
   vector<double>  *InitElecRadius;
   vector<double>  *InitElecPhi;
   vector<double>  *InitElecCosTheta;
   vector<double>  *InitElecTime;
   vector<double>  *InitIonRadius;
   vector<double>  *InitIonPhi;
   vector<double>  *InitIonCosTheta;
   vector<double>  *InitIonTime;
   vector<double>  *FinElecRadius;
   vector<double>  *FinElecPhi;
   vector<double>  *FinElecCosTheta;
   vector<double>  *FinElecTime;
   vector<double>  *FinIonRadius;
   vector<double>  *FinIonPhi;
   vector<double>  *FinIonCosTheta;
   vector<double>  *FinIonTime;
   vector<double>  *IonCharge;
   vector<int>     *AvalancheSize;
   vector<double>  *Signal;
   vector<double>  *Signalt;
   vector<double>  *Pulse;
   vector<double>  *Pulset;
   vector<double>  *ElecDriftTime;
   vector<double>  *IonDriftTime;
   vector<int>     *NumInitElecs;
   vector<double>  *AverageGain;
   vector<double>  *IntegratedTownsend;
   vector<int>     *PrimaryProcess;
   vector<double>  *PrimaryDeltaEnergy;
   vector<double>  *PrimaryRadius;
   vector<double>  *PrimaryCosTheta;
   vector<double>  *PrimaryPhi;
   Double_t        Amplitude;
   Double_t        RiseTime;
   Double_t        PulseWidth;
   Double_t        PulseIntegral;

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
   TBranch        *b_Amplitude;   //!
   TBranch        *b_RiseTime;   //!
   TBranch        *b_PulseWidth;   //!
   TBranch        *b_PulseIntegral;   //!

   Analysis(TTree *tree=0);
   virtual ~Analysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analysis_cxx
Analysis::Analysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("./analyseTree/outputAnalysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("./analyseTree/outputAnalysis.root");
      }
      f->GetObject("simul",tree);

   }
   Init(tree);
}

Analysis::~Analysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analysis::LoadTree(Long64_t entry)
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

void Analysis::Init(TTree *tree)
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
   fChain->SetBranchAddress("Amplitude", &Amplitude, &b_Amplitude);
   fChain->SetBranchAddress("RiseTime", &RiseTime, &b_RiseTime);
   fChain->SetBranchAddress("PulseWidth", &PulseWidth, &b_PulseWidth);
   fChain->SetBranchAddress("PulseIntegral", &PulseIntegral, &b_PulseIntegral);
   Notify();
}

Bool_t Analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analysis_cxx