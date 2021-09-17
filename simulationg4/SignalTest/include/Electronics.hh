#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include <vector>
#include <cmath>
#include <iostream>

class Electronics{
public:
  Electronics();
  ~Electronics();
  
  inline void SetTimeConstant(double t){m_tRC=t;}
  inline void SetSamplingTime(double t){m_tSample=t;}
  inline void SetfCtomV(double fc)     {m_fCtomV=fc;}
  
  int ProcessPulse(std::vector<double>& currentIn, 
		   std::vector<double>& current_time_In, 
		   std::vector<double>& pulseOut, 
		   std::vector<double>& pulse_time_Out);
  
private:
  double m_tRC;
  double m_tSample;
  double m_fCtomV;
};

#endif //ELECTRONICS_H
