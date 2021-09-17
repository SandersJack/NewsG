#include <iostream>

#include <TROOT.h>
#include <TF1.h>
#include <TAxis.h>
#include <TCanvas.h>

#include "Garfield/PlottingEngineRoot.hh"

namespace Garfield {

PlottingEngineRoot plottingEngine;

PlottingEngineRoot::PlottingEngineRoot()
    : PlottingEngine("PlottingEngineRoot"), 
      m_garfieldStyle("Garfield", "Garfield Style") {}

PlottingEngineRoot::~PlottingEngineRoot() {}

void PlottingEngineRoot::SetDefaultStyle() {
  m_garfieldStyle.Reset();
  m_garfieldStyle.SetFillColor(1);
  m_garfieldStyle.SetFillStyle(1001);
  m_garfieldStyle.SetCanvasBorderMode(0);
  m_garfieldStyle.SetCanvasColor(0);
  m_garfieldStyle.SetCanvasDefH(600);
  m_garfieldStyle.SetCanvasDefW(600);
  m_garfieldStyle.SetPadBorderMode(0);
  m_garfieldStyle.SetPadColor(0);
  m_garfieldStyle.SetPadLeftMargin(0.15);
  m_garfieldStyle.SetPadBottomMargin(0.1);
  m_garfieldStyle.SetPadRightMargin(0.05);
  m_garfieldStyle.SetPadTopMargin(0.05);
  m_garfieldStyle.SetPadTickX(1);
  m_garfieldStyle.SetPadTickY(1);
  m_garfieldStyle.SetFrameFillColor(0);
  m_garfieldStyle.SetFrameBorderMode(0);
  m_garfieldStyle.SetDrawBorder(0);
  m_garfieldStyle.SetLegendBorderSize(0);

  m_garfieldStyle.SetGridColor(kGray);
  m_garfieldStyle.SetGridStyle(3);
  m_garfieldStyle.SetGridWidth(1);
  m_garfieldStyle.SetPadGridX(kTRUE);
  m_garfieldStyle.SetPadGridY(kTRUE);

  const short font = m_serif ? 132 : 42;
  const double tsize = 0.04;
  m_garfieldStyle.SetTextFont(font);
  m_garfieldStyle.SetTextSize(tsize);
  m_garfieldStyle.SetTitleStyle(0);
  m_garfieldStyle.SetTitleBorderSize(0);
  m_garfieldStyle.SetTitleColor(1, "xyz");
  m_garfieldStyle.SetTitleColor(1, "t");
  m_garfieldStyle.SetTitleFillColor(0);
  m_garfieldStyle.SetTitleFont(font, "xyz");
  m_garfieldStyle.SetTitleFont(font, "t");
  m_garfieldStyle.SetTitleOffset(1.2, "x");
  m_garfieldStyle.SetTitleOffset(0, "y");
  m_garfieldStyle.SetTitleSize(tsize, "xyz");
  m_garfieldStyle.SetTitleSize(tsize, "t");

  m_garfieldStyle.SetLegendFont(font);
  m_garfieldStyle.SetStatStyle(0);
  m_garfieldStyle.SetStatBorderSize(0);
  m_garfieldStyle.SetStatColor(0);
  m_garfieldStyle.SetStatFont(font);
  m_garfieldStyle.SetStatFontSize(tsize);
  m_garfieldStyle.SetStatX(0.88);
  m_garfieldStyle.SetStatY(0.88);
  m_garfieldStyle.SetStatW(0.25);
  m_garfieldStyle.SetStatH(0.1);
  m_garfieldStyle.SetOptStat(111110);
  m_garfieldStyle.SetStatFormat("6.3g");
  m_garfieldStyle.SetLabelFont(font, "xyz");
  m_garfieldStyle.SetLabelSize(tsize, "xyz");
  m_garfieldStyle.SetLabelOffset(0.01, "xyz");
  m_garfieldStyle.SetOptTitle(0);
  m_garfieldStyle.SetPaperSize(TStyle::kA4);
  m_garfieldStyle.SetFuncWidth(2);
  m_garfieldStyle.SetHistLineColor(kOrange - 3);
  // m_garfieldStyle.SetPalette(1);
  m_garfieldStyle.SetAxisColor(kBlack, "X");
  m_garfieldStyle.SetAxisColor(kBlack, "Y");
  m_garfieldStyle.SetAxisColor(kBlack, "Z");
  m_garfieldStyle.SetNdivisions(505, "x");
  m_garfieldStyle.SetNdivisions(510, "y");
  m_garfieldStyle.SetMarkerStyle(20);
  m_garfieldStyle.SetMarkerSize(1.2);
  const short lw = 2;
  m_garfieldStyle.SetLineWidth(lw);
  m_garfieldStyle.SetLineStyleString(2, "[12 12]");
  m_garfieldStyle.SetFrameLineWidth(lw);
  m_garfieldStyle.SetHistLineWidth(lw);
  m_garfieldStyle.SetFuncWidth(lw);
  m_garfieldStyle.SetGridWidth(lw);

  m_garfieldStyle.SetMarkerSize(1.2);

  const Int_t NRGBs = 5;
  const int NCont = 255;
 
  double stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  double red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  double green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  double blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };

  int FI = TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  int MyPalette[NCont];
  for (int i=0;i<NCont;i++)
    MyPalette[i] = FI+i;
  
  m_garfieldStyle.SetNumberContours(NCont);
  m_garfieldStyle.SetPalette(NCont,MyPalette);
  m_garfieldStyle.cd();
}

}