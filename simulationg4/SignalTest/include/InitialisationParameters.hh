#ifndef INITIALISATIONPARAMETERS_H
#define INITIALISATIONPARAMETERS_H
 
//This class stores all of the variables used in initialising the garfield++//
//simulation of the SPC detectors-------------------------------------------//

#include <string> 

class InitialisationParameters
{
public:
 
  InitialisationParameters();
  ~InitialisationParameters();

  void Print();
  
  // Set commands 
  inline void SetGenerationType(std::string type)   {m_generationType = type;}
  inline void SetAr37Calib(bool state)          {m_ar37Calib = state;}
  inline void SetnElec(int nElec)               {m_nElec = nElec;}
  inline void SetGridPos(int gridPos)           {m_gridPos = gridPos;}
  inline void SetAvalType(std::string type)         {m_avalType = type;}
  inline void SetMicroMaxState(bool state)      {m_microMaxState = state;}
  inline void SetMicroMaxSize(int avalSize)     {m_microMaxSize = avalSize;}
  inline void SetMCStepType(std::string type)       {m_MCStepType = type;}
  inline void SetMCnColl(int nColl)             {m_nColl = nColl;}
  inline void SetMCStepSize(double stepSize)    {m_MCStepSize = stepSize;}
  inline void SetCustomStepSize(double stepSize){m_customStepSize = stepSize;}
  inline void SetGas(std::string gasType)           {m_gasType = gasType;}
  inline void SetIonMobDir(std::string ionMobDir)   {m_ionMobDir = ionMobDir;}
  inline void SetSensorDir(std::string sensorDir)   {m_sensorDir = sensorDir;}
  inline void SetDiffusion(bool state)          {m_diffusion = state;}
  inline void SetIonTracking(bool state)        {m_ionTrack = state;}
  inline void SetIonDriftType(std::string type)     {m_ionDriftType = type;}
  inline void SetSignalCalc(bool state)         {m_signalCalc = state;}
  inline void SetPulseCalc(bool state)          {m_pulseCalc = state;}
  inline void SetSignalBinSize(double size)     {m_signalBinSize = size;}
  inline void SetSignalnBins(int nBins)         {m_signalnBins = nBins;}
  inline void SetSingleElec(bool state)         {m_singleElec = state;}
  inline void SetSingleIon(bool state)          {m_singleIon = state;}
  inline void SetFieldPlot(bool state)          {m_fieldPlot = state;}
  inline void SetWValue(double value)           {m_wValue = value;}
  inline void SetFanoFactor(double value)       {m_fanoFactor = value;}
  inline void SetDebug(int level)               {m_debug = level;}
  inline void SetSafetyCounter(bool state)      {m_safetyCounter = state;}
  inline void SetPressure(double pressure)      {m_pressure = pressure;}
  
  // Get commands
  inline std::string GetGenerationType(){return m_generationType;}
  inline bool    GetAr37Calib()     {return m_ar37Calib;}
  inline int     GetnElec()         {return m_nElec;}
  inline int     GetGridPos()       {return m_gridPos;}
  inline std::string GetAvalType()      {return m_avalType;}
  inline bool    GetMicroMaxState() {return m_microMaxState;}
  inline int     GetMicroMaxSize()  {return m_microMaxSize;}
  inline std::string GetMCStepType()    {return m_MCStepType;}
  inline int     GetMCnColl()       {return m_nColl;}
  inline double  GetMCStepSize()    {return m_MCStepSize;}
  inline double  GetCustomStepSize(){return m_customStepSize;}
  inline std::string GetGas()           {return m_gasType;}
  inline std::string GetIonMobDir()     {return m_ionMobDir;}
  inline std::string GetSensorDir()     {return m_sensorDir;}
  inline bool    GetDiffusion()     {return m_diffusion;}
  inline bool    GetIonTracking()   {return m_ionTrack;}
  inline std::string GetIonDriftType()  {return m_ionDriftType;}
  inline bool    GetSignalCalc()    {return m_signalCalc;}
  inline bool    GetPulseCalc()     {return m_pulseCalc;}
  inline double  GetSignalBinSize() {return m_signalBinSize;}
  inline int     GetSignalnBins()   {return m_signalnBins;}
  inline bool    GetSingleElec()    {return m_singleElec;}
  inline bool    GetSingleIon()     {return m_singleIon;}
  inline bool    GetFieldPlot()     {return m_fieldPlot;}
  inline double  GetWValue()        {return m_wValue;}
  inline double  GetFanoFactor()    {return m_fanoFactor;}
  inline int     GetDebug()         {return m_debug;}
  inline bool    GetSafetyCounter() {return m_safetyCounter;}
  inline double  GetPressure()      {return m_pressure;}
   
private:
 
  // Initialisation variables
  std::string m_generationType;
  bool    m_ar37Calib;
  int     m_nElec;
  int     m_gridPos;
  std::string m_avalType;
  bool    m_microMaxState;
  int     m_microMaxSize;
  std::string m_MCStepType;
  int     m_nColl;
  double  m_MCStepSize;
  double  m_customStepSize;
  std::string m_gasType;
  std::string m_ionMobDir;
  std::string m_sensorDir;
  bool    m_diffusion;
  bool    m_ionTrack;
  std::string m_ionDriftType;
  bool    m_signalCalc;
  bool    m_pulseCalc;
  double  m_signalBinSize;
  int     m_signalnBins;
  bool    m_singleElec;
  bool    m_singleIon;
  bool    m_fieldPlot;
  int     m_debug;
  double  m_wValue;
  double  m_fanoFactor;
  bool    m_safetyCounter;
  double  m_pressure;
};
 
#endif // INITIALISATIONPARAMETERS_H
