#include <iostream>
#include <string> 
#include <vector>

#include <TROOT.h>
#include <TLatex.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TString.h>

#include "MediumMagboltz.hh"
#include "FundamentalConstants.hh"

#include "TransportParameters.hh"

void rootlogonATLAS(double ytoff = 1.0, bool atlasmarker =true, double left_margin=0.14);

void SavePlots(TCanvas* canvas, TString plotName, TString dirName);

std::vector<double> GenerateEFieldPoints(double npoints, double EMax, double EMin); //Generate logarithmically spaced E-Field Points between EMin and EMax for use in plotting.

std::vector<double> GetAttachmentVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType, double O2ppm, double refPurity=50.); //Function for Oxygen attachment scaling

int main(int argc, char *argv[])
{
  if(argc == 1)
    {
      puts("ERROR: Must run code with argument 1 (1.1 bar) or 0 (0.2 bar). Exiting.");
      return 0;
    }

  TApplication app("app", &argc, argv);
  TGaxis::SetMaxDigits(3);

  rootlogonATLAS();
  TString plotDir{"./Plots"};

  Garfield::MediumMagboltz* pureGas = new Garfield::MediumMagboltz();
  Garfield::MediumMagboltz* contaminatedGas = new Garfield::MediumMagboltz();

  // Gases to load in
  pureGas->LoadGasFile("../gasFile_150_50_Ar_98_CH4.gas");
  contaminatedGas->EnableDebugging();
  contaminatedGas->LoadGasFile("../gasFile_150_100_Ar_98_CH4_imp_O2_50.gas");//../gasFile_150_50_Ar_98_CH4_imp_O2_50.gas");

  TransportParameters* parameters = new TransportParameters(pureGas, contaminatedGas, NULL, "Ar:CH_{4} (98%:2%)");

  //Set up EField points vector
  int nPoints = 1000;
  double EMax = 5.e4;
  double EMin = 1.e-2;
  bool highPressure = std::stoi(argv[1]);
  double pressure = 0;
  TString plotString = "";
  double legSize = 0;
  double x = 0;
  double y = 0;
  double legX[2] = {0.,0.};
  if (highPressure){
    pressure = 1.1; //bar
    plotString = "1p1bar";
    x = 0.35;
    y = 0.85;
    legSize = 0.025;
    legX[0] = 0.75;
    legX[1] = 0.9;
  }
  else {
    pressure = 0.2;
    plotString = "200mbar";
    x = 0.3;
    y = 0.85; 
    legSize = 0.025;
    legX[0] = 0.65;
    legX[1] = 0.9;
  }

  
  std::vector<double> EFields = GenerateEFieldPoints(nPoints, EMax, EMin);
  
  // O2 ppm for attachment scaling
  std::vector<double> o2ppm{5.,1.,0.5,0.2,0.1,0};//50.,20.,10.,
  std::vector<std::vector<double>> attachmentPoints;

  // Calculate attachment
  for(int iConc = 0; iConc < o2ppm.size(); ++iConc){
    attachmentPoints.push_back(GetAttachmentVector(parameters, EFields, pressure, 1, o2ppm.at(iConc),50.));
  }

  // Make a graph showing the plot
  TCanvas* c = new TCanvas("c", "", 600, 600);
  c->SetLogx();
  c->SetLogy();

  TH2F* h_dummy=new TH2F("h_dummy","; Electric Field Strength [V/cm]; Attachment Coefficient [1/cm]",10000,EMin,EMax,1000,0.5e-5,0.5e0);
  h_dummy->GetXaxis()->SetTitleOffset(1.2);
  h_dummy->GetYaxis()->SetTitleOffset(1.25);
  h_dummy->Draw();

  double size = 0.035;
  TLatex* p = new TLatex(); 
  p->SetNDC();
  p->SetTextSize(size);//l->SetTextAlign(12);
  p->SetTextFont(42);
  p->SetTextColor(kBlack);
  if (pressure < 1.){ // use mbar as unit
    p->DrawLatex(x,y,"Ar:CH_{4} (98%:2%) " + static_cast<TString>(Form("%1.3g mbar", pressure*1e3)));
  }
  else{
    p->DrawLatex(x,y,"Ar:CH_{4} (98%:2%) " + static_cast<TString>(Form("%1.3g bar", pressure)));
  }
  
  TLegend* leg = new TLegend(legX[0], 0.15, legX[1], 0.5);
  leg->SetHeader("O_{2} Contamination");
  leg->SetTextFont(42);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(legSize);
  leg->SetFillStyle(1000);

  // Styling for the plot lines
  std::vector<TGraph*> attachmentGraphs;
  for(int iConc = 0; iConc < o2ppm.size(); ++iConc){
    TGraph* graph = new TGraph{EFields.size(), &(EFields[0]), &(attachmentPoints.at(iConc)[0])};
    int colour = 0;
    int style = 0;
    switch (iConc){
    case 0:
      colour = kBlue + 2;
      style = 9;
      break;
    // case 1:
    //   colour = kAzure + 9;
    //   break;
    // case 2:
    //   colour = kCyan + 1;
    //   break;
    case 1:
      colour = kGreen - 3;
      style = 6;
      break;
    case 2:
      colour = kOrange - 3;
      style = kDashed;
      break;
    case 3:
      colour = kRed;
      style = 10;
      break;
    case 4:
      colour = kMagenta + 1;
      style = 7;
      break;
    case 5:
      colour = kBlack;
      style = kSolid;
      break;
    default:
      break;
    }
    graph->SetLineColor(colour);
    graph->SetLineWidth(2.5);
    graph->SetLineStyle(style);
    graph->Draw("sameL");
    leg->AddEntry(graph, Form("%1.3g ppm ",o2ppm.at(iConc)),  "L");
    attachmentGraphs.push_back(graph);
  }

  leg->Draw();

  SavePlots(c, "o2attachment_" + plotString,  plotDir);

  puts("Plots generated: do ^C (ctrl-C/cmd-C) to leave interactive mode and exit");
  app.Run();
  return 0;
}



//=================================FUNCTIONS=================================//

void SavePlots(TCanvas* canvas, TString plotName, TString dirName)
{
  canvas->Print(dirName + "/" + plotName + ".eps");
  canvas->Print(dirName + "/" + plotName + ".pdf");
  canvas->Print(dirName + "/" + plotName + ".png");
  // canvas->Print(dirName + "/" + plotName + ".root");
  // canvas->Print(dirName + "/" + plotName + ".C");
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

std::vector<double> GetAttachmentVector(TransportParameters* gas, std::vector<double> EFields, double pressureBar, int impurityType, double O2ppm, double refPurity)
{
  std::vector<double> etaVec;
  double eta;
  
  if(impurityType == 1)
    for(unsigned int iPoint = 0; iPoint < EFields.size(); iPoint++)
      {
	eta = gas->GetElectronAttachment(EFields[iPoint], pressureBar, impurityType, O2ppm, refPurity);
	etaVec.push_back(eta);
      }
  else
    {
      std::cout << "[transportPlots] ERROR: Entered a value for O2 contamination for impurity type != 1 \n"
		<< "Perhaps you meant to use GetAttachmentVector(TransportParameters*, std::vector<double>, double, int, double)?" << std::endl;
    }
  
  
  return etaVec;  
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
