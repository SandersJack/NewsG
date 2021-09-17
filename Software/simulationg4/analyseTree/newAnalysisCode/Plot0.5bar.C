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

#include <iostream>
#include <fstream>
#include <vector>
#include "TVector3.h"
 
int main()
{
  TString fileName = "/disk/moose/general/user149/output_gamma_5.9+keV_spherical+29+0.5+0+cm_radial_5000_20190805.root";
  // TString fileName = "./analyseTree/outputAnalysis.root";
  
  TFile* file = new TFile(fileName);
  TTree * tree = (TTree*)file->Get("simul");
  Reader myReader(tree); //Analysis a(tree);

  TString cos ("cos0.5_tube");
  TString energy ("5.9keV");
  
  
  //Clears existing pulse and time files
    
  TFile*fileOutTime=new TFile("./Output_from_" + cos + "_" + energy + "_analysis/Time.root","Recreate");
  fileOutTime->Close();
  std::ofstream fileOutPara;
  fileOutPara.open ("./Output_from_" + cos + "_" + energy + "_analysis/Pulse_parameters.txt",std::ofstream::trunc);
  fileOutPara.close();
  TFile*fileOutPulse=new TFile("./Output_from_" + cos + "_" + energy + "_analysis/Pulse_and_signal.root","RECREATE");
  fileOutPulse->Close();
 
  // Makes Histograms
  
  THStack* h_nElec = new THStack("h_nElec",";Number of Electrons;");
  TH1F* h_nElec1 = new TH1F("h_nElec1",";Number of Electrons;",250,0,500);
  TH1F* h_nElec2 = new TH1F("h_nElec2",";Number of Electrons;",250,0,500);
  TH1F* h_nElec3 = new TH1F("h_nElec3",";Number of Electrons;",250,0,500);
  TH1F* h_nElec4 = new TH1F("h_nElec4",";Number of Electrons;",250,0,500);
  TH1F* h_nElec5 = new TH1F("h_nElec5",";Number of Electrons;",250,0,500);

  TH1F* h_nElecRadius = new TH1F("h_nElecRadius",";ElecRadius;",300,0,300);
  TH1F* h_nElecPhi = new TH1F("h_nElecPhi",";ElecPhi;",128,-3.2,3.2);
  TH1F* h_nElecCosTheta = new TH1F("h_nElecCosTheta",";ElecCosTheta;",100,-1,1);

  TH2F* h_nInitElecPos = new TH2F("h_nInitElecPos",";x;y",300,0,300,300,-50,250);
  TH2F* h_nInitElecPos1 = new TH2F("h_nInitElecPos1",";x;y",300,0,300,300,-50,250);
  TH2F* h_nInitElecPos2 = new TH2F("h_nInitElecPos2",";x;y",300,0,300,300,-50,250);
  TH2F* h_nInitElecPos3 = new TH2F("h_nInitElecPos3",";x;y",300,0,300,300,-50,250);
  TH2F* h_nInitElecPos4 = new TH2F("h_nInitElecPos4",";x;y",300,0,300,300,-50,250);
  TH2F* h_nInitElecPos5 = new TH2F("h_nInitElecPos5",";x;y",300,0,300,300,-50,250);
  
  TH1F* h_nElecTime = new TH1F("h_nElecTime",";ElecTime;",120,0,1.2);
  TH1F* h_nElecTime1Event = new TH1F("h_nElecTime1Event",";ElecTime;",100,0,1);

  TH1F* h_nIon = new TH1F("h_nIon",";n_{Ion};",500,0,500);
  TH1F* h_nIonRadius = new TH1F("h_nIonRadius",";IonRadius;",100,0,1);
  TH1F* h_nIonPhi = new TH1F("h_nIonPhi",";IonPhi;",128,-3.2,3.2);
  TH1F* h_nIonCosTheta = new TH1F("h_nIonCosTheta",";IonCosTheta;",100,-1,1);
  TH1F* h_nIonTime = new TH1F("h_nIonTime",";IonTime;",1000,0,1e6);
  TH1F* h_nIonTime1Event = new TH1F("h_nIonTime1Event",";IonTime;",1000,0,500000);
  TH1F* h_nIonDriftTime = new TH1F("h_nIonDriftTime",";IonDriftTime;",300,0,3000e06);

  TH1F* h_nPulse = new TH1F("h_nPulse",";Pulse;",100,0,100);
  std::vector<double> nPulse;
  TH1F* h_nSignal = new TH1F("h_nSignal",";Signal;",70,-7,0);
  std::vector<double> nPulset;
  TH2F* h_nPulset = new TH2F("h_nPulset",";Time;Pulse",1000,0,2500,1000,0,5000);
  std::vector<double> nSignal;
  TH2F* h_nSignalt = new TH2F("h_nSignalt",";Time;Signal",1000,0,10e5,700,-70,0);
  std::vector<double> nSignalt;
  
  
  TH1F* h_nParameterGrad = new TH1F("h_nParameterGrad",";Gradient of exponential fit;",100,-0.0066,-0.0064);
  TH1F* h_nParameterConst = new TH1F("h_nParameterConst",";Const of exponential fit;",120,7,10);
  
  TH2F* h_nAmpRiseTime = new TH2F("h_nAmpRiseTime",";Amplitude;Rise Time;",1100,0,5500,250,0,250);
  THStack* h_nPulseWidth = new THStack("h_nPulseWidth",";Pulse Width;");
  TH1F* h_nPulseWidth1 = new TH1F("h_nPulseWidth1",";Pulse Width;",200,0,1000);
  TH1F* h_nPulseWidth2 = new TH1F("h_nPulseWidth2",";Pulse Width;",200,0,1000);
  TH1F* h_nPulseWidth3 = new TH1F("h_nPulseWidth3",";Pulse Width;",200,0,1000);
  TH1F* h_nPulseWidth4 = new TH1F("h_nPulseWidth4",";Pulse Width;",200,0,1000);
  TH1F* h_nPulseWidth5 = new TH1F("h_nPulseWidth5",";Pulse Width;",200,0,1000);
  
  THStack* h_nPulseIntegral = new THStack("h_nPulseIntegral",";Integral");
  TH1F* h_nPulseIntegral1 = new TH1F("h_nPulseIntegral1",";Integral:",200,0,2e6);
  TH1F* h_nPulseIntegral2 = new TH1F("h_nPulseIntegral2",";Integral:",200,0,2e6);
  TH1F* h_nPulseIntegral3 = new TH1F("h_nPulseIntegral3",";Integral:",200,0,2e6);
  TH1F* h_nPulseIntegral4 = new TH1F("h_nPulseIntegral4",";Integral:",200,0,2e6);
  TH1F* h_nPulseIntegral5 = new TH1F("h_nPulseIntegral5",";Integral:",200,0,2e6);

  std::vector <double> CosTheta;
  std::vector <double> Radius;
  std::vector <double> SinTheta;

  int R1Events,R1Elec,R2Events,R2Elec,R3Events,R3Elec,R4Events,R4Elec,R5Elec,R5Events,RAllEvents,RAllElec;

  R1Events=0;
  R1Elec=0;
  R2Events=0;
  R2Elec=0;
  R3Events=0;
  R3Elec=0;
  R4Events=0;
  R4Elec=0;
  R5Events=0;
  R5Elec=0;
  
  RAllEvents=0;
  RAllElec=0;
  
  ////////////////////////////////////////////////////////////////////////////////////////////
  

  
  ////////////////////////////////////////////////////////////////////////////////////////////

  Long64_t nentries = myReader.fChain->GetEntries();

  // Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      //     Long64_t ientry = LoadTree(jentry);
      //     if (ientry < 0) break;
      //     nb = fChain->GetEntry(jentry);   nbytes += nb;
      //     // if (Cut(ientry) < 0) continue;

      myReader.GetEntry(jentry);
      if(myReader.InitElecRadius->size() == 0) continue;
      //if(jentry == 1000) break;
      

      ////////////////////////////////////////////////////////////////////////////////////////

      //Fill electron histograms
      for(int i=0;i<myReader.InitElecRadius->size();i++)
	{
	  if (myReader.InitElecRadius->at(i) == 0) break;
	   
	  //std::cout << myReader.InitElecCosTheta->at(i);
	  
	  CosTheta.push_back (myReader.InitElecCosTheta->at(i));
	  
	  Radius.push_back (myReader.InitElecRadius->at(i));
	  
	  SinTheta.push_back (sqrt(1 - pow(CosTheta[i],2)));
	  
	  h_nElecRadius->Fill(Radius[i]);
	  h_nElecPhi->Fill(myReader.InitElecPhi->at(i));
	  h_nElecCosTheta->Fill(CosTheta[i]);
	  h_nElecTime->Fill(myReader.InitElecTime->at(i));

	  //Time electrons are formed for 1 event
	  //if (jentry%100 ==0)
	  //{
	  //  h_nElecTime1Event->Fill(myReader.InitElecTime->at(i));
	  //}
	}
      
      
      //Fill Pulse Graphs
      double PulseIntegral = 0;
      for(int i=0;i<myReader.Pulse->size();i++)
	{
	  //Fill Histograms for all pulses
	  //std::cout<< "Pulse = " << Pulse << "\n";
	  h_nPulse->Fill(myReader.Pulse->at(i));
	  h_nPulset->Fill(myReader.Pulset->at(i),myReader.Pulse->at(i));

	  //Fill Vectors for individual pulses
	  nPulse.push_back(myReader.Pulse->at(i));
	  nPulset.push_back(myReader.Pulset->at(i));
	  PulseIntegral += myReader.Pulse->at(i);
	  
	}
      


      //Fill signal graphs
      for(int i=0;i<myReader.Signal->size();i++)
	{
	  //Fill Histograms for all signals
	  // std::cout<< "Signal = " << Signal << "\n";
	  h_nSignal->Fill(myReader.Signal->at(i));
	  h_nSignalt->Fill(myReader.Signalt->at(i),myReader.Signal->at(i));

	  //Fill vectors for individual signals
	  nSignal.push_back(myReader.Signal->at(i));
	  nSignalt.push_back(myReader.Signalt->at(i));
	}

      //Amplitude against rise time Histogram
	  

      auto Index = std::max_element(nPulse.begin(),nPulse.end());
      int AmpIndex = std::distance(nPulse.begin(),Index);//AmpIndex is the index of the max pulse
      double Amplitude = nPulse[AmpIndex];
	  
      double Amp10 = Amplitude*0.1;
      double Amp90 = Amplitude*0.9;
      double Amp50 = Amplitude*0.5;

      int Index90;
      int Index10;
      int Index50_low;
      int Index50_high;
      
      //Find time when pulse is 10% and 90% of maximum (rising edge)
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

      //Find time when pulse is 50% maximum for rising and falling edges
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
	  
      //Amp rise time histogram	  
      double Time10 = nPulset[Index10];
      double Time90 = nPulset[Index90];
      double RiseTime =Time90-Time10;
      h_nAmpRiseTime->Fill(Amplitude,RiseTime);
      
      // Initial electron position, number of electrons, pulse width and pulse integral histograms

     
      
      //Region 4
      if (RiseTime>110)
	{
	  R4Events += 1;
	  for (int elecNumber = 0; elecNumber<Radius.size(); elecNumber++)
	    {
	      R4Elec += 1;
	      h_nInitElecPos4->Fill(Radius[elecNumber]*SinTheta[elecNumber],Radius[elecNumber]*CosTheta[elecNumber]);
	    }
	  
	  h_nElec4->Fill(myReader.InitElecRadius->size());
	  h_nPulseWidth4->Fill(nPulset[Index50_high]-nPulset[Index50_low]);
	  h_nPulseIntegral4->Fill(PulseIntegral);
	}
       
      
      //Region 3
      else if (Amplitude>2550&& RiseTime>40)
	{
	  R3Events += 1;
	  for (int elecNumber = 0; elecNumber<Radius.size(); elecNumber++)
	    {
	      R3Elec += 1;
	      h_nInitElecPos3->Fill(Radius[elecNumber]*SinTheta[elecNumber],Radius[elecNumber]*CosTheta[elecNumber]);
	    }
	  h_nElec3->Fill(myReader.InitElecRadius->size());
	  h_nPulseWidth3->Fill(nPulset[Index50_high]-nPulset[Index50_low]);
	  h_nPulseIntegral3->Fill(PulseIntegral);
	}

      //Region 2
      else if (Amplitude>2800&& RiseTime<40)
	{
	  R2Events += 1;
	  for (int elecNumber = 0; elecNumber<Radius.size(); elecNumber++)
	    {
	      R2Elec += 1;
	      h_nInitElecPos2->Fill(Radius[elecNumber]*SinTheta[elecNumber],Radius[elecNumber]*CosTheta[elecNumber]);
	    }
	  h_nElec2->Fill(myReader.InitElecRadius->size());
	  h_nPulseWidth2->Fill(nPulset[Index50_high]-nPulset[Index50_low]);
	  h_nPulseIntegral2->Fill(PulseIntegral);
	}

      //Region 5
      else if (Amplitude < 500)
	{
	  R5Events += 1;
	  for (int elecNumber = 0; elecNumber<Radius.size(); elecNumber++)
	    {
	      R5Elec += 1;
	      h_nInitElecPos5->Fill(Radius[elecNumber]*SinTheta[elecNumber],Radius[elecNumber]*CosTheta[elecNumber]);
	    }
	  h_nElec5->Fill(myReader.InitElecRadius->size());
	  h_nPulseWidth5->Fill(nPulset[Index50_high]-nPulset[Index50_low]);
	  h_nPulseIntegral5->Fill(PulseIntegral);
	  }

      //Region 1
      else
	{
	  R1Events += 1;
	  for (int elecNumber = 0; elecNumber<Radius.size(); elecNumber++)
	    {
	      R1Elec += 1;
	      h_nInitElecPos1->Fill(Radius[elecNumber]*SinTheta[elecNumber],Radius[elecNumber]*CosTheta[elecNumber]);
	    }
	  h_nElec1->Fill(myReader.InitElecRadius->size());
	  h_nPulseWidth1->Fill(nPulset[Index50_high]-nPulset[Index50_low]);
	  h_nPulseIntegral1->Fill(PulseIntegral);
	}

 
      //Electron position for all regions
      for (int elecNumber = 0; elecNumber<Radius.size(); elecNumber++)
	{
	  h_nInitElecPos->Fill(Radius[elecNumber]*SinTheta[elecNumber],Radius[elecNumber]*CosTheta[elecNumber]);
	}	 


      //Pulse and Signal graphs for single events for a cut

      /*TFile*fileOutPulse=new TFile("./Output_from_" + cos + "_" + energy + "_analysis/Pulse_and_signal.root","Update");
      //Signal graphs for each event
      char signalFile[256];
      sprintf(signalFile, "Signal_%lld", jentry);
      TGraph*gr2=new TGraph(nSignal.size(),&(nSignalt[0]),&(nSignal[0]));
      gr2->SetTitle("Signal;Time;Signal");
      gr2->GetXaxis()->SetRange(0,500e03);
      gr2->Draw();
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

	  
	 

      fileOutPulseCut->Close();

      //Pulse parameters
	  
      std::vector<double> parameters;
      parameters.push_back(f1->GetParameter(0));
      parameters.push_back(f1->GetParameter(1));
      h_nParameterGrad->Fill(parameters[1]);
      h_nParameterConst->Fill(parameters[0]);
	  
      fileOutParaCut.open ("./Output_from_" + cos + "_" + energy + "_analysis/Pulse_parameters_cut.txt",std::ofstream::app);
      if (fileOutParaCut.is_open())
      {
       
      fileOutParaCut << pulseFile << "\n";
      fileOutParaCut << "y=e^(ax+b)";
      fileOutParaCut << ": a = " << parameters[1] ;
      fileOutParaCut << ", b = " << parameters[0] << "\n\n"; 
      fileOutParaCut.close();
      }
      else std::cout << "Unable to open file";

      parameters.clear();
      delete gr1;
      delete gr2;*/

	  
	
      
     

      
    
      //Fill ion histograms
      h_nIon->Fill(myReader.InitIonRadius->size());

      
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
          
     
   
	  

	  
      if (jentry%500 ==0)
	{

	  
	  
	  std::cout<< "This is event #"<<jentry << " out of "<< nentries<<std::endl;

	  //Pulse and Signal graphs for single events

	  /* 

	  //Inital electron and ion times for 1 event
	  TFile*fileOutTime=new TFile("./Output_from_" + cos + "_" + energy + "_analysis/Time.root","Update");
	  char elecTimeFile[256];
	  sprintf(elecTimeFile, "Elec_Event_%lld", jentry);
	  h_nElecTime1Event->Write(elecTimeFile);
	  h_nElecTime1Event->Reset("ICES");
	  char ionTimeFile[256];
	  sprintf(ionTimeFile, "Ion_Event_%lld", jentry);
	  h_nIonTime1Event->Write(ionTimeFile);
	  h_nIonTime1Event->Reset("ICES");

	  fileOutTime->Close();
	 

	  TFile*fileOutPulse=new TFile("./Output_from_" + cos + "_" + energy + "_analysis/Pulse_and_signal.root","Update");
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
	  
	  fileOutPara.open ("./Output_from_" + cos + "_" + energy + "_analysis/Pulse_parameters.txt",std::ofstream::app);
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
	  delete gr2;*/


	   
	}
     
      //clear vectors used for single events  

      nPulset.clear();
      nPulse.clear();
      nSignal.clear();
      nSignalt.clear();
      
      Radius.clear();
      CosTheta.clear();
      SinTheta.clear();
    }
 
  ////////////////////////////////////////////////////////////////////////////////////////////   
      
  
  TString fileOutHistpdf("./Output_from_" + cos + "_" + energy + "_analysis/Histograms/");
   	    
  TCanvas*c1=new TCanvas("c1","Number of electrons per event",600,600);
  h_nElec1->SetFillColor(kRed+1);
  h_nElec2->SetFillColor(kBlue+2);
  h_nElec3->SetFillColor(kGreen+1);
  h_nElec4->SetFillColor(kCyan+2);
  h_nElec5->SetFillColor(kMagenta+2);
  
  h_nElec->Add(h_nElec1);
  h_nElec->Add(h_nElec2);
  h_nElec->Add(h_nElec3);
  h_nElec->Add(h_nElec4);
  h_nElec->Add(h_nElec5);
  h_nElec->Draw();
  auto legendElec = new TLegend(0.6,0.7,0.9,0.9);
  legendElec->AddEntry(h_nElec1,"Region 1","f");
  legendElec->AddEntry(h_nElec2,"Region 2","f");
  legendElec->AddEntry(h_nElec3,"Region 3","f");
  legendElec->AddEntry(h_nElec4,"Region 4","f");
  legendElec->AddEntry(h_nElec5,"Region 5","f");
  legendElec->Draw();
  c1->SaveAs(fileOutHistpdf + "Elec.pdf");
  
  TCanvas*c2=new TCanvas("c2","Initial electron radii",600,600);
  h_nElecRadius->Draw();
  c2->SaveAs(fileOutHistpdf + "ElecRadius.pdf");
  TCanvas*c3=new TCanvas("c3","Initial electron phi",600,600);
  h_nElecPhi->Draw();
  c3->SaveAs(fileOutHistpdf + "ElecPhi.pdf");
  TCanvas*c4=new TCanvas("c4","Initial electron cos(theta)",600,600);
  h_nElecCosTheta->Draw();
  c4->SaveAs(fileOutHistpdf + "ElecCosTheta.pdf");
  TCanvas*c5=new TCanvas("c5","Initial electron time",600,600);
  h_nElecTime->Draw();
  c5->SaveAs(fileOutHistpdf + "ElecTime.pdf");
  TCanvas*c6=new TCanvas("c6","Number of ions per event",600,600);
  h_nIon->Draw();
  c6->SaveAs(fileOutHistpdf + "Ion.pdf");
  
  TCanvas*c7=new TCanvas("c7","Initial ion radii",600,600);
  h_nIonRadius->Draw();
  c7->SaveAs(fileOutHistpdf + "IonRadius.pdf");
  TCanvas*c8=new TCanvas("c8","Initial ion phi",600,600);
  h_nIonPhi->Draw();
  c8->SaveAs(fileOutHistpdf + "IonPhi.pdf");
  TCanvas*c9=new TCanvas("c9","Initial ion cos(theta)",600,600);
  h_nIonCosTheta->Draw();
  c9->SaveAs(fileOutHistpdf + "IonCosTheta.pdf");
  TCanvas*c10=new TCanvas("c10","Initial ion time",600,600);
  h_nIonTime->Draw();
  c10->SaveAs(fileOutHistpdf + "IonTime.pdf");
  TCanvas*c15=new TCanvas("c15","Ion Drift Time",600,600);
  h_nIonDriftTime->Draw();
  c15->SaveAs(fileOutHistpdf + "IonDriftTime.pdf");
  
  TCanvas*c11=new TCanvas("c11","Pulse",600,600);
  h_nPulse->Draw();
  c11->SaveAs(fileOutHistpdf + "Pulse.pdf");
  TCanvas*c12=new TCanvas("c12","Signal",600,600);
  h_nSignal->Draw();
  c12->SaveAs(fileOutHistpdf + "Signal.pdf");
  TCanvas*c13=new TCanvas("c13","Signal against time",600,600);
  h_nSignalt->SetOption("colz");
  h_nInitElecPos->SetStats(kFALSE);
  h_nSignalt->Draw();
  c13->SaveAs(fileOutHistpdf + "Signalt.pdf");
  TCanvas*c14=new TCanvas("c14","Pulse against time",600,600);
  h_nPulset->SetOption("colz");
  h_nInitElecPos->SetStats(kFALSE);
  h_nPulset->Draw();
  c14->SaveAs(fileOutHistpdf + "Pulset.pdf");
  
  TCanvas*c16=new TCanvas("c16","Amplitdue Against Rise Time",600,600);
  h_nAmpRiseTime->SetOption("colz");
  h_nAmpRiseTime->Draw();
  c16->SaveAs(fileOutHistpdf + "AmpRiseTime.pdf");
  
  /*  TCanvas*c17=new TCanvas("c17","Pulse Parameter Gradient",600,600);
      TGaxis::SetMaxDigits(3);
      h_nParameterGrad->Draw();
      c17->SaveAs("PulseParameterGrad.pdf");
      TCanvas*c18=new TCanvas("c18","Pulse Parameter Constant",600,600);
      h_nParameterConst->Draw();
      c18->SaveAs("PulseParameterConst.pdf");*/
  
  TCanvas*c19=new TCanvas("c19","Pulse FWHM",600,600);
  h_nPulseWidth1->SetFillColor(kRed+1);
  h_nPulseWidth2->SetFillColor(kBlue+2);
  h_nPulseWidth3->SetFillColor(kGreen+1);
  h_nPulseWidth4->SetFillColor(kCyan+2);
  h_nPulseWidth5->SetFillColor(kMagenta+2);
  h_nPulseWidth->Add(h_nPulseWidth1);
  h_nPulseWidth->Add(h_nPulseWidth2);
  h_nPulseWidth->Add(h_nPulseWidth3);
  h_nPulseWidth->Add(h_nPulseWidth4);
  h_nPulseWidth->Add(h_nPulseWidth5);
  h_nPulseWidth->Draw();
  auto legendPulseWidth = new TLegend(0.6,0.7,0.9,0.9);
  legendPulseWidth->AddEntry(h_nPulseWidth1,"Region 1","f");
  legendPulseWidth->AddEntry(h_nPulseWidth2,"Region 2","f");
  legendPulseWidth->AddEntry(h_nPulseWidth3,"Region 3","f");
  legendPulseWidth->AddEntry(h_nPulseWidth4,"Region 4","f");
  legendPulseWidth->AddEntry(h_nPulseWidth5,"Region 5","f");
  legendPulseWidth->Draw();
  c19->SaveAs(fileOutHistpdf + "PulseWidth.pdf");
  TCanvas*c20=new TCanvas("c20","Pulse Integral",600,600);
  h_nPulseIntegral1->SetFillColor(kRed+1);
  h_nPulseIntegral2->SetFillColor(kBlue+2);
  h_nPulseIntegral3->SetFillColor(kGreen+1);
  h_nPulseIntegral4->SetFillColor(kCyan+2);
  h_nPulseIntegral5->SetFillColor(kMagenta+2);
  h_nPulseIntegral->Add(h_nPulseIntegral1);
  h_nPulseIntegral->Add(h_nPulseIntegral2);
  h_nPulseIntegral->Add(h_nPulseIntegral3);
  h_nPulseIntegral->Add(h_nPulseIntegral4);
  h_nPulseIntegral->Add(h_nPulseIntegral5);
  h_nPulseIntegral->Draw();
  auto legendPulseIntegral = new TLegend(0.6,0.7,0.9,0.9);
  legendPulseIntegral->AddEntry(h_nPulseIntegral1,"Region 1","f");
  legendPulseIntegral->AddEntry(h_nPulseIntegral2,"Region 2","f");
  legendPulseIntegral->AddEntry(h_nPulseIntegral3,"Region 3","f");
  legendPulseIntegral->AddEntry(h_nPulseIntegral4,"Region 4","f");
  legendPulseIntegral->AddEntry(h_nPulseIntegral5,"Region 5","f");
  legendPulseIntegral->Draw();
  c20->SaveAs(fileOutHistpdf + "PulseIntegral.pdf");

  gStyle->SetPalette(51);
  TCanvas*c21=new TCanvas("c21","Initial Electron Position",600,600);
  h_nInitElecPos->SetOption("colz");
  h_nInitElecPos->SetStats(kFALSE);
  h_nInitElecPos->GetXaxis()->SetLabelSize(0.05);
  h_nInitElecPos->GetYaxis()->SetLabelSize(0.05);
  h_nInitElecPos->Draw();
  c21->SaveAs(fileOutHistpdf + "InitElecPos.pdf");
  TCanvas*c22=new TCanvas("c22","Initial Electron Position 1",600,600);
  h_nInitElecPos1->SetOption("colz");
  h_nInitElecPos1->SetStats(kFALSE);
  h_nInitElecPos1->GetXaxis()->SetLabelSize(0.05);
  h_nInitElecPos1->GetYaxis()->SetLabelSize(0.05);
  h_nInitElecPos1->Draw();
  c22->SaveAs(fileOutHistpdf + "InitElecPos1.pdf");
  TCanvas*c23=new TCanvas("c23","Initial Electron Position 2",600,600);
  h_nInitElecPos2->SetOption("colz");
  h_nInitElecPos2->SetStats(kFALSE);
  h_nInitElecPos2->GetXaxis()->SetLabelSize(0.05);
  h_nInitElecPos2->GetYaxis()->SetLabelSize(0.05);
  h_nInitElecPos2->Draw();
  c23->SaveAs(fileOutHistpdf + "InitElecPos2.pdf");
  TCanvas*c24=new TCanvas("c24","Initial Electron Position 3",600,600);
  h_nInitElecPos3->SetOption("colz");
  h_nInitElecPos3->SetStats(kFALSE);
  h_nInitElecPos3->GetXaxis()->SetLabelSize(0.05);
  h_nInitElecPos3->GetYaxis()->SetLabelSize(0.05);
  h_nInitElecPos3->Draw();
  c24->SaveAs(fileOutHistpdf + "InitElecPos3.pdf");
  TCanvas*c25=new TCanvas("c25","Initial Electron Position 4",600,600);
  h_nInitElecPos4->SetOption("colz");
  h_nInitElecPos4->SetStats(kFALSE);
  h_nInitElecPos4->GetXaxis()->SetLabelSize(0.05);
  h_nInitElecPos4->GetYaxis()->SetLabelSize(0.05);
  h_nInitElecPos4->Draw();
  c25->SaveAs(fileOutHistpdf + "InitElecPos4.pdf");
  TCanvas*c26=new TCanvas("c26","Initial Electron Position 5",600,600);
  h_nInitElecPos5->SetOption("colz");
  h_nInitElecPos5->SetStats(kFALSE);
  h_nInitElecPos5->GetXaxis()->SetLabelSize(0.05);
  h_nInitElecPos5->GetYaxis()->SetLabelSize(0.05);
  h_nInitElecPos5->Draw();
  c26->SaveAs(fileOutHistpdf + "InitElecPos5.pdf"); 


  RAllEvents = R1Events + R2Events + R3Events + R4Events + R5Events;
  RAllElec = R1Elec + R2Elec + R3Elec + R4Elec + R5Elec;
  std::cout << "In region 1 there are " << R1Elec << ", " << R1Elec*100/RAllElec << "% electrons and " << R1Events << ", " << R1Events*100/RAllEvents << "% events. \n";
  std::cout << "In region 2 there are " << R2Elec << ", " << R2Elec*100/RAllElec << "% electrons and " << R2Events << ", " << R2Events*100/RAllEvents << "% events. \n";
  std::cout << "In region 3 there are " << R3Elec << ", " << R3Elec*100/RAllElec << "% electrons and " << R3Events << ", " << R3Events*100/RAllEvents << "% events. \n";
  std::cout << "In region 4 there are " << R4Elec << ", " << R4Elec*100/RAllElec << "% electrons and " << R4Events << ", " << R4Events*100/RAllEvents << "% events. \n";
  std::cout << "In region 5 there are " << R5Elec << ", " << R5Elec*100/RAllElec << "% electrons and " << R5Events << ", " << R5Events*100/RAllEvents << "% events. \n";
  
 
      
   
  TFile*fileOutHist=new TFile("./Output_from_" + cos + "_" + energy + "_analysis/Histograms.root","RECREATE");
   
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
  //h_nParameterGrad->Write();
  //h_nParameterConst->Write();
  h_nPulseWidth->Write();
  h_nPulseIntegral->Write();
  h_nInitElecPos->Write();
  h_nInitElecPos1->Write();
  h_nInitElecPos2->Write();
  h_nInitElecPos3->Write();
  h_nInitElecPos4->Write();
  h_nInitElecPos5->Write();
  fileOutHist->Close();



  return 0;
}
