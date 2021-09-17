#include "ElectronAvalanche.hh"

#include "Garfield/Random.hh"
#include "Garfield/AvalancheMC.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentFieldMap.hh"
#include "Garfield/Medium.hh"
#include "Garfield/Sensor.hh"

#include "Randomize.hh"

ElectronAvalanche::ElectronAvalanche()
    : m_avalancheMicro(new Garfield::AvalancheMicroscopic()),
      m_avalancheMC(new Garfield::AvalancheMC()),
      m_doSignal(true),
      m_avalType(avalType::Microscopic),
      m_sensorRadius(1.),
      m_diffusion(true),
      m_singleIon(false),
      m_debug(0),
      m_safetyMax(40) {
  if (m_doSignal) {
    m_avalancheMicro->EnableSignalCalculation();
    m_avalancheMC->EnableSignalCalculation();
  }
  m_ne = 0;
  m_np = 0;
  m_ni = 0;
  m_neTot = 0;
  m_maxAval = 100000;
  m_step = 10000;
  m_stepSize = 0.01;
  m_ionsOut = new std::vector<ChargeCarrier>;
  m_elecsOut = new std::vector<ChargeCarrier>;

  //NOTE: also have m_avGain and m_intTowns, which are empty std::vector<double> variables

}

ElectronAvalanche::~ElectronAvalanche() {
  delete m_avalancheMicro;
  delete m_avalancheMC;
  delete m_ionsOut;
  delete m_elecsOut;
}

void ElectronAvalanche::SetSensors(std::vector<Garfield::Sensor *> sensorList) {
  m_sensors = sensorList;
  m_avalancheMicro->SetSensor(m_sensors[0]);
  m_avalancheMC->SetSensor(m_sensors[0]);
}

void ElectronAvalanche::Avalanche(std::vector<ChargeCarrier> &electronsIn) {
  m_ne = 0;
  m_np = 0;
  m_ni = 0;
  m_neTot = 0;
  m_ionsOut->clear();
  m_elecsOut->clear();
  m_intTowns.clear();
  m_avGain.clear();

  // 2020/04/27 Tom: Move to hard coded distance stepping for drift
  // Can fix in the future if we need to
  m_avalancheMC->SetDistanceSteps(0.05);

  for (unsigned iElectrons = 0; iElectrons < electronsIn.size(); iElectrons++) {

    if (iElectrons != 0 && (iElectrons % 1000) == 0) {
      std::cout << "[ElectronAvalanche] electron number " << iElectrons + 1
                << " out of " << electronsIn.size() << " electrons in the event"
                << std::endl;
    }

    if (m_debug >= 1) {
      std::cout << "[ElectronAvalanche] electron number " << iElectrons + 1
                << " out of " << electronsIn.size() << " electrons in the event"
                << std::endl;
      std::cout << "[ElectronAvalanche] electron  initial position = "
                << "r = " << electronsIn[iElectrons].GetRadius()
                << ",\t cosTheta = " << electronsIn[iElectrons].GetCosTheta()
                << ",\t phi = " << electronsIn[iElectrons].GetPhi()
                << ",\t t = " << electronsIn[iElectrons].GetTime() << std::endl;
    }

    double x0_init = electronsIn[iElectrons].GetX();
    double y0_init = electronsIn[iElectrons].GetY();
    double z0_init = electronsIn[iElectrons].GetZ();
    double t0_init = electronsIn[iElectrons].GetTime();

    double x0 = x0_init, y0 = y0_init, z0 = z0_init;
    double t0 = t0_init;
    double e0 = 0.1;
    double dx0 = 0, dy0 = 0., dz0 = 0.;

    int status = -1;

    int safetycounter = 0;

    while (status == -1 && safetycounter < m_safetyMax)  // Should be 40
    {
      safetycounter++;
      for (unsigned int iSensor = 0; iSensor < m_sensors.size(); iSensor++) {
        // std::cout<< "checking "<< iSensor << " "<<
        // m_sensors[iSensor]->IsInArea(x0,y0,z0)<<std::endl;
        if (!m_sensors[iSensor]->IsInArea(x0, y0, z0)) continue;

        // Check if we have a medium and we've not gone out of the detector
        // This can happen and it causes a message in DriftElectron that
        // is less clear than the one below
        Garfield::Medium *medium;
        if (!m_sensors[iSensor]->GetMedium(x0, y0, z0, medium)) {
          double r = std::sqrt(x0 * x0 + y0 * y0 + z0 * z0);
          status = -12;
          std::cerr << "[ElectronAvalanche] Couldn't get medium @ r = " << r
                    << " i elec = " << iElectrons << std::endl;
          break;
        }
        // std::cout << "[ElectronAvalanche] now in sensor "<< iSensor<< "
        // "<<x0<<" "<< y0<< " "<<z0<<std::endl;
        if (iSensor == 0) {
          // std::cout << "[ElectronAvalanche] Initial electron position: x = "
          // << x0 << ",\t y = " << y0 << ",\t z = " << z0 << ",\t t = " << t0
          // << std::endl;
          if (m_avalType == avalType::Microscopic) {
            m_avalancheMicro->SetSensor(
                m_sensors[iSensor]);  // this should redundant really...

            int electronVecSize = m_elecsOut->size();
            // std::cout << "[ElectronAvalanche] Avalanche Electron Vector Size
            // before avalanche " << iElectrons << " is: " << electronVecSize <<
            // std::endl;
            status =
                this->AvalancheMicroscopic(x0, y0, z0, t0, e0, dx0, dy0, dz0);

            electronsIn[iElectrons].SetDriftTime(
                m_elecsOut->at(electronVecSize).GetTime() - t0_init);
	    m_ionsOut->back().SetStatus(status);
	    electronsIn[iElectrons].SetStatus(status);

	    if (m_debug >= 1){
                std::cout << "[ElectronAvalanche] Size of initial electrons: "
			  << electronsIn.size() << std::endl;
            }
            // This drift time assumes that the first electron in AvalMicro is
            // the initial electron - not neccesarily true but shouldn't change
            // much
            /*electronsIn[iElectrons].SetDriftTime(m_elecsOut->at(electronVecSize).GetTime()-t0_init);
            std::cout << "[ElectronAvalanche] Final time of initial electron "
            << iElectrons << " is: " << m_elecsOut->at(electronVecSize).GetTime()
            << std::endl; std::cout << "[ElectronAvalanche] Stored drift time of
            electron " << iElectrons << " is: " <<
            electronsIn[iElectrons].driftTime() << std::endl; std::cout <<
            "[ElectronAvalanche] Avalanche Electron Vector Size after avalanche
            " << iElectrons << " is: " << m_elecsOut->size() << std::endl;*/
          } else if (m_avalType == avalType::MC)  // avalancheMC in sensor 0
          {
            m_avalancheMC->SetSensor(
                m_sensors[iSensor]);  // this should redundant really...

            int electronVecSize = m_elecsOut->size();
            // std::cout << "[ElectronAvalanche] Avalanche Electron Vector Size
            // before avalanche " << iElectrons << " is: " << electronVecSize <<
            // std::endl;

            status = this->AvalancheMC(x0, y0, z0, t0, e0, dx0, dy0, dz0);
            electronsIn[iElectrons].SetDriftTime(
                m_elecsOut->at(electronVecSize).GetTime() - t0_init);
	    m_ionsOut->back().SetStatus(status);
	    electronsIn[iElectrons].SetStatus(status);
            /*std::cout << "[ElectronAvalanche] Final time of initial electron "
            << iElectrons << " is: " << m_elecsOut->at(electronVecSize).GetTime()
            << std::endl; std::cout << "[ElectronAvalanche] Stored drift time of
            electron " << iElectrons << " is: " <<
            electronsIn[iElectrons].driftTime() << std::endl; std::cout <<
            "[ElectronAvalanche] Avalanche Electron Vector Size after avalanche
            " << iElectrons << " is: " << m_elecsOut->size() << std::endl;*/
          } else if (m_avalType == avalType::Custom)  // avalancheMC in sensor 0
          {
            m_avalancheMC->SetSensor(
                m_sensors[iSensor]);  // this should redundant really...
            status = this->AvalancheCustom(x0, y0, z0, t0, e0, dx0, dy0, dz0);
            electronsIn[iElectrons].SetDriftTime(t0 - t0_init);
	    m_ionsOut->back().SetStatus(status);
	    electronsIn[iElectrons].SetStatus(status);
          } else {
            status = -10;
            std::cout << "[ElectronAvalanche] Something is wrong" << std::endl;
          }
        } else {
          m_avalancheMC->SetSensor(m_sensors[iSensor]);
          double x2, y2, z2, t2 /*, e2*/;
          bool foundArea = m_avalancheMC->DriftElectron(x0, y0, z0, t0);
          if (foundArea) {
            m_ne = m_avalancheMC->GetNumberOfElectronEndpoints();
            if (m_ne > 1)
              std::cout << "[ElectronAvalanche] WARNING :: m_avalancheMC :: "
                           "Amplification in drift area"
                        << std::endl;
            if (m_ne == 0)
              std::cout << "[ElectronAvalanche] WARNING :: m_avalancheMC :: no "
                           "electron"
                        << std::endl;

            m_avalancheMC->GetElectronEndpoint(0, x2, y2, z2, t2, x0, y0, z0,
                                               t0, status);
            if (status == -1) {
              if (m_debug >= 1)
                std::cout << "[ElectronAvalanche] avaMC:: Sensor :: " << iSensor
                          << " :: electron left area at " << x0 << " " << y0
                          << " " << z0 << " t=" << t0 << " ns" << std::endl;
            } else if (status == -5) {
              // Status -5 is "particle not inside a drift medium"
              // This is fine if the electron has drifted into the wall for
              // example, but is not good news if it has drifted onto the anode
              // Therefore, check the radius that the electron has left the
              // drift medium and if it is < 2cm then print an error
              double r = std::sqrt(x0 * x0 + y0 * y0 + z0 * z0);
	      electronsIn[iElectrons].SetStatus(status);
	      m_intTowns.push_back(-2);
	      m_avGain.push_back(-2);
	      m_ionsOut->emplace_back();
	      m_ionsOut->back().SetPositionCartesian(x0, y0, z0, t0);
	      m_ionsOut->back().SetCharge(0.);
	      m_ionsOut->back().SetStatus(status);
	      if ((r < 2) || m_debug) {
                std::cerr << "[ElectronAvalanche] avaMC:: Sensor :: STATUS=-5 "
                             "(particle not inside a drift medium)"
                          << iSensor
                          << " will carry on :: electron left area at " << x0
                          << " " << y0 << " " << z0 << " t=" << t0 << " ns"
                          << std::endl;
              }
              break;
            } else {
              ChargeCarrier errorElectron;
              errorElectron.SetPositionCartesian(x0, y0, z0, t0);
              std::cout << "[ElectronAvalanche] avalMC:: Warning, status is "
                           "not -1, it is: "
                        << status << ",(" << x0 << " " << y0 << " " << z0
                        << "), position is r=" << errorElectron.r()
                        << " cosTheta=" << errorElectron.cosTheta()
                        << " phi=" << errorElectron.phi()
                        << " time=" << errorElectron.t() << std::endl;
	      electronsIn[iElectrons].SetStatus(status);
	      m_intTowns.push_back(-2);
	      m_avGain.push_back(-2);
	      m_ionsOut->emplace_back();
	      m_ionsOut->back().SetPositionCartesian(x0, y0, z0, t0);
	      m_ionsOut->back().SetCharge(0.);
	      m_ionsOut->back().SetStatus(status);
              break;
            }

            if (fabs((x2 - x0) / x2) < 0.0001 &&
                fabs((y2 - y0) / y2) < 0.0001 &&
                fabs((z2 - z0) / z2) < 0.0001) {
              // it seems that it got stuck...
              // move things around a bit (ok could do it a bit more elaborate
              // but whatever..)
              std::cout << "[ElectronAvalanche] avaMC:: Sensor :: seems "
                           "stuck... will move things a bit around"
                        << std::endl;
              x0 += 0.1;
              y0 += 0.1;
              z0 += 0.1;
            }
          } else {
            std::cout << "[ElectronAvalanche] WARNING :: m_avalancheMC :: No "
                         "area found"
                      << std::endl;
            m_avalancheMC->GetElectronEndpoint(0, x2, y2, z2, t2, x0, y0, z0,
                                               t0, status);
          }
        }
      }
    }
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] What happened to my electron? "
                << status << " " << safetycounter << std::endl;
  }  // looped over all electrons in the event
}

int ElectronAvalanche::AvalancheMicroscopic(double &x0, double &y0, double &z0,
                                            double &t0, double &e0, double &dx0,
                                            double &dy0, double &dz0) {
  double x2, y2, z2, t2, e2;
  int status = -1;
  if (m_enableMaxAval)
    m_avalancheMicro->EnableAvalancheSizeLimit(m_maxAval);
  else
    m_avalancheMicro->DisableAvalancheSizeLimit();
  m_avalancheMicro->AvalancheElectron(x0, y0, z0, t0, e0, dx0, dy0, dz0);
  m_avalancheMicro->GetAvalancheSize(m_ne, m_ni);
  if (m_debug >= 1)
    std::cout
        << "[ElectronAvalanche] Number of electrons from GetAvalancheSize = "
        << m_ne << std::endl;
  m_ne = m_avalancheMicro->GetNumberOfElectronEndpoints();
  if (m_debug >= 1) {
    std::cout << "[ElectronAvalanche] Number of electrons from "
                 "GetNumberOfElectronEndpoints = "
              << m_ne << std::endl;
    std::cout
        << "[ElectronAvalanche] m_avalancheMicro::  avalanche electrons = "
        << m_ne << " ions: " << m_ni << " "
        << m_avalancheMicro->GetNumberOfHoleEndpoints() << std::endl;
  }
  // If no avalanche
  if (m_ne == 1) {
    m_avalancheMicro->GetElectronEndpoint(0, x2, y2, z2, t2, e2, x0, y0, z0, t0,
                                          e0, status);

    // check if electron returned to other areas
    bool backwards = false;
    for (unsigned int iSensor2 = 1; iSensor2 < m_sensors.size(); iSensor2++) {
      if (!m_sensors[iSensor2]->IsInArea(x0, y0, z0)) continue;
      backwards = true;
    }
    if (backwards) {
      std::cout << "[ElectronAvalanche] avaMicro:: Sensor :: " << 0
                << " electron left area backwards" << std::endl;
      return -1;
    }
    // electron must have reached sensor or rod
    if (sqrt(x0 * x0 + y0 * y0 + z0 * z0) > m_sensorRadius * 1.01) {
      // electron on rod
      m_ionsOut->emplace_back();
      m_ionsOut->back().SetPositionCartesian(x2, y2, z2, t2);
      m_ionsOut->back().SetCharge(1.);
      m_intTowns.push_back(-1);
      m_avGain.push_back(-1);
      return 3;
      // status = 3;
      // break;
    }
    else {
      // something else happened
      m_ionsOut->emplace_back();
      m_ionsOut->back().SetPositionCartesian(x2, y2, z2, t2);
      m_ionsOut->back().SetCharge(1.);
      m_intTowns.push_back(-1);
      m_avGain.push_back(-1);
      return status;  //       status = 2;
      // break;
    }
  }

  double rElec_tot = 0.;
  double thetaElec_tot = 0.;
  double phiElec_tot = 0.;
  double tElec_tot = 0.;

  double rIon_tot = 0.;
  double thetaIon_tot = 0.;
  double phiIon_tot = 0.;
  double tIon_tot = 0.;

  for (int k = 0; k < m_ne; k++) {
    m_avalancheMicro->GetElectronEndpoint(k, x2, y2, z2, t2, e2, x0, y0, z0, t0,
                                          e0, status);
    if (m_debug >= 1) {
      std::cout << "[ElectronAvalanche] m_avalancheMicro:: Electron  " << k + 1
                << " " << x2 << "\t" << y2 << "\t" << z2 << "\t" << t2 << "\t"
                << e2 << "\t" << x0 << "\t" << y0 << "\t" << z0 << "\t" << t0
                << "\t" << e0 << "\t" << status << std::endl;
    }

    if (m_singleElectron) {
      double r0 = sqrt(x0 * x0 + y0 * y0 + z0 * z0);
      double theta0 = acos(y0 / r0);
      double phi0 = atan2(z0, x0);

      rElec_tot += r0;
      thetaElec_tot += theta0;
      phiElec_tot += phi0;
      tElec_tot += t0;
    } else {
      m_elecsOut->emplace_back();
      m_elecsOut->back().SetPositionCartesian(x0, y0, z0, t0);
      m_elecsOut->back().SetCharge(1.);
    }

    if (m_singleIon) {
      double r2 = sqrt(x2 * x2 + y2 * y2 + z2 * z2);
      double theta2 = acos(y2 / r2);
      double phi2 = atan2(z2, x2);

      rIon_tot += r2;
      thetaIon_tot += theta2;
      phiIon_tot += phi2;
      tIon_tot += t2;
    } else {
      m_ionsOut->emplace_back();
      m_ionsOut->back().SetPositionCartesian(x2, y2, z2, t2);
      m_ionsOut->back().SetCharge(1.);
    }
  }

  if (m_singleElectron) {
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] Doing single electron!" << std::endl;
    double rElec_av = rElec_tot / m_ne;
    double thetaElec_av = thetaElec_tot / m_ne;
    double phiElec_av = phiElec_tot / m_ne;
    double tElec_av = tElec_tot / m_ne;

    m_elecsOut->emplace_back();
    m_elecsOut->back().SetPositionSphere(
        rElec_av, cos(thetaElec_av), phiElec_av, tElec_av);
    m_elecsOut->back().SetCharge(m_ne);
  }

  if (m_singleIon) {
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] Doing single ion!" << std::endl;
    double rIon_av = rIon_tot / m_ne;
    double thetaIon_av = thetaIon_tot / m_ne;
    double phiIon_av = phiIon_tot / m_ne;
    double tIon_av = tIon_tot / m_ne;

    m_ionsOut->emplace_back();
    m_ionsOut->back().SetPositionSphere(
        rIon_av, cos(thetaIon_av), phiIon_av, tIon_av);
    m_ionsOut->back().SetCharge(m_ne);
  }

  m_neTot += m_ne;
  if (m_debug >= 1)
    {
      std::cout << "[ElectronAvalanche] Total number of electrons so far: "
                << m_neTot << std::endl;
      std::cout << "[ElectronAvalanche] Size of electron vector: "
                << m_elecsOut->size() << std::endl;
      std::cout << "[ElectronAvalanche] Size of ion vector: "
                << m_ionsOut->size() << std::endl;

    }

  // Do not know average gain or integrated townsend for microscopic avalanches
  m_intTowns.push_back(-1);
  m_avGain.push_back(-1);

  // done bussiness
  // go away
  return 1;
  // status=1;
  // break;
}

int ElectronAvalanche::AvalancheMC(double &x0, double &y0, double &z0,
                                   double &t0, double &e0, double &/*dx0*/,
                                   double &/*dy0*/, double &/*dz0*/) {
  double x2, y2, z2, t2, e2;
  int status = -1;
  if (m_debug >= 1)
    std::cout << "[ElectronAvalanche] Initial Position: x = " << x0
              << ",\t y = " << y0 << ",\t z = " << z0 << ",\t t = " << t0
              << std::endl;

  if (m_diffusion) {
    m_avalancheMC->EnableDiffusion();
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] AvalMC Diffusion Enabled!" << std::endl;
  } else {
    m_avalancheMC->DisableDiffusion();
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] AvalMC Diffusion Disabled!"
                << std::endl;
  }
  if (m_avalMCStepType == avalMCStepType::nColl) {
    int nCollisions = std::round(m_step);
    m_avalancheMC->SetCollisionSteps(nCollisions);
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] Number of collisions for step size is: "
                << nCollisions << std::endl;
  } else if (m_avalMCStepType == avalMCStepType::tStep) {
    m_avalancheMC->SetTimeSteps(m_step);
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] Using time steps of size: " << m_step
                << " ns" << std::endl;
  } else if (m_avalMCStepType == avalMCStepType::dStep) {
    m_avalancheMC->SetDistanceSteps(m_step);
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] Using distance steps of size: "
                << m_step << " cm" << std::endl;
  } else {
    double defaultColl = 10000;
    std::cout << "[ElectronAvalanche] ERROR: Invalid type entered. Using "
              << defaultColl << " collisions by default." << std::endl;
    m_avalancheMC->SetCollisionSteps(defaultColl);
  }
  m_avalancheMC->AvalancheElectron(x0, y0, z0, t0);

  // This is kind of ridiculous, but Garfield has inconsistent GetAvalancheSize
  // signatures for different avalanche classes... hence the slightly odd thing
  // here
  unsigned int tmp_ne, tmp_ni;
  m_avalancheMC->GetAvalancheSize(tmp_ne, tmp_ni);
  m_ne = tmp_ne;
  m_ni = tmp_ni;
  if (m_debug >= 1)
    std::cout
        << "[ElectronAvalanche] Number of electrons from GetAvalancheSize = "
        << m_ne << std::endl;
  m_ne = m_avalancheMC->GetNumberOfElectronEndpoints();
  if (m_debug >= 1) {
    std::cout << "[ElectronAvalanche] Number of electrons from "
                 "GetNumberOfElectronEndpoints = "
              << m_ne << std::endl;
    std::cout << "m_avalancheMC::  avalanche electrons = " << m_ne
              << " ions: " << m_ni << " "
              << m_avalancheMC->GetNumberOfIonEndpoints() << std::endl;
  }
  // If no avalanche
  if (m_ne == 1) {
    m_avalancheMC->GetElectronEndpoint(0, x2, y2, z2, t2, x0, y0, z0, t0,
                                       status);

    // std::cout<<"endpoint at = "<< sqrt(x0*x0+y0*y0+z0*z0)<< std::endl;
    // std::cout << "m_avalancheMC:: Electron " << 0 << " "
    //<< x2 << "\t" <<y2 << "\t" <<z2 << "\t" <<t2<< "\t" <<e2<< "\t"
    //	<< x0 << "\t" <<y0 <<"\t" <<z0 << "\t" <<t0 <<"\t" <<e0<< "\t"
    //	<< status << std::endl;

    // check if electron returned to other areas
    bool backwards = false;
    for (unsigned int iSensor2 = 1; iSensor2 < m_sensors.size(); iSensor2++) {
      if (!m_sensors[iSensor2]->IsInArea(x0, y0, z0)) continue;
      backwards = true;
    }
    if (backwards) {
      std::cout << "avaMC:: Sensor :: " << 0 << " electron left area backwards"
                << std::endl;
      return -1;
      // status  = -1;
      //	  break;
    }
    // electron must have reached sensor or rod
    if (sqrt(x0 * x0 + y0 * y0 + z0 * z0) > m_sensorRadius * 1.01) {
      // electron on rod
      m_ionsOut->emplace_back();
      m_ionsOut->back().SetPositionCartesian(x2, y2, z2, t2);
      m_ionsOut->back().SetCharge(1.);
      m_intTowns.push_back(-1);
      m_avGain.push_back(-1);
      return 3;
      // status = 3;
      // break;
    } else {
      // something else happened
      m_ionsOut->emplace_back();
      m_ionsOut->back().SetPositionCartesian(x2, y2, z2, t2);
      m_ionsOut->back().SetCharge(1.);
      m_intTowns.push_back(-1);
      m_avGain.push_back(-1);
      return status;
      // status = 2;
      // break;
    }
  }

  double rElec_tot = 0.;
  double thetaElec_tot = 0.;
  double phiElec_tot = 0.;
  double tElec_tot = 0.;

  double rIon_tot = 0.;
  double thetaIon_tot = 0.;
  double phiIon_tot = 0.;
  double tIon_tot = 0.;

  for (int k = 0; k < m_ne; k++) {
    m_avalancheMC->GetElectronEndpoint(k, x2, y2, z2, t2, x0, y0, z0, t0,
                                       status);
    if (m_debug >= 1) {
      std::cout << "[ElectronAvalanche] m_avalancheMC:: Electron  " << k + 1
                << " " << x2 << "\t" << y2 << "\t" << z2 << "\t" << t2 << "\t"
                << e2 << "\t" << x0 << "\t" << y0 << "\t" << z0 << "\t" << t0
                << "\t" << e0 << "\t" << status << std::endl;
    }

    if (m_singleElectron) {
      double r0 = sqrt(x0 * x0 + y0 * y0 + z0 * z0);
      double theta0 = acos(y0 / r0);
      double phi0 = atan2(z0, x0);

      rElec_tot += r0;
      thetaElec_tot += theta0;
      phiElec_tot += phi0;
      tElec_tot += t0;
    } else {
      m_elecsOut->emplace_back();
      m_elecsOut->back().SetPositionCartesian(x0, y0, z0, t0);
      m_elecsOut->back().SetCharge(1.);
    }

    if (m_singleIon) {
      double r2 = sqrt(x2 * x2 + y2 * y2 + z2 * z2);
      double theta2 = acos(y2 / r2);
      double phi2 = atan2(z2, x2);

      rIon_tot += r2;
      thetaIon_tot += theta2;
      phiIon_tot += phi2;
      tIon_tot += t2;
    } else {
      m_ionsOut->emplace_back();
      m_ionsOut->back().SetPositionCartesian(x2, y2, z2,
                                                                 t2);
      m_ionsOut->back().SetCharge(1.);
    }
  }

  if (m_singleElectron) {
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] Doing single electron!" << std::endl;

    double rElec_av = rElec_tot / m_ne;
    double thetaElec_av = thetaElec_tot / m_ne;
    double phiElec_av = phiElec_tot / m_ne;
    double tElec_av = tElec_tot / m_ne;

    m_elecsOut->emplace_back();
    m_elecsOut->back().SetPositionSphere(
        rElec_av, cos(thetaElec_av), phiElec_av, tElec_av);
    m_elecsOut->back().SetCharge(m_ne);
  }

  if (m_singleIon) {
    if (m_debug >= 1)
      std::cout << "[ElectronAvalanche] Doing single ion!" << std::endl;

    double rIon_av = rIon_tot / m_ne;
    double thetaIon_av = thetaIon_tot / m_ne;
    double phiIon_av = phiIon_tot / m_ne;
    double tIon_av = tIon_tot / m_ne;

    m_ionsOut->emplace_back();
    m_ionsOut->back().SetPositionSphere(
        rIon_av, cos(thetaIon_av), phiIon_av, tIon_av);
    m_ionsOut->back().SetCharge(m_ne);
  }

  // TODO: obtain integrated townsend and average gain from AvalancheMC
  if (m_debug >= 1)
    std::cout << "[ElectronAvalanche] WARNING: Setting integrated townsend and average gain to -1 for AvalancheMC" << std::endl;

  m_intTowns.push_back(-1);
  m_avGain.push_back(-1);

  m_neTot += m_ne;
  if (m_debug >= 1)
    std::cout << "[ElectronAvalanche] Total number of electrons so far: "
              << m_neTot << std::endl;

  // done bussiness
  // go away
  return 1;
  // status=1;
  // break;
}

int ElectronAvalanche::AvalancheCustom(double &x0, double &y0, double &z0,
                                       double &t0, double &/*e0*/, double &/*dx0*/,
                                       double &/*dy0*/, double &/*dz0*/) {
  double x2 = x0, y2 = y0, z2 = z0, t2 = t0 /*, e2*/;
  int status = -1;

  /// also TODO, drift the electron and try to obtain the electron signal
  /// component which is ignored for the moment
  // m_avalancheMC->DriftElectron(x0, y0, z0, t0);

  /// need to integrate townsend coefficient
  /// to obtain gain, and then put polya for fluctuations, and then put ions
  // std::cout << "[ElectronAvalanche] Before dynamic cast" << std::endl;
  // Garfield::ComponentFieldMap
  // *fm=dynamic_cast<Garfield::ComponentFieldMap*>(m_sensors[0]->GetComponent(0));
  // std::cout << "[ElectronAvalanche] After dynamic cast" << std::endl;

  double x = x0;
  double y = y0;
  double z = z0;
  double t = t0;
  double ex = 0.;
  double ey = 0.;
  double ez = 0.;
  // Velocity is used to get time of each step
  double vx = 0., vy = 0., vz = 0.;

  Garfield::Medium *medium = NULL;
  const double step = m_stepSize;  // in cm
  // std::cout << "[ElectronAvalanche] Step Size is: " << step << " cm" <<
  // std::endl;
  double integrateTownsend = 0.;

  // Store whether you initially wanted diffusion on or off
  bool diffusion = m_diffusion;

  if (m_debug >= 1)
    std::cout << "[ElectronAvalanche] Initial Position is: x = " << x
              << ", y = " << y << ", z = " << z << std::endl;

  // std::cout << "[ElectronAvalanche] Before efield" << std::endl;
  // fm->ElectricField(x,y,z,ex,ey,ez,medium,status);
  m_sensors[0]->ElectricField(x, y, z, ex, ey, ez, medium, status);
  // std::cout << "[ElectronAvalanche] After efield" << std::endl;

  if (m_debug >= 1) {
    if (medium)
      std::cout << "[ElectronAvalanche] Inside drift medium!" << std::endl;
    else
      std::cout << "[ElectronAvalanche] Outside drift medium!" << std::endl;
  }

  int errorInt = 0;
  int iteration = 0;

  double initRadius = 0;
  double finalRadius = 0;

  // std::cout << "[ElectronAvalanche] Test Electric field is: ex = " << ex <<
  // ",\t ey = " << ey
  //	    << ",\t ez = " << ez << ",\t magnitude = " << sqrt(ex*ex + ey*ey +
  //ez*ez) << std::endl; if you get out of the drift area, you are outside the
  // medium and the pointer will be null

  int nStepsCount = 0;
  while (medium) {
    iteration++;
    // field magnitude at initial position
    double FieldMagnitude = sqrt(ex * ex + ey * ey + ez * ez);

    // change effective step based on field
    // reference step for 1kV/cm

    double dstep = step;
    // double dstep =
    // (step*1.e3/FieldMagnitude<step/20.)?step/20.:step*1.e3/FieldMagnitude;

    // keep the old position and field
    x2 = x;
    y2 = y;
    z2 = z;
    t2 = t;
    initRadius = sqrt(x2 * x2 + y2 * y2 + z2 * z2);

    // Including diffusion - assuming ideal spherical field here
    double longDiff = 0.;
    double transDiff = 0.;
    medium->ElectronDiffusion(ex, ey, ez, 0., 0., 0., longDiff, transDiff);

    // double dstep = sqrt(longDiff*longDiff +
    // transDiff*transDiff)/(alpha*alpha); std::cout << "[ElectronAvalanche] Size
    // of step (cm) is: " << dstep << std::endl;

    // Get random diffusion lengths and transverse direction
    double rndmLongDiff =
        G4RandGauss::shoot(0, longDiff * sqrt(dstep) / exp(integrateTownsend));
    double rndmTranDiff =
        G4RandGauss::shoot(0, transDiff * sqrt(dstep) / exp(integrateTownsend));
    double rndmPhiTranDiff = G4RandFlat::shoot(0., 2 * acos(-1.));

    TVector3 eField(ex, ey, ez);
    TVector3 longVec = eField.Unit();
    TVector3 tranVec = longVec.Orthogonal();
    tranVec.Rotate(rndmPhiTranDiff,
                   longVec);  // Rotate() alters the vector itself

    double dx = 0.;
    double dy = 0.;
    double dz = 0.;
    if (diffusion) {
      dx = longVec.x() * rndmLongDiff + tranVec.x() * rndmTranDiff;
      dy = longVec.y() * rndmLongDiff + tranVec.y() * rndmTranDiff;
      dz = longVec.z() * rndmLongDiff + tranVec.z() * rndmTranDiff;
    }

    // new position
    // the - is because we are drifting electrons here
    x = x - ex / FieldMagnitude * dstep + dx;
    y = y - ey / FieldMagnitude * dstep + dy;
    z = z - ez / FieldMagnitude * dstep + dz;

    double distance =
        sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y) + (z2 - z) * (z2 - z));
    // double townsBefore = integrateTownsend;
    double nSteps = 10;  // Try this as 10 and look for diff.
    double distance_step = distance / nSteps;

    for (unsigned int iStep = 0; iStep < nSteps; iStep++) {
      double x_step = x2 + iStep * (x - x2) / (nSteps - 1);
      double y_step = y2 + iStep * (y - y2) / (nSteps - 1);
      double z_step = z2 + iStep * (z - z2) / (nSteps - 1);

      double ex_step = 0.;
      double ey_step = 0.;
      double ez_step = 0.;

      double alpha = 0.;
      double eta = 0.;
      double driftv = 0.;

      // fm->ElectricField(x_step,y_step,z_step,ex_step,ey_step,ez_step,medium,status);
      m_sensors[0]->ElectricField(x_step, y_step, z_step, ex_step, ey_step,
                                  ez_step, medium, status);

      // if the end point is outside of the medium, stop calculating

      if (medium) {
        medium->ElectronTownsend(ex_step, ey_step, ez_step, 0., 0., 0., alpha);
        medium->ElectronAttachment(ex_step, ey_step, ez_step, 0., 0., 0., eta);
        medium->ElectronVelocity(ex_step, ey_step, ez_step, 0., 0., 0., vx, vy,
                                 vz);

        driftv = sqrt(vx * vx + vy * vy + vz * vz);

        t += distance_step / driftv;
        integrateTownsend += (alpha - eta) * distance_step;
        if (sqrt(x_step * x_step + y_step * y_step + z_step * z_step) < 0.5)
          nStepsCount++;
      }
    }
    finalRadius = sqrt(x * x + y * y + z * z);
    if (finalRadius > initRadius) errorInt++;

    // fm->ElectricField(x,y,z,ex,ey,ez,medium,status);
    m_sensors[0]->ElectricField(x, y, z, ex, ey, ez, medium, status);
  }
  if (m_debug >= 1)
    std::cout << "[ElectronAvalanche] Final position is: x = " << x
              << ",\t y = " << y << ",\t z = " << z
              << ",\t Radius = " << finalRadius << " townsend is "
              << integrateTownsend << std::endl;

  m_elecsOut->emplace_back();
  m_elecsOut->back().SetPositionCartesian(x, y, z, t);
  m_elecsOut->back().SetCharge( m_ne * 1.);  // Converts charge to a double - may not be necessary

  x0 = x;
  y0 = y;
  z0 = z;
  t0 = t;

  // std::cout << "[ElectronAvalanche] Electron avalanche time is: t = " << t-t0
  // << " ns" << std::endl;

  // std::cout << "[ElectronAvalanche] Electron moved away from anode in " <<
  // errorInt << " steps out of " << iteration << std::endl;

  // std::cout << "Finished : integrated townsend " << integrateTownsend
  // <<std::endl;
  if (integrateTownsend > 19.) {
    std::cout
        << "[ElectronAvalanche] WARNING: Integrated townsend went above 19! ("
        << integrateTownsend << ")" << std::endl;
    integrateTownsend = 19.;
  }
  double averageGain = exp(integrateTownsend);
  if (m_debug >= 1) {
    std::cout << "[ElectronAvalanche] Average Gain = " << averageGain
              << std::endl;
    std::cout << "[ElectronAvalanche] Integrated Townsend = "
              << integrateTownsend << std::endl;
  }

  m_intTowns.push_back(integrateTownsend);
  m_avGain.push_back(averageGain);
  m_ni = (integrateTownsend > 0.) ? averageGain * Garfield::RndmPolya(0.2) : 0;
  if (averageGain <= 1)
    std::cout << "[ElectronAvalanche] Failed to avalanche!" << std::endl;
  m_ne = 1 + m_ni;
  // std::cout << "m_avalancheCustom::  avalanche electrons = " << m_ne << "
  // ions: "<< m_ni<< std::endl;

  m_neTot += m_ne;
  // std::cout << "[ElectronAvalanche] Total number of electrons so far: " <<
  // m_neTot << std::endl;

  // std::cout << "t2 is: " << t2 << std::endl;

  m_ionsOut->emplace_back();
  m_ionsOut->back().SetPositionCartesian(x2, y2, z2, t2);
  m_ionsOut->back().SetCharge(m_ni * 1.);
  // std::cout << " ion  position " <<
  // m_ionsOut->back().GetRadius() <<" "
  // <<m_ionsOut->back().GetCosTheta()<< " "<<x2 << " "<<y2 <<
  // " "<< z2<< " "<<t2 <<std::endl;
  // done bussiness
  // go away
  return 1;
}

/*electronsIn[iElectrons].SetDriftTime(t0);
                      electronsIn[iElectrons].SetPositionCartesian(x0, y0, z0,
   t0); std::cout << "[ElectronAvalanche] Stored electron final position is: x =
   " << electronsIn[iElectrons].GetX() << " cm, \t y = " <<
   electronsIn[iElectrons].y() << " cm, z = " << electronsIn[iElectrons].GetZ()
   << " cm" << std::endl; std::cout << "[ElectronAvalanche] Stored electron
   final position is: r = " << electronsIn[iElectrons].GetRadius() << " cm, \t
   cosTheta = " << electronsIn[iElectrons].cosTheta() << ", phi = " <<
   electronsIn[iElectrons].phi() << " rad" << std::endl; std::cout <<
   "[ElectronAvalanche] Stored electron drift time is: " <<
   electronsIn[iElectrons].driftTime() << " ns" << std::endl;*/
