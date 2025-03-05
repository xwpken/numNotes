'''

By weipeng

Last modified: 01/09/2024

This fenicsx example reproduce the poisson demo in JAX-FEM

please check:
    https://github.com/deepmodeling/jax-fem/tree/main/demos/poisson
    
Reference:
    https://jsdokken.com/dolfinx-tutorial/chapter1/fundamentals_code.html
    
'''

import os 
import time

from mpi4py import MPI
from dolfinx import mesh, fem, default_scalar_type
from dolfinx.fem.petsc import LinearProblem
import ufl

import numpy as np

import utils

input_dir = os.path.join(os.path.dirname(__file__), 'input')
output_dir = os.path.join(os.path.dirname(__file__), 'output')


'''

MPI.COMM_WORLD means the mesh is distributed over several processors

we can use: mpirun -n 2 python3 poisson.py

'''

t0 = time.time()


# Generating simple meshes
domain = mesh.create_unit_square(MPI.COMM_WORLD, 32, 32, mesh.CellType.quadrilateral)    


# finite element function space V
V = fem.functionspace(domain, ('Lagrange', 1))


# define boundary conditions
x_max = domain.geometry.x.max(0)[0]
x_min = domain.geometry.x.min(0)[0]

def left(x):
    return np.isclose(x[0], x_min)

def right(x):
    return np.isclose(x[0], x_max)

y_max = domain.geometry.x.max(0)[1]
y_min = domain.geometry.x.min(0)[1]

def top(x):
    return np.isclose(x[1], y_max)

def bottom(x):
    return np.isclose(x[1], y_min)

# dirichlet
dofs_left = fem.locate_dofs_geometrical(V, left)
dofs_right = fem.locate_dofs_geometrical(V, right)
bc_left = fem.dirichletbc(default_scalar_type(0), dofs_left, V)
bc_right = fem.dirichletbc(default_scalar_type(0), dofs_right, V)
bcs = [bc_left, bc_right]

# neumann
boundaries = [(1, top),
              (2, bottom)]
facet_tag = utils.get_facet_tag(domain, boundaries)
ds = ufl.Measure('ds', domain=domain, subdomain_data=facet_tag)

x = ufl.SpatialCoordinate(domain)
t = ufl.sin(5.*x[0])


# weak form
u = ufl.TrialFunction(V)
v = ufl.TestFunction(V)

f = 10 * ufl.exp(-((x[0] - 0.5)**2 + (x[1] - 0.5)**2) / 0.02)

dx = ufl.Measure('dx', domain=domain, metadata={"quadrature_degree": 2})

a = ufl.inner(ufl.grad(u), ufl.grad(v)) * ufl.dx
L = ufl.dot(f, v) * dx + ufl.dot(t, v) * ds(1) + ufl.dot(t, v) * ds(2)

# solve the linear system
problem = LinearProblem(a, L, bcs,
                        petsc_options={"ksp_type": "preonly", "pc_type": "lu"})
uh = problem.solve()

t1 = time.time()


# post
print(f"max of dofs = {np.max(uh.x.array)}")
print(f"min of dofs = {np.min(uh.x.array)}")
print(f'FEniCSx: Solve took {t1-t0:.3f} [s]')

filename = os.path.join(output_dir, 'paraview/poisson.bp')
utils.fenicsx2paraview(domain, uh, filename)
