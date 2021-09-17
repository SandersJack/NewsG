#include <algorithm>
#include <cmath>
#include <iostream>

#include "TVirtualFFT.h"  // ROOT include

#include "Electronics.hh"

Electronics::Electronics(double tRC, double tSample, double fCtomV)
    : m_tRC(tRC),
      m_tSample(tSample),
      m_fCtomV(fCtomV)
/*
    : m_tRC(140),       // us
      m_tSample(0.96),  // us
      m_fCtomV(1.4)     // fC to mV
*/
{}

Electronics::~Electronics() {}

int Electronics::ProcessPulse(std::vector<double> &currentIn,
                              std::vector<double> &current_time_In,
                              std::vector<double> &pulseOut,
                              std::vector<double> &pulse_time_Out) {
  // current_time_in is in ns
  // Electronics in microseco
  std::cout << "[Electronics] I am here " << std::endl;
  double t0 = current_time_In[0] / 1.e3;
  double currentBinSize = (current_time_In[1] - current_time_In[0]) / 1.e3;
  std::cout << "[Electronics] Current Bin Size: " << currentBinSize << " us"
            << std::endl;
  double dt =
      (current_time_In[current_time_In.size() - 1] - current_time_In[0]) / 1.e3;
  if (dt < 10 * m_tRC) {
    dt = 10. * m_tRC;
  }
  unsigned int nbins = (int)(dt / m_tSample);

  double im_tRC = 1. / m_tRC;
  for (unsigned int i = 0; i < nbins; ++i) {
    pulse_time_Out.push_back(t0 + i * m_tSample);
    pulseOut.push_back(0.);
  }

  unsigned int currentInSize = currentIn.size();
  unsigned int pulseOutSize = pulseOut.size();

  std::cout << "New event" << std::endl;
  for (unsigned int i = 0; i < currentInSize; ++i) {
    // if(fabs(currentIn[i])<1e-9)
    // continue;
    double currentInTmp = currentIn[i];
    if (std::abs(currentInTmp) < 1e-7) continue;

    if (fabs(currentInTmp) < 0.) {
      std::cout << "[Electronics] input " << i << " " << currentInTmp
                << std::endl;
    }

    double current_time = current_time_In[i] * 1.e-3;  // us
    // convert from charge to mV
    double pulseSize = currentInTmp * currentBinSize * m_fCtomV;

    for (unsigned int j = 0; j < pulseOutSize; ++j) {
      double pulse_time_OutTmp = pulse_time_Out[j];
      if (current_time > pulse_time_OutTmp) continue;

      pulseOut[j] +=
          pulseSize * exp((current_time - pulse_time_OutTmp) * im_tRC);
    }
  }
  return 0;
}

int Electronics::ProcessPulseFFT(std::vector<double> &currentIn,
                                 std::vector<double> &current_time_In,
                                 std::vector<double> &pulseOut,
                                 std::vector<double> &pulse_time_Out) {

  // Right, it turns out an FFT can give a wrap around effect. To avoid this, we
  // pad the current with zeroes beyond the edge of the window. Do it by a
  // factor of 2 which is almost certainly overkill but we can revisit this in
  // the future
  int N = static_cast<int>(currentIn.size());
  static bool loaded_exp_fft = false;
  int two_N = 2*N;

  // The first time that we call this function we setup the exponential FFT This
  // is just done once and the results (Re and Im components) are stored in
  // these two vectors. This could go in an initialisation step... 
  
  // NOTE: Below we stop filling the exponential after N steps (the size of the
  // current). Really we could keep going to 2*N here
  static std::vector<double> exp_re(two_N, 0), exp_im(two_N, 0);
  if (!loaded_exp_fft) {
    std::vector<double> exp_points(two_N, 0);
    double current_t0 = current_time_In.at(0);
    const double im_tRC = (1. / m_tRC) * 1e-3;
    for (int i = 0; i < N; ++i) {
      exp_points[i] =
          0.1 * std::exp(-1 * (current_time_In.at(i) - current_t0) * im_tRC);
    }
    TVirtualFFT *exp_fft = TVirtualFFT::FFT(1, &two_N, "R2C");
    exp_fft->SetPoints(&exp_points[0]);
    exp_fft->Transform();
    double re, im;
    for (unsigned int i = 0; i < static_cast<unsigned int>(N); ++i) {
      exp_fft->GetPointComplex(i, re, im);
      exp_re[i] = re;
      exp_im[i] = im;
    }
    loaded_exp_fft = true;
  }

  // We then do an FFT of the input current
  
  TVirtualFFT *fft = TVirtualFFT::FFT(1, &two_N, "R2C");
  std::vector<double> fft_current(currentIn);
  fft_current.resize(two_N, 0);
  fft->SetPoints(&fft_current[0]);
  fft->Transform();

  // We get each point from the current FFT and multiply
  // it by the expoential FFT
  double re, im;
  std::vector<double> fft_re(two_N), fft_im(two_N);
  for (int i = 0; i < two_N; ++i) {
    fft->GetPointComplex(i, re, im);
    fft_re[i] = (re * exp_re[i]) - (im * exp_im[i]);
    fft_im[i] = (re * exp_im[i]) + (im * exp_re[i]);
  }

  // Now setup the inverse transform to go back to t
  
  TVirtualFFT *ifft = TVirtualFFT::FFT(1, &two_N, "C2R");
  ifft->SetPointsComplex(&fft_re[0], &fft_im[0]);
  ifft->Transform();

  pulseOut.clear();
  pulse_time_Out.clear();
  // ROOT introduces a normalisation constant (don't know why)
  // So we need to multiply our answer by 1 / N
  const double norm_constant = 1.0 / two_N;
  // Take every 10 measurements rather than all of them
  // Pulse time has different units to signal time
  int take_every = 10;
  for (int i = 0; i < N; i = i + take_every) {
    double real = ifft->GetPointReal(i);
    pulseOut.push_back(real * norm_constant * m_fCtomV);
    pulse_time_Out.push_back(current_time_In[i] * 1e-3);
  }

  return 0;
}
