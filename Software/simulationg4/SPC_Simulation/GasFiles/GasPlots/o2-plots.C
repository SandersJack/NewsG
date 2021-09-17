#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TFile.h>
#include <iostream>
#include <string>

#include "MediumMagboltz.hh"

using namespace Garfield;
using namespace std;
void rootlogonATLAS(double ytoff = 1.0, bool atlasmarker =true, double left_margin=0.14);

int main(int argc, char *argv[])
{
  TApplication app("app", &argc, argv);

  rootlogonATLAS();

  std::vector<double> efields,  bfields, angles;

  MediumMagboltz* gas = new MediumMagboltz();

  int ngasfiles = 4;
  vector<string> gasfiles;
  gasfiles.push_back("log64.gas");
  gasfiles.push_back("o2-contamination/1ppm-o2.gas");
  gasfiles.push_back("o2-contamination/20ppm-o2.gas");
  gasfiles.push_back("o2-contamination/100ppm-o2.gas");
  
  //char neon = "Oxygen Concentration";

  //==========TOWNSEND CURVE==========//
  
  TCanvas* c1 = new TCanvas("c1", "Townsend Curve",600,600);
  c1->SetLogx();
  c1->SetLogy();

  TLegend* leg = new TLegend(0.15,0.15,0.30,0.40);
  leg->SetTextFont(42);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(1000);
  leg->SetHeader("Oxygen Concentration");  

  std::vector<TGraph*> graphs;  
  
  for (int igas=0; igas<ngasfiles; igas++) 
    {
      if (igas==0) {gas->LoadGasFile(gasfiles[0]);}
      if (igas==1) {gas->LoadGasFile(gasfiles[1]);}
      if (igas==2) {gas->LoadGasFile(gasfiles[2]);}        
      if (igas==3) {gas->LoadGasFile(gasfiles[3]);}
            
      gas->GetFieldGrid(efields, bfields, angles);

      std::vector<double> alphavec;
      std::vector<double> Evec;     
    
      for (unsigned int i=0; i < efields.size(); i++)
	{
	  double logalpha;
	  gas->GetElectronTownsend(i, 0, 0, logalpha);
	  double alpha = exp(logalpha); 
	  double e = efields[i];
	  alphavec.push_back(alpha);
	  Evec.push_back(e);
	}

      graphs.push_back(new TGraph(efields.size(), &(Evec[0]), &(alphavec[0])));
      graphs[graphs.size()-1]->SetLineWidth(2);
      graphs[graphs.size()-1]->GetXaxis()->SetTitle("E-Field Strength [V/cm]");
      graphs[graphs.size()-1]->GetYaxis()->SetTitle("Attachment Coefficient [1/cm]");    
      graphs[graphs.size()-1]->SetTitle("Townsend Curve");    
      graphs[graphs.size()-1]->SetMarkerStyle(24);

      switch (igas)
	{
	case 0:
	  graphs[graphs.size()-1]->SetLineColor(1);
	  leg->AddEntry(graphs[graphs.size()-1], "0 ppm", "l");
	  break;
	case 1:
	  graphs[graphs.size()-1]->SetLineColor(2);
	  leg->AddEntry(graphs[graphs.size()-1], "1 ppm", "l");
	  break;
	case 2:
	  graphs[graphs.size()-1]->SetLineColor(3);
	  leg->AddEntry(graphs[graphs.size()-1], "20 ppm", "l");
	  break;
	case 3:
	  graphs[graphs.size()-1]->SetLineColor(6);
	  leg->AddEntry(graphs[graphs.size()-1], "100 ppm", "l");
	  break;
	}      
    }

  TH2F*dummyTownsend=new TH2F("dummyTownsend","Townsend Curve;E-Field Strength [V/cm];Townsend Coefficient [1/cm]", 10000,0.01,1e4,1000,1e-4,100.e0);
  dummyTownsend->GetXaxis()->SetTitleOffset(1.2);
  dummyTownsend->GetYaxis()->SetTitleOffset(1.25);
  dummyTownsend->Draw();
  for(unsigned int nn=0;nn<graphs.size();nn++)
    {
      graphs[nn]->Draw("PL");
    }
  leg->Draw();

  c1->Print("o2-contamination/plots/O2_towns.png");  
  c1->Print("o2-contamination/plots/O2_towns.pdf");  
  c1->Print("o2-contamination/plots/O2_towns.eps"); 
  c1->Print("o2-contamination/plots/O2_towns.C");  
 
  


  

  //==========ATTACHMENT CURVE==========//
  
  TCanvas* c2 = new TCanvas("c2", "Attachment Curve",600,600);
  c2->SetLogx();
  c2->SetLogy();

  TLegend* leg2 = new TLegend(0.65,0.65,0.80,0.90);
  leg2->SetTextFont(42);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->SetTextSize(0.035);
  leg2->SetFillStyle(1000);
  leg2->SetHeader("Oxygen Concentration");
  
  std::vector<TGraph*> graphs2;
  
  for (int igas=0; igas<ngasfiles; igas++)
    {
      if (igas==0) {gas->LoadGasFile(gasfiles[0]);}
      if (igas==1) {gas->LoadGasFile(gasfiles[1]);}
      if (igas==2) {gas->LoadGasFile(gasfiles[2]);}        
      if (igas==3) {gas->LoadGasFile(gasfiles[3]);}
      
          
      gas->GetFieldGrid(efields, bfields, angles);

      std::vector<double> etavec;
      std::vector<double> Evec;
      
      for (unsigned int i=0; i < efields.size(); i++)
	{
	  double logeta;
	  gas->GetElectronAttachment(i, 0, 0, logeta);
	  double eta = exp(logeta);
	  double e = efields[i];
	  etavec.push_back(eta);
	  Evec.push_back(e);
	}

      graphs2.push_back(new TGraph(efields.size(), &(Evec[0]), &(etavec[0])));
      graphs2[graphs2.size()-1]->SetLineWidth(2);
      graphs2[graphs2.size()-1]->GetXaxis()->SetTitle("E-Field Strength [V/cm]");
      graphs2[graphs2.size()-1]->GetYaxis()->SetTitle("Attachment Coefficient [1/cm]");    
      graphs2[graphs2.size()-1]->SetTitle("Attachment Curve");    
      graphs2[graphs2.size()-1]->SetMarkerStyle(24);
      
      switch (igas)
	{
	case 0:
	  graphs2[graphs2.size()-1]->SetLineColor(1);
	  leg2->AddEntry(graphs2[graphs2.size()-1], "0 ppm", "l");
	  break;
	case 1:
	  graphs2[graphs2.size()-1]->SetLineColor(2);
	  leg2->AddEntry(graphs2[graphs2.size()-1], "1 ppm", "l");
	  break;
	case 2:
	  graphs2[graphs2.size()-1]->SetLineColor(3);
	  leg2->AddEntry(graphs2[graphs2.size()-1], "20 ppm", "l");
	  break;
	case 3:
	  graphs2[graphs2.size()-1]->SetLineColor(6);
	  leg2->AddEntry(graphs2[graphs2.size()-1], "100 ppm", "l");
	  break;
	}
    }

  TH2F*dummyAttachment=new TH2F("dummyAttachment","Attachment Curve;E-Field Strength [V/cm];Attachment Coefficient [1/cm]", 10000,0.01,1e4,1000,1e-4,1e1);
  dummyAttachment->GetXaxis()->SetTitleOffset(1.2);
  dummyAttachment->GetYaxis()->SetTitleOffset(1.25);
  dummyAttachment->Draw();
  for(unsigned int nn=0;nn<graphs2.size();nn++)
    {
      graphs2[nn]->Draw("PL");
    }
  leg2->Draw();

  c2->Print("o2-contamination/plots/O2_attach.png");  
  c2->Print("o2-contamination/plots/O2_attach.pdf");  
  c2->Print("o2-contamination/plots/O2_attach.eps");  
  c2->Print("o2-contamination/plots/O2_attach.C");  


  



  //==========DRIFT VELOCITY==========//
  
  TCanvas* c3 = new TCanvas("c3", "Electron Drift Velocity",600,600);
  c3->SetLogx();
  c3->SetLogy();
  
  TLegend* leg3 = new TLegend(0.2,0.65,0.3,0.90);
  leg3->SetTextFont(42);
  leg3->SetBorderSize(0);
  leg3->SetFillColor(0);
  leg3->SetTextSize(0.035);
  leg3->SetFillStyle(1000);
  leg3->SetHeader("Oxygen Concentration");
  
  std::vector<TGraph*> graphs3;
  
  for (int igas=0; igas<ngasfiles; igas++)
    {
      if (igas==0) {gas->LoadGasFile(gasfiles[0]);}
      if (igas==1) {gas->LoadGasFile(gasfiles[1]);}
      if (igas==2) {gas->LoadGasFile(gasfiles[2]);}        
      if (igas==3) {gas->LoadGasFile(gasfiles[3]);}
      
      std::vector<double> vvec;
      std::vector<double> Evec;
      
      gas->GetFieldGrid(efields, bfields, angles);
    
      for (unsigned int i=0; i < efields.size(); i++)
	{
	  double v;
	  gas->GetElectronVelocityE(i, 0, 0, v);
	  double e = efields[i];
	  vvec.push_back(v);
	  Evec.push_back(e);
	}

      graphs3.push_back(new TGraph(efields.size(), &(Evec[0]), &(vvec[0])));
      graphs3[graphs3.size()-1]->SetLineWidth(2);
      graphs3[graphs3.size()-1]->GetXaxis()->SetTitle("E-Field Strength [V/cm]");
      graphs3[graphs3.size()-1]->GetYaxis()->SetTitle("Drift Velocity [cm/ns]");    
      graphs3[graphs3.size()-1]->SetTitle("Electron Drift Velocity");    
      graphs3[graphs3.size()-1]->SetMarkerStyle(24);
      
      switch (igas)
	{
	case 0:
	  graphs3[graphs3.size()-1]->SetLineColor(1);
	  leg3->AddEntry(graphs3[graphs3.size()-1], "0 ppm", "l");
	  break;
	case 1:
	  graphs3[graphs3.size()-1]->SetLineColor(2);
	  leg3->AddEntry(graphs3[graphs3.size()-1], "1 ppm", "l");
	  break;
	case 2:
	  graphs3[graphs3.size()-1]->SetLineColor(3);
	  leg3->AddEntry(graphs3[graphs3.size()-1], "20 ppm", "l");
	  break;
	case 3:
	  graphs3[graphs3.size()-1]->SetLineColor(6);
	  leg3->AddEntry(graphs3[graphs3.size()-1], "100 ppm", "l");
	  break;
	}      
    }
  
  TH2F*dummyDriftv=new TH2F("dummyDriftv","Electron Drift Velocity;E-Field Strength [V/cm];Drift Velocity [cm/ns]", 10000,0.01,1e4,1000,1e-7,1.e-2);
  dummyDriftv->GetXaxis()->SetTitleOffset(1.2);
  dummyDriftv->GetYaxis()->SetTitleOffset(1.25);
  dummyDriftv->Draw();
  for(unsigned int nn=0;nn<graphs3.size();nn++)
    {
      graphs3[nn]->Draw("PL");
    }
  leg3->Draw();
  
  c3->Print("o2-contamination/plots/O2_driftv.png");
  c3->Print("o2-contamination/plots/O2_driftv.pdf");
  c3->Print("o2-contamination/plots/O2_driftv.eps");
  c3->Print("o2-contamination/plots/O2_driftv.C");

  


  
  //==========TRANSVERSE DIFFUSION==========//

  TCanvas* c4 = new TCanvas("c4", "Electron Transverse Diffusion Curve",600,600);
  c4->SetLogx();
  
  TLegend* leg4 = new TLegend(0.65,0.65,0.80,0.90);
  leg4->SetTextFont(42);
  leg4->SetBorderSize(0);
  leg4->SetFillColor(0);
  leg4->SetTextSize(0.035);
  leg4->SetFillStyle(1000);
  leg4->SetHeader("Oxygen Concentration");
  
  std::vector<TGraph*> graphs4;
  
  for (int igas=0; igas<ngasfiles; igas++)
    {
      if (igas==0) {gas->LoadGasFile(gasfiles[0]);}
      if (igas==1) {gas->LoadGasFile(gasfiles[1]);}
      if (igas==2) {gas->LoadGasFile(gasfiles[2]);}        
      if (igas==3) {gas->LoadGasFile(gasfiles[3]);}
            
      gas->GetFieldGrid(efields, bfields, angles);

      std::vector<double> Tdvec;
      std::vector<double> Evec;      
    
      for (unsigned int i=0; i < efields.size(); i++)
	{
	  double Td;
	  gas->GetElectronTransverseDiffusion(i, 0, 0, Td);
	  double e = efields[i];
	  Tdvec.push_back(Td);
	  Evec.push_back(e);
	}

      graphs4.push_back(new TGraph(efields.size(), &(Evec[0]), &(Tdvec[0])));
      graphs4[graphs4.size()-1]->SetLineWidth(2);
      graphs4[graphs4.size()-1]->GetXaxis()->SetTitle("E-Field Strength [V/cm]");
      graphs4[graphs4.size()-1]->GetYaxis()->SetTitle("Electron Transverse Diffusion Coefficient [cm^{1/2}]");    
      graphs4[graphs4.size()-1]->SetTitle("Electron Transverse Diffusion Coefficient");    
      graphs4[graphs4.size()-1]->SetMarkerStyle(24);      

      switch (igas)
	{
	case 0:
	  graphs4[graphs4.size()-1]->SetLineColor(1);
	  leg4->AddEntry(graphs4[graphs4.size()-1], "0 ppm", "l");
	  break;
	case 1:
	  graphs4[graphs4.size()-1]->SetLineColor(2);
	  leg4->AddEntry(graphs4[graphs4.size()-1], "1 ppm", "l");
	  break;
	case 2:
	  graphs4[graphs4.size()-1]->SetLineColor(3);
	  leg4->AddEntry(graphs4[graphs4.size()-1], "20 ppm", "l");
	  break;
	case 3:
	  graphs4[graphs4.size()-1]->SetLineColor(6);
	  leg4->AddEntry(graphs4[graphs4.size()-1], "100 ppm", "l");
	  break;
	}        
  }

  TH2F*dummyTransDiff=new TH2F("dummyTransDiff","Electron Transverse Diffusion;E-Field Strength [V/cm];Electron Transverse Diffusion Coefficient [cm^{1/2}]", 10000,0.01,1e4,1000,0.,0.8);
  dummyTransDiff->GetXaxis()->SetTitleOffset(1.2);
  dummyTransDiff->GetYaxis()->SetTitleSize(0.04);
  dummyTransDiff->GetYaxis()->SetTitleOffset(1.75);  
  dummyTransDiff->Draw();
  for(unsigned int nn=0;nn<graphs4.size();nn++)
    {
      graphs4[nn]->Draw("PL");
    }
  leg4->Draw();

  c4->Print("o2-contamination/plots/O2_transdiff.png");
  c4->Print("o2-contamination/plots/O2_transdiff.pdf");
  c4->Print("o2-contamination/plots/O2_transdiff.eps");
  c4->Print("o2-contamination/plots/O2_transdiff.C");
  


  

  //==========LONGITUDINAL DIFFUSION==========//  

  TCanvas* c5 = new TCanvas("c5", "Electron Longitudinal Diffusion Curve",600,600);
  c5->SetLogx();

  TLegend* leg5 = new TLegend(0.65,0.65,0.80,0.90);
  leg5->SetTextFont(42);
  leg5->SetBorderSize(0);
  leg5->SetFillColor(0);
  leg5->SetTextSize(0.035);
  leg5->SetFillStyle(1000);
  leg5->SetHeader("Oxygen Concentration");

  std::vector<TGraph*> graphs5;  
  
  for (int igas=0; igas<ngasfiles; igas++)
    {
      if (igas==0) {gas->LoadGasFile(gasfiles[0]);}
      if (igas==1) {gas->LoadGasFile(gasfiles[1]);}
      if (igas==2) {gas->LoadGasFile(gasfiles[2]);}        
      if (igas==3) {gas->LoadGasFile(gasfiles[3]);}
      
      gas->GetFieldGrid(efields, bfields, angles);

      std::vector<double> Ldvec;
      std::vector<double> Evec;
      
      for (unsigned int i=0; i < efields.size(); i++)
	{
	  double Ld;
	  gas->GetElectronLongitudinalDiffusion(i, 0, 0, Ld);
	  double e = efields[i];
	  Ldvec.push_back(Ld);
	  Evec.push_back(e);
	}

      graphs5.push_back(new TGraph(efields.size(), &(Evec[0]), &(Ldvec[0])));
      graphs5[graphs5.size()-1]->SetLineWidth(2);
      graphs5[graphs5.size()-1]->GetXaxis()->SetTitle("E-Field Strength [V/cm]");
      graphs5[graphs5.size()-1]->GetYaxis()->SetTitle("Electron Longitudinal Diffusion Coefficient [cm^{1/2}]");    
      graphs5[graphs5.size()-1]->SetTitle("Electron Longitudinal Diffusion");    
      graphs5[graphs5.size()-1]->SetMarkerStyle(24);
      
       switch (igas)
	{
	case 0:
	  graphs5[graphs5.size()-1]->SetLineColor(1);
	  leg5->AddEntry(graphs5[graphs5.size()-1], "0 ppm", "l");
	  break;
	case 1:
	  graphs5[graphs5.size()-1]->SetLineColor(2);
	  leg5->AddEntry(graphs5[graphs5.size()-1], "1 ppm", "l");
	  break;
	case 2:
	  graphs5[graphs5.size()-1]->SetLineColor(3);
	  leg5->AddEntry(graphs5[graphs5.size()-1], "20 ppm", "l");
	  break;
	case 3:
	  graphs5[graphs5.size()-1]->SetLineColor(6);
	  leg5->AddEntry(graphs5[graphs5.size()-1], "100 ppm", "l");
	  break;
	}       
  }

  TH2F*dummyLongDiff=new TH2F("dummyLongDiff","Electron Longitudinal Diffusion;E-Field Strength [V/cm];Electron Longitudinal Diffusion Coefficient [cm^{1/2}]", 10000,0.01,1e4,1000,0.,0.8);
  dummyLongDiff->GetXaxis()->SetTitleOffset(1.2);
  dummyLongDiff->GetYaxis()->SetTitleSize(0.04);
  dummyLongDiff->GetYaxis()->SetTitleOffset(1.75);
  dummyLongDiff->Draw();
  for(unsigned int nn=0;nn<graphs5.size();nn++)
    {
      graphs5[nn]->Draw("PL");
    }
  leg5->Draw();

  c5->Print("o2-contamination/plots/O2_longdiff.png");  
  c5->Print("o2-contamination/plots/O2_longdiff.pdf");  
  c5->Print("o2-contamination/plots/O2_longdiff.eps");  
  c5->Print("o2-contamination/plots/O2_longdiff.C");  
 
  TFile*f=new TFile("O2_attach.root","RECREATE");
  graphs2[0]->SetName("0ppmO2Attachment");
  graphs2[0]->Write();
  graphs2[1]->SetName("1ppmO2Attachment");
  graphs2[1]->Write();
  graphs2[2]->SetName("20ppmO2Attachment");
  graphs2[2]->Write();
  graphs2[3]->SetName("100ppmO2Attachment");
  graphs2[3]->Write();
  f->Close();
  
  app.Run();
  return 0;
}

void rootlogonATLAS(double ytoff, bool atlasmarker, double left_margin) 
{

  TStyle* atlasStyle= new TStyle("ATLAS","Atlas style");

  // use plain black on white colors
  Int_t icol=0;
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol);

  // set the paper & margin sizes
  atlasStyle->SetPaperSize(20,26);
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.12);

  // use large fonts
  //Int_t font=72;
  Int_t font=42;
  Double_t tsize=0.05;
  atlasStyle->SetTextFont(font);


  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");

  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");


  //use bold lines and markers
  if ( atlasmarker ) {
    atlasStyle->SetMarkerStyle(20);
    atlasStyle->SetMarkerSize(1.2);
  }
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  //get rid of X error bars and y error bar caps
  //atlasStyle->SetErrorX(0.001);

  //do not display any of the standard histogram decorations
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  //gStyle->SetPadTickX(1);
  //gStyle->SetPadTickY(1);

  // DLA overrides
  atlasStyle->SetPadLeftMargin(left_margin);
  atlasStyle->SetPadBottomMargin(0.13);
  atlasStyle->SetTitleYOffset(ytoff);
  atlasStyle->SetTitleXOffset(1.0);

  // Enforce the style.
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}
