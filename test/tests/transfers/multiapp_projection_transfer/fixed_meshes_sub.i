[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 5
  #nx = 160
  #ny = 80
  #uniform_refine=5
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./from_master]
  [../]
  [./elemental_from_master]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
  [./td]
    type = TimeDerivative
    variable = u
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 5
  dt = 0.01
  solve_type = NEWTON
[]

[Outputs]
  output_initial = true
  exodus = true
  #print_linear_residuals = true
  print_perf_log = true
[]

