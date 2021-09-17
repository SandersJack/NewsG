#include "IonDrift.hh"

IonDrift::IonDrift()
  :m_sensor(NULL),
   m_avalRKF(new Garfield::DriftLineRKF()),
   m_avalancheMC(new Garfield::AvalancheMC()),
   m_driftType(DriftType::RKF),
   m_doSignal(true),
   m_debug(0)
{}



IonDrift::~IonDrift()
{
  delete m_avalRKF;
  delete m_avalancheMC;
}



void IonDrift::SetSensor(Garfield::Sensor *sensor)
{
  m_sensor=sensor;
  m_avalRKF->SetSensor(m_sensor);
  m_avalancheMC->SetSensor(m_sensor);
}



void IonDrift::DriftIons(std::vector<ChargeCarrier>* ions)
{
  if(m_driftType==DriftType::RKF)
    {
      //No way to switch off signal calculation within DriftLineRKF it seems
      for(unsigned int kk=0;kk<(*ions).size();kk++)
	{
	  //drift the ions
	  m_avalRKF->SetIonSignalScalingFactor((*ions)[kk].GetCharge());

	  bool statusDrift=m_avalRKF->DriftIon((*ions)[kk].GetX(),(*ions)[kk].GetY(),(*ions)[kk].GetZ(),(*ions)[kk].GetTime());
	  if(m_debug>=1)
	    {
	      std::cout << "avalRKF :: Drifting ion "<< kk+1 << " of "<< (*ions).size()
			<< " with scaling of " << (*ions)[kk].GetCharge() <<" this had a drift time of "
			<< m_avalRKF->GetDriftTime()<<" status is " << statusDrift<<std::endl;
	    }
	  (*ions)[kk].SetDriftTime(m_avalRKF->GetDriftTime());
	  m_avalRKF->SetIonSignalScalingFactor(1.);

	  int status = 1000;
	  double x,y,z,t;
	  m_avalRKF->GetEndPoint(x, y, z, t, status);

	  (*ions)[kk].SetPositionCartesian(x, y, z, t);
	  
	  //std::cout << "[IonDrift] Ion Endpoint is: x = " << (*ions)[kk].GetX()
	  //    << ",\t y = " << (*ions)[kk].GetY() << ",\t z = " << (*ions)[kk].GetZ()
	  //	    << ",\t r = " << (*ions)[kk].r() << ",\t t = " << (*ions)[kk].GetTime()
	  //	    << ",\t status = " << status << std::endl;
	}
    }
  else
    {
      if(m_doSignal)
	m_avalancheMC->EnableSignalCalculation(1); 
      else // <-- off by default in new Garfield
      	m_avalancheMC->EnableSignalCalculation(0);
      for(unsigned int kk=0;kk<(*ions).size();kk++)
	{
	  //drift the ions
	  if(m_debug>=1)
	    {
	      std::cout << "avalMC :: Drifting ion "<< kk+1 << " of "<< (*ions).size()<<std::endl;
	    }
	  m_avalancheMC->DriftIon((*ions)[kk].GetX(),(*ions)[kk].GetY(),(*ions)[kk].GetZ(),(*ions)[kk].GetTime());
	}
    }

  /**
  if(m_doSignal)
    {
      for(int ibin=0;ibin<signal_bins;ibin++)
	{
	  signalHistNt->Fill(ibin,allArea->GetIonSignal("readout",ibin));
	  signalNt[ibin]+=allArea->GetIonSignal("readout",ibin);
	  //std::cout<< "signal "<<ibin << " "<<allArea->GetIonSignal("readout",ibin)<< " "<<signalHistNt->GetBinContent(ibin)<<std::endl;
	}
      
      allArea->ClearSignal();
    }
  **/
}
