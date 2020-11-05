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

class FVScalarRANSDiffusion : public FVFluxKernel
{
public:
  static InputParameters validParams();

  FVScalarRANSDiffusion(const InputParameters & params);

protected:
  ADReal computeQpResidual() override;

  std::vector<BoundaryName> _wall_boundary_names;

  // A cache of wall distances indexed per face (actually indexed per pair of
  // element pointers bounding that face).
  std::unordered_map<const Elem *, std::unordered_map<const Elem *, Real>>
    _dist_map;

  const ADVariableValue & _visc;
};
