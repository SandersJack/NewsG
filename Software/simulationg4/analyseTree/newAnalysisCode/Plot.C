#define Analysis_cxx
//#include "Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TGraph.h>
#include "TTree.h"
#include "Reader.h"
#include "TGaxis.h"

#include <iostream>
#include <fstream>
#include <vector>
 
int main(int argc, char** argv)
{
  TString fileName = "../";
  fileName+=argv[1];
  
  TFile* file = new TFile(fileName);
  TTree * tree = (TTree*)file->Get("simul");
  Reader myReader(tree); //Analysis a(tree);

  //TString newName = "../Complete_";
  //newName+=argv[1];
  //TFile*f=new TFile(newName,"RECREATE");
  //TTree *newTree = tree->CloneTree(0);
  double Amplitude = 0;
  //TBranch *amplBranch = newTree->Branch("Amplitude", &Amplitude, "Amplitude/D");
  double RiseTime = 0;
  //TBranch *risetimeBranch = newTree->Branch("RiseTime", &RiseTime, "RiseTime/D");
  double pulseWidth = 0;
  //TBranch *pulsewidthBranch = newTree->Branch("PulseWidth", &pulseWidth, "PulseWidth/D");
  double pulseIntegral = 0;
  //TBranch *pulseIntegralBranch = newTree->Branch("PulseIntegral", &pulseIntegral, "PulseIntegral/D");

  TString cos ("cosx");
  TString energy ("5.9keV");
  /* std::vector<const char*> Histograms = {"h_nElec","h_nElecRadius","h_nElecPhi","h_nElecCosTheta","h_nElecTime","h_nIon","h_nIonRadius","h_nIonPhi","h_nIonCosTheta","h_nIonTime","h_nPulse","h_nSignal","h_nPulset","h_nSignalt", "h_nIonTime"};
     for(int i=0;i<Histograms.size(); i++)
     {
     delete gROOT->FindObject(Histograms.at(i));
     }*/

    
  TFile*fileOutTime=new TFile("../Output_from_" + cos + "_" + energy + "_analysis/Time.root","Recreate");
  fileOutTime->Close();
  std::ofstream fileOutPara;
  fileOutPara.open ("../Output_from_" + cos + "_" + energy + "_analysis/Pulse_parameters.txt",std::ofstream::trunc);
  fileOutPara.close();
  TFile*fileOutPulse=new TFile("../Output_from_" + cos + "_" + energy + "_analysis/Pulse_and_signal.root","RECREATE");
  fileOutPulse->Close();
  
  TH1F* h_nElec = new TH1F("h_nElec",";n_{Elec};",500,0,500);
  TH1F* h_nElecRadius = new TH1F("h_nElecRadius",";ElecRadius;",300,0,300);
  TH1F* h_nElecPhi = new TH1F("h_nElecPhi",";ElecPhi;",64,-3.2,3.2);
  TH1F* h_nElecCosTheta = new TH1F("h_nElecCosTheta",";ElecCosTheta;",100,-1,1);
  TH1F* h_nElecTime = new TH1F("h_nElecTime",";ElecTime;",120,0,1.2);
  TH1F* h_nElecTime1Event = new TH1F("h_nElecTime1Event",";ElecTime;",100,0,1);
  TH1F* h_nIon = new TH1F("h_nIon",";n_{Ion};",500,0,500);
  TH1F* h_nIonRadius = new TH1F("h_nIonRadius",";IonRadius;",100,0,1);
  TH1F* h_nIonPhi = new TH1F("h_nIonPhi",";IonPhi;",64,-3.2,3.2);
  TH1F* h_nIonCosTheta = new TH1F("h_nIonCosTheta",";IonCosTheta;",100,-1,1);
  TH1F* h_nIonTime = new TH1F("h_nIonTime",";IonTime;",1000,0,1e6);
  TH1F* h_nIonTime1Event = new TH1F("h_nIonTime1Event",";IonTime;",1000,0,500000);
  TH1F* h_nIonDriftTime = new TH1F("h_nIonDriftTime",";IonDriftTime;",300,0,3000e06);

  TH1F* h_nPulse = new TH1F("h_nPulse",";Pulse;",100,0,100);
  TH1F* h_nPulse1Event = new TH1F("h_nPulse1Event",";Pulse;",100,0,50);
  std::vector<double> nPulse;
  TH1F* h_nSignal = new TH1F("h_nSignal",";Signal;",70,-7,0);
  std::vector<double> nPulset;
  TH2F* h_nPulset = new TH2F("h_nPulset",";Time;Pulse",500,0,2500,1000,0,5000);
  std::vector<double> nSignal;
  TH2F* h_nSignalt = new TH2F("h_nSignalt",";Time;Signal",7000,0,10e5,500,-70,0);
  std::vector<double> nSignalt;
  TH1F* h_nParameterGrad = new TH1F("h_nParameterGrad",";Gradient of exponential fit;",100,-0.0066,-0.0064);
  TH1F* h_nParameterConst = new TH1F("h_nParameterConst",";Const of exponential fit;",120,7,10);
  
  TH2F* h_nAmpRiseTime = new TH2F("h_nAmpRiseTime",";Amplitude;Rise Time;",1100,0,5500,200,0,200);
  TH1F* h_nPulseWidth = new TH1F("h_nPulseWidth",";Pulse Width;",100,0,1000);
  TH1F* h_nPulseIntegral = new TH1F("h_nPulseIntegral",";Integral:",100,0,2e6);
  // std::vector<double> Amplitude;
  //std::vector<double> RiseTime;

  

  Long64_t nentries = myReader.fChain->GetEntries();

  // Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      //     Long64_t ientry = LoadTree(jentry);
      //     if (ientry < 0) break;
      //     nb = fChain->GetEntry(jentry);   nbytes += nb;
      //     // if (Cut(ientry) < 0) continue;

      myReader.GetEntry(jentry);
      //std::cout<< "This is event #"<<jentry << " out of "<< nentries<<std::endl;
      //std::cout<< "We have "<<myReader.InitElecRadius->size()<<" electrons"<<std::endl;
      h_nElec->Fill(myReader.InitElecRadius->size());

      if(myReader.InitElecRadius->size() == 0) continue;

      //Fill electron histograms
      for(int i=0;i<myReader.InitElecRadius->size();i++)
	{
	  if (myReader.InitElecRadius->at(i) == 0) break;
	  h_nElecRadius->Fill(myReader.InitElecRadius->at(i));
	  h_nElecPhi->Fill(myReader.InitElecPhi->at(i));
	  h_nElecCosTheta->Fill(myReader.InitElecCosTheta->at(i));
	  h_nElecTime->Fill(myReader.InitElecTime->at(i));
	  if (jentry%100 ==0)
	    {
	      h_nElecTime1Event->Fill(myReader.InitElecTime->at(i));
	    }
	}

      //std::cout<< "We have " <<myReader.InitIonRadius->size()<< " ions \n";
      h_nIon->Fill(myReader.InitIonRadius->size());

      //Fill ion histograms
      for(int i=0;i<myReader.InitIonRadius->size();i++)
	{
	  h_nIonRadius->Fill(myReader.InitIonRadius->at(i));
	  h_nIonPhi->Fill(myReader.InitIonPhi->at(i));
	  h_nIonCosTheta->Fill(myReader.InitIonCosTheta->at(i));
	  h_nIonTime->Fill(myReader.InitIonTime->at(i));
	  if (jentry%100 ==0)
	    {
	      h_nIonTime1Event->Fill(myReader.InitIonTime->at(i));
	    }
	  h_nIonDriftTime->Fill(myReader.FinIonTime->at(i)-myReader.InitIonTime->at(i));
	}
      //std::cout<< "We have " << myReader.Pulse->size() << " pulses\n Max pulset =  " << myReader.Pulset->at(myReader.Pulset->size()-1) << "\n";
      //std::cout<< "We have " << myReader.Signal->size() << " signals\n Max signalt =  " << myReader.Signalt->at(myReader.Signalt->size()-1) << "\n";

      
      //Fill Pulse Graphs
      for(int i=0;i<myReader.Pulse->size();i++)
	{
	  //std::cout<< "Pulse = " << Pulse << "\n";
	  h_nPulse->Fill(myReader.Pulse->at(i));
	  h_nPulse1Event->Fill(myReader.Pulse->at(i));
	  h_nPulset->Fill(myReader.Pulset->at(i),myReader.Pulse->at(i));
	  nPulse.push_back(myReader.Pulse->at(i));
	  nPulset.push_back(myReader.Pulset->at(i));
	}


      //Fill signal graphs
      for(int i=0;i<myReader.Signal->size();i++)
	{
	  // std::cout<< "Signal = " << Signal << "\n";
	  h_nSignal->Fill(myReader.Signal->at(i));
	  h_nSignalt->Fill(myReader.Signalt->at(i),myReader.Signal->at(i));
	  nSignal.push_back(myReader.Signal->at(i));
	  nSignalt.push_back(myReader.Signalt->at(i));
	}

      //Amplitude against rise time Histogram

      /*double Amplitude= h_nPulse1Event->GetMaximum();
	int rt1 = h_nPulse1Event->FindFirstBinAbove(Amplitude*0.10);
	int rt2 = h_nPulse1Event->FindFirstBinAbove(Amplitude*0.90);
	double risetime1 = h_nPulse1Event->GetBinCenter(rt1);
	double risetime2 = h_nPulse1Event->GetBinCenter(rt2);
	double RiseTime = nPulset[risetime2] - nPulset[risetime1];
	h_nAmpRiseTime->Fill(Amplitude,RiseTime);
	h_nPulse1Event->Reset("ICES");*/
	  

      auto Index = std::max_element(nPulse.begin(),nPulse.end());
      int AmpIndex = std::distance(nPulse.begin(),Index);
      //std::cout << "AmpIndex: " <<AmpIndex<<"\n";
      Amplitude = nPulse[AmpIndex];
	  
      double Amp10 = Amplitude*0.1;
      double Amp90 = Amplitude*0.9;
      double Amp50 = Amplitude*0.5;

      int Index90;
      int Index10;
      int Index50_low;
      int Index50_high;
      
	  
      for (int i=0; i<nPulse.size(); i++)
	{
	  if (nPulse[i]<Amp10) continue;
	  else
	    Index10=i;
	  break;
	}
      for (int i=Index10; i<nPulse.size(); i++)
	{
	  if (nPulse[i]<Amp90) continue;
	  else
	    Index90=i;
	  break;
	}
      for (int i=0; i<nPulse.size(); i++)
	{
	  if (nPulse[i]<Amp50) continue;
	  else
	    Index50_low=i;
	  break;
	}
      for (int i=nPulse.size()-1; i>0; i--)
	{
	  if (nPulse[i]<Amp50) continue;
	  else
	    Index50_high=i;
	  break;
	}
	  
	  
      double Time10 = nPulset[Index10];
      double Time90 = nPulset[Index90];
      RiseTime =Time90-Time10;
      h_nAmpRiseTime->Fill(Amplitude,RiseTime);
      pulseWidth = nPulset[Index50_high]-nPulset[Index50_low];
      h_nPulseWidth->Fill(nPulset[Index50_high]-nPulset[Index50_low]);
      //std::cout<<"Event No."<<jentry<<"\n";
      pulseIntegral = h_nPulse1Event->Integral("width");
	  
      //h_nPulseIntegral->Fill(PulseIntegral);
	  

	  
	   if (jentry%500 ==0)
	{

	  
	  
	  std::cout<< "This is event #"<<jentry << " out of "<< nentries<<std::endl;
	  // std::cout<<"Amplitude = "<< Amplitude[Amplitude.size() -1] << ", " << Index10<<", " << Index90 << ", " << Time10 << ", " << Time90 <<  " ,Rise Time = " << RiseTime[RiseTime.size() - 1] << "\n\n";

	  //Inital electron and ion times for 1 event
	  TFile*fileOutTime=new TFile("../Output_from_" + cos + "_" + energy + "_analysis/Time.root","Update");
	  char elecTimeFile[256];
	  sprintf(elecTimeFile, "Elec_Event_%lld", jentry);
	  h_nElecTime1Event->Write(elecTimeFile);
	  h_nElecTime1Event->Reset("ICES");
	  char ionTimeFile[256];
	  sprintf(ionTimeFile, "Ion_Event_%lld", jentry);
	  h_nIonTime1Event->Write(ionTimeFile);
	  h_nIonTime1Event->Reset("ICES");

	  fileOutTime->Close();
	 

	  TFile*fileOutPulse=new TFile("../Output_from_" + cos + "_" + energy + "_analysis/Pulse_and_signal.root","Update");
	  //Signal graphs for each event
	  char signalFile[256];
	  sprintf(signalFile, "Signal_%lld", jentry);
	  TGraph*gr2=new TGraph(nSignal.size(),&(nSignalt[0]),&(nSignal[0]));
	  gr2->SetTitle("Signal;Time;Signal");
	  gr2->GetXaxis()->SetRange(0,100e03);
	  gr2->Write(signalFile);

	      
	  //Pulse graphs and fits for each event
	  char pulseFile[256];
	  sprintf(pulseFile,"Pulse_%lld", jentry);
	  TGraph*gr1=new TGraph(nPulse.size(),&(nPulset[0]),&(nPulse[0]));
	  gr1->SetTitle("Pulse;Time;Pulse");
	  gr1->GetXaxis()->SetRange(0,1500);
	  gr1->Draw();
	  auto Index = std::max_element(nPulse.begin(),nPulse.end());
	  double Range = nPulset[std::distance(nPulse.begin(),Index)];
	  TF1 *f1 = new TF1("f1",  "expo",Range + 40 ,1400);
	  gr1->Fit("f1","R");
	  f1->Draw("same");
	  gr1->Write(pulseFile);

	  
	 

	  fileOutPulse->Close();

	  //Pulse parameters
	  
	  std::vector<double> parameters;
	  parameters.push_back(f1->GetParameter(0));
	  parameters.push_back(f1->GetParameter(1));
	  h_nParameterGrad->Fill(parameters[1]);
	  h_nParameterConst->Fill(parameters[0]);
	  
	  fileOutPara.open ("../Output_from_" + cos + "_" + energy + "_analysis/Pulse_parameters.txt",std::ofstream::app);
	  if (fileOutPara.is_open())
	    {
       
	      fileOutPara << pulseFile << "\n";
	      fileOutPara << "y=e^(ax+b)";
	      fileOutPara << ": a = " << parameters[1] ;
	      fileOutPara << ", b = " << parameters[0] << "\n\n"; 
	      fileOutPara.close();
	    }
	  else std::cout << "Unable to open file";

	  parameters.clear();
	  delete gr1;
	  delete gr2;


	   
	}
     
       
	   
      nPulset.clear();
      nPulse.clear();
      nSignal.clear();
      nSignalt.clear();
      h_nPulse1Event->Reset("ICES");
      //newTree->Fill();
      }
  //newTree->SetBranchStatus("*", 1);
  //newTree->Write();
  //f->Close();
  std::cout << "Histograms\n";
      
   
      
  
  TFile*fileOutHistpdf=new TFile("../Output_from_" + cos + "_" + energy + "_analysis/Histograms/","Update");
   	    
  TCanvas*c1=new TCanvas("c1","Number of electrons per event",600,600);
  h_nElec->Draw();
  c1->SaveAs("Elec.pdf");
  TCanvas*c2=new TCanvas("c2","Initial electron radii",600,600);
  h_nElecRadius->Draw();
  c2->SaveAs("ElecRadius.pdf");
  TCanvas*c3=new TCanvas("c3","Initial electron phi",600,600);
  h_nElecPhi->Draw();
  c3->SaveAs("ElecPhi.pdf");
  TCanvas*c4=new TCanvas("c4","Initial electron cos(theta)",600,600);
  h_nElecCosTheta->Draw();
  c4->SaveAs("ElecCosTheta.pdf");
  TCanvas*c5=new TCanvas("c5","Initial electron time",600,600);
  h_nElecTime->Draw();
  c5->SaveAs("ElecTime.pdf");
  TCanvas*c6=new TCanvas("c6","Number of ions per event",600,600);
  h_nIon->Draw();
  c6->SaveAs("Ion.pdf");
  TCanvas*c7=new TCanvas("c7","Initial ion radii",600,600);
  h_nIonRadius->Draw();
  c7->SaveAs("IonRadius.pdf");
  TCanvas*c8=new TCanvas("c8","Initial ion phi",600,600);
  h_nIonPhi->Draw();
  c8->SaveAs("IonPhi.pdf");
  TCanvas*c9=new TCanvas("c9","Initial ion cos(theta)",600,600);
  h_nIonCosTheta->Draw();
  c8->SaveAs("IonCosTheta.pdf");
  TCanvas*c10=new TCanvas("c10","Initial ion time",600,600);
  h_nIonTime->Draw();
  c10->SaveAs("IonTime.pdf");
  TCanvas*c11=new TCanvas("c11","Pulse",600,600);
  h_nPulse->Draw();
  c11->SaveAs("Pulse.pdf");
  TCanvas*c12=new TCanvas("c12","Signal",600,600);
  h_nSignal->Draw();
  c12->SaveAs("Signal.pdf");
  TCanvas*c13=new TCanvas("c13","Signal against time",600,600);
  h_nSignalt->SetOption("colz");
  h_nSignalt->Draw();
  c13->SaveAs("Signalt.pdf");
  TCanvas*c14=new TCanvas("c14","Pulse against time",600,600);
  h_nPulset->SetOption("colz");
  h_nPulset->Draw();
  c14->SaveAs("Pulset.pdf");
  TCanvas*c15=new TCanvas("c15","Ion Drift Time",600,600);
  h_nIonDriftTime->Draw();
  c15->SaveAs("IonDriftTime.pdf");
  TCanvas*c16=new TCanvas("c16","Amplitdue Against Rise Time",600,600);
  h_nAmpRiseTime->SetOption("colz");
  h_nAmpRiseTime->Draw();
  c16->SaveAs("AmpRiseTime.pdf");
  TCanvas*c17=new TCanvas("c17","Pulse Parameter Gradient",600,600);
  TGaxis::SetMaxDigits(3);
  h_nParameterGrad->Draw();
  c17->SaveAs("PulseParameterGrad.pdf");
  TCanvas*c18=new TCanvas("c18","Pulse Parameter Constant",600,600);
  h_nParameterConst->Draw();
  c18->SaveAs("PulseParameterConst.pdf");
  TCanvas*c19=new TCanvas("c19","Pulse FWHM",600,600);
  h_nPulseWidth->Draw();
  c19->SaveAs("PulseWidth.pdf");
  //TCanvas*c20=new TCanvas("c20","Pulse Integral",600,600);
  //h_nPulseIntegral->Draw();
  //c20->SaveAs("PulseIntegral.pdf");

  fileOutHistpdf->Close();
      
   
  TFile*fileOutHist=new TFile("../Output_from_" + cos + "_" + energy + "_analysis/Histograms.root","RECREATE");
   
  //save histograms
  h_nElec->Write();
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
  h_nIonDriftTime->Write();
  h_nAmpRiseTime->Write();
  h_nParameterGrad->Write();
  h_nParameterConst->Write();
  h_nPulseWidth->Write();
  //h_nPulseIntegral->Write();
  fileOutHist->Close();



  return 0;
}
