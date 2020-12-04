//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "AuxKernel.h"

class MixingLengthEddyViscosityAux;

template <>
InputParameters validParams<MixingLengthEddyViscosityAux>();

/**
 * Auxiliary kernel responsible for computing the components of the flux vector
 * in diffusion problems
 */
class MixingLengthEddyViscosityAux : public AuxKernel
{
public:
  static InputParameters validParams();

  MixingLengthEddyViscosityAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  const MooseVariableFV<Real> * _u_var;
  const MooseVariableFV<Real> * _v_var;
  const MooseVariableFV<Real> * _w_var;

  const VariableValue & _mixing_len;
};
