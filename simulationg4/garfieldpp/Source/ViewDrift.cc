#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <limits>

#include <TGraph.h>
#include <TPolyLine3D.h>
#include <TPolyMarker3D.h>
#include <TAxis.h>
#include <TAxis3D.h>
#include <TH1F.h>
#include <TView3D.h>
#include <TVirtualViewer3D.h>

#include "Garfield/Plotting.hh"
#include "Garfield/ViewDrift.hh"

namespace Garfield {

ViewDrift::ViewDrift() : ViewBase("ViewDrift") {
  m_driftLines.reserve(1000);
  m_tracks.reserve(100);
  m_exc.reserve(1000);
  m_ion.reserve(1000);
  m_att.reserve(1000);
}

void ViewDrift::Clear() {
  m_driftLines.clear();
  m_tracks.clear();

  m_exc.clear();
  m_ion.clear();
  m_att.clear();
}

void ViewDrift::SetClusterMarkerSize(const double size) {
  if (size > 0.) {
    m_markerSizeCluster = size;
  } else {
    std::cerr << m_className << "::SetClusterMarkerSize: Size must be > 0.\n";
  }
}

void ViewDrift::SetCollisionMarkerSize(const double size) {
  if (size > 0.) {
    m_markerSizeCollision = size;
  } else {
    std::cerr << m_className << "::SetCollisionMarkerSize: Size must be > 0.\n";
  }
}

void ViewDrift::GetDriftLine(const size_t i, 
                             std::vector<std::array<float, 3> >& driftLine,
                             bool& electron) const {
  driftLine.clear();
  if (i >= m_driftLines.size()) return;
  std::copy(m_driftLines[i].first.begin(), m_driftLines[i].first.end(),
            std::back_inserter(driftLine));
  if (m_driftLines[i].second == Particle::Electron) {
    electron = true;
  } else {
    electron = false;
  }
}

void ViewDrift::NewElectronDriftLine(const unsigned int np, int& id,
                                     const float x0, const float y0,
                                     const float z0) {
  std::lock_guard<std::mutex> guard(m_mutex);
  // Create a new electron drift line and add it to the list.
  std::array<float, 3> p = {x0, y0, z0};
  std::vector<std::array<float, 3> > dl(std::max(1U, np), p);
  m_driftLines.push_back(std::make_pair(std::move(dl), Particle::Electron));
  // Return the index of this drift line.
  id = m_driftLines.size() - 1;
}

void ViewDrift::NewHoleDriftLine(const unsigned int np, int& id,
                                 const float x0, const float y0,
                                 const float z0) {
  std::lock_guard<std::mutex> guard(m_mutex);
  std::array<float, 3> p = {x0, y0, z0};
  std::vector<std::array<float, 3> > dl(std::max(1U, np), p);
  m_driftLines.push_back(std::make_pair(std::move(dl), Particle::Hole));
  // Return the index of this drift line.
  id = m_driftLines.size() - 1;
}

void ViewDrift::NewIonDriftLine(const unsigned int np, int& id, const float x0,
                                const float y0, const float z0) {
  std::lock_guard<std::mutex> guard(m_mutex);
  std::array<float, 3> p = {x0, y0, z0};
  std::vector<std::array<float, 3> > dl(std::max(1U, np), p);
  m_driftLines.push_back(std::make_pair(std::move(dl), Particle::Ion));
  // Return the index of this drift line.
  id = m_driftLines.size() - 1;
}

void ViewDrift::AddPhoton(const float x0, const float y0, const float z0, 
                          const float x1, const float y1, const float z1) {
  std::lock_guard<std::mutex> guard(m_mutex);
  std::array<float, 3> p0 = {x0, y0, z0};
  std::array<float, 3> p1 = {x1, y1, z1};
  m_photons.push_back({p0, p1});
}

void ViewDrift::NewChargedParticleTrack(const unsigned int np, int& id,
                                        const float x0, const float y0,
                                        const float z0) {
  std::lock_guard<std::mutex> guard(m_mutex);
  // Create a new track and add it to the list.
  std::vector<std::array<float, 3> > track(std::max(1U, np));
  track[0] = {x0, y0, z0};
  m_tracks.push_back(std::move(track));
  // Return the index of this track.
  id = m_tracks.size() - 1;
}

void ViewDrift::SetDriftLinePoint(const unsigned int iL, const unsigned int iP,
                                  const float x, const float y,
                                  const float z) {
  std::lock_guard<std::mutex> guard(m_mutex);
  if (iL >= m_driftLines.size() || iP >= m_driftLines[iL].first.size()) {
    std::cerr << m_className << "::SetDriftLinePoint: Index out of range.\n";
    return;
  }
  m_driftLines[iL].first[iP] = {x, y, z};
}

void ViewDrift::AddDriftLinePoint(const unsigned int iL, const float x,
                                  const float y, const float z) {
  std::lock_guard<std::mutex> guard(m_mutex);
  if (iL >= m_driftLines.size()) {
    std::cerr << m_className << "::AddDriftLinePoint: Index out of range.\n";
    return;
  }
  std::array<float, 3> p = {x, y, z};
  m_driftLines[iL].first.push_back(std::move(p));
}

void ViewDrift::SetTrackPoint(const unsigned int iL, const unsigned int iP,
                              const float x, const float y, const float z) {
  std::lock_guard<std::mutex> guard(m_mutex);
  if (iL >= m_tracks.size() || iP >= m_tracks[iL].size()) {
    std::cerr << m_className << "::SetTrackPoint: Index out of range.\n";
    return;
  }
  m_tracks[iL][iP] = {x, y, z};
}

void ViewDrift::AddTrackPoint(const unsigned int iL, const float x,
                              const float y, const float z) {
  std::lock_guard<std::mutex> guard(m_mutex);
  if (iL >= m_tracks.size()) {
    std::cerr << m_className << "::AddTrackPoint: Index out of range.\n";
    return;
  }
  std::array<float, 3> p = {x, y, z};
  m_tracks[iL].push_back(std::move(p));
}

void ViewDrift::AddExcitation(const float x, const float y, const float z) {
  std::lock_guard<std::mutex> guard(m_mutex);
  std::array<float, 3> p = {x, y, z};
  m_exc.push_back(std::move(p));
}

void ViewDrift::AddIonisation(const float x, const float y, const float z) {
  std::lock_guard<std::mutex> guard(m_mutex);
  std::array<float, 3> p = {x, y, z};
  m_ion.push_back(std::move(p));
}

void ViewDrift::AddAttachment(const float x, const float y, const float z) {
  std::lock_guard<std::mutex> guard(m_mutex);
  std::array<float, 3> p = {x, y, z};
  m_ion.push_back(std::move(p));
}

void ViewDrift::Plot(const bool twod, const bool axis) {
  if (twod) {
    Plot2d(axis);
  } else {
    Plot3d(axis, false);
  }
}

void ViewDrift::Plot2d(const bool axis) {
  auto pad = GetCanvas();
  pad->cd();
  pad->SetTitle("Drift lines");
  // Check if the canvas range has already been set.
  const bool rangeSet = RangeSet(pad);
  if (axis || !rangeSet) {
    // Determine the plot limits.
    if (!SetPlotLimits2d()) {
      std::cerr << m_className << "::Plot2d:\n"
                << "     Could not determine the plot limits.\n";
      return;
    }
  }
  if (axis) {
    auto frame = pad->DrawFrame(m_xMinPlot, m_yMinPlot, 
                                m_xMaxPlot, m_yMaxPlot);
    frame->GetXaxis()->SetTitle(LabelX().c_str());
    frame->GetYaxis()->SetTitle(LabelY().c_str());
  } else if (!rangeSet) {
    SetRange(pad, m_xMinPlot, m_yMinPlot, m_xMaxPlot, m_yMaxPlot);
  } 

  for (const auto& driftLine : m_driftLines) {
    const short lw = 1;
    if (driftLine.second == Particle::Electron) {
      DrawLine(driftLine.first, m_colElectron, lw);
    } else if (driftLine.second == Particle::Hole) {
      DrawLine(driftLine.first, m_colHole, lw);
    } else {
      DrawLine(driftLine.first, m_colIon, lw);
    }
  }
  gPad->Update();

  TGraph gr;
  gr.SetMarkerColor(m_colTrack);
  gr.SetMarkerSize(m_markerSizeCluster);
  for (const auto& track : m_tracks) {
    DrawLine(track, m_colTrack, 2);
    if (!m_drawClusters) continue;
    std::vector<float> xgr;
    std::vector<float> ygr;
    for (const auto& p : track) {
      if (!InBox(p)) continue;
      float xp = 0., yp = 0.;
      ToPlane(p[0], p[1], p[2], xp, yp);
      xgr.push_back(xp);
      ygr.push_back(yp);
    }
    gr.DrawGraph(xgr.size(), xgr.data(), ygr.data(), "Psame");
  }

  gr.SetLineColor(m_colPhoton);
  gr.SetLineStyle(2);
  for (const auto& photon : m_photons) {
    float xp0 = 0., yp0 = 0.;
    float xp1 = 0., yp1 = 0.;
    ToPlane(photon[0][0], photon[0][1], photon[0][2], xp0, yp0);
    ToPlane(photon[1][0], photon[1][1], photon[1][2], xp1, yp1);
    std::vector<float> xgr = {xp0, xp1};
    std::vector<float> ygr = {yp0, yp1};
    gr.DrawGraph(2, xgr.data(), ygr.data(), "Lsame"); 
  }

  gr.SetMarkerSize(m_markerSizeCollision);
  gr.SetMarkerStyle(20);
  if (!m_exc.empty()) {
    gr.SetMarkerColor(m_colExcitation);
    std::vector<float> xgr;
    std::vector<float> ygr;
    for (const auto& p : m_exc) {
      if (!InBox(p)) continue;
      float xp = 0., yp = 0.;
      ToPlane(p[0], p[1], p[2], xp, yp);
      xgr.push_back(xp);
      ygr.push_back(yp); 
    }
    if (!xgr.empty()) {
      gr.DrawGraph(xgr.size(), xgr.data(), ygr.data(), "Psame");
    }
  } 
  if (!m_ion.empty()) {
    gr.SetMarkerColor(m_colIonisation);
    std::vector<float> xgr;
    std::vector<float> ygr;
    for (const auto& p : m_ion) {
      if (!InBox(p)) continue;
      float xp = 0., yp = 0.;
      ToPlane(p[0], p[1], p[2], xp, yp);
      xgr.push_back(xp);
      ygr.push_back(yp); 
    }
    if (!xgr.empty()) {
      gr.DrawGraph(xgr.size(), xgr.data(), ygr.data(), "Psame");
    }
  }
  if (!m_att.empty()) {
    gr.SetMarkerColor(m_colAttachment);
    std::vector<float> xgr;
    std::vector<float> ygr;
    for (const auto& p : m_att) {
      if (!InBox(p)) continue;
      float xp = 0., yp = 0.;
      ToPlane(p[0], p[1], p[2], xp, yp);
      xgr.push_back(xp);
      ygr.push_back(yp); 
    }
    if (!xgr.empty()) {
      gr.DrawGraph(xgr.size(), xgr.data(), ygr.data(), "Psame");
    }
  }
 
  gPad->Update();
}

void ViewDrift::Plot3d(const bool axis, const bool ogl) {
  auto pad = GetCanvas();
  pad->cd();
  pad->SetTitle("Drift lines");
  if (!pad->GetView()) {
    if (!SetPlotLimits3d()) {
      std::cerr << m_className << "::Plot3d:\n"
                << "     Could not determine the plot limits.\n";
    }
    auto view = TView::CreateView(1, 0, 0);
    view->SetRange(m_xMinBox, m_yMinBox, m_zMinBox, 
                   m_xMaxBox, m_yMaxBox, m_zMaxBox);
    if (axis) view->ShowAxis();
    pad->SetView(view);
    if (ogl) pad->GetViewer3D("ogl");
  }
  for (const auto& driftLine : m_driftLines) {
    std::vector<float> points;
    for (const auto& p : driftLine.first) {
      points.push_back(p[0]);
      points.push_back(p[1]);
      points.push_back(p[2]);
    }
    TPolyLine3D pl;
    if (driftLine.second == Particle::Electron) {
      pl.SetLineColor(m_colElectron);
    } else if (driftLine.second == Particle::Hole) {
      pl.SetLineColor(m_colHole);
    } else {
      pl.SetLineColor(m_colIon);
    }
    pl.SetLineWidth(1);
    const int nP = driftLine.first.size();
    pl.DrawPolyLine(nP, points.data(), "same");
  }

  for (const auto& track : m_tracks) {
    std::vector<float> points;
    for (const auto& p : track) {
      points.push_back(p[0]);
      points.push_back(p[1]);
      points.push_back(p[2]);
    }
    TPolyLine3D pl;
    pl.SetLineColor(m_colTrack);
    pl.SetLineWidth(1);
    const int nP = track.size();
    pl.DrawPolyLine(nP, points.data(), "same");
    if (!m_drawClusters) continue;
    TPolyMarker3D pm;
    pm.SetMarkerColor(m_colTrack);
    pm.SetMarkerSize(m_markerSizeCluster);
    pm.DrawPolyMarker(nP, points.data(), 20, "same");
  }

  if (!m_exc.empty()) {
    const size_t nP = m_exc.size();
    std::vector<float> points;
    for (size_t i = 0; i < nP; ++i) {
      points.push_back(m_exc[i][0]);
      points.push_back(m_exc[i][1]);
      points.push_back(m_exc[i][2]);
    }
    TPolyMarker3D pm;
    pm.SetMarkerColor(m_colExcitation);
    pm.SetMarkerSize(m_markerSizeCollision);
    pm.DrawPolyMarker(nP, points.data(), 20, "same");
  }

  if (!m_ion.empty()) {
    const size_t nP = m_ion.size();
    std::vector<float> points;
    for (size_t i = 0; i < nP; ++i) {
      points.push_back(m_ion[i][0]);
      points.push_back(m_ion[i][1]);
      points.push_back(m_ion[i][2]);
    }
    TPolyMarker3D pm;
    pm.SetMarkerColor(m_colIonisation);
    pm.SetMarkerSize(m_markerSizeCollision);
    pm.DrawPolyMarker(nP, points.data(), 20, "same");
  }

  if (!m_att.empty()) {
    const size_t nP = m_att.size();
    std::vector<float> points;
    for (size_t i = 0; i < nP; ++i) {
      points.push_back(m_att[i][0]);
      points.push_back(m_att[i][1]);
      points.push_back(m_att[i][2]);
    }
    TPolyMarker3D pm;
    pm.SetMarkerColor(m_colAttachment);
    pm.SetMarkerSize(m_markerSizeCollision);
    pm.DrawPolyMarker(nP, points.data(), 20, "same");
  }
  pad->Update();

  if (axis) {
    TAxis3D* ax3d = TAxis3D::GetPadAxis();
    if (ax3d) {
      ax3d->SetLabelColor(kGray + 2);
      ax3d->SetAxisColor(kGray + 2);
      ax3d->SetXTitle("x");
      ax3d->SetYTitle("y");
      ax3d->SetZTitle("z");
    }
    pad->Update();
  }
}

bool ViewDrift::SetPlotLimits2d() {

  if (m_userPlotLimits) return true;
  double xmin = 0., ymin = 0., xmax = 0., ymax = 0.;
  if (m_userBox) {
    if (PlotLimitsFromUserBox(xmin, ymin, xmax, ymax)) {
      m_xMinPlot = xmin;
      m_yMinPlot = ymin;
      m_xMaxPlot = xmax;
      m_yMaxPlot = ymax;
      return true;
    }
  }

  // Try to determine the limits from the drift lines themselves.
  std::array<double, 3> bbmin;
  std::array<double, 3> bbmax;
  bbmin.fill(std::numeric_limits<double>::max());
  bbmax.fill(-std::numeric_limits<double>::max());
  for (const auto& driftLine : m_driftLines) {
    for (const auto& p : driftLine.first) {
      for (unsigned int i = 0; i < 3; ++i) {
        bbmin[i] = std::min(bbmin[i], double(p[i])); 
        bbmax[i] = std::max(bbmax[i], double(p[i]));
      }
    }
  }
  for (const auto& track : m_tracks) {
    for (const auto& p : track) {
      for (unsigned int i = 0; i < 3; ++i) {
        bbmin[i] = std::min(bbmin[i], double(p[i])); 
        bbmax[i] = std::max(bbmax[i], double(p[i]));
      }
    }
  }
  return PlotLimits(bbmin, bbmax, 
                    m_xMinPlot, m_yMinPlot, m_xMaxPlot, m_yMaxPlot);
}

bool ViewDrift::SetPlotLimits3d() {

  if (m_userBox) return true;
  if (m_driftLines.empty() && m_tracks.empty()) return false;
  // Try to determine the limits from the drift lines themselves.
  std::array<double, 3> bbmin;
  std::array<double, 3> bbmax;
  bbmin.fill(std::numeric_limits<double>::max());
  bbmax.fill(-std::numeric_limits<double>::max());
  for (const auto& driftLine : m_driftLines) {
    for (const auto& p : driftLine.first) {
      for (unsigned int i = 0; i < 3; ++i) {
        bbmin[i] = std::min(bbmin[i], double(p[i])); 
        bbmax[i] = std::max(bbmax[i], double(p[i]));
      }
    }
  }
  for (const auto& track : m_tracks) {
    for (const auto& p : track) {
      for (unsigned int i = 0; i < 3; ++i) {
        bbmin[i] = std::min(bbmin[i], double(p[i])); 
        bbmax[i] = std::max(bbmax[i], double(p[i]));
      }
    }
  }
  double r = 0.;
  for (size_t i = 0; i < 3; ++i) r += fabs(bbmax[i] - bbmin[i]);
  m_xMinBox = bbmin[0];
  m_yMinBox = bbmin[1];
  m_zMinBox = bbmin[2];
  m_xMaxBox = bbmax[0];
  m_yMaxBox = bbmax[1];
  m_zMaxBox = bbmax[2];
  if (fabs(m_xMaxBox - m_xMinBox) < 0.1 * r) {
    m_xMinBox -= 0.1 * r;
    m_xMaxBox += 0.1 * r;
  }
  if (fabs(m_yMaxBox - m_yMinBox) < 0.1 * r) {
    m_yMinBox -= 0.1 * r;
    m_yMaxBox += 0.1 * r;
  }
  if (fabs(m_zMaxBox - m_zMinBox) < 0.1 * r) {
    m_zMinBox -= 0.1 * r;
    m_zMaxBox += 0.1 * r;
  }
  return true;
}

}