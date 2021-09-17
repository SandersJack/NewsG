std::vector<double> GenerateEnergyPoints(double npoints, double EMax, double EMin); //Generate logarithmically spaced Energy Points between EMin and EMax for use in plotting.

int MakeMuonHistogram()
{
  TFile* outputFile = new TFile("MuonDistribution.root", "recreate");//("./RootFiles/Hardccbar_True_WithBaryons.root", "RECREATE");
  
  std::vector<double> energyPoints = GenerateEnergyPoints(36, 1e4, 1e-3);

  double xBins[36];
  std::copy(energyPoints.begin(), energyPoints.end(), xBins);
  
  for (int i = 0; i < 35; ++i)
    {
      std::cout << xBins[i] << std::endl;
    }

  double yValues[35] = { 0.0006525805811569842,
			 0.0008047531264507647,
			 0.0012083616865131203,
			 0.0015578687581109427,
			 0.0024611151072099348,
			 0.0036954403827756505,
			 0.005548817925111444,
			 0.007918956625952397,
			 0.010741592428601739,
			 0.01457032957145631,
			 0.017854040367936565,
			 0.0209834726101597,
			 0.024217941061536248,
			 0.024217941061536248,
			 0.023018150944127912,
			 0.018784658176519684,
			 0.013162421885904428,
			 0.007526640620398441,
			 0.0036954403827756505,
			 0.0015578687581109427,
			 0.0005932830858480781,
			 0.00020363689290767408,
			 0.00006328786192336205,
			 0.000016927275745065787,
			 0.000004273442084849124,
			 9.836648448038166e-7,
			 2.2537742202280947e-7,
			 4.664875902289769e-8,
			 9.655389163853974e-9,
			 1.8095431262478449e-9,
			 3.5516389163434035e-10,
			 5.419482128205484e-11,
			 1.0636963194612388e-11,
			 1.5462613138288825e-12,
			 2.621329651749793e-13};

  TH1D h_muonDistribution = TH1D("h_muonDistribution", "; Energy [GeV]; Vertical Intensity", 35, xBins);
  
  for (int i = 0; i < 35; ++i)
    {
      std::cout << h_muonDistribution.GetBinCenter(i+1) << std::endl;
      h_muonDistribution.SetBinContent(i + 1, yValues[i]);
    }
  
  h_muonDistribution.Write();
  outputFile->Write();
  outputFile->Close();
  
  return 0;
}

std::vector<double> GenerateEnergyPoints(double npoints, double EMax, double EMin)
{
  double Energy=0;
  
  double LogMin = log(EMin);
  double LogMax = log(EMax);
  double step = (LogMax - LogMin)/(npoints-1);
  
  std::vector<double> EnergyPoints;
  
  for (double logEnergy = LogMin; logEnergy<LogMax+step/2; logEnergy+=step)
    {
      Energy = exp(logEnergy);
      EnergyPoints.push_back(Energy);
    }
  
  return EnergyPoints;
}
