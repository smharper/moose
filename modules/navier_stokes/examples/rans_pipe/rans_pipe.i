# Note that 1 / mu = Re
rho=1
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
    ymax = 5
    nx = 100
    ny = 100
  []
[]

[Outputs]
  exodus = true
  csv = true
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
  []
  [v]
    order = CONSTANT
    family = MONOMIAL
    fv = true
  []
  [pressure]
    order = CONSTANT
    family = MONOMIAL
    fv = true
  []
[]

[FVKernels]
  [mass]
    type = INSFVMassAdvection
    variable = pressure
    velocity_interp_method = ${velocity_interp_method}
    vel = 'velocity'
    pressure = pressure
    u = u
    v = v
    mu = 'mu'
    rho = ${rho}
    force_boundary_execution = ${force_boundary_execution}
  []

  [u_advection]
    type = INSFVMomentumAdvection
    variable = u
    advected_quantity = 'rhou'
    vel = 'velocity'
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    pressure = pressure
    u = u
    v = v
    mu = 'mu'
    rho = ${rho}
    force_boundary_execution = ${force_boundary_execution}
  []
  [u_viscosity]
    type = FVDiffusion
    variable = u
    coeff = 'mu'
    force_boundary_execution = ${force_boundary_execution}
  []
  [u_viscosity_rans]
    type = INSFVRANSDiffusion
    variable = u
    force_boundary_execution = ${force_boundary_execution}
    walls = 'right'
    rho = ${rho}
  []
  [u_pressure]
    type = INSFVMomentumPressure
    variable = u
    momentum_component = 'x'
    vel = 'velocity'
    advected_interp_method = ${advected_interp_method}
    force_boundary_execution = ${force_boundary_execution}
  []
  [u_pressure_rz]
    type = INSFVMomentumPressureRZ
    variable = u
    p = pressure
  []

  [v_advection]
    type = INSFVMomentumAdvection
    variable = v
    advected_quantity = 'rhov'
    vel = 'velocity'
    advected_interp_method = ${advected_interp_method}
    velocity_interp_method = ${velocity_interp_method}
    pressure = pressure
    u = u
    v = v
    mu = 'mu'
    rho = ${rho}
    force_boundary_execution = ${force_boundary_execution}
  []
  [v_viscosity]
    type = FVDiffusion
    variable = v
    coeff = 'mu'
    force_boundary_execution = ${force_boundary_execution}
  []
  [v_viscosity_rans]
    type = INSFVRANSDiffusion
    variable = v
    force_boundary_execution = ${force_boundary_execution}
    walls = 'right'
    rho = ${rho}
  []
  [v_pressure]
    type = INSFVMomentumPressure
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
  [sym_u]
    type = FVDirichletBC
    boundary = 'left'
    variable = u
    value = 0
  []
[]

[Functions]
  [mu_func]
    type = PiecewiseLinear
    x = '1 2 3'
    y = '1e-3 3e-4 1e-4'
  []
[]

[Materials]
  [mu]
    type = ADGenericFunctionMaterial
    prop_names = 'mu'
    prop_values = mu_func
  []
  [ins_fv]
    type = INSFVMaterial
    u = 'u'
    v = 'v'
    pressure = 'pressure'
    rho = ${rho}
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  #type = Steady
  #solve_type = 'PJFNK'
  type = Transient
  solve_type = 'PJFNK'
  start_time = 0
  end_time = 3
  dt = 1.0
  petsc_options_iname = '-pc_type -ksp_gmres_restart -sub_pc_type -sub_pc_factor_shift_type'
  petsc_options_value = 'asm      500                lu           NONZERO'
  line_search = 'none'
  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-11
[]

[Postprocessors]
  [p01]
    type = PointValue
    variable = v
    point = '0.05 4.9 0'
  []
  [p02]
    type = PointValue
    variable = v
    point = '0.10 4.9 0'
  []
  [p03]
    type = PointValue
    variable = v
    point = '0.15 4.9 0'
  []
  [p04]
    type = PointValue
    variable = v
    point = '0.20 4.9 0'
  []
  [p05]
    type = PointValue
    variable = v
    point = '0.25 4.9 0'
  []
  [p06]
    type = PointValue
    variable = v
    point = '0.30 4.9 0'
  []
  [p07]
    type = PointValue
    variable = v
    point = '0.35 4.9 0'
  []
  [p08]
    type = PointValue
    variable = v
    point = '0.40 4.9 0'
  []
  [p09]
    type = PointValue
    variable = v
    point = '0.45 4.9 0'
  []
  [p10]
    type = PointValue
    variable = v
    point = '0.46 4.9 0'
  []
  [p11]
    type = PointValue
    variable = v
    point = '0.47 4.9 0'
  []
  [p12]
    type = PointValue
    variable = v
    point = '0.48 4.9 0'
  []
  [p13]
    type = PointValue
    variable = v
    point = '0.49 4.9 0'
  []
[]

[Debug]
  show_var_residual_norms = true
[]
