// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME GarfieldDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "Garfield/AvalancheMC.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/Component.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/ComponentAnsys121.hh"
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/ComponentCST.hh"
#include "Garfield/ComponentComsol.hh"
#include "Garfield/ComponentConstant.hh"
#include "Garfield/ComponentElmer.hh"
#include "Garfield/ComponentElmer2D.hh"
#include "Garfield/ComponentFieldMap.hh"
#include "Garfield/ComponentGrid.hh"
#include "Garfield/ComponentNeBem2d.hh"
#include "Garfield/ComponentNeBem3d.hh"
#include "Garfield/ComponentNeBem3dMap.hh"
#include "Garfield/ComponentTcad2d.hh"
#include "Garfield/ComponentTcad3d.hh"
#include "Garfield/ComponentUser.hh"
#include "Garfield/ComponentVoxel.hh"
#include "Garfield/DriftLineRKF.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Geometry.hh"
#include "Garfield/GeometryRoot.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/KDTree.hh"
#include "Garfield/MagboltzInterface.hh"
#include "Garfield/Medium.hh"
#include "Garfield/MediumCdTe.hh"
#include "Garfield/MediumConductor.hh"
#include "Garfield/MediumGaAs.hh"
#include "Garfield/MediumGaN.hh"
#include "Garfield/MediumGas.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/MediumPlastic.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Numerics.hh"
#include "Garfield/OpticalData.hh"
#include "Garfield/Plotting.hh"
#include "Garfield/PlottingEngine.hh"
#include "Garfield/PlottingEngineRoot.hh"
#include "Garfield/Polygon.hh"
#include "Garfield/Random.hh"
#include "Garfield/RandomEngine.hh"
#include "Garfield/RandomEngineRoot.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/Shaper.hh"
#include "Garfield/Solid.hh"
#include "Garfield/SolidBox.hh"
#include "Garfield/SolidExtrusion.hh"
#include "Garfield/SolidHole.hh"
#include "Garfield/SolidRidge.hh"
#include "Garfield/SolidSphere.hh"
#include "Garfield/SolidTube.hh"
#include "Garfield/SolidWire.hh"
#include "Garfield/TetrahedralTree.hh"
#include "Garfield/Track.hh"
#include "Garfield/TrackBichsel.hh"
#include "Garfield/TrackElectron.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/TrackPAI.hh"
#include "Garfield/TrackSimple.hh"
#include "Garfield/TrackSrim.hh"
#include "Garfield/Utilities.hh"
#include "Garfield/ViewBase.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ViewGeometry.hh"
#include "Garfield/ViewIsochrons.hh"
#include "Garfield/ViewMedium.hh"
#include "Garfield/ViewSignal.hh"

// Header files passed via #pragma extra_include

namespace Garfield {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *Garfield_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("Garfield", 0 /*version*/, "Garfield/FundamentalConstants.hh", 8,
                     ::ROOT::Internal::DefineBehavior((void*)0,(void*)0),
                     &Garfield_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *Garfield_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static TClass *GarfieldcLcLMedium_Dictionary();
   static void GarfieldcLcLMedium_TClassManip(TClass*);
   static void *new_GarfieldcLcLMedium(void *p = 0);
   static void *newArray_GarfieldcLcLMedium(Long_t size, void *p);
   static void delete_GarfieldcLcLMedium(void *p);
   static void deleteArray_GarfieldcLcLMedium(void *p);
   static void destruct_GarfieldcLcLMedium(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::Medium*)
   {
      ::Garfield::Medium *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::Medium));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::Medium", "Garfield/Medium.hh", 13,
                  typeid(::Garfield::Medium), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLMedium_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::Medium) );
      instance.SetNew(&new_GarfieldcLcLMedium);
      instance.SetNewArray(&newArray_GarfieldcLcLMedium);
      instance.SetDelete(&delete_GarfieldcLcLMedium);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLMedium);
      instance.SetDestructor(&destruct_GarfieldcLcLMedium);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::Medium*)
   {
      return GenerateInitInstanceLocal((::Garfield::Medium*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::Medium*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLMedium_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::Medium*)0x0)->GetClass();
      GarfieldcLcLMedium_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLMedium_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLSolid_Dictionary();
   static void GarfieldcLcLSolid_TClassManip(TClass*);
   static void delete_GarfieldcLcLSolid(void *p);
   static void deleteArray_GarfieldcLcLSolid(void *p);
   static void destruct_GarfieldcLcLSolid(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::Solid*)
   {
      ::Garfield::Solid *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::Solid));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::Solid", "Garfield/Solid.hh", 28,
                  typeid(::Garfield::Solid), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLSolid_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::Solid) );
      instance.SetDelete(&delete_GarfieldcLcLSolid);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLSolid);
      instance.SetDestructor(&destruct_GarfieldcLcLSolid);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::Solid*)
   {
      return GenerateInitInstanceLocal((::Garfield::Solid*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::Solid*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLSolid_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::Solid*)0x0)->GetClass();
      GarfieldcLcLSolid_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLSolid_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLGeometry_Dictionary();
   static void GarfieldcLcLGeometry_TClassManip(TClass*);
   static void delete_GarfieldcLcLGeometry(void *p);
   static void deleteArray_GarfieldcLcLGeometry(void *p);
   static void destruct_GarfieldcLcLGeometry(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::Geometry*)
   {
      ::Garfield::Geometry *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::Geometry));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::Geometry", "Garfield/Geometry.hh", 13,
                  typeid(::Garfield::Geometry), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLGeometry_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::Geometry) );
      instance.SetDelete(&delete_GarfieldcLcLGeometry);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLGeometry);
      instance.SetDestructor(&destruct_GarfieldcLcLGeometry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::Geometry*)
   {
      return GenerateInitInstanceLocal((::Garfield::Geometry*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::Geometry*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLGeometry_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::Geometry*)0x0)->GetClass();
      GarfieldcLcLGeometry_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLGeometry_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLComponent_Dictionary();
   static void GarfieldcLcLComponent_TClassManip(TClass*);
   static void delete_GarfieldcLcLComponent(void *p);
   static void deleteArray_GarfieldcLcLComponent(void *p);
   static void destruct_GarfieldcLcLComponent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::Component*)
   {
      ::Garfield::Component *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::Component));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::Component", "Garfield/Component.hh", 13,
                  typeid(::Garfield::Component), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLComponent_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::Component) );
      instance.SetDelete(&delete_GarfieldcLcLComponent);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLComponent);
      instance.SetDestructor(&destruct_GarfieldcLcLComponent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::Component*)
   {
      return GenerateInitInstanceLocal((::Garfield::Component*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::Component*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLComponent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::Component*)0x0)->GetClass();
      GarfieldcLcLComponent_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLComponent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLSensor_Dictionary();
   static void GarfieldcLcLSensor_TClassManip(TClass*);
   static void *new_GarfieldcLcLSensor(void *p = 0);
   static void *newArray_GarfieldcLcLSensor(Long_t size, void *p);
   static void delete_GarfieldcLcLSensor(void *p);
   static void deleteArray_GarfieldcLcLSensor(void *p);
   static void destruct_GarfieldcLcLSensor(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::Sensor*)
   {
      ::Garfield::Sensor *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::Sensor));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::Sensor", "Garfield/Sensor.hh", 16,
                  typeid(::Garfield::Sensor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLSensor_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::Sensor) );
      instance.SetNew(&new_GarfieldcLcLSensor);
      instance.SetNewArray(&newArray_GarfieldcLcLSensor);
      instance.SetDelete(&delete_GarfieldcLcLSensor);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLSensor);
      instance.SetDestructor(&destruct_GarfieldcLcLSensor);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::Sensor*)
   {
      return GenerateInitInstanceLocal((::Garfield::Sensor*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::Sensor*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLSensor_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::Sensor*)0x0)->GetClass();
      GarfieldcLcLSensor_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLSensor_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLViewDrift_Dictionary();
   static void GarfieldcLcLViewDrift_TClassManip(TClass*);
   static void *new_GarfieldcLcLViewDrift(void *p = 0);
   static void *newArray_GarfieldcLcLViewDrift(Long_t size, void *p);
   static void delete_GarfieldcLcLViewDrift(void *p);
   static void deleteArray_GarfieldcLcLViewDrift(void *p);
   static void destruct_GarfieldcLcLViewDrift(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ViewDrift*)
   {
      ::Garfield::ViewDrift *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ViewDrift));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ViewDrift", "Garfield/ViewDrift.hh", 18,
                  typeid(::Garfield::ViewDrift), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLViewDrift_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ViewDrift) );
      instance.SetNew(&new_GarfieldcLcLViewDrift);
      instance.SetNewArray(&newArray_GarfieldcLcLViewDrift);
      instance.SetDelete(&delete_GarfieldcLcLViewDrift);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLViewDrift);
      instance.SetDestructor(&destruct_GarfieldcLcLViewDrift);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ViewDrift*)
   {
      return GenerateInitInstanceLocal((::Garfield::ViewDrift*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ViewDrift*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLViewDrift_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ViewDrift*)0x0)->GetClass();
      GarfieldcLcLViewDrift_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLViewDrift_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLAvalancheMC_Dictionary();
   static void GarfieldcLcLAvalancheMC_TClassManip(TClass*);
   static void *new_GarfieldcLcLAvalancheMC(void *p = 0);
   static void *newArray_GarfieldcLcLAvalancheMC(Long_t size, void *p);
   static void delete_GarfieldcLcLAvalancheMC(void *p);
   static void deleteArray_GarfieldcLcLAvalancheMC(void *p);
   static void destruct_GarfieldcLcLAvalancheMC(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::AvalancheMC*)
   {
      ::Garfield::AvalancheMC *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::AvalancheMC));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::AvalancheMC", "Garfield/AvalancheMC.hh", 17,
                  typeid(::Garfield::AvalancheMC), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLAvalancheMC_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::AvalancheMC) );
      instance.SetNew(&new_GarfieldcLcLAvalancheMC);
      instance.SetNewArray(&newArray_GarfieldcLcLAvalancheMC);
      instance.SetDelete(&delete_GarfieldcLcLAvalancheMC);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLAvalancheMC);
      instance.SetDestructor(&destruct_GarfieldcLcLAvalancheMC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::AvalancheMC*)
   {
      return GenerateInitInstanceLocal((::Garfield::AvalancheMC*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::AvalancheMC*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLAvalancheMC_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::AvalancheMC*)0x0)->GetClass();
      GarfieldcLcLAvalancheMC_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLAvalancheMC_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLAvalancheMicroscopic_Dictionary();
   static void GarfieldcLcLAvalancheMicroscopic_TClassManip(TClass*);
   static void *new_GarfieldcLcLAvalancheMicroscopic(void *p = 0);
   static void *newArray_GarfieldcLcLAvalancheMicroscopic(Long_t size, void *p);
   static void delete_GarfieldcLcLAvalancheMicroscopic(void *p);
   static void deleteArray_GarfieldcLcLAvalancheMicroscopic(void *p);
   static void destruct_GarfieldcLcLAvalancheMicroscopic(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::AvalancheMicroscopic*)
   {
      ::Garfield::AvalancheMicroscopic *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::AvalancheMicroscopic));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::AvalancheMicroscopic", "Garfield/AvalancheMicroscopic.hh", 17,
                  typeid(::Garfield::AvalancheMicroscopic), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLAvalancheMicroscopic_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::AvalancheMicroscopic) );
      instance.SetNew(&new_GarfieldcLcLAvalancheMicroscopic);
      instance.SetNewArray(&newArray_GarfieldcLcLAvalancheMicroscopic);
      instance.SetDelete(&delete_GarfieldcLcLAvalancheMicroscopic);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLAvalancheMicroscopic);
      instance.SetDestructor(&destruct_GarfieldcLcLAvalancheMicroscopic);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::AvalancheMicroscopic*)
   {
      return GenerateInitInstanceLocal((::Garfield::AvalancheMicroscopic*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::AvalancheMicroscopic*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLAvalancheMicroscopic_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::AvalancheMicroscopic*)0x0)->GetClass();
      GarfieldcLcLAvalancheMicroscopic_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLAvalancheMicroscopic_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLComponentAnalyticField_Dictionary();
   static void GarfieldcLcLComponentAnalyticField_TClassManip(TClass*);
   static void *new_GarfieldcLcLComponentAnalyticField(void *p = 0);
   static void *newArray_GarfieldcLcLComponentAnalyticField(Long_t size, void *p);
   static void delete_GarfieldcLcLComponentAnalyticField(void *p);
   static void deleteArray_GarfieldcLcLComponentAnalyticField(void *p);
   static void destruct_GarfieldcLcLComponentAnalyticField(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ComponentAnalyticField*)
   {
      ::Garfield::ComponentAnalyticField *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ComponentAnalyticField));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ComponentAnalyticField", "Garfield/ComponentAnalyticField.hh", 16,
                  typeid(::Garfield::ComponentAnalyticField), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLComponentAnalyticField_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ComponentAnalyticField) );
      instance.SetNew(&new_GarfieldcLcLComponentAnalyticField);
      instance.SetNewArray(&newArray_GarfieldcLcLComponentAnalyticField);
      instance.SetDelete(&delete_GarfieldcLcLComponentAnalyticField);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLComponentAnalyticField);
      instance.SetDestructor(&destruct_GarfieldcLcLComponentAnalyticField);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ComponentAnalyticField*)
   {
      return GenerateInitInstanceLocal((::Garfield::ComponentAnalyticField*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ComponentAnalyticField*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLComponentAnalyticField_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ComponentAnalyticField*)0x0)->GetClass();
      GarfieldcLcLComponentAnalyticField_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLComponentAnalyticField_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLComponentFieldMap_Dictionary();
   static void GarfieldcLcLComponentFieldMap_TClassManip(TClass*);
   static void delete_GarfieldcLcLComponentFieldMap(void *p);
   static void deleteArray_GarfieldcLcLComponentFieldMap(void *p);
   static void destruct_GarfieldcLcLComponentFieldMap(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ComponentFieldMap*)
   {
      ::Garfield::ComponentFieldMap *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ComponentFieldMap));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ComponentFieldMap", "Garfield/ComponentFieldMap.hh", 13,
                  typeid(::Garfield::ComponentFieldMap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLComponentFieldMap_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ComponentFieldMap) );
      instance.SetDelete(&delete_GarfieldcLcLComponentFieldMap);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLComponentFieldMap);
      instance.SetDestructor(&destruct_GarfieldcLcLComponentFieldMap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ComponentFieldMap*)
   {
      return GenerateInitInstanceLocal((::Garfield::ComponentFieldMap*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ComponentFieldMap*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLComponentFieldMap_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ComponentFieldMap*)0x0)->GetClass();
      GarfieldcLcLComponentFieldMap_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLComponentFieldMap_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLComponentAnsys121_Dictionary();
   static void GarfieldcLcLComponentAnsys121_TClassManip(TClass*);
   static void *new_GarfieldcLcLComponentAnsys121(void *p = 0);
   static void *newArray_GarfieldcLcLComponentAnsys121(Long_t size, void *p);
   static void delete_GarfieldcLcLComponentAnsys121(void *p);
   static void deleteArray_GarfieldcLcLComponentAnsys121(void *p);
   static void destruct_GarfieldcLcLComponentAnsys121(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ComponentAnsys121*)
   {
      ::Garfield::ComponentAnsys121 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ComponentAnsys121));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ComponentAnsys121", "Garfield/ComponentAnsys121.hh", 10,
                  typeid(::Garfield::ComponentAnsys121), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLComponentAnsys121_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ComponentAnsys121) );
      instance.SetNew(&new_GarfieldcLcLComponentAnsys121);
      instance.SetNewArray(&newArray_GarfieldcLcLComponentAnsys121);
      instance.SetDelete(&delete_GarfieldcLcLComponentAnsys121);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLComponentAnsys121);
      instance.SetDestructor(&destruct_GarfieldcLcLComponentAnsys121);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ComponentAnsys121*)
   {
      return GenerateInitInstanceLocal((::Garfield::ComponentAnsys121*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ComponentAnsys121*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLComponentAnsys121_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ComponentAnsys121*)0x0)->GetClass();
      GarfieldcLcLComponentAnsys121_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLComponentAnsys121_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLComponentAnsys123_Dictionary();
   static void GarfieldcLcLComponentAnsys123_TClassManip(TClass*);
   static void *new_GarfieldcLcLComponentAnsys123(void *p = 0);
   static void *newArray_GarfieldcLcLComponentAnsys123(Long_t size, void *p);
   static void delete_GarfieldcLcLComponentAnsys123(void *p);
   static void deleteArray_GarfieldcLcLComponentAnsys123(void *p);
   static void destruct_GarfieldcLcLComponentAnsys123(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ComponentAnsys123*)
   {
      ::Garfield::ComponentAnsys123 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ComponentAnsys123));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ComponentAnsys123", "Garfield/ComponentAnsys123.hh", 10,
                  typeid(::Garfield::ComponentAnsys123), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLComponentAnsys123_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ComponentAnsys123) );
      instance.SetNew(&new_GarfieldcLcLComponentAnsys123);
      instance.SetNewArray(&newArray_GarfieldcLcLComponentAnsys123);
      instance.SetDelete(&delete_GarfieldcLcLComponentAnsys123);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLComponentAnsys123);
      instance.SetDestructor(&destruct_GarfieldcLcLComponentAnsys123);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ComponentAnsys123*)
   {
      return GenerateInitInstanceLocal((::Garfield::ComponentAnsys123*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ComponentAnsys123*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLComponentAnsys123_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ComponentAnsys123*)0x0)->GetClass();
      GarfieldcLcLComponentAnsys123_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLComponentAnsys123_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLComponentCST_Dictionary();
   static void GarfieldcLcLComponentCST_TClassManip(TClass*);
   static void *new_GarfieldcLcLComponentCST(void *p = 0);
   static void *newArray_GarfieldcLcLComponentCST(Long_t size, void *p);
   static void delete_GarfieldcLcLComponentCST(void *p);
   static void deleteArray_GarfieldcLcLComponentCST(void *p);
   static void destruct_GarfieldcLcLComponentCST(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ComponentCST*)
   {
      ::Garfield::ComponentCST *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ComponentCST));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ComponentCST", "Garfield/ComponentCST.hh", 15,
                  typeid(::Garfield::ComponentCST), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLComponentCST_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ComponentCST) );
      instance.SetNew(&new_GarfieldcLcLComponentCST);
      instance.SetNewArray(&newArray_GarfieldcLcLComponentCST);
      instance.SetDelete(&delete_GarfieldcLcLComponentCST);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLComponentCST);
      instance.SetDestructor(&destruct_GarfieldcLcLComponentCST);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ComponentCST*)
   {
      return GenerateInitInstanceLocal((::Garfield::ComponentCST*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ComponentCST*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLComponentCST_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ComponentCST*)0x0)->GetClass();
      GarfieldcLcLComponentCST_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLComponentCST_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLComponentConstant_Dictionary();
   static void GarfieldcLcLComponentConstant_TClassManip(TClass*);
   static void *new_GarfieldcLcLComponentConstant(void *p = 0);
   static void *newArray_GarfieldcLcLComponentConstant(Long_t size, void *p);
   static void delete_GarfieldcLcLComponentConstant(void *p);
   static void deleteArray_GarfieldcLcLComponentConstant(void *p);
   static void destruct_GarfieldcLcLComponentConstant(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ComponentConstant*)
   {
      ::Garfield::ComponentConstant *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ComponentConstant));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ComponentConstant", "Garfield/ComponentConstant.hh", 10,
                  typeid(::Garfield::ComponentConstant), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLComponentConstant_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ComponentConstant) );
      instance.SetNew(&new_GarfieldcLcLComponentConstant);
      instance.SetNewArray(&newArray_GarfieldcLcLComponentConstant);
      instance.SetDelete(&delete_GarfieldcLcLComponentConstant);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLComponentConstant);
      instance.SetDestructor(&destruct_GarfieldcLcLComponentConstant);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ComponentConstant*)
   {
      return GenerateInitInstanceLocal((::Garfield::ComponentConstant*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ComponentConstant*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLComponentConstant_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ComponentConstant*)0x0)->GetClass();
      GarfieldcLcLComponentConstant_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLComponentConstant_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLComponentUser_Dictionary();
   static void GarfieldcLcLComponentUser_TClassManip(TClass*);
   static void *new_GarfieldcLcLComponentUser(void *p = 0);
   static void *newArray_GarfieldcLcLComponentUser(Long_t size, void *p);
   static void delete_GarfieldcLcLComponentUser(void *p);
   static void deleteArray_GarfieldcLcLComponentUser(void *p);
   static void destruct_GarfieldcLcLComponentUser(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ComponentUser*)
   {
      ::Garfield::ComponentUser *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ComponentUser));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ComponentUser", "Garfield/ComponentUser.hh", 12,
                  typeid(::Garfield::ComponentUser), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLComponentUser_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ComponentUser) );
      instance.SetNew(&new_GarfieldcLcLComponentUser);
      instance.SetNewArray(&newArray_GarfieldcLcLComponentUser);
      instance.SetDelete(&delete_GarfieldcLcLComponentUser);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLComponentUser);
      instance.SetDestructor(&destruct_GarfieldcLcLComponentUser);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ComponentUser*)
   {
      return GenerateInitInstanceLocal((::Garfield::ComponentUser*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ComponentUser*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLComponentUser_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ComponentUser*)0x0)->GetClass();
      GarfieldcLcLComponentUser_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLComponentUser_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLGeometryRoot_Dictionary();
   static void GarfieldcLcLGeometryRoot_TClassManip(TClass*);
   static void *new_GarfieldcLcLGeometryRoot(void *p = 0);
   static void *newArray_GarfieldcLcLGeometryRoot(Long_t size, void *p);
   static void delete_GarfieldcLcLGeometryRoot(void *p);
   static void deleteArray_GarfieldcLcLGeometryRoot(void *p);
   static void destruct_GarfieldcLcLGeometryRoot(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::GeometryRoot*)
   {
      ::Garfield::GeometryRoot *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::GeometryRoot));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::GeometryRoot", "Garfield/GeometryRoot.hh", 15,
                  typeid(::Garfield::GeometryRoot), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLGeometryRoot_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::GeometryRoot) );
      instance.SetNew(&new_GarfieldcLcLGeometryRoot);
      instance.SetNewArray(&newArray_GarfieldcLcLGeometryRoot);
      instance.SetDelete(&delete_GarfieldcLcLGeometryRoot);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLGeometryRoot);
      instance.SetDestructor(&destruct_GarfieldcLcLGeometryRoot);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::GeometryRoot*)
   {
      return GenerateInitInstanceLocal((::Garfield::GeometryRoot*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::GeometryRoot*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLGeometryRoot_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::GeometryRoot*)0x0)->GetClass();
      GarfieldcLcLGeometryRoot_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLGeometryRoot_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLGeometrySimple_Dictionary();
   static void GarfieldcLcLGeometrySimple_TClassManip(TClass*);
   static void *new_GarfieldcLcLGeometrySimple(void *p = 0);
   static void *newArray_GarfieldcLcLGeometrySimple(Long_t size, void *p);
   static void delete_GarfieldcLcLGeometrySimple(void *p);
   static void deleteArray_GarfieldcLcLGeometrySimple(void *p);
   static void destruct_GarfieldcLcLGeometrySimple(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::GeometrySimple*)
   {
      ::Garfield::GeometrySimple *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::GeometrySimple));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::GeometrySimple", "Garfield/GeometrySimple.hh", 13,
                  typeid(::Garfield::GeometrySimple), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLGeometrySimple_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::GeometrySimple) );
      instance.SetNew(&new_GarfieldcLcLGeometrySimple);
      instance.SetNewArray(&newArray_GarfieldcLcLGeometrySimple);
      instance.SetDelete(&delete_GarfieldcLcLGeometrySimple);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLGeometrySimple);
      instance.SetDestructor(&destruct_GarfieldcLcLGeometrySimple);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::GeometrySimple*)
   {
      return GenerateInitInstanceLocal((::Garfield::GeometrySimple*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::GeometrySimple*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLGeometrySimple_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::GeometrySimple*)0x0)->GetClass();
      GarfieldcLcLGeometrySimple_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLGeometrySimple_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLMediumGas_Dictionary();
   static void GarfieldcLcLMediumGas_TClassManip(TClass*);
   static void *new_GarfieldcLcLMediumGas(void *p = 0);
   static void *newArray_GarfieldcLcLMediumGas(Long_t size, void *p);
   static void delete_GarfieldcLcLMediumGas(void *p);
   static void deleteArray_GarfieldcLcLMediumGas(void *p);
   static void destruct_GarfieldcLcLMediumGas(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::MediumGas*)
   {
      ::Garfield::MediumGas *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::MediumGas));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::MediumGas", "Garfield/MediumGas.hh", 15,
                  typeid(::Garfield::MediumGas), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLMediumGas_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::MediumGas) );
      instance.SetNew(&new_GarfieldcLcLMediumGas);
      instance.SetNewArray(&newArray_GarfieldcLcLMediumGas);
      instance.SetDelete(&delete_GarfieldcLcLMediumGas);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLMediumGas);
      instance.SetDestructor(&destruct_GarfieldcLcLMediumGas);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::MediumGas*)
   {
      return GenerateInitInstanceLocal((::Garfield::MediumGas*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::MediumGas*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLMediumGas_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::MediumGas*)0x0)->GetClass();
      GarfieldcLcLMediumGas_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLMediumGas_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLMediumMagboltz_Dictionary();
   static void GarfieldcLcLMediumMagboltz_TClassManip(TClass*);
   static void *new_GarfieldcLcLMediumMagboltz(void *p = 0);
   static void *newArray_GarfieldcLcLMediumMagboltz(Long_t size, void *p);
   static void delete_GarfieldcLcLMediumMagboltz(void *p);
   static void deleteArray_GarfieldcLcLMediumMagboltz(void *p);
   static void destruct_GarfieldcLcLMediumMagboltz(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::MediumMagboltz*)
   {
      ::Garfield::MediumMagboltz *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::MediumMagboltz));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::MediumMagboltz", "Garfield/MediumMagboltz.hh", 15,
                  typeid(::Garfield::MediumMagboltz), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLMediumMagboltz_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::MediumMagboltz) );
      instance.SetNew(&new_GarfieldcLcLMediumMagboltz);
      instance.SetNewArray(&newArray_GarfieldcLcLMediumMagboltz);
      instance.SetDelete(&delete_GarfieldcLcLMediumMagboltz);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLMediumMagboltz);
      instance.SetDestructor(&destruct_GarfieldcLcLMediumMagboltz);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::MediumMagboltz*)
   {
      return GenerateInitInstanceLocal((::Garfield::MediumMagboltz*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::MediumMagboltz*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLMediumMagboltz_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::MediumMagboltz*)0x0)->GetClass();
      GarfieldcLcLMediumMagboltz_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLMediumMagboltz_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLMediumSilicon_Dictionary();
   static void GarfieldcLcLMediumSilicon_TClassManip(TClass*);
   static void *new_GarfieldcLcLMediumSilicon(void *p = 0);
   static void *newArray_GarfieldcLcLMediumSilicon(Long_t size, void *p);
   static void delete_GarfieldcLcLMediumSilicon(void *p);
   static void deleteArray_GarfieldcLcLMediumSilicon(void *p);
   static void destruct_GarfieldcLcLMediumSilicon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::MediumSilicon*)
   {
      ::Garfield::MediumSilicon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::MediumSilicon));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::MediumSilicon", "Garfield/MediumSilicon.hh", 9,
                  typeid(::Garfield::MediumSilicon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLMediumSilicon_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::MediumSilicon) );
      instance.SetNew(&new_GarfieldcLcLMediumSilicon);
      instance.SetNewArray(&newArray_GarfieldcLcLMediumSilicon);
      instance.SetDelete(&delete_GarfieldcLcLMediumSilicon);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLMediumSilicon);
      instance.SetDestructor(&destruct_GarfieldcLcLMediumSilicon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::MediumSilicon*)
   {
      return GenerateInitInstanceLocal((::Garfield::MediumSilicon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::MediumSilicon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLMediumSilicon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::MediumSilicon*)0x0)->GetClass();
      GarfieldcLcLMediumSilicon_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLMediumSilicon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLOpticalData_Dictionary();
   static void GarfieldcLcLOpticalData_TClassManip(TClass*);
   static void *new_GarfieldcLcLOpticalData(void *p = 0);
   static void *newArray_GarfieldcLcLOpticalData(Long_t size, void *p);
   static void delete_GarfieldcLcLOpticalData(void *p);
   static void deleteArray_GarfieldcLcLOpticalData(void *p);
   static void destruct_GarfieldcLcLOpticalData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::OpticalData*)
   {
      ::Garfield::OpticalData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::OpticalData));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::OpticalData", "Garfield/OpticalData.hh", 11,
                  typeid(::Garfield::OpticalData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLOpticalData_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::OpticalData) );
      instance.SetNew(&new_GarfieldcLcLOpticalData);
      instance.SetNewArray(&newArray_GarfieldcLcLOpticalData);
      instance.SetDelete(&delete_GarfieldcLcLOpticalData);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLOpticalData);
      instance.SetDestructor(&destruct_GarfieldcLcLOpticalData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::OpticalData*)
   {
      return GenerateInitInstanceLocal((::Garfield::OpticalData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::OpticalData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLOpticalData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::OpticalData*)0x0)->GetClass();
      GarfieldcLcLOpticalData_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLOpticalData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLSolidBox_Dictionary();
   static void GarfieldcLcLSolidBox_TClassManip(TClass*);
   static void delete_GarfieldcLcLSolidBox(void *p);
   static void deleteArray_GarfieldcLcLSolidBox(void *p);
   static void destruct_GarfieldcLcLSolidBox(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::SolidBox*)
   {
      ::Garfield::SolidBox *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::SolidBox));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::SolidBox", "Garfield/SolidBox.hh", 10,
                  typeid(::Garfield::SolidBox), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLSolidBox_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::SolidBox) );
      instance.SetDelete(&delete_GarfieldcLcLSolidBox);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLSolidBox);
      instance.SetDestructor(&destruct_GarfieldcLcLSolidBox);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::SolidBox*)
   {
      return GenerateInitInstanceLocal((::Garfield::SolidBox*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::SolidBox*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLSolidBox_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::SolidBox*)0x0)->GetClass();
      GarfieldcLcLSolidBox_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLSolidBox_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLSolidTube_Dictionary();
   static void GarfieldcLcLSolidTube_TClassManip(TClass*);
   static void delete_GarfieldcLcLSolidTube(void *p);
   static void deleteArray_GarfieldcLcLSolidTube(void *p);
   static void destruct_GarfieldcLcLSolidTube(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::SolidTube*)
   {
      ::Garfield::SolidTube *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::SolidTube));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::SolidTube", "Garfield/SolidTube.hh", 10,
                  typeid(::Garfield::SolidTube), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLSolidTube_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::SolidTube) );
      instance.SetDelete(&delete_GarfieldcLcLSolidTube);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLSolidTube);
      instance.SetDestructor(&destruct_GarfieldcLcLSolidTube);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::SolidTube*)
   {
      return GenerateInitInstanceLocal((::Garfield::SolidTube*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::SolidTube*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLSolidTube_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::SolidTube*)0x0)->GetClass();
      GarfieldcLcLSolidTube_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLSolidTube_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLTrack_Dictionary();
   static void GarfieldcLcLTrack_TClassManip(TClass*);
   static void delete_GarfieldcLcLTrack(void *p);
   static void deleteArray_GarfieldcLcLTrack(void *p);
   static void destruct_GarfieldcLcLTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::Track*)
   {
      ::Garfield::Track *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::Track));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::Track", "Garfield/Track.hh", 14,
                  typeid(::Garfield::Track), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLTrack_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::Track) );
      instance.SetDelete(&delete_GarfieldcLcLTrack);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLTrack);
      instance.SetDestructor(&destruct_GarfieldcLcLTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::Track*)
   {
      return GenerateInitInstanceLocal((::Garfield::Track*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::Track*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLTrack_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::Track*)0x0)->GetClass();
      GarfieldcLcLTrack_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLTrack_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLTrackBichsel_Dictionary();
   static void GarfieldcLcLTrackBichsel_TClassManip(TClass*);
   static void *new_GarfieldcLcLTrackBichsel(void *p = 0);
   static void *newArray_GarfieldcLcLTrackBichsel(Long_t size, void *p);
   static void delete_GarfieldcLcLTrackBichsel(void *p);
   static void deleteArray_GarfieldcLcLTrackBichsel(void *p);
   static void destruct_GarfieldcLcLTrackBichsel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::TrackBichsel*)
   {
      ::Garfield::TrackBichsel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::TrackBichsel));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::TrackBichsel", "Garfield/TrackBichsel.hh", 14,
                  typeid(::Garfield::TrackBichsel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLTrackBichsel_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::TrackBichsel) );
      instance.SetNew(&new_GarfieldcLcLTrackBichsel);
      instance.SetNewArray(&newArray_GarfieldcLcLTrackBichsel);
      instance.SetDelete(&delete_GarfieldcLcLTrackBichsel);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLTrackBichsel);
      instance.SetDestructor(&destruct_GarfieldcLcLTrackBichsel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::TrackBichsel*)
   {
      return GenerateInitInstanceLocal((::Garfield::TrackBichsel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::TrackBichsel*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLTrackBichsel_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::TrackBichsel*)0x0)->GetClass();
      GarfieldcLcLTrackBichsel_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLTrackBichsel_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLTrackElectron_Dictionary();
   static void GarfieldcLcLTrackElectron_TClassManip(TClass*);
   static void *new_GarfieldcLcLTrackElectron(void *p = 0);
   static void *newArray_GarfieldcLcLTrackElectron(Long_t size, void *p);
   static void delete_GarfieldcLcLTrackElectron(void *p);
   static void deleteArray_GarfieldcLcLTrackElectron(void *p);
   static void destruct_GarfieldcLcLTrackElectron(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::TrackElectron*)
   {
      ::Garfield::TrackElectron *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::TrackElectron));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::TrackElectron", "Garfield/TrackElectron.hh", 13,
                  typeid(::Garfield::TrackElectron), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLTrackElectron_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::TrackElectron) );
      instance.SetNew(&new_GarfieldcLcLTrackElectron);
      instance.SetNewArray(&newArray_GarfieldcLcLTrackElectron);
      instance.SetDelete(&delete_GarfieldcLcLTrackElectron);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLTrackElectron);
      instance.SetDestructor(&destruct_GarfieldcLcLTrackElectron);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::TrackElectron*)
   {
      return GenerateInitInstanceLocal((::Garfield::TrackElectron*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::TrackElectron*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLTrackElectron_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::TrackElectron*)0x0)->GetClass();
      GarfieldcLcLTrackElectron_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLTrackElectron_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLTrackHeed_Dictionary();
   static void GarfieldcLcLTrackHeed_TClassManip(TClass*);
   static void *new_GarfieldcLcLTrackHeed(void *p = 0);
   static void *newArray_GarfieldcLcLTrackHeed(Long_t size, void *p);
   static void delete_GarfieldcLcLTrackHeed(void *p);
   static void deleteArray_GarfieldcLcLTrackHeed(void *p);
   static void destruct_GarfieldcLcLTrackHeed(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::TrackHeed*)
   {
      ::Garfield::TrackHeed *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::TrackHeed));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::TrackHeed", "Garfield/TrackHeed.hh", 35,
                  typeid(::Garfield::TrackHeed), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLTrackHeed_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::TrackHeed) );
      instance.SetNew(&new_GarfieldcLcLTrackHeed);
      instance.SetNewArray(&newArray_GarfieldcLcLTrackHeed);
      instance.SetDelete(&delete_GarfieldcLcLTrackHeed);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLTrackHeed);
      instance.SetDestructor(&destruct_GarfieldcLcLTrackHeed);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::TrackHeed*)
   {
      return GenerateInitInstanceLocal((::Garfield::TrackHeed*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::TrackHeed*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLTrackHeed_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::TrackHeed*)0x0)->GetClass();
      GarfieldcLcLTrackHeed_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLTrackHeed_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLTrackPAI_Dictionary();
   static void GarfieldcLcLTrackPAI_TClassManip(TClass*);
   static void *new_GarfieldcLcLTrackPAI(void *p = 0);
   static void *newArray_GarfieldcLcLTrackPAI(Long_t size, void *p);
   static void delete_GarfieldcLcLTrackPAI(void *p);
   static void deleteArray_GarfieldcLcLTrackPAI(void *p);
   static void destruct_GarfieldcLcLTrackPAI(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::TrackPAI*)
   {
      ::Garfield::TrackPAI *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::TrackPAI));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::TrackPAI", "Garfield/TrackPAI.hh", 13,
                  typeid(::Garfield::TrackPAI), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLTrackPAI_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::TrackPAI) );
      instance.SetNew(&new_GarfieldcLcLTrackPAI);
      instance.SetNewArray(&newArray_GarfieldcLcLTrackPAI);
      instance.SetDelete(&delete_GarfieldcLcLTrackPAI);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLTrackPAI);
      instance.SetDestructor(&destruct_GarfieldcLcLTrackPAI);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::TrackPAI*)
   {
      return GenerateInitInstanceLocal((::Garfield::TrackPAI*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::TrackPAI*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLTrackPAI_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::TrackPAI*)0x0)->GetClass();
      GarfieldcLcLTrackPAI_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLTrackPAI_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLViewCell_Dictionary();
   static void GarfieldcLcLViewCell_TClassManip(TClass*);
   static void *new_GarfieldcLcLViewCell(void *p = 0);
   static void *newArray_GarfieldcLcLViewCell(Long_t size, void *p);
   static void delete_GarfieldcLcLViewCell(void *p);
   static void deleteArray_GarfieldcLcLViewCell(void *p);
   static void destruct_GarfieldcLcLViewCell(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ViewCell*)
   {
      ::Garfield::ViewCell *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ViewCell));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ViewCell", "Garfield/ViewCell.hh", 18,
                  typeid(::Garfield::ViewCell), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLViewCell_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ViewCell) );
      instance.SetNew(&new_GarfieldcLcLViewCell);
      instance.SetNewArray(&newArray_GarfieldcLcLViewCell);
      instance.SetDelete(&delete_GarfieldcLcLViewCell);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLViewCell);
      instance.SetDestructor(&destruct_GarfieldcLcLViewCell);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ViewCell*)
   {
      return GenerateInitInstanceLocal((::Garfield::ViewCell*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ViewCell*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLViewCell_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ViewCell*)0x0)->GetClass();
      GarfieldcLcLViewCell_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLViewCell_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLViewField_Dictionary();
   static void GarfieldcLcLViewField_TClassManip(TClass*);
   static void *new_GarfieldcLcLViewField(void *p = 0);
   static void *newArray_GarfieldcLcLViewField(Long_t size, void *p);
   static void delete_GarfieldcLcLViewField(void *p);
   static void deleteArray_GarfieldcLcLViewField(void *p);
   static void destruct_GarfieldcLcLViewField(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ViewField*)
   {
      ::Garfield::ViewField *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ViewField));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ViewField", "Garfield/ViewField.hh", 15,
                  typeid(::Garfield::ViewField), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLViewField_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ViewField) );
      instance.SetNew(&new_GarfieldcLcLViewField);
      instance.SetNewArray(&newArray_GarfieldcLcLViewField);
      instance.SetDelete(&delete_GarfieldcLcLViewField);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLViewField);
      instance.SetDestructor(&destruct_GarfieldcLcLViewField);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ViewField*)
   {
      return GenerateInitInstanceLocal((::Garfield::ViewField*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ViewField*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLViewField_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ViewField*)0x0)->GetClass();
      GarfieldcLcLViewField_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLViewField_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLViewGeometry_Dictionary();
   static void GarfieldcLcLViewGeometry_TClassManip(TClass*);
   static void *new_GarfieldcLcLViewGeometry(void *p = 0);
   static void *newArray_GarfieldcLcLViewGeometry(Long_t size, void *p);
   static void delete_GarfieldcLcLViewGeometry(void *p);
   static void deleteArray_GarfieldcLcLViewGeometry(void *p);
   static void destruct_GarfieldcLcLViewGeometry(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ViewGeometry*)
   {
      ::Garfield::ViewGeometry *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ViewGeometry));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ViewGeometry", "Garfield/ViewGeometry.hh", 18,
                  typeid(::Garfield::ViewGeometry), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLViewGeometry_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ViewGeometry) );
      instance.SetNew(&new_GarfieldcLcLViewGeometry);
      instance.SetNewArray(&newArray_GarfieldcLcLViewGeometry);
      instance.SetDelete(&delete_GarfieldcLcLViewGeometry);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLViewGeometry);
      instance.SetDestructor(&destruct_GarfieldcLcLViewGeometry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ViewGeometry*)
   {
      return GenerateInitInstanceLocal((::Garfield::ViewGeometry*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ViewGeometry*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLViewGeometry_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ViewGeometry*)0x0)->GetClass();
      GarfieldcLcLViewGeometry_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLViewGeometry_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLViewMedium_Dictionary();
   static void GarfieldcLcLViewMedium_TClassManip(TClass*);
   static void *new_GarfieldcLcLViewMedium(void *p = 0);
   static void *newArray_GarfieldcLcLViewMedium(Long_t size, void *p);
   static void delete_GarfieldcLcLViewMedium(void *p);
   static void deleteArray_GarfieldcLcLViewMedium(void *p);
   static void destruct_GarfieldcLcLViewMedium(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ViewMedium*)
   {
      ::Garfield::ViewMedium *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ViewMedium));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ViewMedium", "Garfield/ViewMedium.hh", 17,
                  typeid(::Garfield::ViewMedium), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLViewMedium_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ViewMedium) );
      instance.SetNew(&new_GarfieldcLcLViewMedium);
      instance.SetNewArray(&newArray_GarfieldcLcLViewMedium);
      instance.SetDelete(&delete_GarfieldcLcLViewMedium);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLViewMedium);
      instance.SetDestructor(&destruct_GarfieldcLcLViewMedium);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ViewMedium*)
   {
      return GenerateInitInstanceLocal((::Garfield::ViewMedium*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ViewMedium*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLViewMedium_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ViewMedium*)0x0)->GetClass();
      GarfieldcLcLViewMedium_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLViewMedium_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *GarfieldcLcLViewSignal_Dictionary();
   static void GarfieldcLcLViewSignal_TClassManip(TClass*);
   static void *new_GarfieldcLcLViewSignal(void *p = 0);
   static void *newArray_GarfieldcLcLViewSignal(Long_t size, void *p);
   static void delete_GarfieldcLcLViewSignal(void *p);
   static void deleteArray_GarfieldcLcLViewSignal(void *p);
   static void destruct_GarfieldcLcLViewSignal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Garfield::ViewSignal*)
   {
      ::Garfield::ViewSignal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Garfield::ViewSignal));
      static ::ROOT::TGenericClassInfo 
         instance("Garfield::ViewSignal", "Garfield/ViewSignal.hh", 19,
                  typeid(::Garfield::ViewSignal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &GarfieldcLcLViewSignal_Dictionary, isa_proxy, 0,
                  sizeof(::Garfield::ViewSignal) );
      instance.SetNew(&new_GarfieldcLcLViewSignal);
      instance.SetNewArray(&newArray_GarfieldcLcLViewSignal);
      instance.SetDelete(&delete_GarfieldcLcLViewSignal);
      instance.SetDeleteArray(&deleteArray_GarfieldcLcLViewSignal);
      instance.SetDestructor(&destruct_GarfieldcLcLViewSignal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Garfield::ViewSignal*)
   {
      return GenerateInitInstanceLocal((::Garfield::ViewSignal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Garfield::ViewSignal*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *GarfieldcLcLViewSignal_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Garfield::ViewSignal*)0x0)->GetClass();
      GarfieldcLcLViewSignal_TClassManip(theClass);
   return theClass;
   }

   static void GarfieldcLcLViewSignal_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLMedium(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::Medium : new ::Garfield::Medium;
   }
   static void *newArray_GarfieldcLcLMedium(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::Medium[nElements] : new ::Garfield::Medium[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLMedium(void *p) {
      delete ((::Garfield::Medium*)p);
   }
   static void deleteArray_GarfieldcLcLMedium(void *p) {
      delete [] ((::Garfield::Medium*)p);
   }
   static void destruct_GarfieldcLcLMedium(void *p) {
      typedef ::Garfield::Medium current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::Medium

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GarfieldcLcLSolid(void *p) {
      delete ((::Garfield::Solid*)p);
   }
   static void deleteArray_GarfieldcLcLSolid(void *p) {
      delete [] ((::Garfield::Solid*)p);
   }
   static void destruct_GarfieldcLcLSolid(void *p) {
      typedef ::Garfield::Solid current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::Solid

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GarfieldcLcLGeometry(void *p) {
      delete ((::Garfield::Geometry*)p);
   }
   static void deleteArray_GarfieldcLcLGeometry(void *p) {
      delete [] ((::Garfield::Geometry*)p);
   }
   static void destruct_GarfieldcLcLGeometry(void *p) {
      typedef ::Garfield::Geometry current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::Geometry

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GarfieldcLcLComponent(void *p) {
      delete ((::Garfield::Component*)p);
   }
   static void deleteArray_GarfieldcLcLComponent(void *p) {
      delete [] ((::Garfield::Component*)p);
   }
   static void destruct_GarfieldcLcLComponent(void *p) {
      typedef ::Garfield::Component current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::Component

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLSensor(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::Sensor : new ::Garfield::Sensor;
   }
   static void *newArray_GarfieldcLcLSensor(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::Sensor[nElements] : new ::Garfield::Sensor[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLSensor(void *p) {
      delete ((::Garfield::Sensor*)p);
   }
   static void deleteArray_GarfieldcLcLSensor(void *p) {
      delete [] ((::Garfield::Sensor*)p);
   }
   static void destruct_GarfieldcLcLSensor(void *p) {
      typedef ::Garfield::Sensor current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::Sensor

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLViewDrift(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewDrift : new ::Garfield::ViewDrift;
   }
   static void *newArray_GarfieldcLcLViewDrift(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewDrift[nElements] : new ::Garfield::ViewDrift[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLViewDrift(void *p) {
      delete ((::Garfield::ViewDrift*)p);
   }
   static void deleteArray_GarfieldcLcLViewDrift(void *p) {
      delete [] ((::Garfield::ViewDrift*)p);
   }
   static void destruct_GarfieldcLcLViewDrift(void *p) {
      typedef ::Garfield::ViewDrift current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ViewDrift

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLAvalancheMC(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::AvalancheMC : new ::Garfield::AvalancheMC;
   }
   static void *newArray_GarfieldcLcLAvalancheMC(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::AvalancheMC[nElements] : new ::Garfield::AvalancheMC[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLAvalancheMC(void *p) {
      delete ((::Garfield::AvalancheMC*)p);
   }
   static void deleteArray_GarfieldcLcLAvalancheMC(void *p) {
      delete [] ((::Garfield::AvalancheMC*)p);
   }
   static void destruct_GarfieldcLcLAvalancheMC(void *p) {
      typedef ::Garfield::AvalancheMC current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::AvalancheMC

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLAvalancheMicroscopic(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::AvalancheMicroscopic : new ::Garfield::AvalancheMicroscopic;
   }
   static void *newArray_GarfieldcLcLAvalancheMicroscopic(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::AvalancheMicroscopic[nElements] : new ::Garfield::AvalancheMicroscopic[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLAvalancheMicroscopic(void *p) {
      delete ((::Garfield::AvalancheMicroscopic*)p);
   }
   static void deleteArray_GarfieldcLcLAvalancheMicroscopic(void *p) {
      delete [] ((::Garfield::AvalancheMicroscopic*)p);
   }
   static void destruct_GarfieldcLcLAvalancheMicroscopic(void *p) {
      typedef ::Garfield::AvalancheMicroscopic current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::AvalancheMicroscopic

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLComponentAnalyticField(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentAnalyticField : new ::Garfield::ComponentAnalyticField;
   }
   static void *newArray_GarfieldcLcLComponentAnalyticField(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentAnalyticField[nElements] : new ::Garfield::ComponentAnalyticField[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLComponentAnalyticField(void *p) {
      delete ((::Garfield::ComponentAnalyticField*)p);
   }
   static void deleteArray_GarfieldcLcLComponentAnalyticField(void *p) {
      delete [] ((::Garfield::ComponentAnalyticField*)p);
   }
   static void destruct_GarfieldcLcLComponentAnalyticField(void *p) {
      typedef ::Garfield::ComponentAnalyticField current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ComponentAnalyticField

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GarfieldcLcLComponentFieldMap(void *p) {
      delete ((::Garfield::ComponentFieldMap*)p);
   }
   static void deleteArray_GarfieldcLcLComponentFieldMap(void *p) {
      delete [] ((::Garfield::ComponentFieldMap*)p);
   }
   static void destruct_GarfieldcLcLComponentFieldMap(void *p) {
      typedef ::Garfield::ComponentFieldMap current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ComponentFieldMap

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLComponentAnsys121(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentAnsys121 : new ::Garfield::ComponentAnsys121;
   }
   static void *newArray_GarfieldcLcLComponentAnsys121(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentAnsys121[nElements] : new ::Garfield::ComponentAnsys121[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLComponentAnsys121(void *p) {
      delete ((::Garfield::ComponentAnsys121*)p);
   }
   static void deleteArray_GarfieldcLcLComponentAnsys121(void *p) {
      delete [] ((::Garfield::ComponentAnsys121*)p);
   }
   static void destruct_GarfieldcLcLComponentAnsys121(void *p) {
      typedef ::Garfield::ComponentAnsys121 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ComponentAnsys121

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLComponentAnsys123(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentAnsys123 : new ::Garfield::ComponentAnsys123;
   }
   static void *newArray_GarfieldcLcLComponentAnsys123(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentAnsys123[nElements] : new ::Garfield::ComponentAnsys123[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLComponentAnsys123(void *p) {
      delete ((::Garfield::ComponentAnsys123*)p);
   }
   static void deleteArray_GarfieldcLcLComponentAnsys123(void *p) {
      delete [] ((::Garfield::ComponentAnsys123*)p);
   }
   static void destruct_GarfieldcLcLComponentAnsys123(void *p) {
      typedef ::Garfield::ComponentAnsys123 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ComponentAnsys123

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLComponentCST(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentCST : new ::Garfield::ComponentCST;
   }
   static void *newArray_GarfieldcLcLComponentCST(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentCST[nElements] : new ::Garfield::ComponentCST[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLComponentCST(void *p) {
      delete ((::Garfield::ComponentCST*)p);
   }
   static void deleteArray_GarfieldcLcLComponentCST(void *p) {
      delete [] ((::Garfield::ComponentCST*)p);
   }
   static void destruct_GarfieldcLcLComponentCST(void *p) {
      typedef ::Garfield::ComponentCST current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ComponentCST

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLComponentConstant(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentConstant : new ::Garfield::ComponentConstant;
   }
   static void *newArray_GarfieldcLcLComponentConstant(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentConstant[nElements] : new ::Garfield::ComponentConstant[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLComponentConstant(void *p) {
      delete ((::Garfield::ComponentConstant*)p);
   }
   static void deleteArray_GarfieldcLcLComponentConstant(void *p) {
      delete [] ((::Garfield::ComponentConstant*)p);
   }
   static void destruct_GarfieldcLcLComponentConstant(void *p) {
      typedef ::Garfield::ComponentConstant current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ComponentConstant

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLComponentUser(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentUser : new ::Garfield::ComponentUser;
   }
   static void *newArray_GarfieldcLcLComponentUser(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ComponentUser[nElements] : new ::Garfield::ComponentUser[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLComponentUser(void *p) {
      delete ((::Garfield::ComponentUser*)p);
   }
   static void deleteArray_GarfieldcLcLComponentUser(void *p) {
      delete [] ((::Garfield::ComponentUser*)p);
   }
   static void destruct_GarfieldcLcLComponentUser(void *p) {
      typedef ::Garfield::ComponentUser current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ComponentUser

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLGeometryRoot(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::GeometryRoot : new ::Garfield::GeometryRoot;
   }
   static void *newArray_GarfieldcLcLGeometryRoot(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::GeometryRoot[nElements] : new ::Garfield::GeometryRoot[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLGeometryRoot(void *p) {
      delete ((::Garfield::GeometryRoot*)p);
   }
   static void deleteArray_GarfieldcLcLGeometryRoot(void *p) {
      delete [] ((::Garfield::GeometryRoot*)p);
   }
   static void destruct_GarfieldcLcLGeometryRoot(void *p) {
      typedef ::Garfield::GeometryRoot current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::GeometryRoot

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLGeometrySimple(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::GeometrySimple : new ::Garfield::GeometrySimple;
   }
   static void *newArray_GarfieldcLcLGeometrySimple(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::GeometrySimple[nElements] : new ::Garfield::GeometrySimple[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLGeometrySimple(void *p) {
      delete ((::Garfield::GeometrySimple*)p);
   }
   static void deleteArray_GarfieldcLcLGeometrySimple(void *p) {
      delete [] ((::Garfield::GeometrySimple*)p);
   }
   static void destruct_GarfieldcLcLGeometrySimple(void *p) {
      typedef ::Garfield::GeometrySimple current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::GeometrySimple

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLMediumGas(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::MediumGas : new ::Garfield::MediumGas;
   }
   static void *newArray_GarfieldcLcLMediumGas(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::MediumGas[nElements] : new ::Garfield::MediumGas[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLMediumGas(void *p) {
      delete ((::Garfield::MediumGas*)p);
   }
   static void deleteArray_GarfieldcLcLMediumGas(void *p) {
      delete [] ((::Garfield::MediumGas*)p);
   }
   static void destruct_GarfieldcLcLMediumGas(void *p) {
      typedef ::Garfield::MediumGas current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::MediumGas

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLMediumMagboltz(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::MediumMagboltz : new ::Garfield::MediumMagboltz;
   }
   static void *newArray_GarfieldcLcLMediumMagboltz(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::MediumMagboltz[nElements] : new ::Garfield::MediumMagboltz[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLMediumMagboltz(void *p) {
      delete ((::Garfield::MediumMagboltz*)p);
   }
   static void deleteArray_GarfieldcLcLMediumMagboltz(void *p) {
      delete [] ((::Garfield::MediumMagboltz*)p);
   }
   static void destruct_GarfieldcLcLMediumMagboltz(void *p) {
      typedef ::Garfield::MediumMagboltz current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::MediumMagboltz

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLMediumSilicon(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::MediumSilicon : new ::Garfield::MediumSilicon;
   }
   static void *newArray_GarfieldcLcLMediumSilicon(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::MediumSilicon[nElements] : new ::Garfield::MediumSilicon[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLMediumSilicon(void *p) {
      delete ((::Garfield::MediumSilicon*)p);
   }
   static void deleteArray_GarfieldcLcLMediumSilicon(void *p) {
      delete [] ((::Garfield::MediumSilicon*)p);
   }
   static void destruct_GarfieldcLcLMediumSilicon(void *p) {
      typedef ::Garfield::MediumSilicon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::MediumSilicon

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLOpticalData(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::OpticalData : new ::Garfield::OpticalData;
   }
   static void *newArray_GarfieldcLcLOpticalData(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::OpticalData[nElements] : new ::Garfield::OpticalData[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLOpticalData(void *p) {
      delete ((::Garfield::OpticalData*)p);
   }
   static void deleteArray_GarfieldcLcLOpticalData(void *p) {
      delete [] ((::Garfield::OpticalData*)p);
   }
   static void destruct_GarfieldcLcLOpticalData(void *p) {
      typedef ::Garfield::OpticalData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::OpticalData

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GarfieldcLcLSolidBox(void *p) {
      delete ((::Garfield::SolidBox*)p);
   }
   static void deleteArray_GarfieldcLcLSolidBox(void *p) {
      delete [] ((::Garfield::SolidBox*)p);
   }
   static void destruct_GarfieldcLcLSolidBox(void *p) {
      typedef ::Garfield::SolidBox current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::SolidBox

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GarfieldcLcLSolidTube(void *p) {
      delete ((::Garfield::SolidTube*)p);
   }
   static void deleteArray_GarfieldcLcLSolidTube(void *p) {
      delete [] ((::Garfield::SolidTube*)p);
   }
   static void destruct_GarfieldcLcLSolidTube(void *p) {
      typedef ::Garfield::SolidTube current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::SolidTube

namespace ROOT {
   // Wrapper around operator delete
   static void delete_GarfieldcLcLTrack(void *p) {
      delete ((::Garfield::Track*)p);
   }
   static void deleteArray_GarfieldcLcLTrack(void *p) {
      delete [] ((::Garfield::Track*)p);
   }
   static void destruct_GarfieldcLcLTrack(void *p) {
      typedef ::Garfield::Track current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::Track

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLTrackBichsel(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::TrackBichsel : new ::Garfield::TrackBichsel;
   }
   static void *newArray_GarfieldcLcLTrackBichsel(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::TrackBichsel[nElements] : new ::Garfield::TrackBichsel[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLTrackBichsel(void *p) {
      delete ((::Garfield::TrackBichsel*)p);
   }
   static void deleteArray_GarfieldcLcLTrackBichsel(void *p) {
      delete [] ((::Garfield::TrackBichsel*)p);
   }
   static void destruct_GarfieldcLcLTrackBichsel(void *p) {
      typedef ::Garfield::TrackBichsel current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::TrackBichsel

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLTrackElectron(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::TrackElectron : new ::Garfield::TrackElectron;
   }
   static void *newArray_GarfieldcLcLTrackElectron(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::TrackElectron[nElements] : new ::Garfield::TrackElectron[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLTrackElectron(void *p) {
      delete ((::Garfield::TrackElectron*)p);
   }
   static void deleteArray_GarfieldcLcLTrackElectron(void *p) {
      delete [] ((::Garfield::TrackElectron*)p);
   }
   static void destruct_GarfieldcLcLTrackElectron(void *p) {
      typedef ::Garfield::TrackElectron current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::TrackElectron

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLTrackHeed(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::TrackHeed : new ::Garfield::TrackHeed;
   }
   static void *newArray_GarfieldcLcLTrackHeed(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::TrackHeed[nElements] : new ::Garfield::TrackHeed[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLTrackHeed(void *p) {
      delete ((::Garfield::TrackHeed*)p);
   }
   static void deleteArray_GarfieldcLcLTrackHeed(void *p) {
      delete [] ((::Garfield::TrackHeed*)p);
   }
   static void destruct_GarfieldcLcLTrackHeed(void *p) {
      typedef ::Garfield::TrackHeed current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::TrackHeed

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLTrackPAI(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::TrackPAI : new ::Garfield::TrackPAI;
   }
   static void *newArray_GarfieldcLcLTrackPAI(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::TrackPAI[nElements] : new ::Garfield::TrackPAI[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLTrackPAI(void *p) {
      delete ((::Garfield::TrackPAI*)p);
   }
   static void deleteArray_GarfieldcLcLTrackPAI(void *p) {
      delete [] ((::Garfield::TrackPAI*)p);
   }
   static void destruct_GarfieldcLcLTrackPAI(void *p) {
      typedef ::Garfield::TrackPAI current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::TrackPAI

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLViewCell(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewCell : new ::Garfield::ViewCell;
   }
   static void *newArray_GarfieldcLcLViewCell(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewCell[nElements] : new ::Garfield::ViewCell[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLViewCell(void *p) {
      delete ((::Garfield::ViewCell*)p);
   }
   static void deleteArray_GarfieldcLcLViewCell(void *p) {
      delete [] ((::Garfield::ViewCell*)p);
   }
   static void destruct_GarfieldcLcLViewCell(void *p) {
      typedef ::Garfield::ViewCell current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ViewCell

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLViewField(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewField : new ::Garfield::ViewField;
   }
   static void *newArray_GarfieldcLcLViewField(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewField[nElements] : new ::Garfield::ViewField[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLViewField(void *p) {
      delete ((::Garfield::ViewField*)p);
   }
   static void deleteArray_GarfieldcLcLViewField(void *p) {
      delete [] ((::Garfield::ViewField*)p);
   }
   static void destruct_GarfieldcLcLViewField(void *p) {
      typedef ::Garfield::ViewField current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ViewField

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLViewGeometry(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewGeometry : new ::Garfield::ViewGeometry;
   }
   static void *newArray_GarfieldcLcLViewGeometry(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewGeometry[nElements] : new ::Garfield::ViewGeometry[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLViewGeometry(void *p) {
      delete ((::Garfield::ViewGeometry*)p);
   }
   static void deleteArray_GarfieldcLcLViewGeometry(void *p) {
      delete [] ((::Garfield::ViewGeometry*)p);
   }
   static void destruct_GarfieldcLcLViewGeometry(void *p) {
      typedef ::Garfield::ViewGeometry current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ViewGeometry

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLViewMedium(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewMedium : new ::Garfield::ViewMedium;
   }
   static void *newArray_GarfieldcLcLViewMedium(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewMedium[nElements] : new ::Garfield::ViewMedium[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLViewMedium(void *p) {
      delete ((::Garfield::ViewMedium*)p);
   }
   static void deleteArray_GarfieldcLcLViewMedium(void *p) {
      delete [] ((::Garfield::ViewMedium*)p);
   }
   static void destruct_GarfieldcLcLViewMedium(void *p) {
      typedef ::Garfield::ViewMedium current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ViewMedium

namespace ROOT {
   // Wrappers around operator new
   static void *new_GarfieldcLcLViewSignal(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewSignal : new ::Garfield::ViewSignal;
   }
   static void *newArray_GarfieldcLcLViewSignal(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Garfield::ViewSignal[nElements] : new ::Garfield::ViewSignal[nElements];
   }
   // Wrapper around operator delete
   static void delete_GarfieldcLcLViewSignal(void *p) {
      delete ((::Garfield::ViewSignal*)p);
   }
   static void deleteArray_GarfieldcLcLViewSignal(void *p) {
      delete [] ((::Garfield::ViewSignal*)p);
   }
   static void destruct_GarfieldcLcLViewSignal(void *p) {
      typedef ::Garfield::ViewSignal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Garfield::ViewSignal

namespace {
  void TriggerDictionaryInitialization_libGarfieldDict_Impl() {
    static const char* headers[] = {
"Garfield/AvalancheMC.hh",
"Garfield/AvalancheMicroscopic.hh",
"Garfield/Component.hh",
"Garfield/ComponentAnalyticField.hh",
"Garfield/ComponentAnsys121.hh",
"Garfield/ComponentAnsys123.hh",
"Garfield/ComponentCST.hh",
"Garfield/ComponentComsol.hh",
"Garfield/ComponentConstant.hh",
"Garfield/ComponentElmer.hh",
"Garfield/ComponentElmer2D.hh",
"Garfield/ComponentFieldMap.hh",
"Garfield/ComponentGrid.hh",
"Garfield/ComponentNeBem2d.hh",
"Garfield/ComponentNeBem3d.hh",
"Garfield/ComponentNeBem3dMap.hh",
"Garfield/ComponentTcad2d.hh",
"Garfield/ComponentTcad3d.hh",
"Garfield/ComponentUser.hh",
"Garfield/ComponentVoxel.hh",
"Garfield/DriftLineRKF.hh",
"Garfield/FundamentalConstants.hh",
"Garfield/GarfieldConstants.hh",
"Garfield/Geometry.hh",
"Garfield/GeometryRoot.hh",
"Garfield/GeometrySimple.hh",
"Garfield/KDTree.hh",
"Garfield/MagboltzInterface.hh",
"Garfield/Medium.hh",
"Garfield/MediumCdTe.hh",
"Garfield/MediumConductor.hh",
"Garfield/MediumGaAs.hh",
"Garfield/MediumGaN.hh",
"Garfield/MediumGas.hh",
"Garfield/MediumMagboltz.hh",
"Garfield/MediumPlastic.hh",
"Garfield/MediumSilicon.hh",
"Garfield/Numerics.hh",
"Garfield/OpticalData.hh",
"Garfield/Plotting.hh",
"Garfield/PlottingEngine.hh",
"Garfield/PlottingEngineRoot.hh",
"Garfield/Polygon.hh",
"Garfield/Random.hh",
"Garfield/RandomEngine.hh",
"Garfield/RandomEngineRoot.hh",
"Garfield/Sensor.hh",
"Garfield/Shaper.hh",
"Garfield/Solid.hh",
"Garfield/SolidBox.hh",
"Garfield/SolidExtrusion.hh",
"Garfield/SolidHole.hh",
"Garfield/SolidRidge.hh",
"Garfield/SolidSphere.hh",
"Garfield/SolidTube.hh",
"Garfield/SolidWire.hh",
"Garfield/TetrahedralTree.hh",
"Garfield/Track.hh",
"Garfield/TrackBichsel.hh",
"Garfield/TrackElectron.hh",
"Garfield/TrackHeed.hh",
"Garfield/TrackPAI.hh",
"Garfield/TrackSimple.hh",
"Garfield/TrackSrim.hh",
"Garfield/Utilities.hh",
"Garfield/ViewBase.hh",
"Garfield/ViewCell.hh",
"Garfield/ViewDrift.hh",
"Garfield/ViewFEMesh.hh",
"Garfield/ViewField.hh",
"Garfield/ViewGeometry.hh",
"Garfield/ViewIsochrons.hh",
"Garfield/ViewMedium.hh",
"Garfield/ViewSignal.hh",
0
    };
    static const char* includePaths[] = {
"/cvmfs/sft.cern.ch/lcg/releases/ROOT/v6.22.06-1d426/x86_64-centos7-gcc10-opt/include",
"/cvmfs/sft.cern.ch/lcg/views/LCG_99/x86_64-centos7-gcc10-opt/include",
"/home/user200/Software/simulationg4/garfieldpp/Include",
"/home/user200/Software/simulationg4/garfieldpp/Heed",
"/home/user200/Software/simulationg4/garfieldpp",
"/cvmfs/sft.cern.ch/lcg/releases/ROOT/v6.22.06-1d426/x86_64-centos7-gcc10-opt/include/",
"/disk/homedisk/home/user200/Software/build/garfieldpp/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libGarfieldDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace Garfield{class __attribute__((annotate("$clingAutoload$Medium.hh")))  __attribute__((annotate("$clingAutoload$Garfield/AvalancheMC.hh")))  Medium;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Solid.hh")))  __attribute__((annotate("$clingAutoload$Garfield/AvalancheMC.hh")))  Solid;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Geometry.hh")))  __attribute__((annotate("$clingAutoload$Garfield/AvalancheMC.hh")))  Geometry;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Component.hh")))  __attribute__((annotate("$clingAutoload$Garfield/AvalancheMC.hh")))  Component;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Sensor.hh")))  __attribute__((annotate("$clingAutoload$Garfield/AvalancheMC.hh")))  Sensor;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$ViewDrift.hh")))  __attribute__((annotate("$clingAutoload$Garfield/AvalancheMC.hh")))  ViewDrift;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/AvalancheMC.hh")))  AvalancheMC;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/AvalancheMicroscopic.hh")))  AvalancheMicroscopic;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ComponentAnalyticField.hh")))  ComponentAnalyticField;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$ComponentFieldMap.hh")))  __attribute__((annotate("$clingAutoload$Garfield/ComponentAnsys121.hh")))  ComponentFieldMap;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ComponentAnsys121.hh")))  ComponentAnsys121;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ComponentAnsys123.hh")))  ComponentAnsys123;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ComponentCST.hh")))  ComponentCST;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ComponentConstant.hh")))  ComponentConstant;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ComponentUser.hh")))  ComponentUser;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/GeometryRoot.hh")))  GeometryRoot;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/GeometrySimple.hh")))  GeometrySimple;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/MediumGas.hh")))  MediumGas;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/MediumMagboltz.hh")))  MediumMagboltz;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/MediumSilicon.hh")))  MediumSilicon;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/OpticalData.hh")))  OpticalData;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/SolidBox.hh")))  SolidBox;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/SolidTube.hh")))  SolidTube;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/Track.hh")))  Track;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/TrackBichsel.hh")))  TrackBichsel;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/TrackElectron.hh")))  TrackElectron;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/TrackHeed.hh")))  TrackHeed;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/TrackPAI.hh")))  TrackPAI;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ViewCell.hh")))  ViewCell;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ViewField.hh")))  ViewField;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ViewGeometry.hh")))  ViewGeometry;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ViewMedium.hh")))  ViewMedium;}
namespace Garfield{class __attribute__((annotate("$clingAutoload$Garfield/ViewSignal.hh")))  ViewSignal;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libGarfieldDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Garfield/AvalancheMC.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/Component.hh"
#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/ComponentAnsys121.hh"
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/ComponentCST.hh"
#include "Garfield/ComponentComsol.hh"
#include "Garfield/ComponentConstant.hh"
#include "Garfield/ComponentElmer.hh"
#include "Garfield/ComponentElmer2D.hh"
#include "Garfield/ComponentFieldMap.hh"
#include "Garfield/ComponentGrid.hh"
#include "Garfield/ComponentNeBem2d.hh"
#include "Garfield/ComponentNeBem3d.hh"
#include "Garfield/ComponentNeBem3dMap.hh"
#include "Garfield/ComponentTcad2d.hh"
#include "Garfield/ComponentTcad3d.hh"
#include "Garfield/ComponentUser.hh"
#include "Garfield/ComponentVoxel.hh"
#include "Garfield/DriftLineRKF.hh"
#include "Garfield/FundamentalConstants.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Geometry.hh"
#include "Garfield/GeometryRoot.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/KDTree.hh"
#include "Garfield/MagboltzInterface.hh"
#include "Garfield/Medium.hh"
#include "Garfield/MediumCdTe.hh"
#include "Garfield/MediumConductor.hh"
#include "Garfield/MediumGaAs.hh"
#include "Garfield/MediumGaN.hh"
#include "Garfield/MediumGas.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/MediumPlastic.hh"
#include "Garfield/MediumSilicon.hh"
#include "Garfield/Numerics.hh"
#include "Garfield/OpticalData.hh"
#include "Garfield/Plotting.hh"
#include "Garfield/PlottingEngine.hh"
#include "Garfield/PlottingEngineRoot.hh"
#include "Garfield/Polygon.hh"
#include "Garfield/Random.hh"
#include "Garfield/RandomEngine.hh"
#include "Garfield/RandomEngineRoot.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/Shaper.hh"
#include "Garfield/Solid.hh"
#include "Garfield/SolidBox.hh"
#include "Garfield/SolidExtrusion.hh"
#include "Garfield/SolidHole.hh"
#include "Garfield/SolidRidge.hh"
#include "Garfield/SolidSphere.hh"
#include "Garfield/SolidTube.hh"
#include "Garfield/SolidWire.hh"
#include "Garfield/TetrahedralTree.hh"
#include "Garfield/Track.hh"
#include "Garfield/TrackBichsel.hh"
#include "Garfield/TrackElectron.hh"
#include "Garfield/TrackHeed.hh"
#include "Garfield/TrackPAI.hh"
#include "Garfield/TrackSimple.hh"
#include "Garfield/TrackSrim.hh"
#include "Garfield/Utilities.hh"
#include "Garfield/ViewBase.hh"
#include "Garfield/ViewCell.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ViewGeometry.hh"
#include "Garfield/ViewIsochrons.hh"
#include "Garfield/ViewMedium.hh"
#include "Garfield/ViewSignal.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"Garfield::AvalancheMC", payloadCode, "@",
"Garfield::AvalancheMicroscopic", payloadCode, "@",
"Garfield::Component", payloadCode, "@",
"Garfield::ComponentAnalyticField", payloadCode, "@",
"Garfield::ComponentAnsys121", payloadCode, "@",
"Garfield::ComponentAnsys123", payloadCode, "@",
"Garfield::ComponentCST", payloadCode, "@",
"Garfield::ComponentConstant", payloadCode, "@",
"Garfield::ComponentFieldMap", payloadCode, "@",
"Garfield::ComponentUser", payloadCode, "@",
"Garfield::Geometry", payloadCode, "@",
"Garfield::GeometryRoot", payloadCode, "@",
"Garfield::GeometrySimple", payloadCode, "@",
"Garfield::Medium", payloadCode, "@",
"Garfield::MediumGas", payloadCode, "@",
"Garfield::MediumMagboltz", payloadCode, "@",
"Garfield::MediumSilicon", payloadCode, "@",
"Garfield::OpticalData", payloadCode, "@",
"Garfield::RndmUniform", payloadCode, "@",
"Garfield::Sensor", payloadCode, "@",
"Garfield::Solid", payloadCode, "@",
"Garfield::SolidBox", payloadCode, "@",
"Garfield::SolidTube", payloadCode, "@",
"Garfield::Track", payloadCode, "@",
"Garfield::TrackBichsel", payloadCode, "@",
"Garfield::TrackElectron", payloadCode, "@",
"Garfield::TrackHeed", payloadCode, "@",
"Garfield::TrackPAI", payloadCode, "@",
"Garfield::ViewCell", payloadCode, "@",
"Garfield::ViewDrift", payloadCode, "@",
"Garfield::ViewField", payloadCode, "@",
"Garfield::ViewGeometry", payloadCode, "@",
"Garfield::ViewMedium", payloadCode, "@",
"Garfield::ViewSignal", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libGarfieldDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libGarfieldDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libGarfieldDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libGarfieldDict() {
  TriggerDictionaryInitialization_libGarfieldDict_Impl();
}
