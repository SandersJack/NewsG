#include "TROOT.h"
#include <TApplication.h>
#include "TCanvas.h"
#include <TStyle.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TFile.h>
#include <TLatex.h>
#include <iostream>
#include <string>

#include "MediumMagboltz.hh"

using namespace Garfield;

void SavePlots(TCanvas* canvas, TString plotName, TString dirName);

void rootlogonATLAS(double ytoff = 1.0, bool atlasmarker =true, double left_margin=0.14);

int main(int argc, char *argv[]) {
  //TApplication app("app", &argc, argv);
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};
  typedef std::vector<std::string>::size_type size_type;
  const size_type nArgs {cmdLineArgs.size()};

  TGaxis::SetMaxDigits(3);

  double x = 0.55;
  double y = 0.25;
  double size = 0.03;
  double legX[2] = {0.17,0.37};

  TLatex p; 
  p.SetNDC();
  p.SetTextSize(size);
  p.SetTextFont(42);
  p.SetTextColor(kBlack);
      
  TLatex q; 
  q.SetNDC();
  q.SetTextSize(size);
  q.SetTextFont(42);
  q.SetTextColor(kBlack);

  TLatex r; 
  r.SetNDC();
  r.SetTextSize(size);
  r.SetTextFont(42);
  r.SetTextColor(kBlack);

  int gasType = 0;
  int config = 0;

  for (size_type i {1}; i < nArgs; ++i) {
    if (cmdLineArgs[i] == "--gasType") {
      gasType = std::stoi(cmdLineArgs[i+1]);
      ++i;
    }
    if (cmdLineArgs[i] == "--config") {
      config = std::stoi(cmdLineArgs[i+1]);
      ++i;
    }
  }
  rootlogonATLAS();
  
  std::string gasString = "";
  TString plotString = ""; 
  TString legString = "";
  TString voltString = "";
  double minimum = 0.;
  switch (gasType){
  case 0:
    // gasString = "../gasFile_840_50_Ar_98_CH4";
    plotString = "Ar_98_CH4"; 
    legString = "Ar:CH_{4} (98%:2%)";
    break;
  case 1:
    gasString = "../gasFile_850_100_Xe";
    plotString = "Xe"; 
    legString = "Xe (100%)";
    break;
  default:
    // gasString = "../gasFile_840_50_Ar_98_CH4";
    plotString = "Ar_98_CH4"; 
    legString = "Ar:CH_{4} (98%:2%)";
    break;
  }
  
  TString plotDir = "./AvalancheProbabilityPlots/";
  switch (config){
  case 0:
    plotDir += "1p1bar_2000V";
    gasString = "../gasFile_840_50_Ar_98_CH4";
    legString += "; 1.1 bar";
    voltString = "; 2000 V";
    break;
  case 1:
    plotDir += "0p2bar_720V";
    gasString = "../gasFile_150_50_Ar_98_CH4";
    legString += "; 200 mbar";
    voltString = "; 720 V";
    minimum = 0.95;
    break;
  default:
    plotDir += "1p1bar_2000V";
    gasString = "../gasFile_840_50_Ar_98_CH4";
    legString += "; 1.1 bar";
    voltString = "; 2000 V";
    break;
  }

  MediumMagboltz* gas = new MediumMagboltz();
  MediumMagboltz* pureGas = new MediumMagboltz();
  
  // Pure gas
  std::string pureGasString = gasString + ".gas";
  pureGas->LoadGasFile(pureGasString);
  
  // Gas pressure
  double pressure = 1.1; //bar
  if(config == 1){
    pressure = 0.2;
  }
  double barToTorr = 750.062;

  // Properties of ideal spherical proportional counter
  double dr = 0.005; //Units in cm
  double r_i = 0.1;  //Radius of inner sphere (cm)
  double r_o = 20.;  //Radius of outer sphere (cm) 
  double V_0 = 2000; //Voltage of inner sphere (V) (outer one = 0 V)
  if(config == 1){
    V_0 = 720;
  }

  double A = V_0 * ((r_i * r_o)/(r_o - r_i)); //Constant of proportionality in E = A/(r^2)
  double nSteps = (r_o - r_i)/dr;             //Number of steps in the simulation
  
  std::cout << "Constant of proportionality = " << A << " [V cm]" << std::endl;
  std::cout << "Number of Steps = " << nSteps << std::endl;

  
  //==========AVALANCHE SURVIVAL==========//

  TLegend* probabilityLegend = new TLegend(legX[0],0.15,legX[1],0.40);
  probabilityLegend->SetHeader("O_{2} Contamination");
  probabilityLegend->SetTextFont(42);
  probabilityLegend->SetBorderSize(0);
  probabilityLegend->SetFillColor(0);
  probabilityLegend->SetTextSize(0.03);
  probabilityLegend->SetFillStyle(1000);

  TLegend* normalisedLegend =  new TLegend(legX[0],0.15,legX[1],0.40);
  normalisedLegend->SetHeader("O_{2} Contamination");
  normalisedLegend->SetTextFont(42);
  normalisedLegend->SetBorderSize(0);
  normalisedLegend->SetFillColor(0);
  normalisedLegend->SetTextSize(0.03);
  normalisedLegend->SetFillStyle(1000);

  TLegend* varianceLegend =  new TLegend(legX[0],0.85,legX[1],0.60 );
  varianceLegend->SetHeader("O_{2} Contamination");
  varianceLegend->SetTextFont(42);
  varianceLegend->SetBorderSize(0);
  varianceLegend->SetFillColor(0);
  varianceLegend->SetTextSize(0.03);
  varianceLegend->SetFillStyle(1000);

  TLegend* varianceNormLegend =  new TLegend(legX[0],0.85,legX[1],0.60 );
  varianceNormLegend->SetHeader("O_{2} Contamination");
  varianceNormLegend->SetTextFont(42);
  varianceNormLegend->SetBorderSize(0);
  varianceNormLegend->SetFillColor(0);
  varianceNormLegend->SetTextSize(0.03);
  varianceNormLegend->SetFillStyle(1000);

  TLegend* stdDevLegend =  new TLegend(legX[0],0.85,legX[1],0.60 );
  stdDevLegend->SetHeader("O_{2} Contamination");
  stdDevLegend->SetTextFont(42);
  stdDevLegend->SetBorderSize(0);
  stdDevLegend->SetFillColor(0);
  stdDevLegend->SetTextSize(0.03);
  stdDevLegend->SetFillStyle(1000);

  TLegend* stdDevNormLegend =  new TLegend(legX[0],0.85,legX[1],0.60 );
  stdDevNormLegend->SetHeader("O_{2} Contamination");
  stdDevNormLegend->SetTextFont(42);
  stdDevNormLegend->SetBorderSize(0);
  stdDevNormLegend->SetFillColor(0);
  stdDevNormLegend->SetTextSize(0.03);
  stdDevNormLegend->SetFillStyle(1000);

  TLegend* stdDevMeanLegend =  new TLegend(legX[0],0.85,legX[1],0.60 );
  stdDevMeanLegend->SetHeader("O_{2} Contamination");
  stdDevMeanLegend->SetTextFont(42);
  stdDevMeanLegend->SetBorderSize(0);
  stdDevMeanLegend->SetFillColor(0);
  stdDevMeanLegend->SetTextSize(0.03);
  stdDevMeanLegend->SetFillStyle(1000);

  TLegend* stdDevMeanNormLegend =  new TLegend(legX[0],0.85,legX[1],0.60 );
  stdDevMeanNormLegend->SetHeader("O_{2} Contamination");
  stdDevMeanNormLegend->SetTextFont(42);
  stdDevMeanNormLegend->SetBorderSize(0);
  stdDevMeanNormLegend->SetFillColor(0);
  stdDevMeanNormLegend->SetTextSize(0.03);
  stdDevMeanNormLegend->SetFillStyle(1000);

  std::vector<TGraph*> probabilityGraphs;   
  std::vector<TGraph*> normalisedGraphs;   
  std::vector<TGraph*> varianceGraphs;   
  std::vector<TGraph*> varianceNormGraphs;   
  std::vector<TGraph*> stdDevGraphs;   
  std::vector<TGraph*> stdDevNormGraphs;   
  std::vector<TGraph*> stdDevMeanGraphs;   
  std::vector<TGraph*> stdDevMeanNormGraphs;   


  //==========AVALANCHE VARIANCE==========//
  double energy = 5.3e6; //eV
  double wValue = 26;    //eV - Argon
  if (gasType == 1)
    {wValue = 22;} // eV - Xenon
  double nElecs = energy/wValue;


  std::vector<double> PvecPure; //Vector to store the probability of survival
  std::vector<double> varianceVecPure; //Vector to store the probability of survival
  std::vector<double> stdDevVecPure; //Vector to store the probability of survival
  std::vector<double> stdDevMeanVecPure; //Vector to store the probability of survival
  // Each loop makes the plot for a different concentration of oxygen
  for (int igas=0; igas<6; igas++)
    {
      std::string currentGasString = gasString;
      double refImpurity = 50.; //ppm
      switch (igas){
      case 0:
	break;
      case 1:
	currentGasString += "_imp_O2_50";
	refImpurity = 50.; //ppm
	break;
      case 2:
	currentGasString += "_imp_O2_50";
	refImpurity = 50.; //ppm
	break;
      case 3:
	currentGasString += "_imp_O2_50";
	refImpurity = 50.; //ppm
	break;
      case 4:
	currentGasString += "_imp_O2_50";
	refImpurity = 50.; //ppm
	break;
      case 5:
	currentGasString += "_imp_O2_50";
	refImpurity = 50.; //ppm
	break;
      default:
	currentGasString += "_imp_O2_50";
	refImpurity = 50.; //ppm
	break;
      }

      currentGasString += ".gas";
      
      gas->LoadGasFile(currentGasString);
      
      gas->SetPressure(pressure*barToTorr);
      std::vector<double> Cvec; //Vector to store the value of (eta_av - alpha_av)*dr at each step
      std::vector<double> rvec; //Vector to store the position of starting point in the detector
      std::vector<double> Pvec; //Vector to store the probability of avalanche
      std::vector<double> PvecNorm; //Vector to store the probability of survival (normalised)
      std::vector<double> varianceVec; //Vector to store the variance
      std::vector<double> varianceNormVec; //Vector to store the variance (normalised)
      std::vector<double> stdDevVec; //Vector to store the standard deviation 
      std::vector<double> stdDevNormVec; //Vector to store the standard deviation (normalised)
      std::vector<double> stdDevMeanVec; //Vector to store the standard deviation 
      std::vector<double> stdDevMeanNormVec; //Vector to store the standard deviation (normalised)

      for (int iStep = 0; iStep < nSteps; iStep++)
	{
	  double r_av = r_o - (iStep*dr + dr/2);               //Midpoint between steps
	  double E_av = A/(r_av*r_av);                         //E-Field at midpoint
	  double eta_av;                                       //Attachment coefficient at midpoint variable [1/cm]
	  double eta2_av;
	  double alpha_av;                                     //Townsend coefficient at midpoint variable [1/cm]
	  double C;
	  gas->ElectronAttachment(E_av, 0, 0, 0, 0, 0, eta_av);//Gets the value and changes eta_av
	  gas->ElectronTownsend(E_av, 0, 0, 0, 0, 0, alpha_av);
	  pureGas->ElectronAttachment(E_av, 0, 0, 0, 0, 0, eta2_av);
	  // if(igas==4){eta_av = (eta_av - eta2_av)/5 + eta2_av;}//10ppm
	  // if(igas==5){eta_av = (eta_av - eta2_av)/2.5 + eta2_av;}//20ppm
	  if(igas==1){eta_av = (eta_av - eta2_av)*(0.1/refImpurity) + eta2_av;}//0.1ppm
	  if(igas==2){eta_av = (eta_av - eta2_av)*(0.2/refImpurity) + eta2_av;}//0.2ppm
	  if(igas==3){eta_av = (eta_av - eta2_av)*(0.5/refImpurity) + eta2_av;}//0.5ppm //Oxygen Attachment scaling
	  if(igas==4){eta_av = (eta_av - eta2_av)*(1./refImpurity) + eta2_av;}//1ppm
	  if(igas==5){eta_av = (eta_av - eta2_av)*(5./refImpurity) + eta2_av;}//5ppm

	  if((eta_av - alpha_av) < 0){C = 0;}
	  else{C = (eta_av - alpha_av)*dr;}	                               //Calculates the probability of absorption in that step	                                  
	  Cvec.push_back(C);                                   //Adds this value to the vector of coefficients
	  //std::cout << Cvec[iStep] << std::endl;                         //Outputs the value of C (testing purposes)
	}

      std::cout << "Size of Coefficient Vector is: " << Cvec.size() << std::endl; //Check if the number of values is correct (should be nSteps)

      for (int iStep = 0; iStep <= nSteps; iStep++)            //Need a loop one size bigger to account for starting at the very edge of the detector or sensor
	{
	  double r_s = r_o - iStep*dr;            //Calculates value of starting point and stores it in a vector for plotting
	  rvec.push_back(r_s);

	  double logP_s = 0;                              //Initiates the variable for logP_s (log survival probability) and resets it every loop
	  
	  for(int jStep = iStep; jStep < nSteps; jStep++) //Done so that when iStep = nSteps then the probability of absorption is 0 (it starts at the sensor)
	    {
	      logP_s -= Cvec[jStep];                      //Calculates the sum of the elements in the vector from the starting point onward
	    }

	  double P_s = exp(logP_s);        //Calculates the total probability of survival for that starting point
	  Pvec.push_back(P_s);             //Adds the probability to the vector
	  
	  if (igas == 0){
	    PvecPure.push_back(P_s);                    // Save probability for pure case
	    varianceVecPure.push_back(P_s*(1-P_s));
	    stdDevVecPure.push_back(100*std::sqrt(P_s*(1-P_s)/nElecs));
	    stdDevMeanVecPure.push_back(100*std::sqrt((1-P_s)/(nElecs*P_s)));
	  }

	  
	  double P_norm = P_s/PvecPure.at(iStep); // Probability normalised to pure case
	  double variance = P_s*(1-P_s);
	  double stdDev = 100*std::sqrt(P_s*(1-P_s)/nElecs);
	  double stdDevMean= 100*std::sqrt((1-P_s)/(nElecs*P_s));
	  varianceVec.push_back(variance);                // Binomial variance/number of initial electrons
	  stdDevVec.push_back(stdDev);// Binomial standard deviation/number of initial electrons
	  stdDevMeanVec.push_back(stdDevMean);// Binomial standard deviation/number of initial electrons

	  if(gasType !=1){
	    PvecNorm.push_back(P_norm);       // Normalised probability for pure case should = 1
	    varianceNormVec.push_back(variance/varianceVecPure.at(iStep));
	    stdDevNormVec.push_back(stdDev/stdDevVecPure.at(iStep));
	    stdDevMeanNormVec.push_back(stdDevMean/stdDevMeanVecPure.at(iStep));
	  }
	  // varianceNormVec.push_back(P_norm*(1-P_norm));                // Binomial variance/number of initial electrons
	  // stdDevNormVec.push_back(std::sqrt(P_norm*(1-P_norm)/nElecs));// Binomial standard deviation/number of initial electrons
	  // varianceNormVec.push_back(P_norm*(1-P_norm));                // Binomial variance/number of initial electrons
	  // stdDevNormVec.push_back(std::sqrt(P_norm*(1-P_norm)/nElecs));// Binomial standard deviation/number of initial electrons
	  
	}
      
      std::cout << "Size of Probability vector = " << Pvec.size() << std::endl;
      std::cout << "Size of Starting point vector = " << rvec.size() << std::endl; //Checks the size of these two vectors, should be nSteps+1

      probabilityGraphs.push_back(new TGraph(Pvec.size(), &(rvec[0]), &(Pvec[0])));
      probabilityGraphs[probabilityGraphs.size()-1]->SetLineWidth(2);
      probabilityGraphs[probabilityGraphs.size()-1]->GetXaxis()->SetTitle("Starting Position [cm]");
      probabilityGraphs[probabilityGraphs.size()-1]->GetYaxis()->SetTitle("Probability of Avalanche");    

      normalisedGraphs.push_back(new TGraph(PvecNorm.size(), &(rvec[0]), &(PvecNorm[0])));
      normalisedGraphs[normalisedGraphs.size()-1]->SetLineWidth(2);
      normalisedGraphs[normalisedGraphs.size()-1]->GetXaxis()->SetTitle("Starting Position [cm]");
      normalisedGraphs[normalisedGraphs.size()-1]->GetYaxis()->SetTitle("Probability of Avalanche (Normalised to Pure)");    

      varianceGraphs.push_back(new TGraph(varianceVec.size(), &(rvec[0]), &(varianceVec[0])));
      varianceGraphs[varianceGraphs.size()-1]->SetLineWidth(2);
      varianceGraphs[varianceGraphs.size()-1]->GetXaxis()->SetTitle("Starting Position [cm]");
      varianceGraphs[varianceGraphs.size()-1]->GetYaxis()->SetTitle("Variance of Avalanche/Initial Electrons");    

      varianceNormGraphs.push_back(new TGraph(varianceNormVec.size(), &(rvec[0]), &(varianceNormVec[0])));
      varianceNormGraphs[varianceNormGraphs.size()-1]->SetLineWidth(2);
      varianceNormGraphs[varianceNormGraphs.size()-1]->GetXaxis()->SetTitle("Starting Position [cm]");
      varianceNormGraphs[varianceNormGraphs.size()-1]->GetYaxis()->SetTitle("Variance of Avalanche/Initial Electrons (Normalised)");    

      stdDevGraphs.push_back(new TGraph(stdDevVec.size(), &(rvec[0]), &(stdDevVec[0])));
      stdDevGraphs[stdDevGraphs.size()-1]->SetLineWidth(2);
      stdDevGraphs[stdDevGraphs.size()-1]->GetXaxis()->SetTitle("Starting Position [cm]");
      stdDevGraphs[stdDevGraphs.size()-1]->GetYaxis()->SetTitle("Standard Deviation of Avalanche/Initial Electrons (%)"); 

      stdDevNormGraphs.push_back(new TGraph(stdDevNormVec.size(), &(rvec[0]), &(stdDevNormVec[0])));
      stdDevNormGraphs[stdDevNormGraphs.size()-1]->SetLineWidth(2);
      stdDevNormGraphs[stdDevNormGraphs.size()-1]->GetXaxis()->SetTitle("Starting Position [cm]");
      stdDevNormGraphs[stdDevNormGraphs.size()-1]->GetYaxis()->SetTitle("Standard Deviation of Avalanche/Initial Electrons (Normalised)");    

      stdDevMeanGraphs.push_back(new TGraph(stdDevMeanVec.size(), &(rvec[0]), &(stdDevMeanVec[0])));
      stdDevMeanGraphs[stdDevMeanGraphs.size()-1]->SetLineWidth(2);
      stdDevMeanGraphs[stdDevMeanGraphs.size()-1]->GetXaxis()->SetTitle("Starting Position [cm]");
      stdDevMeanGraphs[stdDevMeanGraphs.size()-1]->GetYaxis()->SetTitle("Standard Deviation of Avalanche/Mean Electrons (%)"); 

      stdDevMeanNormGraphs.push_back(new TGraph(stdDevMeanNormVec.size(), &(rvec[0]), &(stdDevMeanNormVec[0])));
      stdDevMeanNormGraphs[stdDevMeanNormGraphs.size()-1]->SetLineWidth(2);
      stdDevMeanNormGraphs[stdDevMeanNormGraphs.size()-1]->GetXaxis()->SetTitle("Starting Position [cm]");
      stdDevMeanNormGraphs[stdDevMeanNormGraphs.size()-1]->GetYaxis()->SetTitle("Standard Deviation of Avalanche/Mean Electrons (Normalised)");    
    }

  // std::vector<int> lineColours{kBlue + 4, kMagenta - 7, kViolet + 1, kAzure + 1, kSpring + 2, kOrange + 1, kBlue + 1};
  // std::vector<TString> lineLabels{"0 ppm", "0.5 ppm", "1 ppm", "5 ppm", "10 ppm", "20 ppm", "50 ppm"};
  std::vector<int> lineColours{kBlack, kRed, kMagenta + 1, kOrange - 3, kGreen -3, kBlue + 2};
  std::vector<int> lineStyles{kSolid, 7, 10, kDashed, 6, 9};
  std::vector<TString> lineLabels{"0 ppm", "0.1 ppm", "0.2 ppm", "0.5 ppm", "1 ppm", "5 ppm"};
  for (int igas = probabilityGraphs.size() - 1; igas >= 0; --igas)
    {
      probabilityGraphs.at(igas)->SetLineColor(lineColours.at(igas));
      probabilityGraphs.at(igas)->SetLineStyle(lineStyles.at(igas));
      probabilityLegend->AddEntry(probabilityGraphs.at(igas), lineLabels.at(igas), "l");
      varianceGraphs.at(igas)->SetLineColor(lineColours.at(igas));
      varianceGraphs.at(igas)->SetLineStyle(lineStyles.at(igas));
      varianceLegend->AddEntry(varianceGraphs.at(igas), lineLabels.at(igas), "l");
      stdDevGraphs.at(igas)->SetLineColor(lineColours.at(igas));
      stdDevGraphs.at(igas)->SetLineStyle(lineStyles.at(igas));
      stdDevLegend->AddEntry(stdDevGraphs.at(igas), lineLabels.at(igas), "l");
      stdDevMeanGraphs.at(igas)->SetLineColor(lineColours.at(igas));
      stdDevMeanGraphs.at(igas)->SetLineStyle(lineStyles.at(igas));
      stdDevMeanLegend->AddEntry(stdDevMeanGraphs.at(igas), lineLabels.at(igas), "l");
      if (igas == 0){
	continue; // dont plot 0ppm for normalised plots
      }
      normalisedGraphs.at(igas)->SetLineColor(lineColours.at(igas));
      normalisedGraphs.at(igas)->SetLineStyle(lineStyles.at(igas));
      normalisedLegend->AddEntry(normalisedGraphs.at(igas), lineLabels.at(igas), "l");
      varianceNormGraphs.at(igas)->SetLineColor(lineColours.at(igas));
      varianceNormGraphs.at(igas)->SetLineStyle(lineStyles.at(igas));
      varianceNormLegend->AddEntry(varianceNormGraphs.at(igas), lineLabels.at(igas), "l");
      stdDevNormGraphs.at(igas)->SetLineColor(lineColours.at(igas));
      stdDevNormGraphs.at(igas)->SetLineStyle(lineStyles.at(igas));
      stdDevNormLegend->AddEntry(stdDevNormGraphs.at(igas), lineLabels.at(igas), "l");
      stdDevMeanNormGraphs.at(igas)->SetLineColor(lineColours.at(igas));
      stdDevMeanNormGraphs.at(igas)->SetLineStyle(lineStyles.at(igas));
      stdDevMeanNormLegend->AddEntry(stdDevMeanNormGraphs.at(igas), lineLabels.at(igas), "l");
    }

  plotString += "_imp_avalancheProbability";
  TCanvas* cProbability = new TCanvas("cProbability", "",600,600);

  probabilityGraphs.back()->GetXaxis()->SetTitleOffset(1.4);
  probabilityGraphs.back()->GetXaxis()->SetLimits(r_i,r_o);
  probabilityGraphs.back()->GetYaxis()->SetTitleOffset(1.8);  
  probabilityGraphs.back()->SetMinimum(minimum);
  probabilityGraphs.back()->SetMaximum(1.);
  probabilityGraphs.back()->Draw("AL");
  // for(unsigned int nn = 0;nn < probabilityGraphs.size();nn++)
  for(int nn=probabilityGraphs.size()-2;nn>-1;--nn)
    {
      probabilityGraphs.at(nn)->Draw("sameL");
    }
  probabilityLegend->Draw();
  p.DrawLatex(x,y,legString);
  r.DrawLatex(x,y + 0.05,"Anode: 1 mm radius" + voltString);
  q.DrawLatex(x,y + 0.1,"Cathode: 20 cm radius");
  SavePlots(cProbability, plotString, plotDir);

  // cProbability->SetLogx();
  // SavePlots(cProbability, plotString + "_log", plotDir + "/logPlots");

  TCanvas* cVariance = new TCanvas("cVariance", "",600,600);

  varianceGraphs.back()->GetXaxis()->SetTitleOffset(1.4);
  varianceGraphs.back()->GetXaxis()->SetLimits(r_i,r_o);
  varianceGraphs.back()->GetYaxis()->SetTitleOffset(1.8);  
  varianceGraphs.back()->SetMinimum(0.);
  varianceGraphs.back()->SetMaximum(0.25);
  varianceGraphs.back()->Draw("AL");
  // for(unsigned int nn = 0;nn < varianceGraphs.size();nn++)
  for(int nn=varianceGraphs.size()-2;nn>-1;--nn)
    {
      varianceGraphs.at(nn)->Draw("sameL");
    }
  varianceLegend->Draw();
  p.DrawLatex(x,y,legString);
  r.DrawLatex(x,y + 0.05,"Anode: 1 mm radius" + voltString);
  q.DrawLatex(x,y + 0.1,"Cathode: 20 cm radius");
  SavePlots(cVariance, plotString + (TString)"_variance", plotDir);

  // cVariance->SetLogx();
  // SavePlots(cVariance, plotString + (TString)"_variance" + "_log", plotDir + "/logPlots" );

  TCanvas* cStdDev = new TCanvas("cStdDev", "",600,600);

  stdDevGraphs.back()->GetXaxis()->SetTitleOffset(1.4);
  stdDevGraphs.back()->GetXaxis()->SetLimits(r_i,r_o);
  stdDevGraphs.back()->GetYaxis()->SetTitleOffset(1.8);  
  stdDevGraphs.back()->SetMinimum(0.);
  stdDevGraphs.back()->SetMaximum(100*0.5/std::sqrt(nElecs));
  stdDevGraphs.back()->Draw("AL");
  // for(unsigned int nn = 0;nn < stdDevGraphs.size();nn++)
  for(int nn=stdDevGraphs.size()-2;nn>-1;--nn)
    {
      stdDevGraphs.at(nn)->Draw("sameL");
    }
  stdDevLegend->Draw();
  p.DrawLatex(x,y,legString);
  r.DrawLatex(x,y + 0.05,"Anode: 1 mm radius" + voltString);
  q.DrawLatex(x,y + 0.1,"Cathode: 20 cm radius");
  SavePlots(cStdDev, plotString + (TString)"_stdDev", plotDir);

  // cStdDev->SetLogx();
  // SavePlots(cStdDev, plotString + (TString)"_stdDev" + "_log", plotDir + "/logPlots");

  TCanvas* cStdDevMean = new TCanvas("cStdDevMean", "",600,600);

  stdDevMeanGraphs.back()->GetXaxis()->SetTitleOffset(1.4);
  stdDevMeanGraphs.back()->GetXaxis()->SetLimits(r_i,r_o);
  stdDevMeanGraphs.back()->GetYaxis()->SetTitleOffset(1.8);  
  stdDevMeanGraphs.back()->SetMinimum(0.);
  stdDevMeanGraphs.back()->SetMaximum(5*100*0.5/std::sqrt(nElecs));
  stdDevMeanGraphs.back()->Draw("AL");
  // for(unsigned int nn = 0;nn < stdDevMeanGraphs.size();nn++)
  for(int nn=stdDevMeanGraphs.size()-2;nn>-1;--nn)
    {
      stdDevMeanGraphs.at(nn)->Draw("sameL");
    }
  stdDevMeanLegend->Draw();
  p.DrawLatex(x,y,legString);
  r.DrawLatex(x,y + 0.05,"Anode: 1 mm radius" + voltString);
  q.DrawLatex(x,y + 0.1,"Cathode: 20 cm radius");
  SavePlots(cStdDevMean, plotString + (TString)"_stdDevMean", plotDir);

  // cStdDevMean->SetLogx();
  // SavePlots(cStdDevMean, plotString + (TString)"_stdDevMean" + "_log", plotDir + "/logPlots");

  if(gasType == 1)
    return 0;

  TCanvas* cNormalised = new TCanvas("cNormalised", "",600,600);

  normalisedGraphs.back()->GetXaxis()->SetTitleOffset(1.4);
  normalisedGraphs.back()->GetXaxis()->SetLimits(r_i,r_o);
  normalisedGraphs.back()->GetYaxis()->SetTitleOffset(1.8);  
  normalisedGraphs.back()->SetMinimum(minimum);
  normalisedGraphs.back()->SetMaximum(1.);
  normalisedGraphs.back()->Draw("AL");
  // for(unsigned int nn = 0;nn < normalisedGraphs.size();nn++)
  for(int nn=normalisedGraphs.size()-2;nn>0;--nn)
    {
      normalisedGraphs.at(nn)->Draw("sameL");
    }
  normalisedLegend->Draw();
  p.DrawLatex(x,y,legString);
  r.DrawLatex(x,y + 0.05,"Anode: 1 mm radius" + voltString);
  q.DrawLatex(x,y + 0.1,"Cathode: 20 cm radius");
  SavePlots(cNormalised, plotString + (TString)"_normalised", plotDir);

  // cNormalised->SetLogx();
  // SavePlots(cNormalised, plotString + (TString)"_normalised" + "_log", plotDir + "/logPlots");

  TCanvas* cVarianceNorm = new TCanvas("cVarianceNorm", "",600,600);

  varianceNormGraphs.back()->GetXaxis()->SetTitleOffset(1.4);
  varianceNormGraphs.back()->GetXaxis()->SetLimits(r_i,r_o);
  varianceNormGraphs.back()->GetYaxis()->SetTitleOffset(1.8);  
  varianceNormGraphs.back()->SetMinimum(0.);
  varianceNormGraphs.back()->SetMaximum(10.);
  varianceNormGraphs.back()->Draw("AL");
  // for(unsigned int nn = 0;nn < varianceNormGraphs.size();nn++)
  for(int nn=varianceNormGraphs.size()-2;nn>0;--nn)
    {
      varianceNormGraphs.at(nn)->Draw("sameL");
    }
  varianceNormLegend->Draw();
  p.DrawLatex(x,y,legString);
  r.DrawLatex(x,y + 0.05,"Anode: 1 mm radius" + voltString);
  q.DrawLatex(x,y + 0.1,"Cathode: 20 cm radius");
  SavePlots(cVarianceNorm, plotString + (TString)"_varianceNorm", plotDir);

  // cVarianceNorm->SetLogx();
  // SavePlots(cVarianceNorm, plotString + (TString)"_varianceNorm" + "_log", plotDir + "/logPlots");

  TCanvas* cStdDevNorm = new TCanvas("cStdDevNorm", "",600,600);

  stdDevNormGraphs.back()->GetXaxis()->SetTitleOffset(1.4);
  stdDevNormGraphs.back()->GetXaxis()->SetLimits(r_i,r_o);
  stdDevNormGraphs.back()->GetYaxis()->SetTitleOffset(1.8);  
  stdDevNormGraphs.back()->SetMinimum(0.);
  stdDevNormGraphs.back()->SetMaximum(10.);
  stdDevNormGraphs.back()->Draw("AL");
  // for(unsigned int nn = 0;nn < stdDevNormGraphs.size();nn++)
  for(int nn=stdDevNormGraphs.size()-2;nn>0;--nn)
    {
      stdDevNormGraphs.at(nn)->Draw("sameL");
    }
  stdDevNormLegend->Draw();
  p.DrawLatex(x,y,legString);
  r.DrawLatex(x,y + 0.05,"Anode: 1 mm radius" + voltString);
  q.DrawLatex(x,y + 0.1,"Cathode: 20 cm radius");
  SavePlots(cStdDevNorm, plotString + (TString)"_stdDevNorm", plotDir);
  
  // cStdDevNorm->SetLogx();
  // SavePlots(cStdDevNorm, plotString + (TString)"_stdDevNorm" + "_log", plotDir + "/logPlots");

  TCanvas* cStdDevMeanNorm = new TCanvas("cStdDevMeanNorm", "",600,600);

  stdDevMeanNormGraphs.back()->GetXaxis()->SetTitleOffset(1.4);
  stdDevMeanNormGraphs.back()->GetXaxis()->SetLimits(r_i,r_o);
  stdDevMeanNormGraphs.back()->GetYaxis()->SetTitleOffset(1.8);  
  stdDevMeanNormGraphs.back()->SetMinimum(0.);
  stdDevMeanNormGraphs.back()->SetMaximum(10.);
  stdDevMeanNormGraphs.back()->Draw("AL");
  // for(unsigned int nn = 0;nn < stdDevMeanNormGraphs.size();nn++)
  for(int nn=stdDevMeanNormGraphs.size()-2;nn>0;--nn)
    {
      stdDevMeanNormGraphs.at(nn)->Draw("sameL");
    }
  stdDevMeanNormLegend->Draw();
  p.DrawLatex(x,y,legString);
  r.DrawLatex(x,y + 0.05,"Anode: 1 mm radius" + voltString);
  q.DrawLatex(x,y + 0.1,"Cathode: 20 cm radius");
  SavePlots(cStdDevMeanNorm, plotString + (TString)"_stdDevMeanNorm", plotDir);
  
  // cStdDevMeanNorm->SetLogx();
  // SavePlots(cStdDevMeanNorm, plotString + (TString)"_stdDevMeanNorm" + "_log", plotDir + "/logPlots");
 
  // TString graphFile = "./Plots/" + plotString + ".root"; 
  // TFile*f=new TFile(graphFile,"RECREATE");
  // probabilityGraphs[0]->SetName("0ppmO2Avalanche");
  // probabilityGraphs[0]->Write();
  // probabilityGraphs[1]->SetName("0p5ppmO2Avalanche");
  // probabilityGraphs[1]->Write();
  // probabilityGraphs[2]->SetName("1ppmO2Avalanche");
  // probabilityGraphs[2]->Write();
  // probabilityGraphs[3]->SetName("5ppmO2Avalanche");
  // probabilityGraphs[3]->Write();
  // probabilityGraphs[4]->SetName("10ppmO2Avalanche");
  // probabilityGraphs[4]->Write();
  // probabilityGraphs[5]->SetName("20ppmO2Avalanche");
  // probabilityGraphs[5]->Write();
  // probabilityGraphs[6]->SetName("50ppmO2Avalanche");
  // probabilityGraphs[6]->Write();
  // f->Close();   

 
  // app.Run();
  return 0;
}

void SavePlots(TCanvas* canvas, TString plotName, TString dirName)
{
  canvas->Print(dirName + "/" + plotName + ".eps");
  canvas->Print(dirName + "/" + plotName + ".pdf");
  canvas->Print(dirName + "/" + plotName + ".png");
  // canvas->Print(dirName + "/" + plotName + ".C");
  return;
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
  // Int_t font=42;
  Int_t font=42;
  Double_t tsize=0.03;
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


/*TCanvas* c1 = new TCanvas("c1", "Probability of Survival of Primary Electron",600,600);

  TLegend* leg = new TLegend(0.15,0.15,0.30,0.40);
  leg->SetTextFont(42);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(1000);
  leg->SetHeader("Oxygen Contamination");

  std::vector<TGraph*> graphs;   
  
  for (int igas=0; igas<4; igas++)
    {
      if (igas==0) {gas->LoadGasFile("log64.gas");}
      if (igas==1) {gas->LoadGasFile("o2-contamination/100ppm-o2.gas");}

      std::vector<double> Cvec; //Vector to store the value of eta_av*dr at each step
      std::vector<double> rvec; //Vector to store the position of starting point in the detector
      std::vector<double> Pvec; //Vector to store the probability of survival

      for (int iStep = 0; iStep < nSteps; iStep++)
	{
	  double r_av = r_o - (iStep*dr + dr/2);               //Midpoint between steps
	  double E_av = A/(r_av*r_av);                         //E-Field at midpoint
	  double eta_av;                                       //Attachment coefficient at midpoint variable [1/cm]
	  double eta2_av;                                      //Attachment coefficient for pure gas
	  gas->ElectronAttachment(E_av, 0, 0, 0, 0, 0, eta_av);//Gets the value and updates eta_av
	  pureGas->ElectronAttachment(E_av, 0, 0, 0, 0, 0, eta2_av);
	  if(igas==1){eta_av = (eta_av - eta2_av)/100 + eta2_av;}
	  if(igas==2){eta_av = (eta_av - eta2_av)/5 + eta2_av;}	  
	  double C = eta_av*dr;                                //Calculates the probability of absorption in that step
	  Cvec.push_back(C);                                   //Adds this value to the vector of coefficients
	  //std::cout << Cvec[iStep] << std::endl;                         //Outputs the value of C (testing purposes)
	}

      std::cout << "Size of Coefficient Vector is: " << Cvec.size() << std::endl; //Check if the number of values is correct (should be nSteps)

      for (int iStep = 0; iStep <= nSteps; iStep++)            //Need a loop one size bigger to account for starting at the very edge of the detector or sensor
	{
	  double r_s = r_o - iStep*dr;            //Calculates value of starting point and stores it in a vector for plotting
	  rvec.push_back(r_s);

	  double logP_s = 0;                              //Initiates the variable for logP_s (log survival probability) and resets it every loop
	  
	  for(int jStep = iStep; jStep < nSteps; jStep++) //Done so that when iStep = nSteps then the probability of absorption is 0 (it starts at the sensor)
	    {
	      logP_s -= Cvec[jStep];                      //Calculates the sum of the elements in the vector from the starting point onward
	    }

	  double P_s = exp(logP_s);        //Calculates the total probability of survival for that starting point
	  Pvec.push_back(P_s);             //Adds the probability to the vector
	  //std::cout << Pvec[iStep] << std::endl;     //Outputs the probability of survival (testing purposes)
	}

      std::cout << "Size of Probability vector = " << Pvec.size() << std::endl;
      std::cout << "Size of Starting point vector = " << rvec.size() << std::endl; //Checks the size of these two vectors, should be nSteps+1

      graphs.push_back(new TGraph(Pvec.size(), &(rvec[0]), &(Pvec[0])));
      graphs[graphs.size()-1]->SetLineWidth(2);
      graphs[graphs.size()-1]->GetXaxis()->SetTitle("Starting Position [cm]");
      graphs[graphs.size()-1]->GetYaxis()->SetTitle("Probability of Survival");    
      graphs[graphs.size()-1]->SetTitle("Probability of Survival of Primary Electron");    
      graphs[graphs.size()-1]->SetMarkerStyle(42);

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

  TH2F*dummyProbability=new TH2F("dummyProbability","Probability of Survival of Primary Electron;Starting Position [cm];Probability of Survival", 10000,0,30,10000,0,1);
  dummyProbability->GetXaxis()->SetTitleOffset(1.2);
  dummyProbability->GetYaxis()->SetTitleOffset(1.4);
  dummyProbability->Draw();
  for(unsigned int nn=0;nn<graphs.size();nn++)
    {
      graphs.at(nn)->Draw("L");
    }
  leg->Draw();

  c1->Print("./Plots/survival.png");




  //==========ETA - ALPHA==========//

  TCanvas* c2 = new TCanvas("c2", "Difference between Attachment and Townsend Coefficients",600,600);

  TLegend* leg2 = new TLegend(0.65,0.15,0.80,0.40);
  leg2->SetTextFont(42);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->SetTextSize(0.035);
  leg2->SetFillStyle(1000);
  leg2->SetHeader("Oxygen Contamination");

  std::vector<TGraph*> graphs2;   
  
  for (int igas=0; igas<4; igas++)
    {
      if (igas==0) {gas->LoadGasFile("log64.gas");}
      if (igas==1) {gas->LoadGasFile("o2-contamination/100ppm-o2.gas");}

      std::vector<double> diffvec; //Vector to store the value of eta - alpha at each step
      std::vector<double> rvec; //Vector to store the position of starting point in the detector

      for (int iStep = 0; iStep <= nSteps; iStep++)
	{
	  double r = r_o - iStep*dr;                        //Position
	  rvec.push_back(r);
	  double E = A/(r*r);                         //E-Field
	  double alpha;                                     //Townsend coefficient variable [1/cm]
	  double eta;                                       //Attachment coefficient variable [1/cm]
	  double eta2;
	  gas->ElectronTownsend(E, 0, 0, 0, 0, 0, alpha);   //Gets the value and changes alpha
	  gas->ElectronAttachment(E, 0, 0, 0, 0, 0, eta);   //Gets the value and changes eta
	  pureGas->ElectronAttachment(E, 0, 0, 0, 0, 0, eta2);
	  if(igas==1){eta = (eta - eta2)/100 + eta2;}
	  if(igas==2){eta = (eta - eta2)/5 + eta2;}	   
	  double diff = eta - alpha;                        //Calculates the differenct between attachment and townsend coefficients
	  diffvec.push_back(diff);                          //Adds this value to the vector of differences
	}

      std::cout << "Size of Position vector = " << rvec.size() << std::endl;
      std::cout << "Size of Difference vector = " << diffvec.size() << std::endl; //Checks the size of these two vectors, should be nSteps+1

      graphs2.push_back(new TGraph(diffvec.size(), &(rvec[0]), &(diffvec[0])));
      graphs2[graphs2.size()-1]->SetLineWidth(2);
      graphs2[graphs2.size()-1]->GetXaxis()->SetTitle("Position [cm]");
      graphs2[graphs2.size()-1]->GetYaxis()->SetTitle("Difference between eta and alpha [1/cm]");    
      graphs2[graphs2.size()-1]->SetTitle("Difference between Attachment and Townsend Coefficients");    
      graphs2[graphs2.size()-1]->SetMarkerStyle(42);

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

  TH2F*dummyDifference=new TH2F("dummyDifference","Difference between Attachment and Townsend Coefficients;Position [cm];Difference between eta and alpha [1/cm]", 10000,0.,30.,10000,-35,5);
  dummyDifference->GetXaxis()->SetTitleOffset(1.2);
  dummyDifference->GetYaxis()->SetTitleOffset(1.4);
  dummyDifference->Draw();
  for(unsigned int nn=0;nn<graphs2.size();nn++)
    {
      graphs2.at(nn)->Draw("L");
    }
  leg2->Draw();

  c2->Print("./Plots/difference.png");*/


	  //std::cout << Pvec[iStep] << std::endl;     //Outputs the probability of survival (testing purposes)
	  /*if (P_s >= 0.95 && P_s <= 0.951){
	    if(igas==0){std::cout << "Oxygen Concentration = 0 ppm" << std::endl;}
	    if(igas==1){std::cout << "Oxygen Concentration = 0.1 ppm" << std::endl;}
	    if(igas==2){std::cout << "Oxygen Concentration = 1 ppm" << std::endl;}
	    if(igas==3){std::cout << "Oxygen Concentration = 10 ppm" << std::endl;}	    
	    std::cout << "Probability of Survival: " << Pvec[iStep] << std::endl;     //Outputs the probability of survival (testing purposes)
	    std::cout << "Starting Position: " << rvec[iStep] << std::endl << std::endl;
	    }*/	
