'''

By weipeng

Last modified: 01/09/2024

This fenicsx example reproduce the linear_elasticity demo in JAX-FEM

please check:
    https://github.com/deepmodeling/jax-fem/tree/main/demos/linear_elasticity
    
Reference:
    https://jsdokken.com/dolfinx-tutorial/chapter2/linearelasticity.html
    
'''

import os
import time

from dolfinx import mesh, fem, default_scalar_type
from dolfinx.fem.petsc import LinearProblem
import ufl

import numpy as np

import utils

input_dir = os.path.join(os.path.dirname(__file__), 'input')
output_dir = os.path.join(os.path.dirname(__file__), 'output')


t0 = time.time()


# material
E = 70e3
nu = 0.3
mu = E/(2.*(1.+nu))
lmbda = E*nu/((1+nu)*(1-2*nu))


# mesh
domain = utils.input_mesh(os.path.join(input_dir, 'mesh/box.msh'), 'TET10')
Lx = np.max(domain.geometry.x[:, 0])


# finite element space
V = fem.functionspace(domain, ("Lagrange", 2, (domain.geometry.dim, )))


# boudnary conditions
def left(x):
    return np.isclose(x[0], 0)

def right(x):
    return np.isclose(x[0], Lx)

# dirichlet
fdim = domain.topology.dim - 1
boundary_facets = mesh.locate_entities_boundary(domain, fdim, left)
u_D = np.array([0, 0, 0], dtype=default_scalar_type)
bc = fem.dirichletbc(u_D, fem.locate_dofs_topological(V, fdim, boundary_facets), V)
bcs = [bc]

# neumann
boundaries = [(1, right)]
facet_tag = utils.get_facet_tag(domain, boundaries)
ds = ufl.Measure('ds', domain=domain, subdomain_data=facet_tag)
T = fem.Constant(domain, default_scalar_type((0, 0, -100)))  # tractions


# weak from
u = ufl.TrialFunction(V)
v = ufl.TestFunction(V)

def epsilon(u):
    return ufl.sym(ufl.grad(u))  # Equivalent to 0.5*(ufl.nabla_grad(u) + ufl.nabla_grad(u).T)

def sigma(u):
    return lmbda * ufl.nabla_div(u) * ufl.Identity(len(u)) + 2 * mu * epsilon(u)

f = fem.Constant(domain, default_scalar_type((0, 0, 0)))     # body forces

a = ufl.inner(sigma(u), epsilon(v)) * ufl.dx
L = ufl.dot(f, v) * ufl.dx + ufl.dot(T, v) * ds(1)


# solve
# petsc_options={"ksp_type": "preonly", "pc_type": "lu"}
petsc_options={"ksp_type": "bcgsl", "pc_type": "ilu"}

problem = LinearProblem(a, L, bcs=bcs, petsc_options=petsc_options)
uh = problem.solve()

t1 = time.time()


# post
print(f"max of dofs = {np.max(uh.x.array)}")
print(f"min of dofs = {np.min(uh.x.array)}")
print(f'FEniCSx: Solve took {t1-t0:.3f} [s]')

filename = os.path.join(output_dir, 'paraview/linear_elasticity.bp')
utils.fenicsx2paraview(domain, uh, filename)

