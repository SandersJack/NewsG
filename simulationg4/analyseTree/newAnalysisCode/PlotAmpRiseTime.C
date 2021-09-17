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
  TString fileName = "/disk/moose/general/user149/output_gamma_5.9+keV_spherical+29+-0.98+0+cm_spherical+-1+-0.98+0_5000_20190729.root";
  // TString fileName = "./analyseTree/outputAnalysis.root";
  
  TFile* file = new TFile(fileName);
  TTree * tree = (TTree*)file->Get("simul");
  Reader myReader(tree); //Analysis a(tree);

  TString cos ("cos-0.98");
  TString energy ("5.9keV");


  std::vector<double> nPulse;
  TH3F* h_nAmpRiseTimeTime = new TH3F("h_nAmpRiseTimeTime",";Amplitude;Rise Time;Time;",1100,0,5500,1000,0,250,500,0,5000);
  TH2F* h_nAmpRiseTime = new TH2F("h_nAmpRiseTime",";Amplitude;Rise Time;",1100,0,-5500,250,0,-250);
  
  std::vector<double> nPulset;


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
      for(int i=0;i<myReader.Pulse->size();i++)
	{

nPulse.push_back(myReader.Pulse->at(i));
	  nPulset.push_back(myReader.Pulset->at(i));
	}

  auto Index = std::max_element(nPulse.begin(),nPulse.end());
      int AmpIndex = std::distance(nPulse.begin(),Index);//AmpIndex is the index of the max pulse
      double Amplitude = nPulse[AmpIndex];
	  
      double Amp10 = Amplitude*0.1;
      double Amp90 = Amplitude*0.9;
      //double Amp50 = Amplitude*0.5;

      int Index90;
      int Index10;
     
      
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

      double Time10 = nPulset[Index10];
      double Time90 = nPulset[Index90];
      double RiseTime =Time90-Time10;
      h_nAmpRiseTimeTime->Fill(Amplitude,RiseTime,jentry);
      h_nAmpRiseTime->Fill(Amplitude,RiseTime);

      if (jentry%100==0)
	{
	  std::cout << "This is event number " << jentry << "\n";
	}
      nPulse.clear();
      nPulset.clear();
    }
  TString fileOutHistpdf("./Output_from_" + cos + "_" + energy + "_analysis/AmpRise/");

  TCanvas*c1=new TCanvas("c1","Amplitdue Against Rise Time Against Time",600,600);
  h_nAmpRiseTimeTime->Draw("BOX2 Z");
  c1->SaveAs(fileOutHistpdf + "AmpRiseTimeTime.pdf");
  TCanvas*c2=new TCanvas("c2","Amplitdue Against Rise Time",600,600);
  h_nAmpRiseTime->Draw("colz");
  h_nAmpRiseTime->SetStats(kFALSE);
  c2->SaveAs(fileOutHistpdf + "AmpRiseTime.pdf");
      
return 0;
}















int FromDifferentAngles()
{

  std::vector <TString> fileName = {
			       "output_gamma_5.9+keV_spherical+29+1+0+cm_spherical+-1+1+0_5000_20190729.root",
			       "output_gamma_5.9+keV_spherical+29+0.5+0+cm_spherical+-1+0.5+0_5000_20190805.root",
			       "output_gamma_5.9+keV_spherical+29+0+0+cm_spherical+-1+0+0_5000_20190729.root",
			       "output_gamma_5.9+keV_spherical+29+-0.98+0+cm_spherical+-1+-0.98+0_5000_20190729.root",
			       "output_gamma_5.9+keV_spherical+29+1+0+cm_radial_5000_20190805.root",
			       "output_gamma_5.9+keV_spherical+29+0+0+cm_radial_5000_20190805.root",
			       "output_gamma_5.9+keV_spherical+29+0.5+0+cm_radial_5000_20190805.root",
			       "output_gamma_5.9+keV_spherical+29+-0.98+0+cm_radial_5000_20190805.root"
			       
			       
  };        

  std::vector <short> colour = {kRed+1,kMagenta+2,kViolet+5,kBlue+2,kBlue-3,kCyan+3,kGreen+3,kGreen-3};
    std::vector <TString> cos = {"cos1", "cos0.5", "cos0", "cos-0.98", "cos1bar", "cos0.5bar", "cos0bar", "cos-0.98bar"};
    
  TString folderName = "/disk/moose/general/user149/";  

TCanvas*c1=new TCanvas("c1","Amplitude",600,600);
 auto legendAmplitude = new TLegend(0.6,0.7,0.9,0.9);
TCanvas*c2=new TCanvas("c2","Rise Time",600,600);
 auto legendRiseTime = new TLegend(0.6,0.7,0.9,0.9);


 TH1F *h_nRiseTime = new TH1F("h_nRiseTime",";Rise Time;",300,0,300);
 TH1F *h_nAmplitude = new TH1F("h_nAmplitude",";Amplitude;",500,0,5000);


 // THStack *h_nRiseTime = new THStack("h_nRiseTime","Amplitude");
  TH1F *h_nRiseTime1 = new TH1F("h_nRiseTime1",";Rise Time;",300,0,300);
  TH1F *h_nRiseTime05 = new TH1F("h_nRiseTime05",";Rise Time;",300,0,300);
  TH1F *h_nRiseTime0 = new TH1F("h_nRiseTime0",";Rise Time;",300,0,300);
  TH1F *h_nRiseTime098 = new TH1F("h_nRiseTime098",";Rise Time;",300,0,300);
  TH1F *h_nRiseTime1bar = new TH1F("h_nRiseTime1bar",";Rise Time;",300,0,300);
  TH1F *h_nRiseTime05bar = new TH1F("h_nRiseTime05bar",";Rise Time;",300,0,300);
  TH1F *h_nRiseTime0bar = new TH1F("h_nRiseTime0bar",";Rise Time;",300,0,300);
  TH1F *h_nRiseTime098bar = new TH1F("h_nRiseTime098bar",";Rise Time;",300,0,300);
  //TList *RiseTimeList = new TList;

  std::vector<TH1F*> RiseTimeVector;
  RiseTimeVector.push_back(h_nRiseTime1);
  RiseTimeVector.push_back(h_nRiseTime05);
  RiseTimeVector.push_back(h_nRiseTime0);
  RiseTimeVector.push_back(h_nRiseTime098);
  RiseTimeVector.push_back(h_nRiseTime1bar);
  RiseTimeVector.push_back(h_nRiseTime05bar);
  RiseTimeVector.push_back(h_nRiseTime0bar);
  RiseTimeVector.push_back(h_nRiseTime098bar);
  
  
  

  //THStack *h_nAmplitude = new THStack("h_nAmplitude",";Amplitude;");
  TH1F *h_nAmplitude1 = new TH1F("h_nAmplitude1",";Amplitude;",500,0,5000);
  TH1F *h_nAmplitude05 = new TH1F("h_nAmplitude05",";Amplitude;",500,0,5000);
  TH1F *h_nAmplitude0 = new TH1F("h_nAmplitude0",";Amplitude;",500,0,5000);
  TH1F *h_nAmplitude098 = new TH1F("h_nAmplitude098",";Amplitude;",500,0,5000);
  TH1F *h_nAmplitude1bar = new TH1F("h_nAmplitude1bar",";Amplitude;",500,0,5000);
  TH1F *h_nAmplitude05bar = new TH1F("h_nAmplitude05bar",";Amplitude;",500,0,5000);
  TH1F *h_nAmplitude0bar = new TH1F("h_nAmplitude0bar",";Amplitude;",500,0,5000);
  TH1F *h_nAmplitude098bar = new TH1F("h_nAmplitude098bar",";Amplitude;",500,0,5000);

  // TList *AmplitudeList = new TList;
  std::vector<TH1F*> AmplitudeVector;
  RiseTimeVector.push_back(h_nAmplitude1);
  RiseTimeVector.push_back(h_nAmplitude05);
  RiseTimeVector.push_back(h_nAmplitude0);
  RiseTimeVector.push_back(h_nAmplitude098);
  RiseTimeVector.push_back(h_nAmplitude1bar);
  RiseTimeVector.push_back(h_nAmplitude05bar);
  RiseTimeVector.push_back(h_nAmplitude0bar);
  RiseTimeVector.push_back(h_nAmplitude098bar);
  
  
  std::vector<double> nPulse;
  std::vector<double> nPulset;
 
  for (int j=0; j<8;j++)
    {
      TFile* file = new TFile(folderName + fileName[j]);
      TTree * tree = (TTree*)file->Get("simul");
      Reader myReader(tree); //Analysis a(tree);
      

      Long64_t nentries = myReader.fChain->GetEntries();
 
      for (Long64_t jentry=0; jentry<nentries;jentry++)
	{

	  myReader.GetEntry(jentry);
	  if(myReader.InitElecRadius->size() == 0) continue;
	  if(jentry == 100) break;
	  for(int i=0;i<myReader.Pulse->size();i++)
	    {

	      nPulse.push_back(myReader.Pulse->at(i));
	      nPulset.push_back(myReader.Pulset->at(i));
	    }

	  auto Index = std::max_element(nPulse.begin(),nPulse.end());
	  int AmpIndex = std::distance(nPulse.begin(),Index);//AmpIndex is the index of the max pulse
	  double Amplitude = nPulse[AmpIndex];
	  
	  double Amp10 = Amplitude*0.1;
	  double Amp90 = Amplitude*0.9;
      

	  int Index90;
	  int Index10;
     
      
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
      
      double Time10 = nPulset[Index10];
      double Time90 = nPulset[Index90];
      double RiseTime =Time90-Time10;
       std::cout <<"test\n";
       RiseTimeVector[j]->Fill(RiseTime);
       AmplitudeVector[j]->Fill(Amplitude);
       

      if (jentry%100==0)
	{
	  std::cout << "This is event number " << jentry << "\n";
	}
      
      nPulse.clear();
      nPulset.clear();
	}
  

      c1->cd();
      AmplitudeVector[j]->SetLineColor(colour[j]);
      AmplitudeVector[j]->Draw("Same");
      legendAmplitude->AddEntry(h_nAmplitude,cos[j],"l");
      //RiseTimeList->Reset("ICES");
 
      c2->cd();
      RiseTimeVector[j]->SetLineColor(colour[j]);
      RiseTimeVector[j]->Draw("Same");
      legendRiseTime->AddEntry(h_nRiseTime,cos[j],"l");
      //h_nRiseTime->Reset("ICES");



    
  
 


   }
 
  
  
TString fileOutHistpdf("./AmpRiseTime/");
c1->SaveAs(fileOutHistpdf + "Amplitude.pdf");
c2->SaveAs(fileOutHistpdf + "RiseTime.pdf");
return 0;

}







int RadiusRiseTime()
{

  std::vector <TString> fileName = {
			       "output_gamma_5.9+keV_spherical+29+1+0+cm_spherical+-1+1+0_5000_20190729.root",
			       "output_gamma_5.9+keV_spherical+29+0.5+0+cm_spherical+-1+0.5+0_5000_20190805.root",
			       "output_gamma_5.9+keV_spherical+29+0+0+cm_spherical+-1+0+0_5000_20190729.root",
			       "output_gamma_5.9+keV_spherical+29+-0.98+0+cm_spherical+-1+-0.98+0_5000_20190729.root",
			       "output_gamma_5.9+keV_spherical+29+1+0+cm_radial_5000_20190805.root",
			       "output_gamma_5.9+keV_spherical+29+0+0+cm_radial_5000_20190805.root",
			       "output_gamma_5.9+keV_spherical+29+0.5+0+cm_radial_5000_20190805.root",
			       "output_gamma_5.9+keV_spherical+29+-0.98+0+cm_radial_5000_20190805.root"
			       
			       
  };        

  
    std::vector <TString> cos = {"cos1", "cos0.5", "cos0", "cos-0.98", "cos1bar", "cos0.5bar", "cos0bar", "cos-0.98bar"};
    
  TString folderName = "/disk/moose/general/user149/";  

TCanvas*c1=new TCanvas("c1","Radius Rise Time",600,600);






TString fileOutHistpdf("./RadiusRiseTime/");



  TH2F *h_nRadiusRiseTime1 = new TH2F("h_nRadiusRiseTime1",";Radius;Rise Time",300,0,300,300,0,300);
  TH2F *h_nRadiusRiseTime05 = new TH2F("h_nRadiusRiseTime05",";Radius;Rise Time",300,0,300,300,0,300);
  TH2F *h_nRadiusRiseTime0 = new TH2F("h_nRadiusRiseTime0",";Radius;Rise Time",300,0,300,300,0,300);
  TH2F *h_nRadiusRiseTime098 = new TH2F("h_nRadiusRiseTime098",";Radius;Rise Time",300,0,300,300,0,300);
  TH2F *h_nRadiusRiseTime1bar = new TH2F("h_nRadiusRiseTime1bar",";Radius;Rise Time",300,0,300,300,0,300);
  TH2F *h_nRadiusRiseTime05bar = new TH2F("h_nRadiusRiseTime05bar",";Radius;Rise Time",300,0,300,300,0,300);
  TH2F *h_nRadiusRiseTime0bar = new TH2F("h_nRadiusRiseTime0bar",";Radius;Rise Time",300,0,300,300,0,300);
  TH2F *h_nRadiusRiseTime098bar = new TH2F("h_nRadiusRiseTime098bar",";Radius;Rise Time",300,0,300,300,0,300);
  
  //TList *RiseTimeList = new TList;

  std::vector<TH2F*> RadiusRiseTimeVector;
  RadiusRiseTimeVector.push_back(h_nRadiusRiseTime1);
  RadiusRiseTimeVector.push_back(h_nRadiusRiseTime05);
  RadiusRiseTimeVector.push_back(h_nRadiusRiseTime0);
  RadiusRiseTimeVector.push_back(h_nRadiusRiseTime098);
  RadiusRiseTimeVector.push_back(h_nRadiusRiseTime1bar);
  RadiusRiseTimeVector.push_back(h_nRadiusRiseTime05bar);
  RadiusRiseTimeVector.push_back(h_nRadiusRiseTime0bar);
  RadiusRiseTimeVector.push_back(h_nRadiusRiseTime098bar);
  
  
  

  

 
  
  
  std::vector<double> nPulse;
  std::vector<double> nPulset;
 
  for (int j=0; j<8;j++)
    {
      TFile* file = new TFile(folderName + fileName[j]);
      TTree * tree = (TTree*)file->Get("simul");
      Reader myReader(tree); //Analysis a(tree);
      

      Long64_t nentries = myReader.fChain->GetEntries();
 
      for (Long64_t jentry=0; jentry<nentries;jentry++)
	{

	  myReader.GetEntry(jentry);
	  if(myReader.InitElecRadius->size() == 0) continue;
	  //if(jentry == 100) break;
	  for(int i=0;i<myReader.Pulse->size();i++)
	    {

	      nPulse.push_back(myReader.Pulse->at(i));
	      nPulset.push_back(myReader.Pulset->at(i));
	    }

	  auto Index = std::max_element(nPulse.begin(),nPulse.end());
	  int AmpIndex = std::distance(nPulse.begin(),Index);//AmpIndex is the index of the max pulse
	  double Amplitude = nPulse[AmpIndex];
	  
	  double Amp10 = Amplitude*0.1;
	  double Amp90 = Amplitude*0.9;
      

	  int Index90;
	  int Index10;
     
      
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
      
      double Time10 = nPulset[Index10];
      double Time90 = nPulset[Index90];
      double RiseTime =Time90-Time10;
      // std::cout <<"test\n";
       RadiusRiseTimeVector[j]->Fill(myReader.InitElecRadius->at(1),RiseTime); //Will fill radius of first electron in Pulse
      
       

      if (jentry%100==0)
	{
	  std::cout << "This is event number " << jentry << "\n";
	}
      
      nPulse.clear();
      nPulset.clear();
	}
  

      c1->cd();
      RadiusRiseTimeVector[j]->Draw("COLZ");
      c1->SaveAs(fileOutHistpdf + cos[j] + ".pdf");
     
 
     



    
  
 


   }
 
  
  


return 0;



}
