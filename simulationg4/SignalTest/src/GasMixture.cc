#include "GasMixture.hh"

GasMixture::GasMixture():
  m_gas(NULL),
  m_label(""),
  m_dirIonMob("")
{
  m_gas = new Garfield::MediumMagboltz();
}


GasMixture::~GasMixture()
{
  delete m_gas;
}



void GasMixture::SetGas(std::string filename, double wValue, double fanoFactor, double pressure)
{
  std::string gasfile("./gasfiles/");
  if(filename=="sedine2018")
    gasfile+="He_72p5_Ne_25p0_CH4_02p5_1bar/He_72p5_Ne_25_CH4_2p5.gas";
  else if(filename=="sedine2019")
    gasfile+="gasFile_0_CH4_6_Ne.gas";
  else if(filename=="sedineOld")
    gasfile+="Ne_99p3_CH4_00p7_3p1bar/Ne_99p3_CH4_0p7.gas";
  else if(filename=="He_90_CH4_10")
    gasfile+="He_90p0_CH4_10p0_1bar/He_90_CH4_10.gas";
  else if(filename=="He_67_Ne_30_CH4_3")
    gasfile+="He_67p0_Ne_30p0_CH4_03p0_1bar/pure.gas";
  else if(filename=="Ar_98_CH4Broken")
    gasfile+="gasFile_0_0_Ar_98_CH4.gas";
  else if(filename=="Ar_98_CH4")
    gasfile+="gasFile_0_CH4_2_Ar.gas";
  else
    {
      std::cout<< "No valid gas will use my favourite default, but you were WARNED"<<std::endl;
      gasfile+="He_72p5_Ne_25p0_CH4_02p5_1bar/He_72p5_Ne_25_CH4_2p5.gas";
    }

  m_gas->LoadGasFile(gasfile.data());
  m_gas->SetPressure(pressure);
  std::cout<< "using gasfile: "<< filename<< " with label "<< m_label<< " and pressure " <<m_gas->GetPressure()<< " Torr"<<std::endl;

  m_gas->SetMaxElectronEnergy(200.);

  if(m_dirIonMob==""){
    std::cout << "[GasMixture] Using default directory" << std::endl;
    m_gas->LoadIonMobility("../../garfieldpp/Data/IonMobility_He+_He.txt");
  }
  else if(m_dirIonMob=="BasicMobility"){
    std::cout << "[GasMixture] Using default directory" << std::endl;
    m_gas->LoadIonMobility("../../garfieldpp/Data/IonMobility_He+_He.txt");
  }
  else{
    std::string path=m_dirIonMob;
    std::cout << "[GasMixture] Ion mobility directory is: " << m_dirIonMob << std::endl; 
    path+= "/IonMobility_He+_He.txt";
    m_gas->LoadIonMobility(path.data());
  }
  

  const bool verbose = true;
  m_gas->Initialise(verbose);


  if (wValue > 1e-19)
    m_gas->SetW(wValue); // W value in eV
  if (fanoFactor > 1e-19)
    m_gas->SetFanoFactor(fanoFactor);
  // Testing code for the W value and Fano factor
  // m_gas->SetW(2);
  // m_gas->SetFanoFactor(0.7);
  std::cout << "[GasMixture] W Value from Magboltz gas is: " << m_gas->GetW() << std::endl;
  std::cout << "[GasMixture] Fano Factor from Magboltz gas is: " << m_gas->GetFanoFactor() << std::endl;

  std::cout << "[GasMixture] Gas Mixture is set"<<std::endl;
}
