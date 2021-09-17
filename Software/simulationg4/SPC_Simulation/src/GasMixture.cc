#include "GasMixture.hh"

#include <sys/stat.h>

#include <cstdlib>
#include <stdexcept>

#include "Garfield/MediumMagboltz.hh"

GasMixture::GasMixture()
    : m_gas(nullptr), m_label(""), m_dirIonMob(""), m_debug(0) {
  m_gas = new Garfield::MediumMagboltz();
}

GasMixture::~GasMixture() { delete m_gas; }

void GasMixture::SetGas(std::string filename, double wValue, double fanoFactor,
                        double pressure) {
  const char* configDir = std::getenv("SPC_CONFIG_DIR");
  std::string gasfile;
  if (configDir == nullptr) {
    std::cerr << "No SPC_CONFIG_DIR defined using a reletive path" << std::endl;
    gasfile = ".";
  } else {
    gasfile = configDir;
  }

  gasfile += "/GasFiles/";

  std::string tmp_file = gasfile + filename;
  struct stat info;

  if (!stat(tmp_file.c_str(), &info)) {
    gasfile += filename;
  } else {
    std::cerr
        << "To specify a gasfile please give the full filename relative to "
        << gasfile << " e.g. gasFile_760_0_Ar_98_CH4.gas" << std::endl;
        throw std::runtime_error("Could not load gasfile!");
  }

  if (!m_gas->LoadGasFile(gasfile.data())) {
    throw std::runtime_error("Could not load gasfile!");
  };
  m_gas->SetPressure(pressure);
  if (m_debug >= 1)
    std::cout << "using gasfile: " << filename << " with label " << m_label
              << " and pressure " << m_gas->GetPressure() << " Torr"
              << std::endl;

  m_gas->SetMaxElectronEnergy(200.);
  const char* garfieldDirEnv = std::getenv("GARFIELD_HOME");
  std::string garfieldDir;
  if (garfieldDirEnv == nullptr) {
    std::cerr << "No GARFIELD_HOME defined using a reletive path" << std::endl;
    garfieldDir = "../../garfieldpp";
  } else {
    garfieldDir = garfieldDirEnv;
  }

  std::string ion_mob_file = "";
  if (m_dirIonMob == "" || m_dirIonMob == "BasicMobility") {
    if (m_debug >= 1) {
      std::cout << "[GasMixture] Using default directory" << std::endl;
    }
    ion_mob_file = garfieldDir + "/Data/IonMobility_He+_He.txt";
  } else {
    std::string path = m_dirIonMob;
    if (m_debug >= 1) {
      std::cout << "[GasMixture] Ion mobility directory is: " << m_dirIonMob
                << std::endl;
    }
    ion_mob_file = garfieldDir + "/IonMobility_He+_He.txt";
  }
  if (!m_gas->LoadIonMobility(ion_mob_file)) {
    throw std::runtime_error("Failed to LoadIonMobility");
  };

  const bool verbose = true;
  if (!m_gas->Initialise(verbose)) {
    throw std::runtime_error("Failed to initialise gas");
  };

  if (wValue > 1e-19) m_gas->SetW(wValue);  // W value in eV
  if (fanoFactor > 1e-19) m_gas->SetFanoFactor(fanoFactor);
  // Testing code for the W value and Fano factor
  // m_gas->SetW(2);
  // m_gas->SetFanoFactor(0.7);
  if (m_debug >= 1) {
    std::cout << "[GasMixture] W Value from Magboltz gas is: " << m_gas->GetW()
              << std::endl;
    std::cout << "[GasMixture] Fano Factor from Magboltz gas is: "
              << m_gas->GetFanoFactor() << std::endl;

    std::cout << "[GasMixture] Gas Mixture is set" << std::endl;
  }
}
