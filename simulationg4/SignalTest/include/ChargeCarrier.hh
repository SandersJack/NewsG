#ifndef CHARGECARRIER_H
#define CHARGECARRIER_H

#include <cmath>

class ChargeCarrier{
public:
  ChargeCarrier();
  ~ChargeCarrier();

  void SetPositionSphere(double radius,double cosineTheta,double phiAngle, double time);
  void SetPositionCartesian(double xPos,double yPos,double zPos, double time);
  
  inline double GetX()        {return m_x;}
  inline double GetY()        {return m_y;}
  inline double GetZ()        {return m_z;}
  inline double GetRadius()   {return m_r;}
  inline double GetCosTheta() {return m_cosTheta;}  
  inline double GetPhi()      {return m_phi;}
  inline double GetTime()     {return m_t;}
  inline double GetCharge()   {return m_charge;}
  inline double GetDriftTime(){return m_driftTime;}
  
  // Alternate versions of the above
  inline double x()       {return m_x;}
  inline double y()       {return m_y;}
  inline double z()       {return m_z;}
  inline double r()       {return m_r;}
  inline double cosTheta(){return m_cosTheta;}
  inline double phi()     {return m_phi;}
  inline double t()       {return m_t;}
  
  inline void SetX(double xPos)              {m_x = xPos;}
  inline void SetY(double yPos)              {m_y = yPos;}
  inline void SetZ(double zPos)              {m_z = zPos;}
  inline void SetRadius(double radius)       {m_r = radius;}
  inline void SetCosTheta(double cosineTheta){m_cosTheta = cosineTheta;}
  inline void SetPhi(double phiAngle)        {m_phi = phiAngle;}
  inline void SetTime(double time)           {m_t = time;}
  inline void SetCharge(double charge)       {m_charge = charge;}
  inline void SetDriftTime(double time)      {m_driftTime = time;}

private:
  double m_x;
  double m_y;
  double m_z;
  double m_r;
  double m_cosTheta;
  double m_phi;
  double m_t;
  double m_charge;
  double m_driftTime;
};

#endif //CHARGECARRIER_H
