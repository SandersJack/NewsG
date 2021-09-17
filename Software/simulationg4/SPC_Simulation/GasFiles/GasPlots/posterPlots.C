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

void SavePlots(TCanvas* canvas, TString plotName, TString dirName);

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
  
  TString plotDir{"./Plots_20190318"};
  TString label_sedine2015{"Ar:CH_{4} (98.0%:2.0%); 0.3 bar"};
  // TString label_sedine2015{"Ne:CH_{4} (99.3%:0.7%); 3.1 bar"};
  TString label_sedine2015_O2{"Ne:CH_{4} (99.3%:0.7%) 1ppm O_{2}; 3.1 bar"};
  TString label_sedine2018{"He:Ne:CH_{4} (72.5%:25.0%:2.5%); 1.0 bar"};
  TString label_sedine2019{"Ne:CH_{4} (94.0%:6.0%); 1.0 bar"};
  
  
  // Set up TransportParameter Object
  MediumMagboltz* gas_sedine2015 = new MediumMagboltz();
  MediumMagboltz* gas_sedine2015_O2 = new MediumMagboltz();
  MediumMagboltz* gas_sedine2015_H2O_10ppm = new MediumMagboltz();
  MediumMagboltz* gas_sedine2015_H2O_1ppm = new MediumMagboltz();
  MediumMagboltz* gas_sedine2015_H2O_0p1ppm = new MediumMagboltz();
  MediumMagboltz* gas_sedine2018 = new MediumMagboltz();
  MediumMagboltz* gas_sedine2019 = new MediumMagboltz();
  gas_sedine2015->LoadGasFile("../../gasfiles/gasFile_0_CH4_2_Ar.gas");///home/rjw/Software/magboltz/gasfiles/Ne_99p3_CH4_00p7_3p1bar/Ne_99p3_CH4_0p7.gas");
  gas_sedine2015_O2->LoadGasFile("../../gasfiles/Ne_99p3_CH4_00p7_3p1bar/Ne_99p3_CH4_0p7_100ppm_O2.gas");
  // gas_sedine2015_H2O_0p1ppm->LoadGasFile("../../gasfiles/Ne_99p3_CH4_00p7_3p1bar/Ne_99p3_CH4_0p7_0p1ppm_H2O.gas");
  // gas_sedine2015_H2O_1ppm->LoadGasFile("../../gasfiles/Ne_99p3_CH4_00p7_3p1bar/1ppm-h2o.gas");
  // gas_sedine2015_H2O_10ppm->LoadGasFile("../../gasfiles/Ne_99p3_CH4_00p7_3p1bar/10ppm-h2o.gas");
  gas_sedine2015_H2O_0p1ppm->LoadGasFile("../../gasfiles/gasFile_2_0.1_CH4_0.7_Ne.gas");
  gas_sedine2015_H2O_1ppm->LoadGasFile("../../gasfiles/gasFile_2_1_CH4_0.7_Ne.gas");
  gas_sedine2015_H2O_10ppm->LoadGasFile("../../gasfiles/gasFile_2_10_CH4_0.7_Ne.gas");
  gas_sedine2018->LoadGasFile("../../gasfiles/He_72p5_Ne_25p0_CH4_02p5_1bar/He_72p5_Ne_25_CH4_2p5.gas");
  gas_sedine2019->LoadGasFile("../../gasfiles/gasFile_0_CH4_6_Ne.gas");
  // MediumMagboltz* O2 = new MediumMagboltz();
  // O2->LoadGasFile("../../gasfiles/He_72p5_Ne_25_CH4_2p5_1ppm_O2.gas");
  // MediumMagboltz* H2O = new MediumMagboltz();
  // H2O->LoadGasFile("../../gasfiles/He_72p5_Ne_25_CH4_2p5_0p1ppm_H2O.gas");
  //  TransportParameters* parameterTest = new TransportParameters(pure, O2, H2O, label);
  TransportParameters* parameters_sedine2015 = new TransportParameters(gas_sedine2015, gas_sedine2015_O2, NULL, label_sedine2015);
  TransportParameters* parameters_sedine2015_H2O_0p1ppm = new TransportParameters(gas_sedine2015, NULL, gas_sedine2015_H2O_0p1ppm, label_sedine2015 + " H2O 0.1 ppm");
  TransportParameters* parameters_sedine2015_H2O_1ppm = new TransportParameters(gas_sedine2015, NULL, gas_sedine2015_H2O_1ppm, label_sedine2015 + " H2O 1 ppm");
  TransportParameters* parameters_sedine2015_H2O_10ppm = new TransportParameters(gas_sedine2015, NULL, gas_sedine2015_H2O_10ppm, label_sedine2015 + " H2O 10 ppm");
  TransportParameters* parameters_sedine2018 = new TransportParameters(gas_sedine2018, label_sedine2018);
  TransportParameters* parameters_sedine2019 = new TransportParameters(gas_sedine2019, label_sedine2019);

  //Set up EField points vector
  int nPoints = 1000;
  double EMax = 1e4;
  double EMin = 5e-1;
  
  std::vector<double> EFields = GenerateEFieldPoints(nPoints, EMax, EMin);
  
  // Get values of Townsend coefficient using TransportParameter Object, EFields and desired properties
  // double pressureBar = 2.;
  // int impurityType = 1;
  // double O2ppm = 100.;
  // std::vector<double> testVec = GetDriftVelocityVector(parameters, EFields, pressureBar, impurityType);
  
  //std::vector<double> o2attach = GetAttachmentVector(parameters, EFields, 3.1, 1, 0.1);

  std::vector<double> townsVec_sedine2015 = GetTownsendVector(parameters_sedine2015, EFields, 0.3, 0);
  std::vector<double> townsVec_sedine2018 = GetTownsendVector(parameters_sedine2018, EFields, 1., 0);
  std::vector<double> townsVec_sedine2019 = GetTownsendVector(parameters_sedine2019, EFields, 1., 0);

  std::vector<double> attachVec_sedine2015 = GetAttachmentVector(parameters_sedine2015, EFields, 0.3, 0);
  std::vector<double> attachVec_sedine2018 = GetAttachmentVector(parameters_sedine2018, EFields, 1., 0);
  std::vector<double> attachVec_sedine2019 = GetAttachmentVector(parameters_sedine2019, EFields, 1., 0);

  std::vector<double> driftVVec_sedine2015 = GetDriftVelocityVector(parameters_sedine2015, EFields, 0.3, 0);
  std::vector<double> driftVVec_sedine2018 = GetDriftVelocityVector(parameters_sedine2018, EFields, 1., 0);
  std::vector<double> driftVVec_sedine2019 = GetDriftVelocityVector(parameters_sedine2019, EFields, 1., 0);

  std::vector<double> transDiffVec_sedine2015 = GetTransverseDiffusionVector(parameters_sedine2015, EFields, 0.3, 0);
  std::vector<double> transDiffVec_sedine2018 = GetTransverseDiffusionVector(parameters_sedine2018, EFields, 1., 0);
  std::vector<double> transDiffVec_sedine2019 = GetTransverseDiffusionVector(parameters_sedine2019, EFields, 1., 0);

  std::vector<double> longDiffVec_sedine2015 = GetLongitudinalDiffusionVector(parameters_sedine2015, EFields, 0.3, 0);
  std::vector<double> longDiffVec_sedine2018 = GetLongitudinalDiffusionVector(parameters_sedine2018, EFields, 1., 0);
  std::vector<double> longDiffVec_sedine2019 = GetLongitudinalDiffusionVector(parameters_sedine2019, EFields, 1., 0);

  std::vector<double> attachVec_sedine2015_O2_0p1ppm = GetAttachmentVector(parameters_sedine2015, EFields, 0.3, 1, 0.1);
  std::vector<double> attachVec_sedine2015_O2_1ppm = GetAttachmentVector(parameters_sedine2015, EFields, 0.3, 1, 1.);
  std::vector<double> attachVec_sedine2015_O2_10ppm = GetAttachmentVector(parameters_sedine2015, EFields, 0.3, 1, 10.);

  std::vector<double> attachVec_sedine2015_H2O_0p1ppm = GetAttachmentVector(parameters_sedine2015_H2O_0p1ppm, EFields, 0.3, 2);
  std::vector<double> attachVec_sedine2015_H2O_1ppm = GetAttachmentVector(parameters_sedine2015_H2O_1ppm, EFields, 0.3, 2);
  std::vector<double> attachVec_sedine2015_H2O_10ppm = GetAttachmentVector(parameters_sedine2015_H2O_10ppm, EFields, 0.3, 2);

  std::vector<double> driftVVec_sedine2015_H2O_0p1ppm = GetDriftVelocityVector(parameters_sedine2015_H2O_0p1ppm, EFields, 0.3, 2);
  std::vector<double> driftVVec_sedine2015_H2O_1ppm = GetDriftVelocityVector(parameters_sedine2015_H2O_1ppm, EFields, 0.3, 2);
  std::vector<double> driftVVec_sedine2015_H2O_10ppm = GetDriftVelocityVector(parameters_sedine2015_H2O_10ppm, EFields, 0.3, 2);

  std::vector<double> transDiffVec_sedine2015_H2O_0p1ppm = GetTransverseDiffusionVector(parameters_sedine2015_H2O_0p1ppm, EFields, 0.3, 2);
  std::vector<double> transDiffVec_sedine2015_H2O_1ppm = GetTransverseDiffusionVector(parameters_sedine2015_H2O_1ppm, EFields, 0.3, 2);
  std::vector<double> transDiffVec_sedine2015_H2O_10ppm = GetTransverseDiffusionVector(parameters_sedine2015_H2O_10ppm, EFields, 0.3, 2);

  std::vector<double> longDiffVec_sedine2015_H2O_0p1ppm = GetLongitudinalDiffusionVector(parameters_sedine2015_H2O_0p1ppm, EFields, 0.3, 2);
  std::vector<double> longDiffVec_sedine2015_H2O_1ppm = GetLongitudinalDiffusionVector(parameters_sedine2015_H2O_1ppm, EFields, 0.3, 2);
  std::vector<double> longDiffVec_sedine2015_H2O_10ppm = GetLongitudinalDiffusionVector(parameters_sedine2015_H2O_10ppm, EFields, 0.3, 2);


  // TLegend* legend = new TLegend(0.15,0.9,0.25,0.8);
  // legend->SetTextFont(42);
  // legend->SetBorderSize(0);
  // legend->SetFillColor(0);
  // legend->SetTextSize(0.035);
  // legend->SetFillStyle(1000);
  
  // Make a graph showing the plot
  TCanvas* c_towns_attach = new TCanvas("c_towns_attach", "", 600, 600);
  c_towns_attach->SetLogx();
  c_towns_attach->SetLogy();

  TH2F* h_dummy_towns_attach=new TH2F("h_dummy_towns_attach","; Electric Field Strength [V/cm]; Coefficient Value [1/cm]",10000,EMin,EMax,1000,1e-4,1e3);
  h_dummy_towns_attach->GetXaxis()->SetTitleOffset(1.2);
  h_dummy_towns_attach->GetYaxis()->SetTitleOffset(1.25);
  h_dummy_towns_attach->Draw();
  
  TGraph* g_towns_sedine2015 = new TGraph(EFields.size(), &(EFields[0]), &(townsVec_sedine2015[0]));
  TGraph* g_towns_sedine2018 = new TGraph(EFields.size(), &(EFields[0]), &(townsVec_sedine2018[0]));
  TGraph* g_towns_sedine2019 = new TGraph(EFields.size(), &(EFields[0]), &(townsVec_sedine2019[0]));
  TGraph* g_attach_sedine2015 = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2015[0]));
  TGraph* g_attach_sedine2018 = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2018[0]));
  TGraph* g_attach_sedine2019 = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2019[0]));
  
  TLegend* leg_towns_attach_sedine2015 = new TLegend(0.2, 0.8, 0.35, 0.9);
  leg_towns_attach_sedine2015->SetTextFont(42);
  leg_towns_attach_sedine2015->SetBorderSize(0);
  leg_towns_attach_sedine2015->SetFillColor(0);
  leg_towns_attach_sedine2015->SetTextSize(0.035);
  leg_towns_attach_sedine2015->SetFillStyle(1000);

  TLegend* leg_towns_attach_sedine2018 = new TLegend(0.2, 0.675, 0.35, 0.775);
  leg_towns_attach_sedine2018->SetTextFont(42);
  leg_towns_attach_sedine2018->SetBorderSize(0);
  leg_towns_attach_sedine2018->SetFillColor(0);
  leg_towns_attach_sedine2018->SetTextSize(0.035);
  leg_towns_attach_sedine2018->SetFillStyle(1000);

  TLegend* leg_towns_attach_sedine2019 = new TLegend(0.2, 0.55, 0.35, 0.65);
  leg_towns_attach_sedine2019->SetTextFont(42);
  leg_towns_attach_sedine2019->SetBorderSize(0);
  leg_towns_attach_sedine2019->SetFillColor(0);
  leg_towns_attach_sedine2019->SetTextSize(0.035);
  leg_towns_attach_sedine2019->SetFillStyle(1000);

  g_towns_sedine2015->SetLineColor(kBlack);
  g_towns_sedine2015->SetLineWidth(2);
  g_towns_sedine2015->Draw("sameL");
 
  g_attach_sedine2015->SetLineColor(kBlack);
  g_attach_sedine2015->SetLineStyle(kDashed);
  g_attach_sedine2015->SetLineWidth(2);
  g_attach_sedine2015->Draw("sameL");

  leg_towns_attach_sedine2015->SetHeader(label_sedine2015);
  leg_towns_attach_sedine2015->AddEntry(g_towns_sedine2015, "Townsend", "L");
  leg_towns_attach_sedine2015->AddEntry(g_attach_sedine2015, "Attachment", "L");
  leg_towns_attach_sedine2015->Draw();

  g_towns_sedine2018->SetLineColor(kRed);
  g_towns_sedine2018->SetLineWidth(2);
  g_towns_sedine2018->Draw("sameL");

  g_attach_sedine2018->SetLineColor(kRed);
  g_attach_sedine2018->SetLineStyle(kDashed);
  g_attach_sedine2018->SetLineWidth(2);
  g_attach_sedine2018->Draw("sameL");

  leg_towns_attach_sedine2018->SetHeader(label_sedine2018);
  leg_towns_attach_sedine2018->AddEntry(g_towns_sedine2018, "Townsend", "L");
  leg_towns_attach_sedine2018->AddEntry(g_attach_sedine2018, "Attachment", "L");
  leg_towns_attach_sedine2018->Draw();

  g_towns_sedine2019->SetLineColor(kBlue);
  g_towns_sedine2019->SetLineWidth(2);
  g_towns_sedine2019->Draw("sameL");

  g_attach_sedine2019->SetLineColor(kBlue);
  g_attach_sedine2019->SetLineStyle(kDashed);
  g_attach_sedine2019->SetLineWidth(2);
  g_attach_sedine2019->Draw("sameL");

  leg_towns_attach_sedine2019->SetHeader(label_sedine2019);
  leg_towns_attach_sedine2019->AddEntry(g_towns_sedine2019, "Townsend", "L");
  leg_towns_attach_sedine2019->AddEntry(g_attach_sedine2019, "Attachment", "L");
  leg_towns_attach_sedine2019->Draw();
  
  SavePlots(c_towns_attach, "towns_attach",  plotDir);
  

  TCanvas* c_driftV = new TCanvas("c_driftV", "", 600, 600);
  c_driftV->SetLogx();
  c_driftV->SetLogy();

  TH2F* h_dummy_driftV=new TH2F("h_dummy_driftV","; Electric Field Strength [V/cm]; Drift Velocity [cm/ns]",10000,EMin,EMax,1000,1e-5,1e-1);
  h_dummy_driftV->GetXaxis()->SetTitleOffset(1.2);
  h_dummy_driftV->GetYaxis()->SetTitleOffset(1.25);
  h_dummy_driftV->Draw();

  TGraph* g_driftV_sedine2015 = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2015[0]));
  TGraph* g_driftV_sedine2018 = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2018[0]));
  TGraph* g_driftV_sedine2019 = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2019[0]));

  TLegend* leg_driftV = new TLegend(0.2, 0.75, 0.35, 0.9);
  leg_driftV->SetTextFont(42);
  leg_driftV->SetBorderSize(0);
  leg_driftV->SetFillColor(0);
  leg_driftV->SetTextSize(0.035);
  leg_driftV->SetFillStyle(1000);

  g_driftV_sedine2015->SetLineColor(kBlack);
  g_driftV_sedine2015->SetLineWidth(2);
  g_driftV_sedine2015->Draw("sameL");

  g_driftV_sedine2018->SetLineColor(kRed);
  g_driftV_sedine2018->SetLineWidth(2);
  g_driftV_sedine2018->Draw("sameL");

  g_driftV_sedine2019->SetLineColor(kBlue);
  g_driftV_sedine2019->SetLineWidth(2);
  g_driftV_sedine2019->Draw("sameL");

  leg_driftV->SetHeader("Gas Composition");
  leg_driftV->AddEntry(g_driftV_sedine2015, label_sedine2015, "L");
  leg_driftV->AddEntry(g_driftV_sedine2018, label_sedine2018, "L");
  leg_driftV->AddEntry(g_driftV_sedine2019, label_sedine2019, "L");
  leg_driftV->Draw();
  
  SavePlots(c_driftV, "driftV",  plotDir);

  TCanvas* c_diff = new TCanvas("c_diff", "", 600, 600);
  c_diff->SetLogx();
  c_diff->SetLogy();

  TH2F* h_dummy_diff=new TH2F("h_dummy_diff","; Electric Field Strength [V/cm]; Diffusion Coefficient [cm^{1/2}]",10000,EMin,EMax,1000,1e-2,1e0);
  h_dummy_diff->GetXaxis()->SetTitleOffset(1.2);
  h_dummy_diff->GetYaxis()->SetTitleOffset(1.25);
  h_dummy_diff->Draw();
  
  TGraph* g_longDiff_sedine2015 = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2015[0]));
  TGraph* g_longDiff_sedine2018 = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2018[0]));
  TGraph* g_longDiff_sedine2019 = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2019[0]));
  TGraph* g_transDiff_sedine2015 = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2015[0]));
  TGraph* g_transDiff_sedine2018 = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2018[0]));
  TGraph* g_transDiff_sedine2019 = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2019[0]));
  
  TLegend* leg_diff_sedine2015 = new TLegend(0.35, 0.825, 0.5, 0.925);
  leg_diff_sedine2015->SetTextFont(42);
  leg_diff_sedine2015->SetBorderSize(0);
  leg_diff_sedine2015->SetFillColor(0);
  leg_diff_sedine2015->SetTextSize(0.035);
  leg_diff_sedine2015->SetFillStyle(1000);


  TLegend* leg_diff_sedine2018 = new TLegend(0.35, 0.7, 0.5, 0.8);
  leg_diff_sedine2018->SetTextFont(42);
  leg_diff_sedine2018->SetBorderSize(0);
  leg_diff_sedine2018->SetFillColor(0);
  leg_diff_sedine2018->SetTextSize(0.035);
  leg_diff_sedine2018->SetFillStyle(1000);

  TLegend* leg_diff_sedine2019 = new TLegend(0.35, 0.175, 0.5, 0.275);
  leg_diff_sedine2019->SetTextFont(42);
  leg_diff_sedine2019->SetBorderSize(0);
  leg_diff_sedine2019->SetFillColor(0);
  leg_diff_sedine2019->SetTextSize(0.035);
  leg_diff_sedine2019->SetFillStyle(1000);

  g_longDiff_sedine2015->SetLineColor(kBlack);
  g_longDiff_sedine2015->SetLineWidth(2);
  g_longDiff_sedine2015->Draw("sameL");
 
  g_transDiff_sedine2015->SetLineColor(kBlack);
  g_transDiff_sedine2015->SetLineStyle(kDashed);
  g_transDiff_sedine2015->SetLineWidth(2);
  g_transDiff_sedine2015->Draw("sameL");

  leg_diff_sedine2015->SetHeader(label_sedine2015);
  leg_diff_sedine2015->AddEntry(g_longDiff_sedine2015, "Longitudinal", "L");
  leg_diff_sedine2015->AddEntry(g_transDiff_sedine2015, "Transverse", "L");
  leg_diff_sedine2015->Draw();

  g_longDiff_sedine2018->SetLineColor(kRed);
  g_longDiff_sedine2018->SetLineWidth(2);
  g_longDiff_sedine2018->Draw("sameL");

  g_transDiff_sedine2018->SetLineColor(kRed);
  g_transDiff_sedine2018->SetLineStyle(kDashed);
  g_transDiff_sedine2018->SetLineWidth(2);
  g_transDiff_sedine2018->Draw("sameL");

  leg_diff_sedine2018->SetHeader(label_sedine2018);
  leg_diff_sedine2018->AddEntry(g_longDiff_sedine2018, "Longitudinal", "L");
  leg_diff_sedine2018->AddEntry(g_transDiff_sedine2018, "Transverse", "L");
  leg_diff_sedine2018->Draw();

  g_longDiff_sedine2019->SetLineColor(kBlue);
  g_longDiff_sedine2019->SetLineWidth(2);
  g_longDiff_sedine2019->Draw("sameL");

  g_transDiff_sedine2019->SetLineColor(kBlue);
  g_transDiff_sedine2019->SetLineStyle(kDashed);
  g_transDiff_sedine2019->SetLineWidth(2);
  g_transDiff_sedine2019->Draw("sameL");

  leg_diff_sedine2019->SetHeader(label_sedine2019);
  leg_diff_sedine2019->AddEntry(g_longDiff_sedine2019, "Longitudinal", "L");
  leg_diff_sedine2019->AddEntry(g_transDiff_sedine2019, "Transverse", "L");
  leg_diff_sedine2019->Draw();
  
  SavePlots(c_diff, "diff",  plotDir);

 //  // ============================= OXYGEN ATTACHMENT PLOTS ================================= //

 //  TCanvas* c_attach_O2 = new TCanvas("c_attach_O2", "", 600, 600);
 //  c_attach_O2->SetLogx();
 //  c_attach_O2->SetLogy();

 //  TGraph* g_attach_sedine2015_O2_0ppm = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2015[0]));
 //  TGraph* g_attach_sedine2015_O2_0p1ppm = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2015_O2_0p1ppm[0]));
 //  TGraph* g_attach_sedine2015_O2_1ppm = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2015_O2_1ppm[0]));
 //  TGraph* g_attach_sedine2015_O2_10ppm = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2015_O2_10ppm[0]));

 //  TH2F* h_dummy_attach_O2 = new TH2F("h_dummy_attach_O2","; Electric Field Strength [V/cm]; Attachment Coefficient [1/cm]",10000,EMin,EMax,1000,1e-5,1e0);
 //  h_dummy_attach_O2->GetXaxis()->SetTitleOffset(1.2);
 //  h_dummy_attach_O2->GetYaxis()->SetTitleOffset(1.25);
 //  h_dummy_attach_O2->Draw();

 //  TLegend* leg_attach_O2 = new TLegend(0.2, 0.15, 0.35, 0.4);
 //  leg_attach_O2->SetTextFont(42);
 //  leg_attach_O2->SetBorderSize(0);
 //  leg_attach_O2->SetFillColor(0);
 //  leg_attach_O2->SetTextSize(0.035);
 //  leg_attach_O2->SetFillStyle(1000);



 //  g_attach_sedine2015_O2_0ppm->SetLineColor(kBlack);
 //  g_attach_sedine2015_O2_0ppm->SetLineWidth(2);
 //  g_attach_sedine2015_O2_0ppm->Draw("sameL");

 //  g_attach_sedine2015_O2_0p1ppm->SetLineColor(kRed);
 //  g_attach_sedine2015_O2_0p1ppm->SetLineWidth(2);
 //  g_attach_sedine2015_O2_0p1ppm->Draw("sameL");

 //  g_attach_sedine2015_O2_1ppm->SetLineColor(kBlue);
 //  g_attach_sedine2015_O2_1ppm->SetLineWidth(2);
 //  g_attach_sedine2015_O2_1ppm->Draw("sameL");

 //  g_attach_sedine2015_O2_10ppm->SetLineColor(kViolet);
 //  g_attach_sedine2015_O2_10ppm->SetLineWidth(2);
 //  g_attach_sedine2015_O2_10ppm->Draw("sameL");

 //  leg_attach_O2->SetHeader(label_sedine2015);
 //  leg_attach_O2->AddEntry(g_attach_sedine2015_O2_0ppm, "0 ppm O_{2}", "L");
 //  leg_attach_O2->AddEntry(g_attach_sedine2015_O2_0p1ppm, "0.1 ppm O_{2}", "L");
 //  leg_attach_O2->AddEntry(g_attach_sedine2015_O2_1ppm, "1 ppm O_{2}", "L");
 //  leg_attach_O2->AddEntry(g_attach_sedine2015_O2_10ppm, "10 ppm O_{2}", "L");
 //  leg_attach_O2->Draw();

 //  SavePlots(c_attach_O2, "attach_O2",  plotDir);

 //  // ============================= WATER PLOTS ================================= //

 //  TCanvas* c_attach_H2O = new TCanvas("c_attach_H2O", "", 600, 600);
 //  c_attach_H2O->SetLogx();
 //  c_attach_H2O->SetLogy();

 //  TH2F* h_dummy_attach_H2O=new TH2F("h_dummy_attach_H2O","; Electric Field Strength [V/cm]; Attachment Coefficient [1/cm]",10000,EMin,EMax,1000,1e-5,1e0);
 //  h_dummy_attach_H2O->GetXaxis()->SetTitleOffset(1.2);
 //  h_dummy_attach_H2O->GetYaxis()->SetTitleOffset(1.25);
 //  h_dummy_attach_H2O->Draw();

 //  TGraph* g_attach_H2O_sedine2015_H2O_0ppm = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2015[0]));
 //  TGraph* g_attach_H2O_sedine2015_H2O_0p1ppm = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2015_H2O_0p1ppm[0]));
 //  TGraph* g_attach_H2O_sedine2015_H2O_1ppm = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2015_H2O_1ppm[0]));
 //  TGraph* g_attach_H2O_sedine2015_H2O_10ppm = new TGraph(EFields.size(), &(EFields[0]), &(attachVec_sedine2015_H2O_10ppm[0]));

 //  TLegend* leg_attach_H2O = new TLegend(0.2, 0.7, 0.35, 0.9);
 //  leg_attach_H2O->SetTextFont(42);
 //  leg_attach_H2O->SetBorderSize(0);
 //  leg_attach_H2O->SetFillColor(0);
 //  leg_attach_H2O->SetTextSize(0.035);
 //  leg_attach_H2O->SetFillStyle(1000);

 //  g_attach_H2O_sedine2015_H2O_0ppm->SetLineColor(kBlack);
 //  g_attach_H2O_sedine2015_H2O_0ppm->SetLineWidth(2);
 //  g_attach_H2O_sedine2015_H2O_0ppm->Draw("sameL");

 //  g_attach_H2O_sedine2015_H2O_0p1ppm->SetLineColor(kRed);
 //  g_attach_H2O_sedine2015_H2O_0p1ppm->SetLineWidth(2);
 //  g_attach_H2O_sedine2015_H2O_0p1ppm->Draw("sameL");

 //  g_attach_H2O_sedine2015_H2O_1ppm->SetLineColor(kBlue);
 //  g_attach_H2O_sedine2015_H2O_1ppm->SetLineWidth(2);
 //  g_attach_H2O_sedine2015_H2O_1ppm->Draw("sameL");

 //  g_attach_H2O_sedine2015_H2O_10ppm->SetLineColor(kViolet);
 //  g_attach_H2O_sedine2015_H2O_10ppm->SetLineWidth(2);
 //  g_attach_H2O_sedine2015_H2O_10ppm->Draw("sameL");

 //  leg_attach_H2O->SetHeader(label_sedine2015);
 //  leg_attach_H2O->AddEntry(g_attach_H2O_sedine2015_H2O_0ppm, "0 ppm H_{2}O", "L");
 //  leg_attach_H2O->AddEntry(g_attach_H2O_sedine2015_H2O_0p1ppm, "0.1 ppm H_{2}O", "L");
 //  leg_attach_H2O->AddEntry(g_attach_H2O_sedine2015_H2O_1ppm, "1 ppm H_{2}O", "L");
 //  leg_attach_H2O->AddEntry(g_attach_H2O_sedine2015_H2O_10ppm, "10 ppm H_{2}O", "L");
 //  leg_attach_H2O->Draw();
  
 //  SavePlots(c_attach_H2O, "attach_H2O",  plotDir);


 //  TCanvas* c_driftV_H2O = new TCanvas("c_driftV_H2O", "", 600, 600);
 //  c_driftV_H2O->SetLogx();
 //  c_driftV_H2O->SetLogy();

 //  TH2F* h_dummy_driftV_H2O=new TH2F("h_dummy_driftV_H2O","; Electric Field Strength [V/cm]; Drift Velocity [cm/ns]",10000,EMin,EMax,1000,1e-5,1e-2);
 //  h_dummy_driftV_H2O->GetXaxis()->SetTitleOffset(1.2);
 //  h_dummy_driftV_H2O->GetYaxis()->SetTitleOffset(1.25);
 //  h_dummy_driftV_H2O->Draw();

 //  TGraph* g_driftV_H2O_sedine2015_H2O_0ppm = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2015[0]));
 //  TGraph* g_driftV_H2O_sedine2015_H2O_0p1ppm = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2015_H2O_0p1ppm[0]));
 //  TGraph* g_driftV_H2O_sedine2015_H2O_1ppm = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2015_H2O_1ppm[0]));
 //  TGraph* g_driftV_H2O_sedine2015_H2O_10ppm = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2015_H2O_10ppm[0]));

 //  TLegend* leg_driftV_H2O = new TLegend(0.2, 0.7, 0.35, 0.9);
 //  leg_driftV_H2O->SetTextFont(42);
 //  leg_driftV_H2O->SetBorderSize(0);
 //  leg_driftV_H2O->SetFillColor(0);
 //  leg_driftV_H2O->SetTextSize(0.035);
 //  leg_driftV_H2O->SetFillStyle(1000);

 //  g_driftV_H2O_sedine2015_H2O_0ppm->SetLineColor(kBlack);
 //  g_driftV_H2O_sedine2015_H2O_0ppm->SetLineWidth(2);
 //  g_driftV_H2O_sedine2015_H2O_0ppm->Draw("sameL");

 //  g_driftV_H2O_sedine2015_H2O_0p1ppm->SetLineColor(kRed);
 //  g_driftV_H2O_sedine2015_H2O_0p1ppm->SetLineWidth(2);
 //  g_driftV_H2O_sedine2015_H2O_0p1ppm->Draw("sameL");

 //  g_driftV_H2O_sedine2015_H2O_1ppm->SetLineColor(kBlue);
 //  g_driftV_H2O_sedine2015_H2O_1ppm->SetLineWidth(2);
 //  g_driftV_H2O_sedine2015_H2O_1ppm->Draw("sameL");

 //  g_driftV_H2O_sedine2015_H2O_10ppm->SetLineColor(kViolet);
 //  g_driftV_H2O_sedine2015_H2O_10ppm->SetLineWidth(2);
 //  g_driftV_H2O_sedine2015_H2O_10ppm->Draw("sameL");

 //  leg_driftV_H2O->SetHeader(label_sedine2015);
 //  leg_driftV_H2O->AddEntry(g_driftV_H2O_sedine2015_H2O_0ppm, "0 ppm H_{2}O", "L");
 //  leg_driftV_H2O->AddEntry(g_driftV_H2O_sedine2015_H2O_0p1ppm, "0.1 ppm H_{2}O", "L");
 //  leg_driftV_H2O->AddEntry(g_driftV_H2O_sedine2015_H2O_1ppm, "1 ppm H_{2}O", "L");
 //  leg_driftV_H2O->AddEntry(g_driftV_H2O_sedine2015_H2O_10ppm, "10 ppm H_{2}O", "L");
 //  leg_driftV_H2O->Draw();
  
 //  SavePlots(c_driftV_H2O, "driftV_H2O",  plotDir);

 // TCanvas* c_diff_H2O = new TCanvas("c_diff_H2O", "", 600, 600);
 //  c_diff_H2O->SetLogx();
 //  c_diff_H2O->SetLogy();

 //  TH2F* h_dummy_diff_H2O=new TH2F("h_dummy_diff_H2O","; Electric Field Strength [V/cm]; Diffusion Coefficienct [cm^{1/2}]",10000,EMin,EMax,1000,1e-2,1e0);
 //  h_dummy_diff_H2O->GetXaxis()->SetTitleOffset(1.2);
 //  h_dummy_diff_H2O->GetYaxis()->SetTitleOffset(1.25);
 //  h_dummy_diff_H2O->Draw();

 //  TLegend* leg_diff_H2O = new TLegend(0.2, 0.9, 0.35, 0.92);
 //  leg_diff_H2O->SetTextFont(42);
 //  leg_diff_H2O->SetBorderSize(0);
 //  leg_diff_H2O->SetFillColor(0);
 //  leg_diff_H2O->SetTextSize(0.035);
 //  leg_diff_H2O->SetFillStyle(1000);

 //  TLegend* leg_longDiff_H2O = new TLegend(0.2, 0.675, 0.35, 0.875);
 //  leg_longDiff_H2O->SetTextFont(42);
 //  leg_longDiff_H2O->SetBorderSize(0);
 //  leg_longDiff_H2O->SetFillColor(0);
 //  leg_longDiff_H2O->SetTextSize(0.035);
 //  leg_longDiff_H2O->SetFillStyle(1000);

 //  TLegend* leg_transDiff_H2O = new TLegend(0.55, 0.675, 0.7, 0.875);
 //  leg_transDiff_H2O->SetTextFont(42);
 //  leg_transDiff_H2O->SetBorderSize(0);
 //  leg_transDiff_H2O->SetFillColor(0);
 //  leg_transDiff_H2O->SetTextSize(0.035);
 //  leg_transDiff_H2O->SetFillStyle(1000);

 //  leg_diff_H2O->SetHeader(label_sedine2015);
 //  leg_diff_H2O->Draw();

 //  TGraph* g_longDiff_H2O_sedine2015_H2O_0ppm = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2015[0]));
 //  TGraph* g_longDiff_H2O_sedine2015_H2O_0p1ppm = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2015_H2O_0p1ppm[0]));
 //  TGraph* g_longDiff_H2O_sedine2015_H2O_1ppm = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2015_H2O_1ppm[0]));
 //  TGraph* g_longDiff_H2O_sedine2015_H2O_10ppm = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2015_H2O_10ppm[0]));
  
 //  g_longDiff_H2O_sedine2015_H2O_0ppm->SetLineColor(kBlack);
 //  g_longDiff_H2O_sedine2015_H2O_0ppm->SetLineWidth(2);
 //  g_longDiff_H2O_sedine2015_H2O_0ppm->Draw("sameL");

 //  g_longDiff_H2O_sedine2015_H2O_0p1ppm->SetLineColor(kRed);
 //  g_longDiff_H2O_sedine2015_H2O_0p1ppm->SetLineWidth(2);
 //  g_longDiff_H2O_sedine2015_H2O_0p1ppm->Draw("sameL");

 //  g_longDiff_H2O_sedine2015_H2O_1ppm->SetLineColor(kBlue);
 //  g_longDiff_H2O_sedine2015_H2O_1ppm->SetLineWidth(2);
 //  g_longDiff_H2O_sedine2015_H2O_1ppm->Draw("sameL");

 //  g_longDiff_H2O_sedine2015_H2O_10ppm->SetLineColor(kViolet);
 //  g_longDiff_H2O_sedine2015_H2O_10ppm->SetLineWidth(2);
 //  g_longDiff_H2O_sedine2015_H2O_10ppm->Draw("sameL");

 //  leg_longDiff_H2O->SetHeader("Longitudinal Diffusion");
 //  leg_longDiff_H2O->AddEntry(g_longDiff_H2O_sedine2015_H2O_0ppm, "0 ppm H_{2}O", "L");
 //  leg_longDiff_H2O->AddEntry(g_longDiff_H2O_sedine2015_H2O_0p1ppm, "0.1 ppm H_{2}O", "L");
 //  leg_longDiff_H2O->AddEntry(g_longDiff_H2O_sedine2015_H2O_1ppm, "1 ppm H_{2}O", "L");
 //  leg_longDiff_H2O->AddEntry(g_longDiff_H2O_sedine2015_H2O_10ppm, "10 ppm H_{2}O", "L");
 //  leg_longDiff_H2O->Draw();

 //  TGraph* g_transDiff_H2O_sedine2015_H2O_0ppm = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2015[0]));
 //  TGraph* g_transDiff_H2O_sedine2015_H2O_0p1ppm = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2015_H2O_0p1ppm[0]));
 //  TGraph* g_transDiff_H2O_sedine2015_H2O_1ppm = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2015_H2O_1ppm[0]));
 //  TGraph* g_transDiff_H2O_sedine2015_H2O_10ppm = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2015_H2O_10ppm[0]));

 //  g_transDiff_H2O_sedine2015_H2O_0ppm->SetLineColor(kBlack);
 //  g_transDiff_H2O_sedine2015_H2O_0ppm->SetLineStyle(kDashed);
 //  g_transDiff_H2O_sedine2015_H2O_0ppm->SetLineWidth(2);
 //  g_transDiff_H2O_sedine2015_H2O_0ppm->Draw("sameL");

 //  g_transDiff_H2O_sedine2015_H2O_0p1ppm->SetLineColor(kRed);
 //  g_transDiff_H2O_sedine2015_H2O_0p1ppm->SetLineStyle(kDashed);
 //  g_transDiff_H2O_sedine2015_H2O_0p1ppm->SetLineWidth(2);
 //  g_transDiff_H2O_sedine2015_H2O_0p1ppm->Draw("sameL");

 //  g_transDiff_H2O_sedine2015_H2O_1ppm->SetLineColor(kBlue);
 //  g_transDiff_H2O_sedine2015_H2O_1ppm->SetLineStyle(kDashed);
 //  g_transDiff_H2O_sedine2015_H2O_1ppm->SetLineWidth(2);
 //  g_transDiff_H2O_sedine2015_H2O_1ppm->Draw("sameL");

 //  g_transDiff_H2O_sedine2015_H2O_10ppm->SetLineColor(kViolet);
 //  g_transDiff_H2O_sedine2015_H2O_10ppm->SetLineStyle(kDashed);
 //  g_transDiff_H2O_sedine2015_H2O_10ppm->SetLineWidth(2);
 //  g_transDiff_H2O_sedine2015_H2O_10ppm->Draw("sameL");

 //  leg_transDiff_H2O->SetHeader("Transverse Diffusion");
 //  leg_transDiff_H2O->AddEntry(g_transDiff_H2O_sedine2015_H2O_0ppm, "0 ppm H_{2}O", "L");
 //  leg_transDiff_H2O->AddEntry(g_transDiff_H2O_sedine2015_H2O_0p1ppm, "0.1 ppm H_{2}O", "L");
 //  leg_transDiff_H2O->AddEntry(g_transDiff_H2O_sedine2015_H2O_1ppm, "1 ppm H_{2}O", "L");
 //  leg_transDiff_H2O->AddEntry(g_transDiff_H2O_sedine2015_H2O_10ppm, "10 ppm H_{2}O", "L");
 //  leg_transDiff_H2O->Draw();
  
 //  SavePlots(c_diff_H2O, "diff_H2O",  plotDir);


 //  // TCanvas* c_driftV = new TCanvas("c_driftV", "", 600, 600);
 //  // c_driftV->SetLogx();
 //  // c_driftV->SetLogy();

 //  // TH2F* h_dummy_driftV=new TH2F("h_dummy_driftV","; Electric Field Strength [V/cm]; Drift Velocity [cm/ns]",10000,EMin,EMax,1000,1e-5,1e-1);
 //  // h_dummy_driftV->GetXaxis()->SetTitleOffset(1.2);
 //  // h_dummy_driftV->GetYaxis()->SetTitleOffset(1.25);
 //  // h_dummy_driftV->Draw();

 //  // TGraph* g_driftV_sedine2015 = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2015[0]));
 //  // TGraph* g_driftV_sedine2018 = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2018[0]));
 //  // TGraph* g_driftV_sedine2019 = new TGraph(EFields.size(), &(EFields[0]), &(driftVVec_sedine2019[0]));

 //  // TLegend* leg_driftV = new TLegend(0.2, 0.8, 0.9, 0.9);

 //  // g_driftV_sedine2015->SetLineColor(kBlack);
 //  // g_driftV_sedine2015->SetLineWidth(2);
 //  // g_driftV_sedine2015->Draw("sameL");

 //  // g_driftV_sedine2018->SetLineColor(kRed);
 //  // g_driftV_sedine2018->SetLineWidth(2);
 //  // g_driftV_sedine2018->Draw("sameL");

 //  // g_driftV_sedine2019->SetLineColor(kBlue);
 //  // g_driftV_sedine2019->SetLineWidth(2);
 //  // g_driftV_sedine2019->Draw("sameL");

 //  // leg_driftV->SetHeader("Gas Composition");
 //  // leg_driftV->AddEntry(g_driftV_sedine2015, label_sedine2015, "L");
 //  // leg_driftV->AddEntry(g_driftV_sedine2018, label_sedine2018, "L");
 //  // leg_driftV->AddEntry(g_driftV_sedine2019, label_sedine2019, "L");
 //  // leg_driftV->SetBorderSize(0);
 //  // leg_driftV->Draw();
  
 //  // SavePlots(c_driftV, "driftV",  plotDir);

 //  // TCanvas* c_diff = new TCanvas("c_diff", "", 600, 600);
 //  // c_diff->SetLogx();
 //  // c_diff->SetLogy();

 //  // TH2F* h_dummy_diff=new TH2F("h_dummy_diff","; Electric Field Strength [V/cm]; Diffusion Coefficient [cm^{1/2}]",10000,EMin,EMax,1000,1e-2,1);
 //  // h_dummy_diff->GetXaxis()->SetTitleOffset(1.2);
 //  // h_dummy_diff->GetYaxis()->SetTitleOffset(1.25);
 //  // h_dummy_diff->Draw();
  
 //  // TGraph* g_longDiff_sedine2015 = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2015[0]));
 //  // TGraph* g_longDiff_sedine2018 = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2018[0]));
 //  // TGraph* g_longDiff_sedine2019 = new TGraph(EFields.size(), &(EFields[0]), &(longDiffVec_sedine2019[0]));
 //  // TGraph* g_transDiff_sedine2015 = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2015[0]));
 //  // TGraph* g_transDiff_sedine2018 = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2018[0]));
 //  // TGraph* g_transDiff_sedine2019 = new TGraph(EFields.size(), &(EFields[0]), &(transDiffVec_sedine2019[0]));
  
 //  // TLegend* leg_diff_sedine2015 = new TLegend(0.5, 0.8, 0.8, 0.9);
 //  // TLegend* leg_diff_sedine2018 = new TLegend(0.5, 0.65, 0.9, 0.75);
 //  // TLegend* leg_diff_sedine2019 = new TLegend(0.5, 0.5, 0.8, 0.6);

 //  // g_longDiff_sedine2015->SetLineColor(kBlack);
 //  // g_longDiff_sedine2015->SetLineWidth(2);
 //  // g_longDiff_sedine2015->Draw("sameL");
 
 //  // g_transDiff_sedine2015->SetLineColor(kBlack);
 //  // g_transDiff_sedine2015->SetLineStyle(kDashed);
 //  // g_transDiff_sedine2015->SetLineWidth(2);
 //  // g_transDiff_sedine2015->Draw("sameL");

 //  // leg_diff_sedine2015->SetHeader(label_sedine2015);
 //  // leg_diff_sedine2015->AddEntry(g_longDiff_sedine2015, "Longitudinal", "L");
 //  // leg_diff_sedine2015->AddEntry(g_transDiff_sedine2015, "Transverse", "L");
 //  // leg_diff_sedine2015->SetBorderSize(0);
 //  // leg_diff_sedine2015->Draw();

 //  // g_longDiff_sedine2018->SetLineColor(kRed);
 //  // g_longDiff_sedine2018->SetLineWidth(2);
 //  // g_longDiff_sedine2018->Draw("sameL");

 //  // g_transDiff_sedine2018->SetLineColor(kRed);
 //  // g_transDiff_sedine2018->SetLineStyle(kDashed);
 //  // g_transDiff_sedine2018->SetLineWidth(2);
 //  // g_transDiff_sedine2018->Draw("sameL");

 //  // leg_diff_sedine2018->SetHeader(label_sedine2018);
 //  // leg_diff_sedine2018->AddEntry(g_longDiff_sedine2018, "Longitudinal", "L");
 //  // leg_diff_sedine2018->AddEntry(g_transDiff_sedine2018, "Transverse", "L");
 //  // leg_diff_sedine2018->SetBorderSize(0);
 //  // leg_diff_sedine2018->Draw();

 //  // g_longDiff_sedine2019->SetLineColor(kBlue);
 //  // g_longDiff_sedine2019->SetLineWidth(2);
 //  // g_longDiff_sedine2019->Draw("sameL");

 //  // g_transDiff_sedine2019->SetLineColor(kBlue);
 //  // g_transDiff_sedine2019->SetLineStyle(kDashed);
 //  // g_transDiff_sedine2019->SetLineWidth(2);
 //  // g_transDiff_sedine2019->Draw("sameL");

 //  // leg_diff_sedine2019->SetHeader(label_sedine2019);
 //  // leg_diff_sedine2019->AddEntry(g_longDiff_sedine2019, "Longitudinal", "L");
 //  // leg_diff_sedine2019->AddEntry(g_transDiff_sedine2019, "Transverse", "L");
 //  // leg_diff_sedine2019->SetBorderSize(0);
 //  // leg_diff_sedine2019->Draw();
  
 //  // SavePlots(c_diff, "diff",  plotDir);


  app.Run(); // Keeps up canvas
  return 0;
} 

//He_72p5_Ne_25_CH4_2p5


//=================================FUNCTIONS=================================//

void SavePlots(TCanvas* canvas, TString plotName, TString dirName)
{
  canvas->Print(dirName + "/" + plotName + ".eps");
  canvas->Print(dirName + "/" + plotName + ".pdf");
  canvas->Print(dirName + "/" + plotName + ".png");
  canvas->Print(dirName + "/" + plotName + ".root");
  canvas->Print(dirName + "/" + plotName + ".C");
  return;
}

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
  H2O_2->LoadGasFile("../output/He_72p5_Ne_25_CH4_2p5_1ppm_H2O.gas");
  TransportParameters* parameters1 = new TransportParameters(pure, O2, H2O, label);
  parameters1->SetWaterFile(H2O_2);

  MediumMagboltz* H2O_3 = new MediumMagboltz();
  H2O_3->LoadGasFile("../output/He_72p5_Ne_25_CH4_2p5_10ppm_H2O.gas");
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
    H2O_3->LoadGasFile("../output/He_90_CH4_10_10ppm_H2O.gas");
    TransportParameters* parameters2 = new TransportParameters(pure, O2, H2O, label);
    parameters2->SetWaterFile(H2O_3);*/
  
