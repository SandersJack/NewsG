#include "ChargeCarrier.hh"

ChargeCarrier::ChargeCarrier()
  : m_x(0.),
    m_y(0.),
    m_z(0.),
    m_r(0.),
    m_cosTheta(0.),
    m_phi(0.),
    m_t(0.),
    m_charge(-1),
    m_driftTime(0.)
{}



ChargeCarrier::~ChargeCarrier()
{}



void ChargeCarrier::SetPositionSphere(double radius,double cosTheta,double phi, double time = 0.)
{
  m_r = radius;
  m_cosTheta = cosTheta;
  m_phi = phi;
  m_x = m_r*sqrt(1 - m_cosTheta*m_cosTheta)*cos(m_phi);
  m_y = m_r*cosTheta;
  m_z = m_r*sqrt(1 - m_cosTheta*m_cosTheta)*sin(m_phi);
  // In ansys geometry y is the polar coordinate
  m_t = time;
}



void ChargeCarrier::SetPositionCartesian(double xPos,double yPos,double zPos, double time = 0.)
{
  m_x = xPos;
  m_y = yPos;
  m_z = zPos;
  m_r = sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
  m_phi = atan2(m_z, m_x);
  m_cosTheta = m_y/sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
  // In ansys geometry y is the polar coordinate
  m_t = time;
}
