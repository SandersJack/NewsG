#define Analysis_cxx
#include "Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <iostream>
#include <vector>

 


void Analysis::Loop()
{
  //   In a ROOT session, you can do:
  //      root> .L Analysis.C
  //      root> Analysis t
  //      root> t.GetEntry(12); // Fill t data members with entry number 12
  //      root> t.Show();       // Show values of entry 12
  //      root> t.Show(16);     // Read and show values of entry 16
  //      root> t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  //TH1F* h = new TH1F("name","tile;xaxis;yaxis",nBins, xlow, xhigh);


  if (fChain == 0) return;

  
  /*std::vector<const char*> Histograms = {"h_nElec","h_nElecRadius","h_nElecPhi","h_nElecCosTheta","h_nElecTime","h_nIon","h_nIonRadius","h_nIonPhi","h_nIonCosTheta","h_nIonTime","h_nPulse","h_nSignal","h_nPulset","h_nSignalt"};
  for(int i=0;i<Histograms.size(); i++)
    {
      delete gROOT->FindObject(Histograms.at(i));
    }
  
  TH1F* h_nElec = new TH1F("h_nElec",";n_{Elec};",500,0,500);
  TH1F* h_nElecRadius = new TH1F("h_nElecRadius",";ElecRadius;",300,0,300);
  TH1F* h_nElecPhi = new TH1F("h_nElecPhi",";ElecPhi;",64,-3.2,3.2);
  TH1F* h_nElecCosTheta = new TH1F("h_nElecCosTheta",";ElecCosTheta;",100,-1,1);
  TH1F* h_nElecTime = new TH1F("h_nElecTime",";ElecTime;",100,0,1);
  TH1F* h_nIon = new TH1F("h_nIon",";n_{Ion};",500,0,500);
  TH1F* h_nIonRadius = new TH1F("h_nIonRadius",";IonRadius;",100,0,1);
  TH1F* h_nIonPhi = new TH1F("h_nIonPhi",";IonPhi;",64,-3.2,3.2);
  TH1F* h_nIonCosTheta = new TH1F("h_nIonCosTheta",";IonCosTheta;",100,-1,1);
  TH1F* h_nIonTime = new TH1F("h_nIonTime",";IonTime;",1000,0,500000);
  TH1F* h_nIonDriftTime = new TH1F("h_nIonDriftTime",";IonDriftTime;",300,0,3000e06);
  TH1F* h_nPulse = new TH1F("h_nPulse",";Pulse;",70,0,700);
  std::vector<double> nPulse;
  TH1F* h_nSignal = new TH1F("h_nSignal",";Signal;",100,-0.02,0);
  std::vector<double> nPulset;
  TH2F* h_nPulset = new TH2F("h_nPulset",";Time;Pulse",5000,0,50,1400,0,700);
  std::vector<double> nSignal;
  TH2F* h_nSignalt = new TH2F("h_nSignalt",";Time;Signal",2500,0,2.5e6,1000,-1,0);
  std::vector<double> nSignalt;
  

  std::vector<double> Amplitude;
  std::vector<double> RiseTime;*/
  
 
  

  
  // TFile*fileOut=new TFile("Output_from_bottom_signal_graph.root","RECREATE");

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      // if (jentry == 82 || jentry == 83)
      // 	continue;


      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      /* std::cout<< "This is event #"<<jentry << " out of "<< nentries<<std::endl;
      std::cout<< "We have "<<InitElecRadius->size()<<" electrons"<<std::endl;
      h_nElec->Fill(InitElecRadius->size());

      if(InitElecRadius->size() == 0) continue;
    
      for(int i=0;i<InitElecRadius->size();i++)
	{
	  if (InitElecRadius->at(i) == 0) break;
	  //std::cout<< i<< "Radius = "<< InitElecRadius->at(i)<<std::endl;
	  //std::cout<< i<< "Phi = "<< InitElecPhi->at(i)<<"\n";
	  //std::cout<< i<< "Cos(theta) = "<< InitElecCosTheta->at(i)<<"\n";
	  //std::cout<< i<< "Time =" <<InitElecTime->at(i)<<"\n";
	  h_nElecRadius->Fill(InitElecRadius->at(i));
	  h_nElecPhi->Fill(InitElecPhi->at(i));
	  h_nElecCosTheta->Fill(InitElecCosTheta->at(i));
	  h_nElecTime->Fill(InitElecTime->at(i));
	}

      std::cout<< "We have " <<InitIonRadius->size()<< " ions \n";
      h_nIon->Fill(InitIonRadius->size());

      for(int i=0;i<InitIonRadius->size();i++)
	{
	  // std::cout<< i<< "Radius = "<< InitIonRadius->at(i)<<std::endl;
	  //std::cout<< i<< "Phi = "<< InitIonPhi->at(i)<<"\n";
	  //std::cout<< i<< "Cos(theta) = "<< InitIonCosTheta->at(i)<<"\n";
	  // std::cout<< i<< "Time =" <<InitIonTime->at(i)<<"\n";
	  h_nIonRadius->Fill(InitIonRadius->at(i));
	  h_nIonPhi->Fill(InitIonPhi->at(i));
	  h_nIonCosTheta->Fill(InitIonCosTheta->at(i));
	  h_nIonTime->Fill(InitIonTime->at(i));
	  h_nIonDriftTime->Fill(FinIonTime->at(i)-InitIonTime->at(i));
	}
      std::cout<< "We have " << Pulse->size() << " pulses\n Max pulset =  " << Pulset->at(Pulset->size()-1) << "\n";
      std::cout<< "We have " << Signal->size() << " signals\n Max signalt =  " << Signalt->at(Signalt->size()-1) << "\n";


      
      for(int i=0;i<Pulse->size();i++)
	{
	  //std::cout<< "Pulse = " << Pulse << "\n";
	  h_nPulse->Fill(Pulse->at(i));
	  h_nPulset->Fill(Pulset->at(i),Pulse->at(i));
	  nPulse.push_back(Pulse->at(i));
	  nPulset.push_back(Pulset->at(i));
	}


       
      for(int i=0;i<Signal->size();i++)
	{
	  // std::cout<< "Signal = " << Signal << "\n";
	  h_nSignal->Fill(Signal->at(i));
	  h_nSignalt->Fill(Signalt->at(i),Signal->at(i));
	  nSignal.push_back(Signal->at(i));
	  nSignalt.push_back(Signalt->at(i));
	}

      char pulseFile[256];
      sprintf(pulseFile,"Pulse %lld", jentry);
      // h_nPulset->SetOption("colz");
      // h_nPulset->Draw();
      //h_nPulset->Write(pulseFile);
      TCanvas*c1=new TCanvas("c1","Pulse",600,600);
      TGraph*gr1=new TGraph(nPulse.size(),&(nPulset[0]),&(nPulse[0]));
      gr1->SetTitle("Pulse;Time;Pulse");
      gr1->GetXaxis()->SetRange(0,1500);
      gr1->Write(pulseFile);

      auto Index = std::max_element(nPulse.begin(),nPulse.end());
      std::cout << nPulse[std::distance(nPulse.begin(),Index)] << "\t nentries " << nentries << "\t entry " << jentry  <<  "\n";
      Amplitude.push_back(nPulse[std::distance(nPulse.begin(),Index)]);
      std::cout << nPulse[std::distance(nPulse.begin(),Index)] << "\n";
      std::cout << Amplitude.at(Amplitude.size() -1) << "\n";
      double Amp10 = Amplitude[Amplitude.size() -1]*0.1;
      double Amp90 = Amplitude[Amplitude.size() -1]*0.9;
      std::vector<double>::iterator Index10,Index90;
      Index10 = std::upper_bound(nPulset.begin(),nPulset.end(),Amp10);
      Index90 = std::upper_bound(nPulset.begin(),nPulset.end(),Amp90);
      double Time10 = nPulset[Index10-nPulset.begin()];
      double Time90 = nPulset[Index90-nPulset.begin()];
      RiseTime.push_back(Time90-Time10);
      std::cout<<"Amplitude = "<< Amplitude[Amplitude.size() -1] <<  " ,Rise Time = " << RiseTime[RiseTime.size() - 1] << "\n\n";



      h_nPulset->Reset("ICES");
      delete gr1;
      delete c1;
      nPulset.clear();
      nPulse.clear();
     
	  
       

			 char signalFile[256];
			 sprintf(signalFile, "Signal %lld", jentry);
			 // h_nSignalt->SetOption("colz");
			 //h_nSignalt->Draw();
			 //h_nSignalt->Write(signalFile);
			 TCanvas*c2=new TCanvas("c2","Signal",600,600);
			 TGraph*gr2=new TGraph(nSignal.size(),&(nSignalt[0]),&(nSignal[0]));
			 gr2->SetTitle("Signal;Time;Signal");
			 gr2->GetXaxis()->SetRange(0,500e03);
			 gr2->Write(signalFile);
			 h_nSignalt->Reset("ICES");
			 delete gr2;
			 delete c2;
			 nSignal.clear();
			 nSignalt.clear();*/
      
      
       
			 }
  /*TCanvas*c=new TCanvas("c","Amplitude Againt Rise Time",600,600);
  TGraph*gr=new TGraph(Amplitude.size(),&(Amplitude[0]),&(RiseTime[0]));
  gr->SetTitle(";Amplitude;Rise");
  gr->Draw();
  
  
   	    
	   TCanvas*c1=new TCanvas("c1","Number of electrons per event",600,600);
	     h_nElec->Draw();
	     TCanvas*c2=new TCanvas("c2","Initial electron radii",600,600);
	     h_nElecRadius->Draw();
	     TCanvas*c3=new TCanvas("c3","Initial electron phi",600,600);
	     h_nElecPhi->Draw();
	     TCanvas*c4=new TCanvas("c4","Initial electron cos(theta)",600,600);
	     h_nElecCosTheta->Draw();
	     TCanvas*c5=new TCanvas("c5","Initial electron time",600,600);
	     h_nElecTime->Draw();
	     TCanvas*c6=new TCanvas("c6","Number of ions per event",600,600);
	     h_nIon->Draw();
	     TCanvas*c7=new TCanvas("c7","Initial ion radii",600,600);
	     h_nIonRadius->Draw();
	     TCanvas*c8=new TCanvas("c8","Initial ion phi",600,600);
	     h_nIonPhi->Draw();
	     TCanvas*c9=new TCanvas("c9","Initial ion cos(theta)",600,600);
	     h_nIonCosTheta->Draw();
	     TCanvas*c10=new TCanvas("c10","Initial ion time",600,600);
	     h_nIonTime->Draw();
	     TCanvas*c11=new TCanvas("c11","Pulse",600,600);
	     h_nPulse->Draw();
	     TCanvas*c12=new TCanvas("c12","Signal",600,600);
	     h_nSignal->Draw();
	     TCanvas*c13=new TCanvas("c13","Signal against time",600,600);
	     h_nSignalt->SetOption("colz");
	     h_nSignalt->Draw();
	     TCanvas*c14=new TCanvas("c14","Pulse against time",600,600);
	     h_nPulset->SetOption("colz");
	     h_nPulset->Draw();
	     TCanvas*c15=new TCanvas("c15","Ion Drift Time",600,600);
	     h_nIonDriftTime->Draw();*/
   
   
    

   
	     /*h_nElec->Write();
	     h_nElecRadius->Write();
	     h_nElecPhi->Write();
	     h_nElecCosTheta->Write();
	     h_nElecTime->Write();
	     h_nIon->Write();
	     h_nIonRadius->Write();
	     h_nIonPhi->Write();
	     h_nIonCosTheta->Write();
	     h_nIonTime->Write();
	     h_nPulse->Write();
	     h_nPulset->Write();
	     h_nSignal->Write();
	     h_nSignalt->Write();
	fileOut->Close();*/
    
  
   
   
    }



















