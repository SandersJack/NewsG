#include "FieldMap.hh"

#include <algorithm>
#include <cstdlib>
#include <set>
#include <sstream>
#include <stdexcept>

#include "sys/stat.h"

#include "Garfield/ComponentAnsys121.hh"
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/ComponentFieldMap.hh"
#include "Garfield/ComponentUser.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/SolidSphere.hh"

FieldMap::FieldMap() : m_fieldMap(nullptr), m_gas(nullptr), m_sensorDir("NOTSET") {
  // m_ansysMap = new Garfield::ComponentAnsys121();
  // m_ansysMap->EnableTetrahedralTreeForElementSearch(1);
  m_idealMap = new Garfield::ComponentUser();

  m_gas = new Garfield::MediumMagboltz();
  m_owns_gas = true;
  // m_gasIdeal = new Garfield::MediumMagboltz();
  m_weighting_field_names.clear();
}

FieldMap::~FieldMap() {
  // delete m_ansysMap;
  delete m_idealMap;
  if (m_owns_gas) delete m_gas;
  delete m_fieldMap;
  // delete m_gasIdeal;
}

void FieldMap::Initialise() {
  std::string full_dir = find_sensor_dir();

  // Try to initialise the map
  bool success = false;
  {
    auto ansysMap = new Garfield::ComponentAnsys121();
    success = ansysMap->Initialise(
        full_dir + "ELIST.lis", full_dir + "NLIST.lis", full_dir + "MPLIST.lis",
        full_dir + "PRNSOL.lis", "mm");
    if (success) {
      success &=
          ansysMap->SetWeightingField(full_dir + "PRNSOL.lis", "readout");
      m_weighting_field_names = {"readout"};
      ansysMap->From2Dto3D();
      ansysMap->EnableRotationSymmetryY();
      m_fieldMap = ansysMap;
    } else {
      std::cerr
          << "[FieldMap] Failed to load 2D field map - will try to load 3D. "
          << "If that is successful don't worry about the above message."
          << std::endl;
      delete ansysMap;
    }
  }


  // Tom: This is temporary but we will try to load up the darksphere weighting
  // fields. We need to think of a better way to do this in the future
  if (!success) {
    auto ansysMap = new Garfield::ComponentAnsys123();
    success = ansysMap->Initialise(
        full_dir + "ELIST.lis", full_dir + "NLIST.lis", full_dir + "MPLIST.lis",
        full_dir + "PRNSOL.lis", "mm");
    m_weighting_field_names = {"readout"};
    success &=
        ansysMap->SetWeightingField(full_dir + "PRNSOL.lis", "readout");
    for (unsigned int i=1; i<=60; ++i) {
      std::string field_name = "PRNSOL" + std::to_string(i);
      success &= ansysMap->SetWeightingField(full_dir + field_name + ".lis", field_name);
      m_weighting_field_names.push_back(field_name);
    }
    m_fieldMap = ansysMap;
    if (!success) delete ansysMap;
  }


  if (!success) {
    auto ansysMap = new Garfield::ComponentAnsys123();
    success = ansysMap->Initialise(
        full_dir + "ELIST.lis", full_dir + "NLIST.lis", full_dir + "MPLIST.lis",
        full_dir + "PRNSOL.lis", "mm");
    success &=
      ansysMap->SetWeightingField(full_dir + "PRNSOL.lis", "readout");
    success &=
        ansysMap->SetWeightingField(full_dir + "PRNSOL_north.lis", "North");
    success &=
        ansysMap->SetWeightingField(full_dir + "PRNSOL_south.lis", "South");
    m_weighting_field_names = {"readout", "North", "South"};
    m_fieldMap = ansysMap;
    if (!success) delete ansysMap;
  }

  // If we fail to initialise the map then lets fail hard
  if (!success) throw std::runtime_error("Could not load sensor!");

  m_fieldMap->EnableTetrahedralTreeForElementSearch(true);
  m_fieldMap->PrintRange();
  // m_fieldMap->EnableDebugging();

  // Up to now we have always had a convention that the last medium is the drift
  // medium and all others are not drift mediums. If we continue with this then
  // we can just use this loop below instead of finding the specific sensor as a
  // string
  int last_medium = m_fieldMap->GetNumberOfMaterials() - 1;
  for (int i = 0; i < last_medium; ++i) {
    m_fieldMap->NotDriftMedium(i);
  }
  m_fieldMap->DriftMedium(last_medium);
  m_fieldMap->SetMedium(last_medium, m_gas);

  Garfield::GeometrySimple* geo = new Garfield::GeometrySimple();
  Garfield::SolidSphere* solid =
      new Garfield::SolidSphere(0., 0., 0., m_rCathode);
  // new Garfield::SolidSphere(0., 0., 0., m_rAnode, m_rCathode);
  std::cout
      << "WARNING:: FieldMap:: Remember the idealMap is not a hollow sphere! "
      << std::endl;

  // geo->AddSolid(solid, m_gasIdeal);
  geo->AddSolid(solid, m_gas);
  m_idealMap->SetGeometry(geo);
  m_idealMap->SetElectricField(Efield);
  m_idealMap->SetWeightingField(Wfield);

  // m_idealMap->SetDelayedWeightingField(DelayedWfield);

  // m_fieldMap = m_ansysMap;
}

double FieldMap::GetMaxBoundingBox() {
  double xmin, ymin, zmin, xmax, ymax, zmax;
  m_fieldMap->GetBoundingBox(xmin, ymin, zmin, xmax, ymax, zmax);

  return std::max({xmin, ymin, zmin, xmax, ymax, zmax});
}

void FieldMap::Efield(const double x, const double y, const double z,
                      double& ex, double& ey, double& ez) {
  const double rho = (m_rAnode * m_rCathode) / (m_rCathode - m_rAnode);

  double r = std::sqrt(x * x + y * y + z * z);
  double er = (m_voltage * rho) / r / r;
  ex = er * x / r;
  ey = er * y / r;
  ez = er * z / r;
}

void FieldMap::Wfield(const double x, const double y, const double z,
                      double& wx, double& wy, double& wz, const std::string) {
  const double rho = (m_rAnode * m_rCathode) / (m_rCathode - m_rAnode);
  //	const double Wvoltage = 1.;

  double r = std::sqrt(x * x + y * y + z * z);
  double er = (m_voltage * rho) / r / r;
  wx = er * x / r;
  wy = er * y / r;
  wz = er * z / r;
}

std::string FieldMap::find_sensor_dir() {
  const char* configDirEnv = std::getenv("SPC_SENSOR_DIR");
  if (configDirEnv) {
    std::stringstream ss(configDirEnv);
    std::string token;
    struct stat info;
    while (std::getline(ss, token, ':')) {
      std::string dir = token + "/sensors/" + m_sensorDir + "/";
      if (stat(dir.c_str(), &info)) continue;
      return dir;
    }
  }

  // If we've not managed to find the right directory then fall back on previous
  // method
  configDirEnv = std::getenv("SPC_CONFIG_DIR");
  std::string configDir;
  if (configDirEnv == nullptr) {
    std::cerr << "No SPC_CONFIG_DIR defined using a reletive path" << std::endl;
    configDir = ".";
  } else {
    configDir = configDirEnv;
  }

  return (configDir + "/sensors/" + m_sensorDir + "/");
}

// void FieldMap::DelayedWfield(const double x, const double y, const double z,
// const double t, double& wx, double& wy, double& wz, const std::string)
// {
// 	const double rho =(m_rAnode*m_rCathode)/(m_rCathode-m_rAnode);
// 	const double Wvoltage = 1.;

// 	double r = std::sqrt(x*x+y*y+z*z);
// 	double er = (Wvoltage*rho)/r/r;
// 	wx=er*x/r;
// 	wy=er*y/r;
// 	wz=er*z/r;
// }
