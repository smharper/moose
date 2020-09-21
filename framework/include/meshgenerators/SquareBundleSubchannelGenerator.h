//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MeshGenerator.h"

// Forward declarations
class SquareBundleSubchannelGenerator;

template <>
InputParameters validParams<SquareBundleSubchannelGenerator>();

class SquareBundleSubchannelGenerator : public MeshGenerator
{
public:
  static InputParameters validParams();

  SquareBundleSubchannelGenerator(const InputParameters & parameters);

  std::unique_ptr<MeshBase> generate() override;

protected:
  /// Outer radius of the rods in the bundle
  const Real _r_rod;

  /// Distance between the centers of adjacent rods in the bundle
  const Real _pitch;

  /// Number of rod-adjacent prism mesh layers
  const int _n_prism;

  /// Number of azimuthal segments to the prism mesh
  const int _n_azim;
};
