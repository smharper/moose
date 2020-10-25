mu=1e-1
advected_interp_method='average'
velocity_interp_method='rc'
force_boundary_execution=true

[Mesh]
  [gen]
    type = GeneratedMeshGenerator
    dim = 2
    xmin = 0
    xmax = 0.5
    ymin = 0
    ymax = 10
    nx = 20
    ny = 200
  []
[]

[Outputs]
  exodus = true
[]

[Problem]
  kernel_coverage_check = false
  fv_bcs_integrity_check = true
  coord_type = 'RZ'
[]

[Variables]
  [u]
    order = CONSTANT
    family = MONOMIAL
    fv = true
    initial_condition = 0
  []
  [v]
    order = CONSTANT
    family = MONOMIAL
    fv = true
    initial_condition = 0
  []
  [pressure]
    order = CONSTANT
    family = MONOMIAL
    fv = true
  []
[]

[FVKernels]
  [mass]
    type = NSFVKernel
    variable = pressure
    advected_quantity = 1
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    vel = 'velocity'
    pressure = pressure
    u = u
    v = v
    rho = 1.0
    ghost_layers = 2
    force_boundary_execution = ${force_boundary_execution}
  []

  [u_advection]
    type = NSFVKernel
    variable = u
    advected_quantity = 'rhou'
    vel = 'velocity'
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    pressure = pressure
    u = u
    v = v
    rho = 1.0
    ghost_layers = 2
    force_boundary_execution = ${force_boundary_execution}
  []
  [u_viscosity]
    type = FVDiffusion
    variable = u
    coeff = 'mu'
    force_boundary_execution = ${force_boundary_execution}
  []
  [u_pressure]
    type = FVMomPressure
    variable = u
    momentum_component = 'x'
    vel = 'velocity'
    advected_interp_method = ${advected_interp_method}
    force_boundary_execution = ${force_boundary_execution}
  []
  [u_pressure_rz]
    type = FVMomPressureRZ
    variable = u
    p = pressure
  []

  [v_advection]
    type = NSFVKernel
    variable = v
    advected_quantity = 'rhov'
    vel = 'velocity'
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    pressure = pressure
    u = u
    v = v
    rho = 1.0
    ghost_layers = 2
    force_boundary_execution = ${force_boundary_execution}
  []
  [v_viscosity]
    type = FVDiffusion
    variable = v
    coeff = 'mu'
    force_boundary_execution = ${force_boundary_execution}
  []
  [v_pressure]
    type = FVMomPressure
    variable = v
    momentum_component = 'y'
    vel = 'velocity'
    advected_interp_method = ${advected_interp_method}
    force_boundary_execution = ${force_boundary_execution}
  []
[]

[FVBCs]
  [wall_u]
    type = FVDirichletBC
    boundary = 'right bottom'
    variable = u
    value = 0
  []
  [wall_v]
    type = FVDirichletBC
    boundary = 'right'
    variable = v
    value = 0
  []
  [inlet_v]
    type = FVDirichletBC
    variable = v
    boundary = 'bottom'
    value = 1
  []
  [outlet_p]
    type = FVDirichletBC
    variable = pressure
    boundary = 'top'
    value = 0
  []
[]

[Materials]
  [rho]
    type = ADGenericConstantMaterial
    prop_names = 'rho'
    prop_values = 1.0
  []
  [mu]
    type = ADGenericConstantMaterial
    prop_names = 'mu'
    prop_values = ${mu}
  []
  [ins_fv]
    type = INSFVMaterial
    u = 'u'
    v = 'v'
    pressure = 'pressure'
  []
[]

[Executioner]
  type = Steady
  solve_type = 'NEWTON'
  petsc_options_iname = '-pc_type -ksp_gmres_restart -sub_pc_type -sub_pc_factor_shift_type'
  petsc_options_value = 'asm      200                lu           NONZERO'
  line_search = 'none'
  nl_rel_tol = 1e-12
[]
