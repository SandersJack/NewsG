#include "PulseAnalysis.hh"

#include "TH1D.h"
#include "TH1F.h"

PulseAnalysis::PulseAnalysis()
    : m_tSample(0.96),
      m_amplitude(0),
      m_risetime(0),
      m_pulseWidth(0),
      m_pulseIntegral(0),
      m_currentIntegral(0) {}

PulseAnalysis::~PulseAnalysis() {}

double PulseAnalysis::GetTimePoint(TH1F* hist, double y, bool first) {
  int bin = first ? hist->FindFirstBinAbove(y) : hist->FindLastBinAbove(y) + 1;
  double x1 = hist->GetBinCenter(bin);       // x1
  double x0 = hist->GetBinCenter(bin - 1);   // x0
  double y1 = hist->GetBinContent(bin);      // y1
  double y0 = hist->GetBinContent(bin - 1);  // y0
  return x0 + (y - y0) * (x1 - x0) / (y1 - y0);
}

int PulseAnalysis::AnalysePulse(std::vector<double>& current,
                                std::vector<double>& current_time,
                                std::vector<double>& pulse,
                                std::vector<double>& pulse_time) {
  m_pulseIntegral = 0;
  m_currentIntegral = 0;

  TH1F* h_current = new TH1F("h_current", "", current.size(), current_time.at(0),
                             current_time.back());

  TH1F* h_current_cumulative = new TH1F("h_current_cumulative", "",
					current.size(), current_time.at(0),
					current_time.back());
  // Calculate signal integral
  for (unsigned int i = 0; i < current.size(); i++) {
    m_currentIntegral += current.at(i);
    h_current->SetBinContent(i, std::abs(current.at(i)));
    h_current_cumulative->SetBinContent(i, std::abs(m_currentIntegral));
  }

  m_currentIntegral *= -1;
  // Calculate pulse integral

  int max_bin = h_current->GetMaximumBin();
  m_current_peak_time = current_time.at(max_bin);

  double max_peak_dip = 0;

  TH1F* h =
      new TH1F("h", "", pulse.size(), 0, pulse_time.size() * m_tSample);  // C
  for (unsigned int i = 0; i < pulse.size(); i++) {
    m_pulseIntegral += pulse.at(i);
    h->SetBinContent(i + 1, std::abs(pulse.at(i)));
    if (std::abs(pulse.at(i)) > std::abs(max_peak_dip)) {
      max_peak_dip = pulse.at(i);
    }
  }

  // Calculate pulse amplitude
  m_amplitude = max_peak_dip;

  // Calculate pulse risetime
  double risetime1 = GetTimePoint(h, std::abs(m_amplitude) * 0.10);
  double risetime2 = GetTimePoint(h, std::abs(m_amplitude) * 0.90);
  m_risetime = risetime2 - risetime1;


  double cc_rt1 = GetTimePoint(h_current_cumulative, std::abs(m_currentIntegral) * 0.10);
  double cc_rt2 = GetTimePoint(h_current_cumulative, std::abs(m_currentIntegral) * 0.90);
  m_cumulative_current_risetime = cc_rt2 - cc_rt1;


  // Calculate pulse width
  double t1 = GetTimePoint(h, std::abs(m_amplitude) * 0.50);
  double t2 = GetTimePoint(h, std::abs(m_amplitude) * 0.50, false);
  m_pulseWidth = t2 - t1;

  // Current threshold to max
  double CURRENT_THRESHOLD = 0.1;
  m_current_amplitude = h_current->GetMaximum();
  // Current threshold to threshold
  if (m_current_amplitude > CURRENT_THRESHOLD) {
    double current_t1 = GetTimePoint(h_current, CURRENT_THRESHOLD);
    double current_t2 = GetTimePoint(h_current, std::abs(m_current_amplitude) * 0.999);
    m_rt = (current_t2 - current_t1) / 1000.;

    double current_dt_t2 = GetTimePoint(h_current, CURRENT_THRESHOLD, false);
    m_dt = (current_dt_t2 - current_t1) / 1000.;
  } else {
    m_rt = 0;
    m_dt = 0.;
  }

  delete h;
  delete h_current;
  delete h_current_cumulative;
  return 0;
}
