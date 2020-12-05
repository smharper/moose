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

class BuildArrayVariableAux;

template <>
InputParameters validParams<BuildArrayVariableAux>();

class BuildArrayVariableAux : public ArrayAuxKernel
{
public:
  static InputParameters validParams();

  BuildArrayVariableAux(const InputParameters & parameters);

protected:
  virtual RealEigenVector computeValue() override;

  std::vector<const MooseVariableFieldBase *> _component_vars;
};
