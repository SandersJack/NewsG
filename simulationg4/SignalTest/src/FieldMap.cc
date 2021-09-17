#include "FieldMap.hh"

FieldMap::FieldMap():
  m_ansysMap(NULL),
  m_gas(NULL),
  m_sensorDir("UmbrellaSensor")
{
  m_ansysMap = new Garfield::ComponentAnsys121();
  m_ansysMap->EnableTetrahedralTreeForElementSearch(1);

  m_gas = new Garfield::MediumMagboltz();
}



FieldMap::~FieldMap()
{
  delete m_ansysMap;
  delete m_gas;
}



void FieldMap::Initialise()
{
  m_ansysMap->Initialise(Form("./sensors/%s/ELIST.lis",m_sensorDir.data()),
  		 Form("./sensors/%s/NLIST.lis",m_sensorDir.data()),
  		 Form("./sensors/%s/MPLIST.lis",m_sensorDir.data()),
  		 Form("./sensors/%s/PRNSOL.lis",m_sensorDir.data()), "mm");
  
  m_ansysMap->From2Dto3D();
  m_ansysMap->EnableRotationSymmetryY();
  m_ansysMap->SetWeightingField(Form("./sensors/%s/PRNSOL.lis",m_sensorDir.data()),"readout");   //Set Weighting Field
  m_ansysMap->PrintRange();

  if(m_sensorDir=="BasicSensor")
    {
      m_ansysMap->DriftMedium(3);
      m_ansysMap->NotDriftMedium(0);
      m_ansysMap->NotDriftMedium(1);
      m_ansysMap->NotDriftMedium(2);
      m_ansysMap->SetMedium(3,m_gas);
    }
  else if(m_sensorDir=="UmbrellaSensor")
    {
      m_ansysMap->DriftMedium(5);
      m_ansysMap->NotDriftMedium(0);
      m_ansysMap->NotDriftMedium(1);
      m_ansysMap->NotDriftMedium(2);
      m_ansysMap->NotDriftMedium(3);
      m_ansysMap->NotDriftMedium(4);
      m_ansysMap->SetMedium(5,m_gas);
    }
  else
    std::cout << "[FieldMap] ERROR: Unrecognised sensor; Materials are uninitialised!" << std::endl;
}
