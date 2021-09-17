#ifndef G_COMPONENT_FIELD_MAP_H
#define G_COMPONENT_FIELD_MAP_H

#include <iostream>
#include "Component.hh"
#include "TMatrixD.h"
#include "TetrahedralTree.hh"

namespace Garfield {

/// Base class for components based on finite-element field maps.

class ComponentFieldMap : public Component {
 public:
  /// Default constructor.
  ComponentFieldMap() = delete;
  /// Constructor
  ComponentFieldMap(const std::string& name);
  /// Destructor
  virtual ~ComponentFieldMap();

  /// Add x,y,z,V offset to all nodes
  void SetOffSetNodes(double x,double y,double z,double V)
  {
    m_offSetNodes_x=x;
    m_offSetNodes_y=y;
    m_offSetNodes_z=z;
    m_offSetNodes_V=V;
  }

  /// Calculate x, y, z, V and angular ranges.
  virtual void SetRange();
  /// Show x, y, z, V and angular ranges
  void PrintRange();

  bool IsInBoundingBox(const double x, const double y, const double z) const {
    return x >= m_minBoundingBox[0] && x <= m_maxBoundingBox[0] &&
           y >= m_minBoundingBox[1] && y <= m_maxBoundingBox[1] &&
           z >= m_minBoundingBox[2] && y <= m_maxBoundingBox[2];
  }

  bool GetBoundingBox(double& xmin, double& ymin, double& zmin,
                              double& xmax, double& ymax,
                              double& zmax) override;

  bool GetVoltageRange(double& vmin, double& vmax) override {
    vmin = m_mapvmin;
    vmax = m_mapvmax;
    return true;
  }

  /// List all currently defined materials
  void PrintMaterials();
  /// Flag a field map material as a drift medium.
  void DriftMedium(const unsigned int imat);
  /// Flag a field map materials as a non-drift medium.
  void NotDriftMedium(const unsigned int imat);
  /// Return the number of materials in the field map.
  unsigned int GetNumberOfMaterials() const { return m_materials.size(); }
  /// Return the permittivity of a field map material.
  double GetPermittivity(const unsigned int imat) const;
  /// Return the conductivity of a field map material.
  double GetConductivity(const unsigned int imat) const;
  /// Associate a field map material with a Medium class.
  void SetMedium(const unsigned int imat, Medium* medium);
  /// Return the Medium associated to a field map material.
  Medium* GetMedium(const unsigned int i) const;
  using Component::GetMedium;

  unsigned int GetNumberOfMedia() const { return m_materials.size(); }

  /// Return the number of mesh elements.
  unsigned int GetNumberOfElements() const { return m_elements.size(); }
  /// Return the volume and aspect ratio of a mesh element.
  bool GetElement(const unsigned int i, double& vol, double& dmin,
                  double& dmax);

  // Options
  void EnableCheckMapIndices(const bool on = true) {
    m_checkMultipleElement = on;
    if (on) m_lastElement = -1;
  }
  /// Option to eliminate mesh elements in conductors (default: on).
  void EnableDeleteBackgroundElements(const bool on = true) { 
    m_deleteBackground = on; 
  }

  /// Enable or disable the usage of the tetrahedral tree
  /// for searching the element in the mesh.
  void EnableTetrahedralTreeForElementSearch(const bool on = true) {
    m_useTetrahedralTree = on;
  }

  /// Enable or disable warnings that the calculation of the local
  /// coordinates did not achieve the requested precision. 
  void EnableConvergenceWarnings(const bool on = true) {
    m_printConvergenceWarnings = on;
  }

  friend class ViewFEMesh;
 protected:
  bool m_is3d = true;

  double m_offSetNodes_x=0;
  double m_offSetNodes_y=0;
  double m_offSetNodes_z=0;
  double m_offSetNodes_V=0;
  // Elements
  struct Element {
    // Nodes
    int emap[10];
    // Material
    unsigned int matmap;
    bool degenerate;
    // Bounding box of the element
    double xmin, ymin, zmin, xmax, ymax, zmax;
  };
  std::vector<Element> m_elements;

  // Nodes
  struct Node {
    // Coordinates
    double x, y, z;
    // Potential
    double v;
    // Weighting potentials
    std::vector<double> w;
  };
  std::vector<Node> m_nodes;

  // Materials
  struct Material {
    // Permittivity
    double eps;
    // Resistivity
    double ohm;
    bool driftmedium;
    // Associated medium
    Medium* medium;
  };
  std::vector<Material> m_materials;

  std::vector<std::string> m_wfields;
  std::vector<bool> m_wfieldsOk;

  // Bounding box
  bool m_hasBoundingBox = false;
  std::array<double, 3> m_minBoundingBox;
  std::array<double, 3> m_maxBoundingBox;

  // Ranges and periodicities
  std::array<double, 3> m_mapmin;
  std::array<double, 3> m_mapmax;
  std::array<double, 3> m_mapamin;
  std::array<double, 3> m_mapamax;
  std::array<double, 3> m_mapna;
  std::array<double, 3> m_cells;

  double m_mapvmin = 0.;
  double m_mapvmax = 0.;

  std::array<bool, 3> m_setang;

  // Option to delete meshing in conductors
  bool m_deleteBackground = true;

  // Warnings flag
  bool m_warning = false;
  unsigned int m_nWarnings = 0;

  // Print warnings about failed convergence when refining 
  // isoparametric coordinates. 
  bool m_printConvergenceWarnings = true;

  // Get the scaling factor for a given length unit.
  static double ScalingFactor(std::string unit);
 
  // Reset the component
  void Reset() override {}

  // Periodicities
  void UpdatePeriodicity2d();
  void UpdatePeriodicityCommon();

  /// Find the element for a point in curved quadratic quadrilaterals.
  int FindElement5(const double x, const double y, const double z, double& t1,
                   double& t2, double& t3, double& t4, double jac[4][4],
                   double& det);
  /// Find the element for a point in curved quadratic tetrahedra.
  int FindElement13(const double x, const double y, const double z, double& t1,
                    double& t2, double& t3, double& t4, double jac[4][4],
                    double& det);
  /// Find the element for a point in a cube.
  int FindElementCube(const double x, const double y, const double z,
                      double& t1, double& t2, double& t3, TMatrixD*& jac,
                      std::vector<TMatrixD*>& dN);

  /// Move (xpos, ypos, zpos) to field map coordinates.
  void MapCoordinates(double& xpos, double& ypos, double& zpos, bool& xmirrored,
                      bool& ymirrored, bool& zmirrored, double& rcoordinate,
                      double& rotation) const;
  /// Move (ex, ey, ez) to global coordinates.
  void UnmapFields(double& ex, double& ey, double& ez, double& xpos,
                   double& ypos, double& zpos, bool& xmirrored, bool& ymirrored,
                   bool& zmirrored, double& rcoordinate,
                   double& rotation) const;

  int ReadInteger(char* token, int def, bool& error);
  double ReadDouble(char* token, double def, bool& error);

  virtual double GetElementVolume(const unsigned int i) = 0;
  virtual void GetAspectRatio(const unsigned int i, double& dmin,
                              double& dmax) = 0;

  size_t GetWeightingFieldIndex(const std::string& label) const;
  size_t GetOrCreateWeightingFieldIndex(const std::string& label);

  void PrintWarning(const std::string& header) {
    if (!m_warning || m_nWarnings > 10) return;
    std::cerr << m_className << "::" << header << ":\n"
              << "    Warnings have been issued for this field map.\n";
    ++m_nWarnings;
  }
  void PrintNotReady(const std::string& header) const {
    std::cerr << m_className << "::" << header << ":\n"
              << "    Field map not yet initialised.\n";
  }
  void PrintElement(const std::string& header, const double x, const double y,
                    const double z, const double t1, const double t2,
                    const double t3, const double t4, const Element& element,
                    const unsigned int n, const int iw = -1) const;

 private:
  /// Scan for multiple elements that contain a point
  bool m_checkMultipleElement = false;

  // Tetrahedral tree
  bool m_useTetrahedralTree = true;
  bool m_isTreeInitialized = false;
  TetrahedralTree* m_tetTree = nullptr;

  /// Flag to check if bounding boxes of elements are cached
  bool m_cacheElemBoundingBoxes = false;

  /// Keep track of the last element found.
  int m_lastElement = -1;

  /// Calculate local coordinates for curved quadratic triangles.
  int Coordinates3(double x, double y, double z, double& t1, double& t2,
                   double& t3, double& t4, double jac[4][4], double& det,
                   const Element& element) const;
  /// Calculate local coordinates for linear quadrilaterals.
  int Coordinates4(const double x, const double y, const double z, double& t1,
                   double& t2, double& t3, double& t4, 
                   double& det, const Element& element) const;
  /// Calculate local coordinates for curved quadratic quadrilaterals.
  int Coordinates5(const double x, const double y, const double z, double& t1,
                   double& t2, double& t3, double& t4, double jac[4][4],
                   double& det, const Element& element) const;
  /// Calculate local coordinates in linear tetrahedra.
  void Coordinates12(const double x, const double y, const double z, double& t1,
                     double& t2, double& t3, double& t4,
                     const Element& element) const;
  /// Calculate local coordinates for curved quadratic tetrahedra.
  int Coordinates13(const double x, const double y, const double z, double& t1,
                    double& t2, double& t3, double& t4, double jac[4][4],
                    double& det, const Element& element) const;
  /// Calculate local coordinates for a cube.
  int CoordinatesCube(const double x, const double y, const double z,
                      double& t1, double& t2, double& t3, TMatrixD*& jac,
                      std::vector<TMatrixD*>& dN, const Element& element) const;

  /// Calculate Jacobian for curved quadratic triangles.
  void Jacobian3(const Element& element, const double u, const double v,
                 const double w, double& det, double jac[4][4]) const;
  /// Calculate Jacobian for curved quadratic quadrilaterals.
  void Jacobian5(const Element& element, const double u, const double v,
                 double& det, double jac[4][4]) const;
  /// Calculate Jacobian for curved quadratic tetrahedra.
  void Jacobian13(const Element& element, const double t, const double u,
                  const double v, const double w, double& det,
                  double jac[4][4]) const;
  /// Calculate Jacobian for a cube.
  void JacobianCube(const Element& element, const double t1, const double t2,
                    const double t3, TMatrixD*& jac,
                    std::vector<TMatrixD*>& dN) const;

  /// Calculate the bounding boxes of all elements after initialization.
  void CalculateElementBoundingBoxes();

  /// Initialize the tetrahedral tree.
  bool InitializeTetrahedralTree();
};
}

#endif