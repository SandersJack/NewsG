#include "ElectronDrift.hh"

ElectronDrift::ElectronDrift()
  :m_sensor(NULL),
   m_avalRKF(new Garfield::DriftLineRKF()),
   m_avalancheMC(new Garfield::AvalancheMC()),
   m_driftType(ElectronDriftType::RKF),
   m_doSignal(true),
   m_debug(0)
{}



ElectronDrift::~ElectronDrift()
{
  delete m_avalRKF;
  delete m_avalancheMC;
}



void ElectronDrift::SetSensor(Garfield::Sensor *sensor)
{
  m_sensor=sensor;
  m_avalRKF->SetSensor(m_sensor);
  m_avalancheMC->SetSensor(m_sensor);
}


void ElectronDrift::DriftElectrons(std::vector<ChargeCarrier>* electrons)
{
  if(m_driftType==ElectronDriftType::RKF)
    {
      //No way to switch off signal calculation within DriftLineRKF it seems
      for(unsigned int kk=0;kk<(*electrons).size();kk++)
	{
	  //drift the electrons
	  m_avalRKF->SetElectronSignalScalingFactor((*electrons)[kk].GetCharge());

	  bool statusDrift=m_avalRKF->DriftElectron((*electrons)[kk].GetX(),(*electrons)[kk].GetY(),(*electrons)[kk].GetZ(),(*electrons)[kk].GetTime());
	  if(m_debug>=1)
	    {
	      std::cout << "avalRKF :: Drifting electron "<< kk+1 << " of "<< (*electrons).size()
			<< " with scaling of " << (*electrons)[kk].GetCharge() <<" this had a drift time of "
			<< m_avalRKF->GetDriftTime()<<" status is " << statusDrift<<std::endl;
	    }
	  (*electrons)[kk].SetDriftTime(m_avalRKF->GetDriftTime());
	  m_avalRKF->SetElectronSignalScalingFactor(1.);

	  int status = 1000;
	  double x,y,z,t;
	  m_avalRKF->GetEndPoint(x, y, z, t, status);

	  (*electrons)[kk].SetPositionCartesian(x, y, z, t);
	  
	  //std::cout << "[ElectronDrift] Electron Endpoint is: x = " << (*electrons)[kk].GetX()
	  //    << ",\t y = " << (*electrons)[kk].GetY() << ",\t z = " << (*electrons)[kk].GetZ()
	  //	    << ",\t r = " << (*electrons)[kk].r() << ",\t t = " << (*electrons)[kk].GetTime()
	  //	    << ",\t status = " << status << std::endl;
	}
    }
  else
    {
      if(m_doSignal)
	m_avalancheMC->EnableSignalCalculation(1); 
      else //<--- In new version of Garfield it is off by default
      	m_avalancheMC->EnableSignalCalculation(0);
      for(unsigned int kk=0;kk<(*electrons).size();kk++)
	{
	  //drift the electrons
	  if(m_debug>=1)
	    {
	      std::cout << "avalMC :: Drifting electron "<< kk+1 << " of "<< (*electrons).size()<<std::endl;
	    }
	  m_avalancheMC->DriftElectron((*electrons)[kk].GetX(),(*electrons)[kk].GetY(),(*electrons)[kk].GetZ(),(*electrons)[kk].GetTime());
	}
    }
}

