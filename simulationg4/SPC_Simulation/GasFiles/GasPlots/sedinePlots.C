#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TString.h>
#include <iostream>
#include <string> 

#include "MediumMagboltz.hh"
#include "FundamentalConstants.hh"
#include "TransportParameters.hh"
//export GARFIELD_HOME=/home/user120/garfield
//export HEED_DATABASE=$GARFIELD_HOME/Heed/heed++/database/
  
  
using namespace Garfield;

void rootlogonATLAS(double ytoff = 1.0, bool atlasmarker =true, double left_margin=0.14);

std::vector<double> GenerateEFieldPoints(double npoints, double EMax, double EMin); //Generate logarithmically spaced E-Field Points between EMin and EMax for use in plotting.

std::vector<double> GetTownsendVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType); //Use these E-Field Points to Get out values of Townsend Coefficient for desired gas properties

std::vector<double> GetAttachmentVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType); //Use these E-Field Points to Get out values of Attachment Coefficient for desired gas properties

std::vector<double> GetAttachmentVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType, double O2ppm); //Function for Oxygen attachment scaling

std::vector<double> GetDriftVelocityVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType); //Use these E-Field Points to Get out values of Drift Velocity for desired gas properties

std::vector<double> GetTransverseDiffusionVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType); //Use these E-Field Points to Get out values of Transverse Diffusion for desired gas properties

std::vector<double> GetLongitudinalDiffusionVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType); //Use these E-Field Points to Get out values of Longitudinal Diffusion for desired gas properties

//=================================MAIN CODE=================================//

int main(int argc, char *argv[])
{
  TApplication app("app", &argc, argv);
  TGaxis::SetMaxDigits(3);

  rootlogonATLAS();
  
  TString plotDir{"./Plots_20190318/"};
  TString label_30cm{"Ne_93p20_CH4_6p80"};
  TString label_130cm{"Ne_92p00_CH4_8p00"};
  
  
  // Set up TransportParameter Object
  MediumMagboltz* gas_30cm = new MediumMagboltz();
  MediumMagboltz* gas_130cm = new MediumMagboltz();
  gas_30cm->LoadGasFile("/home/rjw/Software/magboltz/output/gasFile_0_CH4_6.8_Ne.gas");
  gas_130cm->LoadGasFile("/home/rjw/Software/magboltz/output/gasFile_0_CH4_8_Ne.gas");
  // MediumMagboltz* O2 = new MediumMagboltz();
  // O2->LoadGasFile("../output/He_72p5_Ne_25_CH4_2p5_100ppm_O2.gas");
  // MediumMagboltz* H2O = new MediumMagboltz();
  // H2O->LoadGasFile("../output/He_72p5_Ne_25_CH4_2p5_10ppm_H2O.gas");
  //  TransportParameters* parameterTest = new TransportParameters(pure, O2, H2O, label);
  TransportParameters* parameters_30cm  = new TransportParameters(gas_30cm, label_30cm);
  TransportParameters* parameters_130cm = new TransportParameters(gas_130cm, label_130cm);

  //Set up EField points vector
  int nPoints = 64;
  double EMax = 1e4;
  double EMin = 1e-1;
  
  std::vector<double> EFields = GenerateEFieldPoints(nPoints, EMax, EMin);
  
  // Get values of Townsend coefficient using TransportParameter Object, EFields and desired properties
  // double pressureBar = 2.;
  // int impurityType = 1;
  // double O2ppm = 100.;
  // std::vector<double> testVec = GetDriftVelocityVector(parameters, EFields, pressureBar, impurityType);
  
  //std::vector<double> o2attach = GetAttachmentVector(parameters, EFields, 3.1, 1, 0.1);

  int graphType = 4;
  double upperLim{0};
  double lowerLim{0};
  TString axisTitle{""};
  TString otherTitles{"; E-Field Strength [V/cm];"};
  TString parameterName{""};

  // std::vector<double> bar1Vec = GetTownsendVector(parameters_30cm, EFields, .98, 0);
  // std::vector<double> bar2Vec = GetTownsendVector(parameters_130cm, EFields, .5, 0);

  // std::vector<double> bar1Vec = GetAttachmentVector(parameters_30cm, EFields, .98, 0);
  // std::vector<double> bar2Vec = GetAttachmentVector(parameters_130cm, EFields, .5, 0);

  // std::vector<double> bar1Vec = GetDriftVelocityVector(parameters_30cm, EFields, .98, 0);
  // std::vector<double> bar2Vec = GetDriftVelocityVector(parameters_130cm, EFields, .5, 0);

  // std::vector<double> bar1Vec = GetTransverseDiffusionVector(parameters_30cm, EFields, .98, 0);
  // std::vector<double> bar2Vec = GetTransverseDiffusionVector(parameters_130cm, EFields, .5, 0);

  std::vector<double> bar1Vec = GetLongitudinalDiffusionVector(parameters_30cm, EFields, .98, 0);
  std::vector<double> bar2Vec = GetLongitudinalDiffusionVector(parameters_130cm, EFields, .5, 0);

  // Make a graph showing the plot
  TCanvas* c1 = new TCanvas("c1", "Test of TransportParameters Class", 600, 600);
  c1->SetLogx();
     
  switch(graphType)
    {
    case 0://Townsend Coefficient
      upperLim=2e2;
      lowerLim=1e-4;
      axisTitle = "Townsend Coefficient [1/cm]";      
      parameterName = "_towns";
      c1->SetLogy();
      break;
    case 1:// Attachment Coefficient
      upperLim=1e0;
      lowerLim=1e-5;
      axisTitle = "Attachment Coefficient [1/cm]";
      parameterName = "_attach";
      c1->SetLogy();
      break;
    case 2://Drift Velocity
      upperLim=1e-1;
      lowerLim=1e-6;
      axisTitle = "Drift Velocity [cm/ns]";
      parameterName = "_driftv";
      c1->SetLogy();
      break;
    case 3://Transverse Diffusion
      upperLim=0.8;
      lowerLim=1e-2;
      axisTitle = "Transverse Diffusion Coefficient [cm^{1/2}]";
      parameterName = "_transDiff";
      break;
    case 4://Longitudinal Diffusion
      upperLim=0.8;
      lowerLim=1e-2;
      axisTitle = "Longitudinal Diffusion Coefficient [cm^{1/2}]";
      parameterName = "_longDiff";
      break;
    default:
      std::cout << "Invalid Plot Type!" << std::endl;
    }
  
  // Print out values of EFields and alphaVec to make sure they're working
  // for (unsigned int iPoint = 0; iPoint< EFields.size(); iPoint++){
  //   std::cout << "Point Index: " << iPoint << " E-Field Value: " << EFields[iPoint] << std::endl;
  // }  

 
  
  TLegend* legend = new TLegend(0.35,0.9,0.55,0.7);
  legend->SetTextFont(42);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextSize(0.035);
  legend->SetFillStyle(1000);
  
  TMultiGraph *mg = new TMultiGraph();
  
  TGraph* g1 = new TGraph(EFields.size(), &(EFields[0]), &(bar1Vec[0]));
  g1->SetLineColor(kBlue);
  g1->SetLineWidth(2);
  g1->SetMarkerStyle(24);
  g1->SetMarkerSize(0.7);
  g1->SetMarkerColor(kBlack);
  
  TGraph* g2 = new TGraph(EFields.size(), &(EFields[0]), &(bar2Vec[0]));
  g2->SetLineColor(kRed);
  g2->SetLineWidth(2);
  g2->SetMarkerStyle(24);
  g2->SetMarkerSize(0.7);
  g2->SetMarkerColor(kBlack);
  
  // TGraph* g3 = new TGraph(EFields.size(), &(EFields[0]), &(bar3Vec[0]));
  // g3->SetLineColor(kGreen);
  // g3->SetLineWidth(2);
  // g3->SetMarkerStyle(24);
  // g3->SetMarkerSize(0.7);
  // g3->SetMarkerColor(kBlack);
  
  // TGraph* g4 = new TGraph(EFields.size(), &(EFields[0]), &(bar4Vec[0]));
  // g4->SetLineColor(kViolet);
  // g4->SetLineWidth(2);
  // g4->SetMarkerStyle(24);
  // g4->SetMarkerSize(0.7);
  // g4->SetMarkerColor(kBlack);
   
  TString newaxisTitle = otherTitles + axisTitle;
    
  TH2F*dummyTest=new TH2F("dummyTest",newaxisTitle,10000,EMin,EMax,1000,lowerLim,upperLim);
  dummyTest->GetXaxis()->SetTitleOffset(1.2);
  dummyTest->GetYaxis()->SetTitleOffset(1.25);
  dummyTest->Draw();
  
  mg->Add(g1);
  mg->Add(g2);
  // mg->Add(g3);
  // mg->Add(g4);
  
  mg->Draw("PL");

  legend->SetHeader("Gas");
  legend->AddEntry(g1, "8% CH_{4}; 980 mbar", "L");
  legend->AddEntry(g2, "6.8% CH_{4}; 500 mbar", "L");
  // legend->AddEntry(g3, "3", "L");
  // legend->AddEntry(g4, "4", "L");
  legend->Draw();  

  c1->Print(plotDir + "compareGas" + parameterName + ".png");
  c1->Print(plotDir + "compareGas" + parameterName + ".pdf");
  c1->Print(plotDir + "compareGas" + parameterName + ".eps");
  c1->Print(plotDir + "compareGas" + parameterName + ".root");
  
  app.Run(); // Keeps up canvas
  return 0;
} 

//He_72p5_Ne_25_CH4_2p5


//=================================FUNCTIONS=================================//


std::vector<double> GenerateEFieldPoints(double npoints, double EMax, double EMin)
{
  double EField=0;
  
  double LogMin = log(EMin);
  double LogMax = log(EMax);
  double step = (LogMax - LogMin)/(npoints-1);
  
  std::vector<double> EFieldPoints;
  
  for (double logEField = LogMin; logEField<LogMax+step/2; logEField+=step)
    {
      EField = exp(logEField);
      EFieldPoints.push_back(EField);
    }
  
  return EFieldPoints;
}

std::vector<double> GetTownsendVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType)
{
  std::vector<double> alphaVec;
  double alpha;
  
  for(unsigned int iPoint = 0; iPoint < EFields.size(); iPoint++){
    alpha = gas->GetElectronTownsend(EFields[iPoint], pressureBar, impurityType);
    alphaVec.push_back(alpha);
  }
  
  return alphaVec;
}

std::vector<double> GetAttachmentVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType)
{
  std::vector<double> etaVec;
  double eta;
  
  for(unsigned int iPoint = 0; iPoint < EFields.size(); iPoint++){
    eta = gas->GetElectronAttachment(EFields[iPoint], pressureBar, impurityType);
    etaVec.push_back(eta);
  }
  
  return etaVec;  
}

std::vector<double> GetAttachmentVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType, double O2ppm)
{
  std::vector<double> etaVec;
  double eta;
  
  if(impurityType == 1)
    for(unsigned int iPoint = 0; iPoint < EFields.size(); iPoint++)
      {
	eta = gas->GetElectronAttachment(EFields[iPoint], pressureBar, impurityType, O2ppm);
	etaVec.push_back(eta);
      }
  else
    {
      std::cout << "[transportPlots] ERROR: Entered a value for O2 contamination for impurity type != 1 \n"
		<< "Perhaps you meant to use GetAttachmentVector(TransportParameters*, std::vector<double>, double, int, double)?" << std::endl;
    }
  
  
  return etaVec;  
}

std::vector<double> GetDriftVelocityVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType)
{
  std::vector<double> driftvVec;
  double driftv;
  
  for(unsigned int iPoint = 0; iPoint < EFields.size(); iPoint++)
    {
      driftv = gas->GetElectronDriftVelocity(EFields[iPoint], pressureBar, impurityType);
      driftvVec.push_back(driftv);
    }

  return driftvVec;
}

std::vector<double> GetTransverseDiffusionVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType)
{
  std::vector<double> transDiffVec;
  double transDiff;

  for(unsigned int iPoint = 0; iPoint < EFields.size(); iPoint++)
    {
      transDiff = gas->GetElectronTransverseDiffusion(EFields[iPoint], pressureBar, impurityType);
      transDiffVec.push_back(transDiff);
    }
  
  return transDiffVec;
}


std::vector<double> GetLongitudinalDiffusionVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType)
{
  std::vector<double> longDiffVec;
  double longDiff;
  
  for(unsigned int iPoint = 0; iPoint < EFields.size(); iPoint++)
    {
      longDiff = gas->GetElectronLongitudinalDiffusion(EFields[iPoint], pressureBar, impurityType);
      longDiffVec.push_back(longDiff);
    }
  
  return longDiffVec;
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
    //lasStyle->SetMarkerStyle(20);
    //lasStyle->SetMarkerSize(0.7);
    // atlasStyle->SetMarkerColor(kBlue);
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



  /* MediumMagboltz* H2O_2 = new MediumMagboltz();
  H2O_2->LoadGasFile("../output/He_72p5_Ne_25_CH4_2p5_100ppm_H2O.gas");
  TransportParameters* parameters1 = new TransportParameters(pure, O2, H2O, label);
  parameters1->SetWaterFile(H2O_2);

  MediumMagboltz* H2O_3 = new MediumMagboltz();
  H2O_3->LoadGasFile("../output/He_72p5_Ne_25_CH4_2p5_1000ppm_H2O.gas");
  TransportParameters* parameters2 = new TransportParameters(pure, O2, H2O, label);
  parameters2->SetWaterFile(H2O_3);*/

  /*MediumMagboltz* pure_1 = new MediumMagboltz();
  pure_1->LoadGasFile("../output/Ne_99p3_CH4_0p7.gas");
  TransportParameters* parameters1 = new TransportParameters(pure, O2, H2O, label);
  parameters1->SetPureGasFile(pure_1);

  MediumMagboltz* pure_2 = new MediumMagboltz();
  pure_2->LoadGasFile("../output/He_72p5_Ne_25_CH4_2p5.gas");
  TransportParameters* parameters2 = new TransportParameters(pure, O2, H2O, label);
  parameters2->SetPureGasFile(pure_2);*/

  

  /*MediumMagboltz* H2O_3 = new MediumMagboltz();
    H2O_3->LoadGasFile("../output/He_90_CH4_10_1000ppm_H2O.gas");
    TransportParameters* parameters2 = new TransportParameters(pure, O2, H2O, label);
    parameters2->SetWaterFile(H2O_3);*/
  
