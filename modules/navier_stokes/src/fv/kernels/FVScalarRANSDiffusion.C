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
  params.addRequiredCoupledVar("visc", "");
  params.addParam<std::vector<BoundaryName>>("walls",
    "Boundaries that correspond to solid walls");
  params.set<unsigned short>("ghost_layers") = 2;
  return params;
}

FVScalarRANSDiffusion::FVScalarRANSDiffusion(const InputParameters & params)
  : FVFluxKernel(params),
    _wall_boundary_names(getParam<std::vector<BoundaryName>>("walls")),
    _visc(adCoupledValue("visc"))
{
}

ADReal
FVScalarRANSDiffusion::computeQpResidual()
{
  // TODO: move this calculation of mixing length into a material.  To do this,
  // we need to update the framework so that _q_point is set when the material's
  // computeQpProperties()

  /*
  // See if we have already computed the distance from this face to the wall.
  Real dist = -1;
  const Elem * elem {&_face_info->elem()};
  const Elem * neighbor {_face_info->neighborPtr()};
  auto search1 = _dist_map.find(elem);
  if (search1 != _dist_map.end()) {
    const auto & inner_map = search1->second;
    auto search2 = inner_map.find(neighbor);
    if (search2 != inner_map.end()) {
      dist = search2->second;
    }
  }

  // Compute the wall distance and cache it if necessary.
  if (dist == -1) {
    // Get references to the Moose and libMesh mesh objects
    const MooseMesh & m_mesh {subProblem().mesh()};
    const MeshBase & l_mesh {m_mesh.getMesh()};

    // Get the ids of the wall boundaries.
    std::vector<BoundaryID> vec_ids =
      m_mesh.getBoundaryIDs(_wall_boundary_names, true);

    // Loop over all boundary elements and find the distance to the closest one.
    auto bnd_to_elem_map = m_mesh.getBoundariesToElems();
    auto bnd_elems = bnd_to_elem_map[vec_ids[0]];
    Real min_sq_dist = 1e9;
    for (dof_id_type elem_id : bnd_elems) {
      const Elem & elem {l_mesh.elem_ref(elem_id)};
      Point bnd_pos = elem.centroid();
      Real sq_dist = (bnd_pos - _face_info->faceCentroid()).norm_sq();
      min_sq_dist = std::min(min_sq_dist, sq_dist);
    }
    Real dist = std::sqrt(min_sq_dist);

    // Cache the distance.
    auto & inner_map = _dist_map[elem];
    inner_map[neighbor] = dist;
  }

  // Approximate the eddy mixing length as the distance to the nearest wall.
  Real mixing_len = dist;

  // Compute the eddy viscosity.
  // TODO: Why are there nan's in the grad_u.norm() derivative terms?  In the
  // meantime, just use the value.
  auto grad_u = _var.adGradSln(*_face_info);
  Real grad_u_norm = grad_u.norm().value();
  ADReal eddy_visc = grad_u_norm * mixing_len * mixing_len;

  // Return the turbulent viscosity contribution to the momentum equation.
  */
  auto dudn = gradUDotNormal();
  auto eddy_visc = _visc[_qp];
  return -1 * eddy_visc * dudn;
}
