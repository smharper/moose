//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "INSFVRANSDiffusion.h"

registerMooseObject("NavierStokesApp", INSFVRANSDiffusion);

InputParameters
INSFVRANSDiffusion::validParams()
{
  InputParameters params = FVFluxKernel::validParams();
  params.addRequiredCoupledVar("mixing_length", "Turbulent eddy mixing length.");
  params.addParam<Real>("rho", "fluid density");
  params.set<unsigned short>("ghost_layers") = 2;
  return params;
}

INSFVRANSDiffusion::INSFVRANSDiffusion(const InputParameters & params)
  : FVFluxKernel(params),
    _mixing_len(coupledValue("mixing_length")),
    _rho(getParam<Real>("rho"))
{
}

ADReal
INSFVRANSDiffusion::computeQpResidual()
{
  Real mixing_len = _mixing_len[_qp];

  // Compute the eddy viscosity.
  // TODO: Why are there nan's in the grad_u.norm() derivative terms?  In the
  // meantime, just use the value.
  ADReal grad_u_norm = _var.adGradSln(*_face_info).norm().value();
  ADReal eddy_visc = grad_u_norm * mixing_len * mixing_len;

  // Return the turbulent viscosity contribution to the momentum equation.
  auto dudn = gradUDotNormal();
  return -1 * _rho * eddy_visc * dudn;
}
