#include "EddyLenMaterial.h"

registerMooseObject("NavierStokesApp", EddyLenMaterial);

defineLegacyParams(EddyLenMaterial);

InputParameters
EddyLenMaterial::validParams()
{
  InputParameters params = Material::validParams();
  //params += BoundaryRestrictableRequired::validParams();
  params.addParam<std::vector<BoundaryName>>("walls", "");
  params.addParam<std::string>("prop_name", "");

  return params;
}

EddyLenMaterial::EddyLenMaterial(const InputParameters & parameters)
  : Material(parameters)
    //BoundaryRestrictableRequired(this, false)
{
  _boundary_names = getParam<std::vector<BoundaryName>>("walls");
  _property = &declareGenericProperty<Real, true>(
    getParam<std::string>("prop_name"));
}

void
EddyLenMaterial::computeQpProperties()
{
  if (_q_point.size() == 0)
    return;

  //const MooseMesh & mesh {*_app.actionWarehouse().mesh()};
  const MooseMesh & m_mesh {_fe_problem.mesh()};
  const MeshBase & l_mesh {m_mesh.getMesh()};

  std::vector<BoundaryID> vec_ids =
    m_mesh.getBoundaryIDs(_boundary_names, true);

  auto bnd_to_elem_map = m_mesh.getBoundariesToElems();
  auto bnd_elems = bnd_to_elem_map[vec_ids[0]];

  Real min_sq_dist = 1e9;
  for (dof_id_type elem_id : bnd_elems) {
    //std::cout << elem_id << "\n";
    const Elem & elem {l_mesh.elem_ref(elem_id)};
    Point bnd_pos = elem.centroid();
    //min_sq_dist = std::min(min_sq_dist, bnd_pos(0));
    Real sq_dist = (bnd_pos - _q_point[_qp]).norm_sq();
    min_sq_dist = std::min(min_sq_dist, sq_dist);
  }

  (*_property)[_qp] = std::sqrt(min_sq_dist);

  //std::cout << _q_point.size();
  //if (_qp >= _q_point.size()) {
  //  std::cout << "PROBLEM! " << _qp << " " <<  _q_point.size() << "\n";
  //}

  //std::cout << _q_point[_qp](0) << " " << _q_point[_qp](1) << "\n";
  //std::cout << min_sq_dist << "\n\n";

  //const BoundaryInfo & boundary_info = l_mesh.get_boundary_info();
  //const BoundaryInfo & input_boundary_info = input->get_boundary_info();

  //std::cout << _q_point[_qp](0) << " " << _q_point[_qp](1) << "\n";
  //std::cout << boundary_info.n_boundary_ids() << "\n";
  //std::cout << vec_ids.size() << "\n";
  //std::cout << vec_ids[0] << "\n";
  //std::cout << bnd_elems.size() << "\n";
  //mooseError("Stop here!");
}
