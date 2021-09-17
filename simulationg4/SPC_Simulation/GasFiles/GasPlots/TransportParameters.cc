//Will be source file for gas class
#include "TransportParameters.hh"
#include "FundamentalConstants.hh"

TransportParameters::TransportParameters(Garfield::MediumMagboltz*pure, TString name):
  m_pure(pure),
  m_O2(NULL),
  m_H2O(NULL),
  m_label(name)
{}

TransportParameters::TransportParameters(Garfield::MediumMagboltz*pure,Garfield::MediumMagboltz*O2,Garfield::MediumMagboltz*H2O,TString name):
  m_pure(pure),
  m_O2(O2),
  m_H2O(H2O),
  m_label(name)
{}

TransportParameters::~TransportParameters()
{}

double TransportParameters::GetElectronTownsend(double electricField, double pressureBar, int impurityType)
{
  double alpha=0.;
  double pressureTorr=0.;
  Garfield::MediumMagboltz* gas;
  
  switch(impurityType)
    {
    case 0: gas = m_pure;
      break;
    case 1: gas = m_O2;
      break;
    case 2: gas = m_H2O;
      break;
    default: std::cout << "[TransportParameters] ERROR: Invalid type entered. Options are:\n"
		       << "\t impurityType = 0 (Uncontaminated Gas) \n"
		       << "\t impurityType = 1 (Oxygen Contamination) \n"
		       << "\t impurityType = 2 (Water Contamination) \n" << std::endl;
      return 0;
    }

  pressureTorr = pressureBar*Garfield::AtmosphericPressure/1.01325; //bar to torr conversion
      
  gas->SetPressure(pressureTorr);
  gas->ElectronTownsend(electricField, 0., 0., 0., 0., 0., alpha);
  
  return alpha;  
}


double TransportParameters::GetElectronAttachment(double electricField, double pressureBar, int impurityType)
{
  double eta=0.;
  double pressureTorr=0.;
  Garfield::MediumMagboltz* gas;
  
  switch(impurityType)
    {
    case 0: gas = m_pure;
      break;
    case 1: gas = m_O2;
      break;
    case 2: gas = m_H2O;
      break;
    default: std::cout << "[TransportParameters] ERROR: Invalid type entered. Options are:\n"
		       << "\t impurityType = 0 (Uncontaminated Gas) \n"
		       << "\t impurityType = 1 (Oxygen Contamination) \n"
		       << "\t impurityType = 2 (Water Contamination) \n" << std::endl;
      return 0;
    }

  pressureTorr = pressureBar*Garfield::AtmosphericPressure/1.01325; //bar to torr conversion
      
  gas->SetPressure(pressureTorr);
  gas->ElectronAttachment(electricField, 0., 0., 0., 0., 0., eta);
  
  return eta;  
}

double TransportParameters::GetElectronAttachment(double electricField, double pressureBar, int impurityType, double O2ppm, double refPurity)
{
  double eta=0.;
  
  if(impurityType == 1)
    {

      double etaPure=0.;
      double pressureTorr=0.;
      Garfield::MediumMagboltz* gas = m_O2;
      Garfield::MediumMagboltz* pureGas = m_pure;

      pressureTorr = pressureBar*Garfield::AtmosphericPressure/1.01325; //bar to torr conversion
      pureGas->SetPressure(pressureTorr);
      gas->SetPressure(pressureTorr);

      pureGas->ElectronAttachment(electricField, 0., 0., 0., 0., 0., etaPure);
      gas->ElectronAttachment(electricField, 0., 0., 0., 0., 0., eta);
      eta = (((eta - etaPure)/refPurity)*O2ppm + etaPure);
    }
  
  else
    {
      std::cout << "[TransportParameters] ERROR: Entered a value for O2 contamination for impurity type != 1 \n"
		<< "Perhaps you meant to use TransportParameters::GetElectronAttachment(double, double, int)?" << std::endl;
      return 0;
    }

  return eta;
}

double TransportParameters::GetElectronDriftVelocity(double electricField, double pressureBar, int impurityType)
{
  double driftVx=0.;
  double driftVy=0.;
  double driftVz=0.;
  double driftV=0.;
  double pressureTorr=0.;
  Garfield::MediumMagboltz* gas;

  switch(impurityType)
    {
    case 0: gas = m_pure;
      break;
    case 1: gas = m_O2;
      break;
    case 2: gas = m_H2O;
      break;
    default: std::cout << "[TransportParameters] ERROR: Invalid type entered. Options are:\n"
		       << "\t impurityType = 0 (Uncontaminated Gas) \n"
		       << "\t impurityType = 1 (Oxygen Contamination) \n"
		       << "\t impurityType = 2 (Water Contamination) \n" << std::endl;
      return 0;
    }
  
  pressureTorr = pressureBar*Garfield::AtmosphericPressure/1.01325; //bar to torr conversion
  
  gas->SetPressure(pressureTorr);
  gas->ElectronVelocity(electricField, 0., 0., 0., 0., 0., driftVx, driftVy, driftVz);
  driftV = sqrt(driftVx*driftVx + driftVy*driftVy + driftVz*driftVz);
  
  return driftV;
}

double TransportParameters::GetElectronTransverseDiffusion(double electricField, double pressureBar, int impurityType)
{
  double transDiff = 0.;
  double longDiff = 0.; // Medium ElectronDiffusion function returns both coefficients - we only want one
  double pressureTorr=0.;
  Garfield::MediumMagboltz* gas;

  switch(impurityType)
    {
    case 0: gas = m_pure;
      break;
    case 1: gas = m_O2;
      break;
    case 2: gas = m_H2O;
      break;
    default: std::cout << "[TransportParameters] ERROR: Invalid type entered. Options are:\n"
		       << "\t impurityType = 0 (Uncontaminated Gas) \n"
		       << "\t impurityType = 1 (Oxygen Contamination) \n"
		       << "\t impurityType = 2 (Water Contamination) \n" << std::endl;
      return 0;
    }
  
  pressureTorr = pressureBar*Garfield::AtmosphericPressure/1.01325; //bar to torr conversion
  gas->SetPressure(pressureTorr);
  gas->ElectronDiffusion(electricField, 0., 0., 0., 0., 0., longDiff, transDiff);
  
  return transDiff;
}

double TransportParameters::GetElectronLongitudinalDiffusion(double electricField, double pressureBar, int impurityType)
{
  double transDiff = 0.;
  double longDiff = 0.; // Medium ElectronDiffusion function returns both coefficients - we only want one
  double pressureTorr=0.;
  Garfield::MediumMagboltz* gas;
  
  switch(impurityType)
    {
    case 0: gas = m_pure;
      break;
    case 1: gas = m_O2;
      break;
    case 2: gas = m_H2O;
      break;
    default: std::cout << "[TransportParameters] ERROR: Invalid type entered. Options are:\n"
		       << "\t impurityType = 0 (Uncontaminated Gas) \n"
		       << "\t impurityType = 1 (Oxygen Contamination) \n"
		       << "\t impurityType = 2 (Water Contamination) \n" << std::endl;
      return 0;
    }
  
  pressureTorr = pressureBar*Garfield::AtmosphericPressure/1.01325; //bar to torr conversion
  gas->SetPressure(pressureTorr);
  gas->ElectronDiffusion(electricField, 0., 0., 0., 0., 0., longDiff, transDiff);

  return longDiff;
}
