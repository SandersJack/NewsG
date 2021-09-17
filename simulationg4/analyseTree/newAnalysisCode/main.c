#include <iostream>
#include "Reader.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TCanvas.h"


int main(int argc, char** argv)
{
  TString fileName = "../";
  fileName+=argv[1];
  TFile *file = new TFile(fileName);
  TTree *tree = (TTree*)file->Get("simul");
  Reader myreader(tree);
  long int nentries=myreader.fChain->GetEntries();
  TString newName = "../Complete_";
  newName+=argv[1];
  TFile *f=new TFile(newName,"RECREATE");
  TTree *newTree = tree->CloneTree(0);
  double max = 0;
  TBranch *amplBranch = newTree->Branch("Amplitude", &max, "Amplitude/D");
  double signalIntegral = 0;
  TBranch *signalIntegralBranch = newTree->Branch("SignalIntegral", &signalIntegral, "SignalIntegral/D");
  double riseTime = 0;
  TBranch *risetimeBranch = newTree->Branch("RiseTime", &riseTime, "RiseTime/D");
  double pulseWidth = 0;
  TBranch *pulsewidthBranch = newTree->Branch("PulseWidth", &pulseWidth, "PulseWidth/D");
  double pulseIntegral = 0;
  TBranch *pulseIntegralBranch = newTree->Branch("PulseIntegral", &pulseIntegral, "PulseIntegral/D");
  double secondaryDeltaEnergyTotal = 0;
  TBranch *secondaryDeltaEnergyTotalBranch = newTree->Branch("SecondaryDeltaEnergyTotal", &secondaryDeltaEnergyTotal, "SecondaryDeltaEnergyTotal/D");
  for(int ientry=0; ientry<nentries; ientry++)
    {
      if(ientry%100==0)
	std::cout << "doing entry " << ientry << " out of " << nentries << std::endl;
      myreader.GetEntry(ientry);

      double r0 = myreader.InitialParticleRadius->at(0);

      TH1F*h=new TH1F("h","",10416,0,10416*0.48);
      for(int i=0;i<myreader.Pulse->size();i++)
	h->SetBinContent(i+1,myreader.Pulse->at(i));

      TH1F*hSignal=new TH1F("hSignal", "", 50000,0,500);
      for(int i=0;i<myreader.Signal->size();i++)
	{
	  if(myreader.Signal->at(i)<-500)
	    std::cout << "missed one, value is " <<myreader.Signal->at(i) << std::endl;;
	  hSignal->SetBinContent(i+1, -1*myreader.Signal->at(i));
	}

      max= h->GetMaximum();
      int fwhm1 = h->FindFirstBinAbove(max*0.50);
      int fwhm2 = h->FindLastBinAbove(max*0.50);
      double t1 = h->GetBinCenter(fwhm1);
      double t2 = h->GetBinCenter(fwhm2);
      pulseWidth = t2-t1;


      int rt1 = h->FindFirstBinAbove(max*0.10);
      int rt2 = h->FindFirstBinAbove(max*0.90);
      double risetime1 = h->GetBinCenter(rt1);
      double risetime2 = h->GetBinCenter(rt2);
      riseTime = risetime2 - risetime1;

      signalIntegral = hSignal->Integral();
      pulseIntegral = h->Integral();

      secondaryDeltaEnergyTotal = 0;
      for(unsigned int i=0; i<myreader.SecondaryDeltaEnergy->size(); i++)
	secondaryDeltaEnergyTotal+=myreader.SecondaryDeltaEnergy->at(i);
      
      newTree->Fill();
      delete h;
      delete hSignal;
    }
  newTree->SetBranchStatus("*", 1);
  newTree->Write();
  TTree *meta = (TTree*)file->Get("treeMetadata");
  TTree *newMeta = meta->CloneTree();
  newMeta->Write();
  f->Close();
  file->Close();
  return 0;
}
