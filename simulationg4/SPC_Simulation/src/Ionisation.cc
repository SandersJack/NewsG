#include "Ionisation.hh"
#include "Randomize.hh"

#include "Garfield/Sensor.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/TrackSrim.hh"

Ionisation::Ionisation()
: m_sensor(NULL),
  m_heed(NULL),
  m_srim(NULL),
  m_isAr37calib(false)
{
  //radial and azimuthal positions -> (1cm, 5cm, 10cm, 14cm, 20cm, 25cm, 29cm) x(0.999, 0.866, 0.5, 0, -0.5, -0.866,-0.9988) = 7*7 = 49
  double radial[7]={2.,5,10,14,20,25,29};
  double cosTheta[7]={0.999, 0.866, 0.5, 0, -0.5, -0.866,-0.988};

  for(int i=0;i<7;i++)
    m_stdGridRadial[i]=radial[i];
  for(int i=0;i<7;i++)
    m_stdGridCosTheta[i]=cosTheta[i];

}

Ionisation::~Ionisation()
{
  delete m_heed;
}



int Ionisation::GetElectrons(std::vector<ChargeCarrier>* electrons)
{
  if(m_ionisationType==IonisationType::SingleElectrons)
    {
      std::vector<double> r0_init;
      std::vector<double> phi_init;
      std::vector<double> cosTheta_init;
      std::cout<< "[Ionisation] grid position = " << m_stdGridPosition<<std::endl;
      if(m_stdGridPosition<0)
	{
	  for(int iElectrons=0;iElectrons<m_nElectrons;iElectrons++)
	    {
	      r0_init.push_back(15 * G4UniformRand());
	      phi_init.push_back(0);//2*acos(-1.)*m_rndm->Uniform();
	      cosTheta_init.push_back(G4RandFlat::shoot(-1.0, 1.0));
	    }
	}
      else
	{
	  for(int iElectrons=0;iElectrons<m_nElectrons;iElectrons++)
	    {
	      r0_init.push_back(m_stdGridRadial[m_stdGridPosition/7]);
	      phi_init.push_back(0);
	      cosTheta_init.push_back(m_stdGridCosTheta[m_stdGridPosition%7]);
	    }
	}

      for(unsigned iElectrons=0;iElectrons<r0_init.size();iElectrons++)
	{
	  electrons->emplace_back();
	  electrons->at(iElectrons).SetPositionSphere(r0_init[iElectrons],
						      cosTheta_init[iElectrons],
						      phi_init[iElectrons],
						      0.);
	}
    }

  /* else if(m_isAr37calib)
     {
     Garfield::TrackElectron*electron_track=new Garfield::TrackElectron();
     electron_track->SetParticle("e");
     electron_track->SetMomentum(2.38e3); //in eV/c
     electron_track->EnableDebugging();


     const int nEvents = 1;
     for (int i = 0; i < nEvents; ++i)
     {
     //if (i == 1) m_heed->DisableDebugging();
     //if (i % 1000 == 0) std::cout << "[Ionisation] calculating "<< i << " of " << nEvents << " initial incoming particles\n";

     double x0 = 14.999, y0 = 0., z0 = 0., t0 = 0.;
     double dx0 = -1.,dy0 = -1., dz0 = 0.;

     double xmin,xmax,ymin,ymax,zmin,zmax;
     m_sensor->GetArea(xmin, ymin,
     zmin, xmax,
     ymax, zmax);

     if(m_isAr37calib)
     {
     Garfield::Medium* medium = nullptr;
     do
     {
     // uniformly distributed in sphere
     x0=m_rndm->Uniform(xmin,xmax);
     y0=m_rndm->Uniform(xmin,xmax);
     z0=m_rndm->Uniform(xmin,xmax);
     double phi0 = m_rndm->Uniform(0,2.*acos(-1.));
     double cosTheta0 = m_rndm->Uniform(-1,1);
     dx0 = sqrt(1-cosTheta0*cosTheta0)*cos(phi0);
     dy0 = sqrt(1-cosTheta0*cosTheta0)*sin(phi0);
     dz0 = cosTheta0;
     }
     while( !m_sensor->GetMedium(x0, y0, z0, medium) ||
     !medium->IsIonisable());
     }
     electron_track->NewTrack(x0, y0, z0, t0, dx0, dy0, dz0);

     double xc = 0., yc = 0., zc = 0., tc = 0.; 	  // Cluster coordinates
     int nc = 0;	  // Number of electrons produced in a collision
     double ec = 0.; 	  // Energy loss in a collision
     double extra = 0.; 	  // Dummy variable (not used at present)
     double esum = 0.; 	  // Total energy loss along the track
     int nsum = 0;
     int clusterCount=0;
     // Loop over the clusters.
     // GetCluster returns false if the list of clusters is exhausted
     // (or if the calculation of the track failed).
     std::vector<double> xElec;
     std::vector<double> yElec;
     std::vector<double> zElec;
     std::vector<double> tElec;
     while (electron_track->GetCluster(xc, yc, zc, tc, nc, ec, extra))
     {
     esum += ec;
     nsum += nc;
     std::cout << " an electron more "<<nc <<std::endl;
     clusterCount++;
     //numElectrons->Fill(nsum);
     //hEdep->Fill(esum * 1.e-3);

     electrons->emplace_back();
     electrons->at(clusterCount).setPositionCartesian(xc,
     yc,
     zc,
     tc);
     }
     }
     }*/

  else if(m_ionisationType==IonisationType::HEED)
    {
      if(!m_heed)
	m_heed = new Garfield::TrackHeed();

      m_heed->SetSensor(m_sensor);
      if(m_isAr37calib)
	{
	  m_heed->SetParticle("mu");
	  m_heed->SetMomentum(3.e9);//(in eV/c).
	}
      else
	{
	  m_heed->SetParticle("mu");
	  m_heed->SetMomentum(3.e9);// Set the particle momentum (in eV/c).
	}

      const int nEvents = 1;
      m_heed->EnableDebugging();
      for (int i = 0; i < nEvents; ++i)
	{
	  if (i == 1) m_heed->DisableDebugging();
	  if (i % 1000 == 0) std::cout << "[Ionisation] calculating "<< i << " of " << nEvents << " initial incoming particles\n";

	  double x0 , y0, z0, t0 = 0;
	  double dx0, dy0, dz0;
	  TVector3 vdirn;
	  TVector3 vunitrad;
	  TVector3 vunitdirn;


	  /**
	  double xmin = 60, xmax = 60, ymin,ymax,zmin,zmax;
	  m_sensor->GetArea(xmin, ymin,
			    zmin, xmax,
			    ymax, zmax);
	  **/
	  Garfield::Medium* medium = nullptr;
	  do
	    {
	      // uniformly distributed on sphere
	      double r0 = 29.999;
	      double phi0pos = G4RandFlat::shoot(0.0, 2.*acos(-1.));
	      double cosTheta0pos= G4RandFlat::shoot(-1.0, 1.0);
	      x0=r0*sqrt(1-cosTheta0pos*cosTheta0pos)*cos(phi0pos);
	      y0=r0*sqrt(1-cosTheta0pos*cosTheta0pos)*sin(phi0pos);
	      z0=r0*cosTheta0pos;

	      // uniformly distributed directions
	      double phi0 = G4RandFlat::shoot(0.0, 2.*acos(-1.));
	      double cosTheta0 = G4RandFlat::shoot(-1,1);
	      dx0 = sqrt(1-cosTheta0*cosTheta0)*cos(phi0);
	      dy0 = sqrt(1-cosTheta0*cosTheta0)*sin(phi0);
	      dz0 = cosTheta0;

	      vdirn.SetXYZ(x0,y0,z0);
	      vunitrad.SetXYZ(dx0,dy0,dz0);
	      vunitdirn = vdirn.Unit();
	    }


	  while( !m_sensor->GetMedium(x0, y0, z0, medium) ||
		 !medium->IsIonisable() ||
		 vunitrad.Dot(vunitdirn)>=0);

	  std::cout <<"x0="<<x0<<std::endl;
	  std::cout <<"y0="<<y0<<std::endl;
	  std::cout <<"z0="<<z0<<std::endl;

	  std::cout <<"dx0="<<dx0<<std::endl;
	  std::cout <<"dy0="<<dy0<<std::endl;
	  std::cout <<"dz0="<<dz0<<std::endl;

	  m_heed->NewTrack(x0, y0, z0, t0, dx0, dy0, dz0);



	  double xc = 0., yc = 0., zc = 0., tc = 0.; 	  // Cluster coordinates
	  int nc = 0;	  // Number of electrons produced in a collision
	  double ec = 0.; 	  // Energy loss in a collision
	  double extra = 0.; 	  // Dummy variable (not used at present)
	  double esum = 0.; 	  // Total energy loss along the track
	  int nsum = 0;
	  int clusterCount=0;
	  // Loop over the clusters.
	  // GetCluster returns false if the list of clusters is exhausted
	  // (or if the calculation of the track failed).
	  std::vector<double> xElec;
	  std::vector<double> yElec;
	  std::vector<double> zElec;
	  std::vector<double> tElec;
	  while (m_heed->GetCluster(xc, yc, zc, tc, nc, ec, extra))
	    {
	      esum += ec;
	      nsum += nc;
	      for(int jele=0;jele<nc;jele++)
		{
		  // Coordinates of the conduction electrons
		  double xe, ye, ze, te;
		  double ee, dxe, dye, dze;
		  m_heed->GetElectron(i, xe, ye, ze, te, ee, dxe, dye, dze);
		  if(sqrt(xe*xe+ye*ye+ze*ze)<29.999 && sqrt(xe*xe+ye*ye+ze*ze)>0.151 ){
		    if(!(ye<-0.15 && sqrt(xe*xe+ze*ze)<0.3))
		      {
			xElec.push_back(xe);
			yElec.push_back(ye);
			zElec.push_back(ze);
			tElec.push_back(te);
		      }
		  }

		}
	      clusterCount++;
	    }

	  std::cout << "[Ionisation] === heed generated "<< nsum << " Ionisation electrons in "<< clusterCount<<" clusters " << std::endl;
	  std::cout << "[Ionisation] === "<< " Total energy loss of " << esum*10e-3 << "keV " << "along the track" << std::endl;

	  //std::cout<< nsum << std::endl;

	  for(unsigned iElectrons=0;iElectrons<xElec.size();iElectrons++)
	    {
	      electrons->emplace_back();
	      electrons->at(iElectrons).SetPositionCartesian(xElec[iElectrons],
							     yElec[iElectrons],
							     zElec[iElectrons],
							     tElec[iElectrons]);
	    }

	}

    }
  else if(m_ionisationType==IonisationType::SRIM)
    {

      if(!m_srim)
	m_srim=new Garfield::TrackSrim();

      m_srim->SetSensor(m_sensor);
      const std::string file = "SRIM/CarbonInH-C-He-Ne-gas.txt";
      if (!m_srim->ReadFile(file))
	{
	  std::cerr << "Unable to load SRIM file.\n";
	  return -10;
	}

      // Set the initial kinetic energy of the particle (in eV).
      m_srim->SetKineticEnergy(1.e5);
      // Set the W value and Fano factor of the gas.
      m_srim->SetWorkFunction(30.0);
      m_srim->SetFanoFactor(0.3);
      // Set ratios of z/a
      const double za =((0.775*0.5)+(0.25*0.5)+0.025*(10./16.));
      m_srim->SetAtomicMassNumbers(6/za, 6. );
      m_srim->PlotEnergyLoss();
      m_srim->PlotRange();
      m_srim->PlotStraggling();
      m_srim->Print();
      // Specify how many electrons we want to be grouped to a cluster.
      //m_srim->SetTargetClusterSize(5);

      // Generate tracks.
      const unsigned int nTracks = 1;
      for (unsigned int i = 0; i < nTracks; ++i)
	{
	  double x0 = 10., y0 = 10., z0 = 0., t0 = 0.;
	  double dx0 = -1.,dy0 = 0., dz0 = 0.;

	  if (!m_srim->NewTrack(x0, y0, z0, t0, dx0, dy0, dz0))
	    {
	      std::cerr << "Failed to generate clusters, skip\n";
	      continue;
	    }

	  //Retrieve the clusters
	  unsigned int netot = 0;
	  bool done = false;
	  int clusterNum = 0;
	  std::vector<double> xElec;
	  std::vector<double> yElec;
	  std::vector<double> zElec;
	  std::vector<double> tElec;
	  while (!done)
	    {
	      double xc, yc, zc, tc, ec, ekin;
	      int ne = 0;
	      std::cout << " here "<<std::endl;
	      done = !m_srim->GetCluster(xc, yc, zc, tc, ne, ec, ekin);
	      netot += ne;
	      std::cout << ne<<std::endl;
	      for(int ielec=0;ielec<ne;ielec++)
		{

		  xElec.push_back(xc);
		  yElec.push_back(yc);
		  zElec.push_back(zc);
		  tElec.push_back(tc);
		}
	      clusterNum++;
	    }
	  std::cout << "[Ionisation] === SRIM generated "<< netot << " electrons in "<< clusterNum <<" clusters " << std::endl;

	  for(unsigned iElectrons=0;iElectrons<xElec.size();iElectrons++)
	    {
	      electrons->emplace_back();
	      electrons->at(iElectrons).SetPositionCartesian(xElec[iElectrons],
							     yElec[iElectrons],
							     zElec[iElectrons],
							     tElec[iElectrons]);
	    }
	}
      return 0;
    }
  else
    {
      std::cout << "[Ionisation] you should not be here "<<std::endl;
      return -1;
    }

  return 0;
}
