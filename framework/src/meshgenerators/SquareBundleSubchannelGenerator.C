//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SquareBundleSubchannelGenerator.h"

#include "CastUniquePointer.h"

#include "libmesh/face_tri3.h"
#include "libmesh/face_quad4.h"

registerMooseObject("MooseApp", SquareBundleSubchannelGenerator);

//TODO: do I need a ``defineLegacyParams'' line?
defineLegacyParams(SquareBundleSubchannelGenerator);

InputParameters
SquareBundleSubchannelGenerator::validParams()
{
  InputParameters params = MeshGenerator::validParams();

  params.addRequiredRangeCheckedParam<Real>(
    "r_rod", "r_rod>0", "Outer radius of rods in the bundle");
  params.addRequiredRangeCheckedParam<Real>(
    "pitch", "pitch>0", "Distance between the centers of adjacent rods in the bundle");
  params.addRangeCheckedParam<int>(
    "n_prism", 2, "n_prism>0", "Number of rod-adjacent prism mesh layers");
  params.addRangeCheckedParam<int>(
    "n_azim", 3, "n_azim>0", "Number of azimuthal segments to the prism mesh");

  return params;
}

SquareBundleSubchannelGenerator::SquareBundleSubchannelGenerator(const InputParameters & parameters)
    : MeshGenerator(parameters),
      _r_rod(getParam<Real>("r_rod")),
      _pitch(getParam<Real>("pitch")),
      _n_prism(getParam<int>("n_prism")),
      _n_azim(getParam<int>("n_azim"))
{
  if (_pitch < 2 * _r_rod) {
    paramError("pitch", "The bundle pitch must be at least 2x the rod radius.");
  }
}

std::unique_ptr<MeshBase>
SquareBundleSubchannelGenerator::generate()
{
  // Have MOOSE construct the correct libMesh::Mesh object using Mesh block and CLI parameters.
  auto mesh = _mesh->buildMeshBaseObject();

  mesh->set_mesh_dimension(2);
  mesh->set_spatial_dimension(2);
  //BoundaryInfo & boundary_info = mesh->get_boundary_info();

  std::vector<Node *> nodes;

  std::cout << "_n_prism = " << _n_prism << "\n";

  int node_id = 0;
  for (int i_rad = 0; i_rad < _n_prism+1; ++i_rad) {
    double radius = _r_rod + (0.5*_pitch - _r_rod) / (_n_prism+1) * i_rad;
    for (int i_az = 0; i_az < _n_azim+1; ++i_az) {
      double theta = M_PI - 0.25 * M_PI / _n_azim * i_az;
      double x = radius * std::cos(theta) + 0.5*_pitch;
      //double x = radius * std::cos(theta);
      double y = radius * std::sin(theta);
      nodes.push_back(mesh->add_point(Point(x, y, 0), node_id++));
    }
  }

  for (int i_az = 0; i_az < _n_azim+1; ++i_az) {
    double theta = M_PI - 0.25 * M_PI / _n_azim * i_az;
    double y = -std::tan(theta) * 0.5 * _pitch;
    nodes.push_back(mesh->add_point(Point(0, y, 0), node_id++));
  }

  //std::cout << nodes.size() << "\n";
  for (int i_rad = 0; i_rad < _n_prism+1; ++i_rad) {
    for (int i_az = 0; i_az < _n_azim; ++i_az) {
      int i0 = (_n_azim+1) * i_rad + i_az;
      Elem * elem = mesh->add_elem(new Quad4);
      elem->set_node(0) = nodes[i0];
      elem->set_node(1) = nodes[i0 + 1];
      elem->set_node(2) = nodes[i0 + _n_azim + 2];
      elem->set_node(3) = nodes[i0 + _n_azim + 1];
    }
  }

  mesh->prepare_for_use();

  return dynamic_pointer_cast<MeshBase>(mesh);
}
