//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MixingLengthEddyViscosityAux.h"

registerMooseObject("MooseApp", MixingLengthEddyViscosityAux);

defineLegacyParams(MixingLengthEddyViscosityAux);

InputParameters
MixingLengthEddyViscosityAux::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("u", "The velocity in the x direction.");
  params.addCoupledVar("v", "The velocity in the y direction.");
  params.addCoupledVar("w", "The velocity in the z direction.");
  params.addRequiredCoupledVar("mixing_length", "The turbulent mixing length.");
  return params;
}

MixingLengthEddyViscosityAux::MixingLengthEddyViscosityAux(const InputParameters & params)
  : AuxKernel(params),
    _mixing_len(coupledValue("mixing_length"))
{
  THREAD_ID tid = params.get<THREAD_ID>("_tid");
  VariableName u_var_name = params.get<std::vector<VariableName>>("u").front();
  const MooseVariableFieldBase * u_var_moose
    = &_subproblem.getVariable(tid, u_var_name);
  _u_var = dynamic_cast<const MooseVariableFV<Real> *>(u_var_moose);
  if (!_u_var)
    mooseError("the u velocity must be a finite volume variable.");

  const MooseVariableFieldBase * v_var_moose = nullptr;
  if (params.isParamValid("v")) {
    VariableName v_var_name
      = params.get<std::vector<VariableName>>("v").front();
    v_var_moose = &_subproblem.getVariable(tid, v_var_name);
  }
  _v_var = dynamic_cast<const MooseVariableFV<Real> *>(v_var_moose);
  if (_subproblem.mesh().dimension() >= 2 && !_v_var)
    mooseError("In two-dimensions, the v velocity must be supplied and it "
               "must be a finite volume variable.");

  const MooseVariableFieldBase * w_var_moose = nullptr;
  if (params.isParamValid("w")) {
    VariableName w_var_name
      = params.get<std::vector<VariableName>>("w").front();
    w_var_moose = &_subproblem.getVariable(tid, w_var_name);
  }
  _w_var = dynamic_cast<const MooseVariableFV<Real> *>(w_var_moose);
  if (_subproblem.mesh().dimension() >= 3 && !_w_var)
    mooseError("In three-dimensions, the w velocity must be supplied and it "
               "must be a finite volume variable.");
}

Real
MixingLengthEddyViscosityAux::computeValue()
{
  auto sq_grad = std::pow(_u_var->adGradSln(_current_elem).norm(), 2);
  if (_v_var)
    sq_grad += std::pow(_v_var->adGradSln(_current_elem).norm(), 2);
  if (_w_var)
    sq_grad += std::pow(_w_var->adGradSln(_current_elem).norm(), 2);
  auto grad = std::sqrt(sq_grad.value());

  return std::pow(_mixing_len[_qp], 2) * grad;
}
