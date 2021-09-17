#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

#include "Garfield/FundamentalConstants.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Random.hh"
#include "Garfield/Numerics.hh"
#include "Garfield/Sensor.hh"

namespace {

double Interpolate(const std::vector<double>& y,
                   const std::vector<double>& x,
                   const double xx, const unsigned int order) {

  if (xx < x.front() || xx > x.back()) return 0.;
  if (order > 1) {
    return Garfield::Numerics::Divdif(y, x, x.size(), xx, order);
  }
  const auto it1 = std::upper_bound(x.cbegin(), x.cend(), xx);
  if (it1 == x.cend()) return y.back();
  const auto it0 = std::prev(it1);
  const double dx = (*it1 - *it0);
  if (dx < Garfield::Small) return y[it0 - x.cbegin()];
  const double f = (xx - *it0) / dx;
  return y[it0 - x.cbegin()] * (1. - f) + f * y[it1 - x.cbegin()];
}

double Trapezoid2(const std::vector<std::pair<double, double> >& f) {

  const unsigned int n = f.size();
  if (n < 2) return -1.;
  double sum = 0.;
  const double x0 = f[0].first;
  const double y0 = f[0].second;
  const double x1 = f[1].first;
  const double y1 = f[1].second;
  if (n == 2) {
    sum = (x1 - x0) * (y0 * y0 + y1 * y1);
  } else if (n == 3) {
    const double x2 = f[2].first;
    const double y2 = f[2].second;
    sum = (x1 - x0) * y0 * y0 + (x2 - x0) * y1 * y1 + (x2 - x1) * y2 * y2;
  } else {
    sum = (x1 - x0) * y0 * y0 + (f[2].first - x0) * y1 * y1;
    const double xm = f[n - 2].first;
    const double ym = f[n - 2].second;
    const double xn = f[n - 1].first;
    const double yn = f[n - 1].second;
    sum += (xn - f[n - 3].first) * ym * ym + (xn - xm) * yn * yn; 
    if (n > 4) {
      for (unsigned int k = 2; k < n - 2; ++k) {
        const double y = f[k].second;
        sum += (f[k + 1].first - f[k - 1].first) * y * y;
      }
    }
  }
  return 0.5 * sum;
}

}

namespace Garfield {

void Sensor::ElectricField(const double x, const double y, const double z,
                           double& ex, double& ey, double& ez, double& v,
                           Medium*& medium, int& status) {
  ex = ey = ez = v = 0.;
  status = -10;
  medium = nullptr;
  double fx = 0., fy = 0., fz = 0., p = 0.;
  Medium* med = nullptr;
  int stat = 0;
  // Add up electric field contributions from all components.
  for (const auto& cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    std::get<0>(cmp)->ElectricField(x, y, z, fx, fy, fz, p, med, stat);
    if (status != 0) {
      status = stat;
      medium = med;
    }
    if (stat == 0) {
      ex += fx;
      ey += fy;
      ez += fz;
      v += p;
    }
  }
}

void Sensor::ElectricField(const double x, const double y, const double z,
                           double& ex, double& ey, double& ez, Medium*& medium,
                           int& status) {
  ex = ey = ez = 0.;
  status = -10;
  medium = nullptr;
  double fx = 0., fy = 0., fz = 0.;
  Medium* med = nullptr;
  int stat = 0;
  // Add up electric field contributions from all components.
  for (const auto& cmp : m_components) {
    if (!std::get<1>(cmp)) continue; 
    std::get<0>(cmp)->ElectricField(x, y, z, fx, fy, fz, med, stat);
    if (status != 0) {
      status = stat;
      medium = med;
    }
    if (stat == 0) {
      ex += fx;
      ey += fy;
      ez += fz;
    }
  }
}

void Sensor::MagneticField(const double x, const double y, const double z,
                           double& bx, double& by, double& bz, int& status) {
  bx = by = bz = 0.;
  double fx = 0., fy = 0., fz = 0.;
  // Add up contributions.
  for (const auto& cmp : m_components) {
    if (!std::get<2>(cmp)) continue;
    std::get<0>(cmp)->MagneticField(x, y, z, fx, fy, fz, status);
    if (status != 0) continue;
    bx += fx;
    by += fy;
    bz += fz;
  }
}

void Sensor::WeightingField(const double x, const double y, const double z,
                            double& wx, double& wy, double& wz,
                            const std::string& label) {
  wx = wy = wz = 0.;
  // Add up field contributions from all components.
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) {
      double fx = 0., fy = 0., fz = 0.;
      electrode.comp->WeightingField(x, y, z, fx, fy, fz, label);
      wx += fx;
      wy += fy;
      wz += fz;
    }
  }
}

double Sensor::WeightingPotential(const double x, const double y,
                                  const double z, const std::string& label) {
  double v = 0.;
  // Add up contributions from all components.
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) {
      v += electrode.comp->WeightingPotential(x, y, z, label);
    }
  }
  return v;
}

bool Sensor::GetMedium(const double x, const double y, const double z,
                       Medium*& m) {
  m = nullptr;

  // Make sure there is at least one component.
  if (m_components.empty()) return false;

  // Check if we are still in the same component as in the previous call.
  if (m_lastComponent) {
    m = m_lastComponent->GetMedium(x, y, z);
    if (m) return true;
  }

  for (const auto& cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    m = std::get<0>(cmp)->GetMedium(x, y, z);
    if (m) {
      m_lastComponent = std::get<0>(cmp);
      return true;
    }
  }
  return false;
}

bool Sensor::SetArea() {
  if (!GetBoundingBox(m_xMinUser, m_yMinUser, m_zMinUser, m_xMaxUser,
                      m_yMaxUser, m_zMaxUser)) {
    std::cerr << m_className << "::SetArea: Bounding box is not known.\n";
    return false;
  }

  std::cout << m_className << "::SetArea:\n"
            << "    " << m_xMinUser << " < x [cm] < " << m_xMaxUser << "\n"
            << "    " << m_yMinUser << " < y [cm] < " << m_yMaxUser << "\n"
            << "    " << m_zMinUser << " < z [cm] < " << m_zMaxUser << "\n";
  if (std::isinf(m_xMinUser) || std::isinf(m_xMaxUser)) {
    std::cerr << m_className << "::SetArea: Warning. Infinite x-range.\n";
  }
  if (std::isinf(m_yMinUser) || std::isinf(m_yMaxUser)) {
    std::cerr << m_className << "::SetArea: Warning. Infinite y-range.\n";
  }
  if (std::isinf(m_zMinUser) || std::isinf(m_zMaxUser)) {
    std::cerr << m_className << "::SetArea: Warning. Infinite z-range.\n";
  }
  m_hasUserArea = true;
  return true;
}

bool Sensor::SetArea(const double xmin, const double ymin, const double zmin,
                     const double xmax, const double ymax, const double zmax) {
  if (fabs(xmax - xmin) < Small || fabs(ymax - ymin) < Small ||
      fabs(zmax - zmin) < Small) {
    std::cerr << m_className << "::SetArea: Invalid range.\n";
    return false;
  }

  m_xMinUser = std::min(xmin, xmax);
  m_yMinUser = std::min(ymin, ymax);
  m_zMinUser = std::min(zmin, zmax);
  m_xMaxUser = std::max(xmax, xmin);
  m_yMaxUser = std::max(ymax, ymin);
  m_zMaxUser = std::max(zmax, zmin);

  m_hasUserArea = true;
  return true;
}

bool Sensor::GetArea(double& xmin, double& ymin, double& zmin, double& xmax,
                     double& ymax, double& zmax) {
  if (m_hasUserArea) {
    xmin = m_xMinUser;
    ymin = m_yMinUser;
    zmin = m_zMinUser;
    xmax = m_xMaxUser;
    ymax = m_yMaxUser;
    zmax = m_zMaxUser;
    return true;
  }

  // User area bounds are not (yet) defined.
  // Get the bounding box of the sensor.
  if (!SetArea()) return false;

  xmin = m_xMinUser;
  ymin = m_yMinUser;
  zmin = m_zMinUser;
  xmax = m_xMaxUser;
  ymax = m_yMaxUser;
  zmax = m_zMaxUser;

  return true;
}

bool Sensor::IsInArea(const double x, const double y, const double z) {
  if (!m_hasUserArea) {
    if (!SetArea()) {
      std::cerr << m_className << "::IsInArea: User area could not be set.\n";
      return false;
    }
    m_hasUserArea = true;
  }

  if (x >= m_xMinUser && x <= m_xMaxUser && y >= m_yMinUser &&
      y <= m_yMaxUser && z >= m_zMinUser && z <= m_zMaxUser) {
    return true;
  }

  if (m_debug) {
    std::cout << m_className << "::IsInArea: (" << x << ", " << y << ", " << z
              << ") "
              << " is outside.\n";
  }
  return false;
}

bool Sensor::IsWireCrossed(const double x0, const double y0, const double z0,
                           const double x1, const double y1, const double z1,
                           double& xc, double& yc, double& zc, 
                           const bool centre, double& rc) {
  for (const auto& cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    if (std::get<0>(cmp)->IsWireCrossed(x0, y0, z0, x1, y1, z1, 
                                        xc, yc, zc, centre, rc)) {
      return true;
    }
  }
  return false;
}

bool Sensor::IsInTrapRadius(const double q0, const double x0, const double y0,
                            double z0, double& xw, double& yw, double& rw) {
  for (const auto& cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    if (std::get<0>(cmp)->IsInTrapRadius(q0, x0, y0, z0, xw, yw, rw)) {
      return true;
    }
  }
  return false;
}

double Sensor::IntegrateFluxLine(
    const double x0, const double y0, const double z0,
    const double x1, const double y1, const double z1,
    const double xp, const double yp, const double zp,
    const unsigned int nI, const int isign) {

  double q = 0.;
  for (const auto& cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    q += std::get<0>(cmp)->IntegrateFluxLine(x0, y0, z0, x1, y1, z1,
                                             xp, yp, zp, nI, isign);
  }
  return q;
}

void Sensor::AddComponent(Component* cmp) {
  if (!cmp) {
    std::cerr << m_className << "::AddComponent: Null pointer.\n";
    return;
  }

  m_components.push_back(std::make_tuple(cmp, true, true));
}

Component* Sensor::GetComponent(const unsigned int i) {
  if (i >= m_components.size()) {
    std::cerr << m_className << "::GetComponent: Index out of range.\n";
    return nullptr;
  };
  return std::get<0>(m_components[i]);
}

void Sensor::EnableComponent(const unsigned int i, const bool on) {
  if (i >= m_components.size()) {
    std::cerr << m_className << "::EnableComponent: Index out of range.\n";
    return;
  };
  std::get<1>(m_components[i]) = on;
}

void Sensor::EnableMagneticField(const unsigned int i, const bool on) {
  if (i >= m_components.size()) {
    std::cerr << m_className << "::EnableMagneticField: Index out of range.\n";
    return;
  };
  std::get<2>(m_components[i]) = on;
}

void Sensor::AddElectrode(Component* cmp, const std::string& label) {
  if (!cmp) {
    std::cerr << m_className << "::AddElectrode: Null pointer.\n";
    return;
  }
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) {
      std::cout << m_className << "::AddElectrode:\n"
                << "    Warning: An electrode with label \"" << label
                << "\" exists already. Weighting fields will be summed up.\n";
      break;
    }
  }

  Electrode electrode;
  electrode.comp = cmp;
  electrode.label = label;
  electrode.signal.assign(m_nTimeBins, 0.);
  electrode.electronsignal.assign(m_nTimeBins, 0.);
  electrode.ionsignal.assign(m_nTimeBins, 0.);
  electrode.delayedElectronSignal.assign(m_nTimeBins, 0.);
  electrode.delayedIonSignal.assign(m_nTimeBins, 0.);
  m_electrodes.push_back(std::move(electrode));
  std::cout << m_className << "::AddElectrode:\n"
            << "    Added readout electrode \"" << label << "\".\n"
            << "    All signals are reset.\n";
  ClearSignal();
}

void Sensor::Clear() {
  m_components.clear();
  m_lastComponent = nullptr;
  m_electrodes.clear();
  m_nTimeBins = 200;
  m_tStart = 0.;
  m_tStep = 10.;
  m_nEvents = 0;
  m_hasUserArea = false;
  m_fTransfer = nullptr;
  m_shaper = nullptr;
  m_fTransferTab.clear();
  m_fTransferSq = -1.;
  m_fTransferFFT.clear();
}

bool Sensor::GetVoltageRange(double& vmin, double& vmax) {
  // We don't know the range yet.
  bool set = false;
  // Loop over the components.
  for (const auto& cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    double umin = 0., umax = 0.;
    if (!std::get<0>(cmp)->GetVoltageRange(umin, umax)) continue;
    if (set) {
      vmin = std::min(umin, vmin);
      vmax = std::max(umax, vmax);
    } else {
      vmin = umin;
      vmax = umax;
      set = true;
    }
  }

  // Warn if we still don't know the range.
  if (!set) {
    std::cerr << m_className << "::GetVoltageRange:\n"
              << "    Sensor voltage range not known.\n";
    vmin = vmax = 0.;
    return false;
  }

  if (m_debug) {
    std::cout << m_className << "::GetVoltageRange: " << vmin << " < V < "
              << vmax << ".\n";
  }
  return true;
}

void Sensor::ClearSignal() {
  for (auto& electrode : m_electrodes) {
    electrode.charge = 0.;
    electrode.signal.assign(m_nTimeBins, 0.);
    electrode.electronsignal.assign(m_nTimeBins, 0.);
    electrode.ionsignal.assign(m_nTimeBins, 0.);
    electrode.delayedElectronSignal.assign(m_nTimeBins, 0.);
    electrode.delayedIonSignal.assign(m_nTimeBins, 0.);
    electrode.integrated = false;
  }
  m_nEvents = 0;
}

void Sensor::SetDelayedSignalTimes(const std::vector<double>& ts) {
  if (!std::is_sorted(ts.begin(), ts.end())) {
    std::cerr << m_className << "::SetDelayedSignalTimes:\n"
              << "    Times are not in ascending order.\n";
    return;
  }
  m_delayedSignalTimes = ts;
}

void Sensor::AddSignal(const double q, const double t0, const double t1,
                       const double x0, const double y0, const double z0,
                       const double x1, const double y1, const double z1,
                       const bool integrateWeightingField,
                       const bool useWeightingPotential) {
  if (m_debug) std::cout << m_className << "::AddSignal: ";
  // Get the time bin.
  if (t0 < m_tStart) {
    if (m_debug) std::cout << "Time " << t0 << " out of range.\n";
    return;
  } 
  const double dt = t1 - t0;
  if (dt < Small) {
    if (m_debug) std::cout << "Time step too small.\n";
    return;
  }
  const int bin = int((t0 - m_tStart) / m_tStep);
  // Check if the starting time is outside the range
  if (bin < 0 || bin >= (int)m_nTimeBins) {
    if (m_debug) std::cout << "Bin " << bin << " out of range.\n";
    return;
  }
  if (m_nEvents <= 0) m_nEvents = 1;

  const bool electron = q < 0;
  const double dx = x1 - x0;
  const double dy = y1 - y0;
  const double dz = z1 - z0;
  const double vx = dx / dt;
  const double vy = dy / dt;
  const double vz = dz / dt;
  if (m_debug) {
    std::cout << "  Time: " << t0 << "\n"
              << "  Step: " << dt << "\n"
              << "  Charge: " << q << "\n"
              << "  Velocity: (" << vx << ", " << vy << ", " << vz << ")\n";
  }

  // Locations and weights for 6-point Gaussian integration
  constexpr double tg[6] = {-0.932469514203152028, -0.661209386466264514,
                            -0.238619186083196909, 0.238619186083196909,
                            0.661209386466264514,  0.932469514203152028};
  constexpr double wg[6] = {0.171324492379170345, 0.360761573048138608,
                            0.467913934572691047, 0.467913934572691047,
                            0.360761573048138608, 0.171324492379170345};
  for (auto& electrode : m_electrodes) {
    const std::string lbl = electrode.label;
    if (m_debug) std::cout << "  Electrode " << electrode.label << ":\n";
    // Induced current.
    double current = 0.;
    if (useWeightingPotential) {
      const double w0 = electrode.comp->WeightingPotential(x0, y0, z0, lbl);
      const double w1 = electrode.comp->WeightingPotential(x1, y1, z1, lbl);
      current = q * (w1 - w0) / dt; 
    } else {
      double wx = 0., wy = 0., wz = 0.;
      // Calculate the weighting field for this electrode.
      if (integrateWeightingField) {
        for (unsigned int j = 0; j < 6; ++j) {
          const double s = 0.5 * (1. + tg[j]);
          const double x = x0 + s * dx;
          const double y = y0 + s * dy;
          const double z = z0 + s * dz;
          double fx = 0., fy = 0., fz = 0.; 
          electrode.comp->WeightingField(x, y, z, fx, fy, fz, lbl);
          wx += wg[j] * fx;
          wy += wg[j] * fy;
          wz += wg[j] * fz;
        }
        wx *= 0.5;
        wy *= 0.5;
        wz *= 0.5;
      } else {
        const double x = x0 + 0.5 * dx;
        const double y = y0 + 0.5 * dy;
        const double z = z0 + 0.5 * dz;
        electrode.comp->WeightingField(x, y, z, wx, wy, wz, lbl);
      }
      if (m_debug) {
        std::cout << "    Weighting field: (" << wx << ", " << wy << ", " 
                  << wz << ")\n";
      }
      // Calculate the induced current.
      current = -q * (wx * vx + wy * vy + wz * vz);

    }
    if (m_debug) std::cout << "    Induced charge: " << current * dt << "\n";
    double delta = m_tStart + (bin + 1) * m_tStep - t0;
    // Check if the provided timestep extends over more than one time bin
    if (dt > delta) {
      FillBin(electrode, bin, current * delta, electron, false);
      delta = dt - delta;
      unsigned int j = 1;
      while (delta > m_tStep && bin + j < m_nTimeBins) {
        FillBin(electrode, bin + j, current * m_tStep, electron, false);
        delta -= m_tStep;
        ++j;
      }
      if (bin + j < m_nTimeBins) {
        FillBin(electrode, bin + j, current * delta, electron, false);
      }
    } else {
      FillBin(electrode, bin, current * dt, electron, false);
    }
  }
  if (!m_delayedSignal) return;
  if (m_delayedSignalTimes.empty()) return;
  const unsigned int nd = m_delayedSignalTimes.size();
  // Establish the points in time at which we evaluate the delayed signal.
  std::vector<double> td(nd); 
  for (unsigned int i = 0; i < nd; ++i) {
    td[i] = t0 + m_delayedSignalTimes[i];
  }
  // Calculate the signals for each electrode.
  for (auto& electrode : m_electrodes) {
    const std::string lbl = electrode.label;
    std::vector<double> id(nd, 0.);
    for (unsigned int i = 0; i < nd; ++i) {
      // Integrate over the drift line segment.
      const double step = std::min(m_delayedSignalTimes[i], dt);
      const double scale = step / dt;
      double sum = 0.;
      for (unsigned int j = 0; j < 6; ++j) {
        double s = 0.5 * (1. + tg[j]);
        const double t = m_delayedSignalTimes[i] - s * step;
        s *= scale; 
        const double x = x0 + s * dx;
        const double y = y0 + s * dy;
        const double z = z0 + s * dz;
        // Calculate the delayed weighting field.
        double wx = 0., wy = 0., wz = 0.;
        electrode.comp->DelayedWeightingField(x, y, z, t, wx, wy, wz, lbl);
        sum += (wx * vx + wy * vy + wz * vz) * wg[j];
      }
      id[i] = -q * 0.5 * sum * step;
    }
    FillSignal(electrode, q, td, id, m_nAvgDelayedSignal, true);
  }

}

void Sensor::AddSignal(const double q, const std::vector<double>& ts,
                       const std::vector<std::array<double, 3> >& xs,
                       const std::vector<std::array<double, 3> >& vs,
                       const std::vector<double>& ns, const int navg) {

  // Don't do anything if there are no points on the signal.
  if (ts.size() < 2) return;
  if (ts.size() != xs.size() || ts.size() != vs.size()) {
    std::cerr << m_className << "::AddSignal: Mismatch in vector size.\n";
    return;
  } 
  const bool aval = ns.size() == ts.size();
  const unsigned int nPoints = ts.size();
  if (m_debug) {
    std::cout << m_className << "::AddSignal: Adding a " << nPoints 
              << "-vector (charge " << q << ").\n";
  }

  if (m_nEvents <= 0) m_nEvents = 1;
  for (auto& electrode : m_electrodes) {
    const std::string label = electrode.label;
    std::vector<double> signal(nPoints, 0.);
    for (unsigned int i = 0; i < nPoints; ++i) {
      // Calculate the weighting field at this point.
      const auto& x = xs[i];
      double wx = 0., wy = 0., wz = 0.;
      electrode.comp->WeightingField(x[0], x[1], x[2], wx, wy, wz, label);
      // Calculate the induced current at this point.
      const auto& v = vs[i];
      signal[i] = -q * (v[0] * wx + v[1] * wy + v[2] * wz);
      if (aval) signal[i] *= ns[i];
    }
    FillSignal(electrode, q, ts, signal, navg);
  }

  if (!m_delayedSignal) return;
  if (m_delayedSignalTimes.empty()) return;
  // Locations and weights for 6-point Gaussian integration
  constexpr double tg[6] = {-0.932469514203152028, -0.661209386466264514,
                            -0.238619186083196909, 0.238619186083196909,
                            0.661209386466264514,  0.932469514203152028};
  constexpr double wg[6] = {0.171324492379170345, 0.360761573048138608,
                            0.467913934572691047, 0.467913934572691047,
                            0.360761573048138608, 0.171324492379170345};
  const unsigned int nd = m_delayedSignalTimes.size();
  for (unsigned int k = 0; k < nPoints - 1; ++k) {
    const double t0 = ts[k];
    const double t1 = ts[k + 1];
    const double dt = t1 - t0;
    if (dt < Small) continue; 
    const auto& x0 = xs[k];
    const auto& x1 = xs[k + 1];
    const auto& v = vs[k];
    std::vector<double> td(nd); 
    for (unsigned int i = 0; i < nd; ++i) {
      td[i] = t0 + m_delayedSignalTimes[i];
    }
    // Calculate the signals for each electrode.
    for (auto& electrode : m_electrodes) {
      const std::string lbl = electrode.label;
      std::vector<double> id(nd, 0.);
      for (unsigned int i = 0; i < nd; ++i) {
        // Integrate over the drift line segment.
        const double step = std::min(m_delayedSignalTimes[i], dt);
        const double scale = step / dt;
        const double dx = scale * (x1[0] - x0[0]);
        const double dy = scale * (x1[1] - x0[1]);
        const double dz = scale * (x1[2] - x0[2]);
        double sum = 0.;
        for (unsigned int j = 0; j < 6; ++j) {
          const double f = 0.5 * (1. + tg[j]);
          const double t = m_delayedSignalTimes[i] - f * step;
          // Calculate the delayed weighting field.
          double wx = 0., wy = 0., wz = 0.;
          electrode.comp->DelayedWeightingField(x0[0] + f * dx, 
                                                x0[1] + f * dy, 
                                                x0[2] + f * dz, 
                                                t, wx, wy, wz, lbl);
          sum += (wx * v[0] + wy * v[1] + wz * v[2]) * wg[j];
        }
        id[i] = -q * 0.5 * sum * step;
      }
      FillSignal(electrode, q, td, id, m_nAvgDelayedSignal, true);
    }
  }

}

void Sensor::FillSignal(Electrode& electrode, const double q, 
                        const std::vector<double>& ts,
                        const std::vector<double>& is, const int navg,
                        const bool delayed) {

  const bool electron = q < 0.;
  // Interpolation order.
  constexpr unsigned int k = 1;
  for (unsigned int i = 0; i < m_nTimeBins; ++i) {
    const double t0 = m_tStart + i * m_tStep; 
    const double t1 = t0 + m_tStep;
    if (ts.front() > t1) continue;
    if (ts.back() < t0) break;
    // Integration over this bin.
    const double tmin = std::max(ts.front(), t0);
    const double tmax = std::min(ts.back(), t1);
    double sum = 0.;
    if (navg <= 0) {
      sum += (tmax - tmin) * Interpolate(is, ts, 0.5 * (tmin + tmax), k);
    } else {
      const double h = 0.5 * (tmax - tmin) / navg;
      for (int j = -navg; j <= navg; ++j) {
        const int jj = j + navg;
        const double t = t0 + jj * h;
        if (t < ts.front() || t > ts.back()) continue;
        if (j == -navg || j == navg) {
          sum += Interpolate(is, ts, t, k);
        } else if (jj == 2 * (jj /2)) {
          sum += 2 * Interpolate(is, ts, t, k);
        } else {
          sum += 4 * Interpolate(is, ts, t, k);
        }
      }
      sum *= h / 3.;
    }
    // Add the result to the signal.
    FillBin(electrode, i, sum, electron, delayed);
  }
}

void Sensor::AddInducedCharge(const double q, const double x0, const double y0,
                              const double z0, const double x1, const double y1,
                              const double z1) {
  if (m_debug) std::cout << m_className << "::AddInducedCharge:\n";
  for (auto& electrode : m_electrodes) {
    // Calculate the weighting potential at the starting point.
    auto cmp = electrode.comp;
    const double w0 = cmp->WeightingPotential(x0, y0, z0, electrode.label);
    // Calculate the weighting potential at the end point.
    const double w1 = cmp->WeightingPotential(x1, y1, z1, electrode.label);
    electrode.charge += q * (w1 - w0);
    if (m_debug) {
      std::cout << "  Electrode " << electrode.label << ":\n"
                << "    Weighting potential at (" << x0 << ", " << y0 << ", "
                << z0 << "): " << w0 << "\n"
                << "    Weighting potential at (" << x1 << ", " << y1 << ", "
                << z1 << "): " << w1 << "\n"
                << "    Induced charge: " << electrode.charge << "\n";
    }
  }
}

void Sensor::SetTimeWindow(const double tstart, const double tstep,
                           const unsigned int nsteps) {
  m_tStart = tstart;
  if (tstep <= 0.) {
    std::cerr << m_className << "::SetTimeWindow: Start time out of range.\n";
  } else {
    m_tStep = tstep;
  }

  if (nsteps == 0) {
    std::cerr << m_className << "::SetTimeWindow: Invalid number of bins.\n";
  } else {
    m_nTimeBins = nsteps;
  }

  if (m_debug) {
    std::cout << m_className << "::SetTimeWindow: " << m_tStart
              << " < t [ns] < " << m_tStart + m_nTimeBins * m_tStep << "\n"
              << "    Step size: " << m_tStep << " ns\n";
  }

  std::cout << m_className << "::SetTimeWindow: Resetting all signals.\n";
  for (auto& electrode : m_electrodes) {
    electrode.signal.assign(m_nTimeBins, 0.);
    electrode.electronsignal.assign(m_nTimeBins, 0.);
    electrode.ionsignal.assign(m_nTimeBins, 0.);
  }
  m_nEvents = 0;
  // Reset the cached FFT of the transfer function 
  // because it depends on the number of time bins.
  m_fTransferFFT.clear();
}

double Sensor::GetElectronSignal(const std::string& label,
                                 const unsigned int bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.electronsignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetIonSignal(const std::string& label, const unsigned int bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.ionsignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetDelayedElectronSignal(const std::string& label,
                                        const unsigned int bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.delayedElectronSignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetDelayedIonSignal(const std::string& label,
                                   const unsigned int bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.delayedIonSignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

void Sensor::SetSignal(const std::string& label, const unsigned int bin,
                       const double signal) {
  if (bin >= m_nTimeBins) return;
  if (m_nEvents == 0) m_nEvents = 1;
  for (auto& electrode : m_electrodes) {
    if (electrode.label == label) {
      electrode.signal[bin] = m_nEvents * m_tStep * signal / ElementaryCharge;
      break;
    }
  }
}

double Sensor::GetSignal(const std::string& label, const unsigned int bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.signal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetInducedCharge(const std::string& label) {
  if (m_nEvents == 0) return 0.;
  double charge = 0.;
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) charge += electrode.charge;
  }

  return charge / m_nEvents;
}

void Sensor::SetTransferFunction(double (*f)(double t)) {
  if (!f) {
    std::cerr << m_className << "::SetTransferFunction: Null pointer.\n";
    return;
  }
  m_fTransfer = f;
  m_shaper = nullptr;
  m_fTransferTab.clear();
  m_fTransferSq = -1.;
  m_fTransferFFT.clear();
}

void Sensor::SetTransferFunction(const std::vector<double>& times,
                                 const std::vector<double>& values) {
  if (times.empty() || values.empty()) {
    std::cerr << m_className << "::SetTransferFunction: Empty vector.\n";
    return;
  } else if (times.size() != values.size()) {
    std::cerr << m_className << "::SetTransferFunction:\n"
              << "    Time and value vectors must have same size.\n";
    return;
  }
  const auto n = times.size();
  m_fTransferTab.clear();
  for (unsigned int i = 0; i < n; ++i) {
    m_fTransferTab.emplace_back(std::make_pair(times[i], values[i]));
  } 
  std::sort(m_fTransferTab.begin(), m_fTransferTab.end());
  m_fTransfer = nullptr;
  m_shaper = nullptr;
  m_fTransferSq = -1.;
  m_fTransferFFT.clear();
}

void Sensor::SetTransferFunction(Shaper &shaper) {
  m_shaper = &shaper;
  m_fTransfer = nullptr;
  m_fTransferTab.clear();
  m_fTransferSq = -1.;
  m_fTransferFFT.clear();
}

double Sensor::InterpolateTransferFunctionTable(const double t) const {
  if (m_fTransferTab.empty()) return 0.;
  // Don't extrapolate beyond the range defined in the table.
  if (t < m_fTransferTab.front().first || t > m_fTransferTab.back().first) {
    return 0.;
  }
  // Find the proper interval in the table.
  const auto begin = m_fTransferTab.cbegin();
  const auto it1 = std::upper_bound(begin, m_fTransferTab.cend(), std::make_pair(t, 0.));
  if (it1 == begin) return m_fTransferTab.front().second;
  const auto it0 = std::prev(it1);
  const double t0 = (*it0).first;
  const double t1 = (*it1).first;
  const double f = t - t0 / (t1 - t0);
  // Linear interpolation.
  return (*it0).second * (1. - f) + (*it1).second * f;
}

double Sensor::GetTransferFunction(const double t) {
  if (m_fTransfer) {
    return m_fTransfer(t);
  } else if (m_shaper) {
    return m_shaper->Shape(t); 
  }
  return InterpolateTransferFunctionTable(t);
}

bool Sensor::ConvoluteSignal(const std::string& label, const bool fft) {
  if (!m_fTransfer && !m_shaper && m_fTransferTab.empty()) {
    std::cerr << m_className << "::ConvoluteSignal: "
              << "Transfer function not set.\n";
    return false;
  }
  if (m_nEvents == 0) {
    std::cerr << m_className << "::ConvoluteSignal: No signals present.\n";
    return false;
  }

  if (fft) return ConvoluteSignalFFT(label);
  std::vector<double> cnvTab;
  MakeTransferFunctionTable(cnvTab);
  // Loop over all electrodes.
  for (auto& electrode : m_electrodes) {
    if (label != electrode.label) continue;
    ConvoluteSignal(electrode, cnvTab);
    return true;
  }
  return false;
}


bool Sensor::ConvoluteSignals(const bool fft) {
  if (!m_fTransfer && !m_shaper && m_fTransferTab.empty()) {
    std::cerr << m_className << "::ConvoluteSignals: "
              << "Transfer function not set.\n";
    return false;
  }
  if (m_nEvents == 0) {
    std::cerr << m_className << "::ConvoluteSignals: No signals present.\n";
    return false;
  }

  if (fft) return ConvoluteSignalFFT();
  std::vector<double> cnvTab;
  MakeTransferFunctionTable(cnvTab);
  // Loop over all electrodes.
  for (auto& electrode : m_electrodes) ConvoluteSignal(electrode, cnvTab);
  return true;
}

void Sensor::MakeTransferFunctionTable(std::vector<double>& cnvTab) {

  // Set the range where the transfer function is valid.
  constexpr double cnvMin = 0.;
  constexpr double cnvMax = 1.e10;

  cnvTab.assign(2 * m_nTimeBins - 1, 0.);
  const unsigned int offset = m_nTimeBins - 1;
  // Evaluate the transfer function.
  for (unsigned int i = 0; i < m_nTimeBins; ++i) {
    // Negative time part.
    double t = (-int(i)) * m_tStep;
    if (t < cnvMin || t > cnvMax) {
      cnvTab[offset - i] = 0.;
    } else {
      cnvTab[offset - i] = GetTransferFunction(t);
    }
    if (i == 0) continue;
    // Positive time part.
    t = i * m_tStep;
    if (t < cnvMin || t > cnvMax) {
      cnvTab[offset + i] = 0.;
    } else {
      cnvTab[offset + i] = GetTransferFunction(t);
    }
  }
}

void Sensor::ConvoluteSignal(Electrode& electrode,
                             const std::vector<double>& tab) {
  // Do the convolution.
  std::vector<double> tmpSignal(m_nTimeBins, 0.);
  const unsigned int offset = m_nTimeBins - 1;
  for (unsigned int j = 0; j < m_nTimeBins; ++j) {
    tmpSignal[j] = 0.;
    for (unsigned int k = 0; k < m_nTimeBins; ++k) {
      tmpSignal[j] += m_tStep * tab[offset + j - k] * electrode.signal[k];
    }
  }
  electrode.signal.swap(tmpSignal);
  electrode.integrated = true;
}

bool Sensor::ConvoluteSignalFFT() {

  // Number of bins must be a power of 2.
  const unsigned int nn = exp2(ceil(log2(m_nTimeBins)));

  if (!m_cacheTransferFunction || m_fTransferFFT.size() != 2 * (nn + 1)) {
    // (Re-)compute the FFT of the transfer function.
    m_fTransferFFT.assign(2 * (nn + 1), 0.);
    for (unsigned int i = 0; i < m_nTimeBins; ++i) {
      m_fTransferFFT[2 * i + 1] = GetTransferFunction(i * m_tStep);
    }
    FFT(m_fTransferFFT, false, nn);
  }

  for (auto& electrode : m_electrodes) {
    ConvoluteSignalFFT(electrode, m_fTransferFFT, nn);
  }
  return true;
}

bool Sensor::ConvoluteSignalFFT(const std::string& label) {

  // Number of bins must be a power of 2.
  const unsigned int nn = exp2(ceil(log2(m_nTimeBins)));

  if (!m_cacheTransferFunction || m_fTransferFFT.size() != 2 * (nn + 1)) {
    // (Re-)compute the FFT of the transfer function.
    m_fTransferFFT.assign(2 * (nn + 1), 0.);
    for (unsigned int i = 0; i < m_nTimeBins; ++i) {
      m_fTransferFFT[2 * i + 1] = GetTransferFunction(i * m_tStep);
    }
    FFT(m_fTransferFFT, false, nn);
  }

  for (auto& electrode : m_electrodes) {
    if (label != electrode.label) continue;
    ConvoluteSignalFFT(electrode, m_fTransferFFT, nn);
    return true;
  }
  return false;
}

void Sensor::ConvoluteSignalFFT(Electrode& electrode,
                                const std::vector<double>& tab,
                                const unsigned int nn) {

  std::vector<double> g(2 * (nn + 1), 0.);
  for (unsigned int i = 0; i < m_nTimeBins; ++i) {
    g[2 * i + 1] = electrode.signal[i];
  }
  FFT(g, false, nn);
  for (unsigned int i = 0; i < nn; ++i) {
    const double fr = tab[2 * i + 1];
    const double fi = tab[2 * i + 2];
    const double gr = g[2 * i + 1];
    const double gi = g[2 * i + 2];
    g[2 * i + 1] = fr * gr - fi * gi;
    g[2 * i + 2] = fr * gi + gr * fi;
  }
  FFT(g, true, nn);
  const double scale = m_tStep / nn;
  for (unsigned int i = 0; i < m_nTimeBins; ++i) {
    electrode.signal[i] = scale * g[2 * i + 1];
  }
  electrode.integrated = true;
}

bool Sensor::IntegrateSignals() {
  if (m_nEvents == 0) {
    std::cerr << m_className << "::IntegrateSignals: No signals present.\n";
    return false;
  }

  for (auto& electrode : m_electrodes) IntegrateSignal(electrode);
  return true;
}

bool Sensor::IntegrateSignal(const std::string& label) {
  if (m_nEvents == 0) {
    std::cerr << m_className << "::IntegrateSignal: No signals present.\n";
    return false;
  }

  for (auto& electrode : m_electrodes) {
    if (label != electrode.label) continue;
    IntegrateSignal(electrode);
    return true; 
  }
  std::cerr << m_className << "::IntegrateSignal: Electrode "
            << label << " not found.\n";
  return false;
}

void Sensor::IntegrateSignal(Electrode& electrode) {

  for (unsigned int j = 0; j < m_nTimeBins; ++j) {
    electrode.signal[j] *= m_tStep;
    electrode.electronsignal[j] *= m_tStep;
    electrode.ionsignal[j] *= m_tStep;
    if (j > 0) {
      electrode.signal[j] += electrode.signal[j - 1];
      electrode.electronsignal[j] += electrode.electronsignal[j - 1];
      electrode.ionsignal[j] += electrode.ionsignal[j - 1];
    }
  }
  electrode.integrated = true;
}

bool Sensor::IsIntegrated(const std::string& label) const {
  
  for (const auto& electrode : m_electrodes) {
    if (electrode.label == label) return electrode.integrated;
  }
  return false;
}

bool Sensor::DelayAndSubtractFraction(const double td, const double f) {

  const int offset = int(td / m_tStep);
  for (auto& electrode : m_electrodes) {
    std::vector<double> signal1(m_nTimeBins, 0.);
    std::vector<double> signal2(m_nTimeBins, 0.);
    for (unsigned int j = 0; j < m_nTimeBins; ++j) {
      signal2[j] = f * electrode.signal[j];
      const int bin = j - offset;
      if (bin < 0 || bin >= (int)m_nTimeBins) continue;
      signal1[j] = electrode.signal[bin];
    }
    for (unsigned int j = 0; j < m_nTimeBins; ++j) {
      electrode.signal[j] = signal1[j] - signal2[j];
    }
  }
  return true;
}

void Sensor::SetNoiseFunction(double (*f)(double t)) {
  if (!f) {
    std::cerr << m_className << "::SetNoiseFunction: Null pointer.\n";
    return;
  }
  m_fNoise = f;
}

void Sensor::AddNoise(const bool total, const bool electron, const bool ion) {
  if (!m_fNoise) {
    std::cerr << m_className << "::AddNoise: Noise function not set.\n";
    return;
  }
  if (m_nEvents == 0) m_nEvents = 1;

  for (auto& electrode : m_electrodes) {
    double t = m_tStart + 0.5 * m_tStep;
    for (unsigned int j = 0; j < m_nTimeBins; ++j) {
      const double noise = m_fNoise(t);
      if (total) electrode.signal[j] += noise;
      if (electron) electrode.electronsignal[j] += noise;
      if (ion) electrode.ionsignal[j] += noise;
      t += m_tStep;
    }
  }
}

void Sensor::AddWhiteNoise(const std::string& label, const double enc, 
                           const bool poisson, const double q0) {

  if (!m_fTransfer && !m_shaper && m_fTransferTab.empty()) {
    std::cerr << m_className << "::AddWhiteNoise: Transfer function not set.\n";
    return;
  }
  if (m_nEvents == 0) m_nEvents = 1;
  
  const double f2 = TransferFunctionSq();
  if (f2 < 0.) {
    std::cerr << m_className << "::AddWhiteNoise:\n"
              << "  Could not calculate transfer function integral.\n";
    return;
  }

  if (poisson) {
    // Frequency of random delta pulses to model noise.
    const double nu = (enc * enc / (q0 * q0)) / f2;
    // Average number of delta pulses.
    const double avg = nu * m_tStep * m_nTimeBins;
    // Sample the number of pulses.
    for (auto& electrode : m_electrodes) {
      if (label != electrode.label) continue;
      const int nPulses = RndmPoisson(avg);
      for (int j = 0; j < nPulses; ++j) {
        const int bin = static_cast<int>(m_nTimeBins * RndmUniform());
        electrode.signal[bin] += q0;
      }
      const double offset = q0 * nu * m_tStep;
      for (unsigned int j = 0; j < m_nTimeBins; ++j) {
        electrode.signal[j] -= offset;
      }
      break;
    }
  } else {
    // Gaussian approximation.
    const double sigma = enc * sqrt(m_tStep / f2);
    for (auto& electrode : m_electrodes) {
      if (label != electrode.label) continue;
      for (unsigned int j = 0; j < m_nTimeBins; ++j) {
        electrode.signal[j] += RndmGaussian(0., sigma);
      }
      break;
    }
  }
}

void Sensor::AddWhiteNoise(const double enc, const bool poisson, 
                           const double q0) {

  if (!m_fTransfer && !m_shaper && m_fTransferTab.empty()) {
    std::cerr << m_className << "::AddWhiteNoise: Transfer function not set.\n";
    return;
  }
  if (m_nEvents == 0) m_nEvents = 1;
  
  const double f2 = TransferFunctionSq();
  if (f2 < 0.) {
    std::cerr << m_className << "::AddWhiteNoise:\n"
              << "  Could not calculate transfer function integral.\n";
    return;
  }

  if (poisson) {
    // Frequency of random delta pulses to model noise.
    const double nu = (enc * enc / (q0 * q0)) / f2;
    // Average number of delta pulses.
    const double avg = nu * m_tStep * m_nTimeBins;
    // Sample the number of pulses.
    for (auto& electrode : m_electrodes) {
      const int nPulses = RndmPoisson(avg);
      for (int j = 0; j < nPulses; ++j) {
        const int bin = static_cast<int>(m_nTimeBins * RndmUniform());
        electrode.signal[bin] += q0;
      }
      const double offset = q0 * nu * m_tStep;
      for (unsigned int j = 0; j < m_nTimeBins; ++j) {
        electrode.signal[j] -= offset;
      }
    }
  } else {
    // Gaussian approximation.
    const double sigma = enc * sqrt(m_tStep / f2);
    for (auto& electrode : m_electrodes) {
      for (unsigned int j = 0; j < m_nTimeBins; ++j) {
        electrode.signal[j] += RndmGaussian(0., sigma);
      }
    }
  }
}

double Sensor::TransferFunctionSq() {

  if (m_fTransferSq >= 0.) return m_fTransferSq;
  double integral = -1.;
  if (m_fTransfer) {
    std::function<double(double)> fsq = [this](double x) {
      const double y = m_fTransfer(x);
      return y * y;
    };
    constexpr double epsrel = 1.e-8;
    double err = 0.;
    unsigned int stat = 0;
    Numerics::QUADPACK::qagi(fsq, 0., 1, 0., epsrel, integral, err, stat);
  } else if (m_shaper) {
    integral = m_shaper->TransferFuncSq();
  } else {
    integral = Trapezoid2(m_fTransferTab);
  }
  if (m_cacheTransferFunction) m_fTransferSq = integral;
  return integral;
}

bool Sensor::ComputeThresholdCrossings(const double thr,
                                       const std::string& label, int& n) {
  // Reset the list of threshold crossings.
  m_thresholdCrossings.clear();
  m_thresholdLevel = thr;

  // Set the interpolation order.
  int iOrder = 1;

  if (m_nEvents == 0) {
    std::cerr << m_className << "::ComputeThresholdCrossings: "
              << "No signals present.\n";
    return false;
  }
  // Compute the total signal.
  std::vector<double> signal(m_nTimeBins, 0.);
  // Loop over the electrodes.
  bool foundLabel = false;
  for (const auto& electrode : m_electrodes) {
    if (electrode.label != label) continue;
    foundLabel = true;
    if (!electrode.integrated) {
      std::cerr << m_className << "::ComputeThresholdCrossings:\n    "
                << "Warning: signal on electrode " << label 
                << " has not been integrated/convoluted.\n";
    }
    for (unsigned int i = 0; i < m_nTimeBins; ++i) {
      signal[i] += electrode.signal[i];
    }
  }
  if (!foundLabel) {
    std::cerr << m_className << "::ComputeThresholdCrossings: Electrode "
              << label << " not found.\n";
    return false;
  }
  const double scale = ElementaryCharge / (m_nEvents * m_tStep);
  for (unsigned int i = 0; i < m_nTimeBins; ++i) signal[i] *= scale;

  // Establish the range.
  const double vMin = *std::min_element(std::begin(signal), std::end(signal));
  const double vMax = *std::max_element(std::begin(signal), std::end(signal));
  if (m_debug) std::cout << m_className << "::ComputeThresholdCrossings:\n";
  if (thr < vMin && thr > vMax) {
    if (m_debug) {
      std::cout << "    Threshold outside the range [" << vMin << ", " 
                << vMax << "]\n";
    }
    return true;
  }

  // Check both rising and falling edges.
  constexpr std::array<int, 2> directions = {1, -1};
  for (const auto dir : directions) {
    const bool up = dir > 0;
    if (m_debug) {
      if (up) {
        std::cout << "  Hunting for rising edges.\n";
      } else {
        std::cout << "  Hunting for falling edges.\n";
      }
    }
    // Initialise the vectors.
    std::vector<double> ts = {m_tStart + 0.5 * m_tStep};
    std::vector<double> vs = {signal[0]};
    // Scan the signal.
    for (unsigned int i = 1; i < m_nTimeBins; ++i) {
      // Compute the vector element.
      const double tNew = m_tStart + (i + 0.5) * m_tStep;
      const double vNew = signal[i];
      // If still increasing or decreasing, add to the vector.
      if ((up && vNew > vs.back()) || (!up && vNew < vs.back())) {
        ts.push_back(tNew);
        vs.push_back(vNew);
        continue;
      }
      // Otherwise see whether we crossed the threshold level.
      if ((vs[0] - thr) * (thr - vs.back()) >= 0. && ts.size() > 1 && 
          ((up && vs.back() > vs[0]) || (!up && vs.back() < vs[0]))) {
        // Compute the crossing time.
        double tcr = Numerics::Divdif(ts, vs, ts.size(), thr, iOrder);
        m_thresholdCrossings.emplace_back(std::make_pair(tcr, up));
        ts = {tNew};
        vs = {vNew};
      } else {
        // No crossing, simply reset the vector.
        ts = {tNew};
        vs = {vNew};
      }
    }
    // Check the final vector.
    if ((vs[0] - thr) * (thr - vs.back()) >= 0. && ts.size() > 1 &&
        ((up && vs.back() > vs[0]) || (!up && vs.back() < vs[0]))) {
      const double tcr = Numerics::Divdif(ts, vs, ts.size(), thr, iOrder);
      m_thresholdCrossings.emplace_back(std::make_pair(tcr, up));
    }
  }
  n = m_thresholdCrossings.size();

  if (m_debug) {
    std::cout << "  Found " << n << " crossings.\n";
    if (n > 0) std::cout << "      Time  [ns]    Direction\n";
    for (const auto& crossing : m_thresholdCrossings) {
      std::cout << "      " << crossing.first << "      ";
      if (crossing.second) {
        std::cout << "rising\n";
      } else {
        std::cout << "falling\n";
      }
    }
  }
  // Seems to have worked.
  return true;
}

bool Sensor::GetThresholdCrossing(const unsigned int i, double& time,
                                  double& level, bool& rise) const {
  level = m_thresholdLevel;

  if (i >= m_thresholdCrossings.size()) {
    std::cerr << m_className << "::GetThresholdCrossing: Index out of range.\n";
    time = m_tStart + m_nTimeBins * m_tStep;
    return false;
  }

  time = m_thresholdCrossings[i].first;
  rise = m_thresholdCrossings[i].second;
  return true;
}

bool Sensor::GetBoundingBox(double& xmin, double& ymin, double& zmin,
                            double& xmax, double& ymax, double& zmax) {
  // We don't know the range yet
  bool set = false;
  // Loop over the fields
  double x0, y0, z0, x1, y1, z1;
  for (const auto& cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    if (!std::get<0>(cmp)->GetBoundingBox(x0, y0, z0, x1, y1, z1)) continue;
    if (set) {
      if (x0 < xmin) xmin = x0;
      if (y0 < ymin) ymin = y0;
      if (z0 < zmin) zmin = z0;
      if (x1 > xmax) xmax = x1;
      if (y1 > ymax) ymax = y1;
      if (z1 > zmax) zmax = z1;
    } else {
      xmin = x0;
      ymin = y0;
      zmin = z0;
      xmax = x1;
      ymax = y1;
      zmax = z1;
      set = true;
    }
  }

  // Warn if we still don't know the range
  if (!set) {
    std::cerr << m_className << "::GetBoundingBox:\n"
              << "    Sensor bounding box not known.\n";
    xmin = ymin = zmin = 0.;
    xmax = ymax = zmax = 0.;
    return false;
  }

  if (m_debug) {
    std::cout << m_className << "::GetBoundingBox:\n"
              << "    " << xmin << " < x [cm] < " << xmax << "\n"
              << "    " << ymin << " < y [cm] < " << ymax << "\n"
              << "    " << zmin << " < z [cm] < " << zmax << "\n";
  }
  return true;
}

void Sensor::FFT(std::vector<double>& data, const bool inverse,
                 const int nn) {

  // Replaces data[1..2*nn] by its discrete fourier transform 
  // or replaces data[1..2*nn] by nn times its inverse discrete 
  // fourier transform. 
  // nn MUST be an integer power of 2 (this is not checked for!).

  const int n = 2 * nn;
  // Bit reversal.
  int j = 1;
  for (int i = 1; i < n; i += 2) {
    if (j > i) {
      // Exchange the two complex numbers.
      std::swap(data[j],data[i]);
      std::swap(data[j+1],data[i+1]);
    }        
    int m = nn;
    while (m >= 2 && j > m) {
      j -= m;
      m >>= 1;
    } 
    j += m;
  }

  const int isign = inverse ? -1 : 1;
  int mmax = 2;
  while (n > mmax) {
    const int step = 2 * mmax;
    const double theta = isign * TwoPi / mmax;
    double wtemp = sin(0.5 * theta);
    const double wpr = -2. * wtemp * wtemp;
    const double wpi = sin(theta);
    double wr = 1.;
    double wi = 0.;
    for (int m = 1; m < mmax; m += 2) {
      for (int i = m; i <= n;i += step) {
        j = i + mmax;
        double tr = wr * data[j] - wi * data[j + 1];
        double ti = wr * data[j + 1] + wi * data[j];
        data[j] = data[i] - tr;
        data[j + 1] = data[i + 1] - ti;
        data[i] += tr;
        data[i + 1] += ti;
      }
      wr = (wtemp = wr) * wpr - wi * wpi + wr;
      wi = wi * wpr + wtemp * wpi + wi;
    }
    mmax = step;
  }
}

}