//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "FVScalarRANSDiffusion.h"

registerMooseObject("NavierStokesApp", FVScalarRANSDiffusion);

InputParameters
FVScalarRANSDiffusion::validParams()
{
  InputParameters params = FVFluxKernel::validParams();
  params.addRequiredCoupledVar("eddy_viscosity", "The turbulent eddy viscosity.");
  params.set<unsigned short>("ghost_layers") = 2;
  return params;
}

FVScalarRANSDiffusion::FVScalarRANSDiffusion(const InputParameters & params)
  : FVFluxKernel(params),
    _eddy_visc(coupledValue("eddy_viscosity"))
{
}

ADReal
FVScalarRANSDiffusion::computeQpResidual()
{
  auto dudn = gradUDotNormal();
  return -1 * _eddy_visc[_qp] * dudn;
}
