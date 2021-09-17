#include "G4SystemOfUnits.hh"
#include "FieldMap.hh"
#include "GasMixture.hh"
#include "ElectronDrift.hh"
#include "IonDrift.hh"
#include "Sensor.hh"
#include "Electronics.hh"
#include "ChargeCarrier.hh"
#include "Reader.hh"
#include "TTree.h"

#include <iostream>
#include <string>
#include <vector>

int main(){
  
  std::string m_ionMobDir("BasicMobility");
  std::string m_gasType("sedine2018");
  std::string m_sensorDir("UmbrellaSensor");
  double m_signalBinSize(50.*ns);
  int m_nSignalBins(50000);
  double m_pressure(760.);
  int m_debug(1);
  
  Electronics* pulseProcess = new Electronics();
  pulseProcess->SetTimeConstant(140.);
  pulseProcess->SetSamplingTime(0.96);
  pulseProcess->SetfCtomV(-1.);  
	   
  GasMixture* gas = new GasMixture();
  gas->SetIonMobilityDir(m_ionMobDir);
  gas->SetGas(m_gasType, 0, 0, m_pressure);
	   
  FieldMap* fieldMap = new FieldMap();
  fieldMap->SetGas(gas->GetGas());
  fieldMap->SetSensorDir(m_sensorDir);
  fieldMap->Initialise();
	   
  double aCube = 30.; // cm 
  double signalt0 = 0.*ns; // ns
	   
  // signalNt->resize(m_nSignalBins, 0);
  // signaltNt->resize(m_nSignalBins, 0);

  Garfield::Sensor* sensor = new Garfield::Sensor();
  sensor->AddComponent(fieldMap->GetFieldMap());
  sensor->AddElectrode(fieldMap->GetFieldMap(), "readout");
  sensor->SetArea(-aCube,-aCube,-aCube, aCube, aCube, aCube);
  sensor->SetTimeWindow(signalt0/ns, m_signalBinSize/ns, m_nSignalBins);
  IonDrift* ionDrift = new IonDrift();
  ionDrift->SetSensor(sensor);
  ionDrift->SetDriftType(DriftType::RKF);
  ionDrift->SetDebug(m_debug);
  ElectronDrift* electronDrift = new ElectronDrift();
  electronDrift->SetSensor(sensor);
  electronDrift->SetDriftType(ElectronDriftType::RKF);
  electronDrift->SetDebug(m_debug);

  // Load in TTree
  Reader myreader;
  long int nentries=myreader.fChain->GetEntries();
  TTree *tree = myreader.fChain;
  tree->Print();
  TFile*f=new TFile("outputAnalysis.root","RECREATE");

  // TTree *newTree = tree->CloneTree(0);
  // double max = 0;
  // TBranch *amplBranch = newTree->Branch("Amplitude", &max, "Amplitude/D");
  // double riseTime = 0;
  // TBranch *risetimeBranch = newTree->Branch("RiseTime", &riseTime, "RiseTime/D");
  // double pulseWidth = 0;
  // TBranch *pulsewidthBranch = newTree->Branch("PulseWidth", &pulseWidth, "PulseWidth/D");
  // double pulseIntegral = 0;
  // TBranch *pulseIntegralBranch = newTree->Branch("PulseIntegral", &pulseIntegral, "PulseIntegral/D");

  for(int ientry=0;ientry<nentries;ientry++)
    {
      myreader.GetEntry(ientry);

      std::vector<ChargeCarrier>* driftIonPositions = new std::vector<ChargeCarrier>;
      std::vector<ChargeCarrier>* driftElectronPositions = new std::vector<ChargeCarrier>;

      double nHit = myreader.InitIonRadius->size();
      
      std::cout << nHit << std::endl;
      int avalancheSize = 0;
      for(int i = 0; i<nHit; ++i) 
    	{
	  ChargeCarrier initIon;
	  initIon.SetPositionSphere(myreader.InitIonRadius->at(i), myreader.InitIonCosTheta->at(i), myreader.InitIonPhi->at(i), myreader.InitIonTime->at(i));
	  initIon.SetCharge(myreader.IonCharge->at(i));
	  double x = initIon.x();
	  double y = initIon.y();
	  double z = initIon.z();
	  double t = initIon.t();
	  double charge = initIon.GetCharge();
	  avalancheSize += charge;
	  //std::cout << "[EventAction] x = " << x/cm << "cm, y = " << y/cm << "cm, z = " << z/cm << "cm, t = " << t/ns << " ns, charge scale = " << charge << std::endl; 
	  driftIonPositions->emplace_back();
	  driftIonPositions->at(driftIonPositions->size()-1).SetPositionCartesian(x, y, z, t);
	  driftIonPositions->at(driftIonPositions->size()-1).SetCharge(charge);
	  
	  driftElectronPositions->emplace_back();
	  driftElectronPositions->at(driftElectronPositions->size()-1).SetPositionCartesian(x, y, z, t);
	  driftElectronPositions->at(driftElectronPositions->size()-1).SetCharge(charge);
	  
	  std::cout << "x = " << x << ", \t y = " << y << ", z = " << z << ", t = " << t << ", charge = " << charge << std::endl;
	}
	  
      std::cout <<"[EventAction] Will drift Ions now!" << std::endl;
      ionDrift->DriftIons(driftIonPositions);
      std::cout <<"[EventAction] Will drift Electrons now!" << std::endl;
      electronDrift->DriftElectrons(driftElectronPositions);
      
		 
	     
	 
	 
    //   for (unsigned int iIon = 0; iIon<driftIonPositions->size(); ++iIon)
    // 	{
    // 	  finIonRadiusNt->  push_back(driftIonPositions->at(iIon).r());
    // 	  finIonCosThetaNt->push_back(driftIonPositions->at(iIon).cosTheta());
    // 	  finIonPhiNt->     push_back(driftIonPositions->at(iIon).phi());
    // 	  finIonTimeNt->    push_back(driftIonPositions->at(iIon).t());
    // 	}
	 
    //   for (unsigned int iElec = 0; iElec<driftElectronPositions->size(); ++iElec)
    // 	{
    // 	  finElecRadiusNt->  push_back(driftElectronPositions->at(iElec).r());
    // 	  finElecCosThetaNt->push_back(driftElectronPositions->at(iElec).cosTheta());
    // 	  finElecPhiNt->     push_back(driftElectronPositions->at(iElec).phi());
    // 	  finElecTimeNt->    push_back(driftElectronPositions->at(iElec).t());
    // 	}

    //   for (unsigned int iElec = 0; iElec<finElecTimeNt->size(); ++iElec)
    // 	{
    // 	  G4double driftTime = finElecTimeNt->at(iElec) - initElecTimeNt->at(iElec);
    // 	  elecDriftTimeNt->push_back(driftTime);
    // 	}
	 
    //   if(m_doSignal){
    // 	for(int iBin=0; iBin<m_nSignalBins; ++iBin)
    // 	  {
    // 	    signalNt->at(iBin)+=sensor->GetIonSignal("readout",iBin);
    // 	    signalNt->at(iBin)+=sensor->GetElectronSignal("readout",iBin);
    // 	    signaltNt->at(iBin)=signalt0+iBin*m_signalBinSize/ns;
    // 	  }       
    // 	sensor->ClearSignal();
    //   }
    //   if(m_doPulse)
    // 	{pulseProcess->ProcessPulse(*signalNt, *signaltNt, *pulseNt, *pulsetNt);}
	     

    //   delete driftElectronPositions;
    //   delete driftIonPositions;

    //   delete electronDrift;
    //   delete ionDrift;
    //   delete sensor;
    //   delete fieldMap;
    //   //delete gas; //<-- belongs to fieldMap
    //   delete pulseProcess;

      delete driftIonPositions;
      delete driftElectronPositions;
    }



  std::cout << "Hello World!" << std::endl;

  return 0;
}
