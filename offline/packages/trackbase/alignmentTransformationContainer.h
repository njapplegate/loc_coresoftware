#ifndef TRACKBASE_ALIGNMENTTRANSFORMATIONCONTAINER_H
#define TRACKBASE_ALIGNMENTTRANSFORMATIONCONTAINER_H

/**
 * @file trackbase/alignmentTranformationContainer
 * @author R. Boucher
 * @date August 2022
 * @brief Storage class for alignment transformation to node tree
 */

#include "ActsGeometry.h"
#include "TrkrDefs.h"

#include <phool/PHObject.h>

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <iostream>              // for cout, ostream
#include <map>
#include <utility>               // for pair



/**
 * @brief Container class for Alignment transformations
 *
 * Association object holding transformations associated with given tracker hitset
 */
class alignmentTransformationContainer : public Acts::GeometryContext
{
  
  public:

  alignmentTransformationContainer() = default;

  virtual ~alignmentTransformationContainer(){}

  void Reset(); 

  void identify(std::ostream &os = std::cout);  

  void addTransform(Acts::GeometryIdentifier, Acts::Transform3); 

  void removeTransform(Acts::GeometryIdentifier id); 
  
  Acts::Transform3& getTransform(Acts::GeometryIdentifier id);

  const std::map<Acts::GeometryIdentifier, Acts::Transform3> getMap();

  void set();

  static bool use_alignment;

  private:
  
  std::map<Acts::GeometryIdentifier, Acts::Transform3> transformMap;
  
  ClassDef(alignmentTransformationContainer,1);

};

#endif //TRACKBASE_ALIGNMENTTRANSFORMATIONCONTAINER_H