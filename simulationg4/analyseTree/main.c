#include <iostream>
#include "Reader.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"


int main()
{

  TH2F*pulseintegral=new TH2F("pulseintegral","",30,0,30,1e6,0,1e8);
  TH2F*ampl=new TH2F("ampl","",30,0,30,1500,0,1000000);
  TH2F*amplPhi=new TH2F("amplPhi","",64,0,3.2,500,0,1000000);
  TH2F*amplCosTheta=new TH2F("amplCosTheta","",20,-1,1,500,0,1000000);
  TH2F*risetime=new TH2F("risetime","",30,0,30,200,0,1500);
  TH2F*pulsewidth=new TH2F("pulsewidth","",30,0,30,200,0,1500);
  TH2F*risetimeAmpl=new TH2F("risetimeAmpl","",500,0,1000000,500,0,1500);

  Reader myreader;
  long int nentries=myreader.fChain->GetEntries();
  TTree *tree = myreader.fChain;
  TFile*f=new TFile("outputAnalysis.root","RECREATE");
  TTree *newTree = tree->CloneTree(0);
  double max = 0;
  TBranch *amplBranch = newTree->Branch("Amplitude", &max, "Amplitude/D");
  double riseTime = 0;
  TBranch *risetimeBranch = newTree->Branch("RiseTime", &riseTime, "RiseTime/D");
  double pulseWidth = 0;
  TBranch *pulsewidthBranch = newTree->Branch("PulseWidth", &pulseWidth, "PulseWidth/D");
  double pulseIntegral = 0;
  TBranch *pulseIntegralBranch = newTree->Branch("PulseIntegral", &pulseIntegral, "PulseIntegral/D");
  for(int ientry=0;ientry<nentries;ientry++)
    {
      myreader.GetEntry(ientry);

      double r0 = myreader.InitialParticleRadius->at(0);

      TH1F*h=new TH1F("h","",10416,0,10416*0.48);
      for(int i=0;i<myreader.Pulse->size();i++)
	h->SetBinContent(i+1,myreader.Pulse->at(i));

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

      pulseIntegral = h->Integral();
      std::cout << max << " " << pulseIntegral<<" "<< t2-t1<<" "<< risetime2-risetime1<< " "<< r0<<std::endl;
      ampl->Fill(r0,max);
      amplCosTheta->Fill(myreader.InitialParticleCosTheta->at(0),max);
      amplPhi->Fill(myreader.InitialParticlePhi->at(0),max);
      risetime->Fill(r0,risetime2-risetime1);
      pulsewidth->Fill(r0,t2-t1);
      pulseintegral->Fill(r0,pulseIntegral);
      risetimeAmpl->Fill(max, risetime2-risetime1);

      newTree->Fill();
      delete h;
    }
  newTree->SetBranchStatus("*", 1);
  ampl->Write();
  amplPhi->Write();
  amplCosTheta->Write();
  risetime->Write();
  pulsewidth->Write();
  pulseintegral->Write();
  risetimeAmpl->Write();
  newTree->Write();
  f->Close();
  return 0;
}
