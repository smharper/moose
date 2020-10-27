//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "FVFluxKernel.h"

class FVRANSDiffusion : public FVFluxKernel
{
public:
  static InputParameters validParams();

  FVRANSDiffusion(const InputParameters & params);

protected:
  ADReal computeQpResidual() override;

  std::vector<BoundaryName> _wall_boundary_names;

  const ADMaterialProperty<Real> & _rho_elem;
  const ADMaterialProperty<Real> & _rho_neighbor;
};
