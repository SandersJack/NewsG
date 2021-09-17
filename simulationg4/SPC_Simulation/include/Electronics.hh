#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include <vector>

class Electronics {
 public:
  Electronics(double tRC, double tSample, double fCtomV);
  ~Electronics();

  /*
  inline void SetTimeConstant(double t) { m_tRC = t; }
  inline void SetSamplingTime(double t) { m_tSample = t; }
  inline void SetfCtomV(double fc) { m_fCtomV = fc; }
  */

  int ProcessPulse(std::vector<double>& currentIn,
                   std::vector<double>& current_time_In,
                   std::vector<double>& pulseOut,
                   std::vector<double>& pulse_time_Out);

  int ProcessPulseFFT(std::vector<double>& currentIn,
                      std::vector<double>& current_time_In,
                      std::vector<double>& pulseOut,
                      std::vector<double>& pulse_time_Out);

 private:
  const double m_tRC;
  const double m_tSample;
  const double m_fCtomV;
};

#endif  // ELECTRONICS_H
