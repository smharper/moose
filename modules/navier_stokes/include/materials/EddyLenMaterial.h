#pragma once

#include "Material.h"
//#include "BoundaryRestrictableRequired.h"

class EddyLenMaterial : public Material
{
public:
  static InputParameters validParams();

  EddyLenMaterial(const InputParameters & parameters);

protected:
  void initQpStatefulProperties() override
  {computeQpProperties();}

  void computeQpProperties() override;

  GenericMaterialProperty<Real, true> * _property;

  std::vector<BoundaryName> _boundary_names;
  //std::set<BoundaryID> _bnd_ids;
};
