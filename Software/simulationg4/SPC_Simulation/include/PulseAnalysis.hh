#ifndef PULSEANALYSIS_H
#define PULSEANALYSIS_H

#include <vector>

class TH1F;

class PulseAnalysis {
 public:
  PulseAnalysis();
  ~PulseAnalysis();

  inline void SetSamplingTime(double tSample) { m_tSample = tSample; }

  inline double samplingTime() { return m_tSample; }
  inline double amplitude() { return m_amplitude; }
  inline double risetime() { return m_risetime; }
  inline double pulseWidth() { return m_pulseWidth; }
  inline double pulseIntegral() { return m_pulseIntegral; }
  inline double currentIntegral() { return m_currentIntegral; }
  inline double currentIntegratedRisetime() { return m_cumulative_current_risetime; }
  inline double currentAmplitude() { return m_current_amplitude; }
  inline double Rt() { return m_rt; }
  inline double Dt() { return m_dt; }
  inline double currentPeakingTime() { return m_current_peak_time; }

  int AnalysePulse(std::vector<double>& current,
                   std::vector<double>& current_time,
                   std::vector<double>& pulse, std::vector<double>& pulse_time);

 private:
  double GetTimePoint(TH1F* hist, double y, bool first = true);

  double m_tSample;
  double m_amplitude;
  double m_risetime;
  double m_pulseWidth;
  double m_pulseIntegral;
  double m_currentIntegral;
  double m_current_amplitude = 0;
  double m_cumulative_current_risetime = 0.0;
  double m_rt = 0.;
  double m_dt = 0.;
  double m_current_peak_time;
};

#endif  // PULSEANALYSIS_H
