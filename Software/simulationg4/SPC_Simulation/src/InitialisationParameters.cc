#include "InitialisationParameters.hh"

#include "G4SystemOfUnits.hh"

#include <iostream>

InitialisationParameters::InitialisationParameters()
  : m_generationType("Geant4"),
    m_ar37Calib(0),
    m_nElec(1),
    m_gridPos(0),
    m_avalType("Micro"),
    m_microMaxState(1),
    m_microMaxSize(10000),
    m_MCStepType("nColl"),
    m_nColl(10000),
    m_MCStepSize(0.001),
    m_customStepSize(0.01),
    m_gasType("sedine2018"),
    m_ionMobDir("BasicMobility"),
    m_sensorDir("UmbrellaSensor"),
    m_diffusion(1),
    m_ionTrack(1),
    m_ionDriftType("RKF"),
    m_signalCalc(0),
    m_pulseCalc(0),
    m_signalBinSize(50),
    m_signalnBins(50000),
    m_singleElec(0),
    m_singleIon(0),
    m_fieldPlot(0),
    m_wValue(0),
    m_fanoFactor(0),
    m_debug(0),
    m_detectorRadius(15.),
    m_safetyCounter(0),
    m_idealField(0),
    m_useGarfield(1),
    m_srimFile(""),
    m_anodeRadius(.1)

{

}



InitialisationParameters::~InitialisationParameters()
{}



void InitialisationParameters::Print()
{
  std::string generationType(this->GetGenerationType());
  bool doAr37Calib = this->GetAr37Calib();
  int nElec        = this->GetnElec();
  int gridPos      = this->GetGridPos();
  std::string avalType(this->GetAvalType());
  bool microMaxState = this->GetMicroMaxState();
  int microMaxSize   = this->GetMicroMaxSize();
  std::string MCStepType(this->GetMCStepType());
  int nColl             = this->GetMCnColl();
  double MCStepSize     = this->GetMCStepSize();
  double customStepSize = this->GetCustomStepSize();
  std::string gasType(this->GetGas());
  std::string ionMobDir(this->GetIonMobDir());
  std::string sensorDir(this->GetSensorDir());
  bool diffusion   = this->GetDiffusion();
  bool ionTrack    = this->GetIonTracking();
  std::string ionDriftType = this->GetIonDriftType();
  bool signalCalc  = this->GetSignalCalc();
  bool pulseCalc   = this->GetPulseCalc();
  double signalBinSize = this->GetSignalBinSize();
  int signalnBins  = this->GetSignalnBins();
  bool singleElec  = this->GetSingleElec();
  bool singleIon   = this->GetSingleIon();
  bool doFieldPlot = this->GetFieldPlot();
  double wValue    = this->GetWValue();
  double fanoFactor= this->GetFanoFactor();
  int debug        = this->GetDebug();
  bool safetyCounter    = this->GetSafetyCounter();
  /*double pressure       = this->GetPressure();*/
  double detectorRadius = this->GetDetectorRadius();
  double anodeRadius    = this->GetAnodeRadius();
  std::string srimFile = this->GetSrimFile();

  std::cout<<"Detector Radius is: "<<detectorRadius<<std::endl;
  std::cout<<"Anode Radius is: "<<anodeRadius<<std::endl;

  if (generationType=="Geant4")
    {std::cout << "Initial electron generation type is: " << generationType  << std::endl;}
  else if (generationType=="HEED")
    {
      std::cout << "Initial electron generation type is: " << generationType  << std::endl;
      if(doAr37Calib)
	std::cout << "Argon-37 calibration enabled." << std::endl;
      else
	std::cout << "Argon-37 calibration disabled." << std::endl;
    }
  else if (generationType=="Electrons")
    {
      std::cout << "Initial electron generation type is: " << generationType  << std::endl;
      std::cout << "Number of initial electrons is: " << nElec << std::endl;
      std::cout << "Initial grid position is: " << gridPos << std::endl;
    }
  else if (generationType=="SRIM")
    {
      std::cout << "Initial electron generation type is: " << generationType  << std::endl;
    }
  else
    {
      std::cout << "Unknown Generation Type! " << std::endl;
    }
  if (avalType=="Micro")
    {
      std::cout << "Avalanche type is: " << avalType << std::endl;
      if (microMaxState)
	{
	  std::cout << "Maximum avalanche size is enabled." << std::endl;
	  std::cout << "Maximum avalanche size is: " << microMaxSize << std::endl;
	}
      else
	std::cout << "Maximum avalanche size is disabled." << std::endl;
    }
  else if (avalType=="MC")
    {
      std::cout << "Avalanche type is: " << avalType << std::endl;
      if (MCStepType=="nColl")
	{
	  std::cout << "Step type is:" << MCStepType << std::endl;
	  std::cout << "Number of collisions per step is: " << nColl << std::endl;
	}
      else if (MCStepType=="tStep")
	{
	  std::cout << "Step type is: " << MCStepType << std::endl;
	  std::cout << "Step size is: " << MCStepSize/ns << " ns" << std::endl;
	}
      else if (MCStepType=="dStep")
	{
	  std::cout << "Step type is: " << MCStepType << std::endl;
	  std::cout << "Step size is: " << MCStepSize/cm << " cm" << std::endl;
	}
      else
	std::cout << "Unknown step type!" << std::endl;
    }
  else if (avalType=="Custom")
  {
    std::cout << "Avalanche type is: " << avalType << std::endl;
    std::cout << "Step size is: " << customStepSize << std::endl;
  }
  else
    std::cout << "Unknown avalanche type!" << std::endl;
  std::cout << "Gas composition is: " << gasType << std::endl;
  std::cout << "Ion mobility directory is: " << ionMobDir << std::endl;
  std::cout << "Sensor directory is: " << sensorDir << std::endl;
  if (diffusion)
    std::cout << "Diffusion is enabled." << std::endl;
  else
    std::cout << "Diffusion is disabled." << std::endl;
  if (ionTrack)
    {
      std::cout << "Ion tracking is enabled." <<  std::endl;
      if (ionDriftType=="RKF")
	  std::cout << "Ion drift type is set to RKF." << std::endl;
      else if (ionDriftType=="MC")
	std::cout << "Ion drift type is set to MC." << std::endl;
      else
	std::cout << "Unknown drift type, setting to RKF." << std::endl;
    }
  else
    std::cout << "Ion tracking is disabled." <<  std::endl;
  if (signalCalc)
    {
    std::cout << "Signal calculation is enabled." << std::endl;
    std::cout << "Signal bin size is: " << signalBinSize/ns << " ns" << std::endl;
    std::cout << "Number of signal bins is: " << signalnBins << std::endl;
    std::cout << "Total signal duration is: " << signalBinSize*signalnBins/ms << " ms" << std::endl;
    }
  else
    std::cout << "Signal calculation is disabled." << std::endl;
  if (pulseCalc)
    std::cout << "Pulse calculation is enabled."<< std::endl;
  else
    std::cout << "Pulse calculation is disabled." << std::endl;
  if(singleElec)
    std::cout << "Single electron option is enabled." << std::endl;
  else
    std::cout << "Single electron option is disabled." << std::endl;
  if(singleIon)
    std::cout << "Single ion option is enabled."  << std::endl;
  else
    std::cout << "Single ion option is disabled." << std::endl;
  if(doFieldPlot)
    std::cout << "Field comparison plot generation enabled." << std::endl;
  else
    std::cout << "Field comparison plot generation disabled." << std::endl;
  std::cout << "W Value is: " << wValue/eV << " eV" << std::endl;
  std::cout << "Fano Factor is: " << fanoFactor << std::endl;
  std::cout << "Verbosity level is: " << debug << std::endl;
  std::cout << "SRIM file to be used if needed: " << srimFile << std::endl;
  if(safetyCounter)
    std::cout << "Safety counter is enabled" << std::endl;
  else
    std::cout << "Safety counter is disabled" << std::endl;
}
