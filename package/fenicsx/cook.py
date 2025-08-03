"""

Cook beam-like example to validate stiffness matrix

Last modified: 23/02/25 by weipeng

"""

import os
import meshio
import numpy as onp

from mpi4py import MPI
import ufl
from dolfinx import fem, io

# See https://fenicsproject.discourse.group/t/module-dolfinx-fem-has-no-attribute-petsc/11847
import dolfinx.fem.petsc

import utils

input_dir = os.path.join(os.path.dirname(__file__), 'input')
output_dir = os.path.join(os.path.dirname(__file__), 'output')


def generate_cook_beam_mesh():
    
    # abaqus order (1,2,3,0)
    points = onp.array([[0., 0.],
                        [2., 0.5],
                        [2., 1.],
                        [0., 1.]])
    
    cells = onp.arange(4).reshape(1,4)
    
    return points, cells


def reorder_stiffness_matrix(A, order):
    
    order = onp.array(order)
    A_reorder = A[:,order]
    A_reorder = A_reorder[order,:]
    
    return A_reorder


def check_stiffness_matrix():
    
    # convert mesh
    cell_type = utils.get_meshio_cell_type("QUAD4")
    points, cells = generate_cook_beam_mesh()
    out_mesh = meshio.Mesh(points=points, cells={
                         cell_type: cells})
    xdmf_path = os.path.join(input_dir, 'mesh/cook.xdmf')
    out_mesh.write(xdmf_path)
    
    # read mesh
    with io.XDMFFile(MPI.COMM_WORLD, xdmf_path, "r") as xdmf:
        domain = xdmf.read_mesh(name="Grid")
    
    V = fem.functionspace(domain, ('Lagrange', 1))
    
    # weak form
    u = ufl.TrialFunction(V)
    v = ufl.TestFunction(V)
    dx = ufl.Measure('dx', domain=domain, metadata={"quadrature_degree": 2})
    a = 5 * ufl.inner(ufl.grad(u), ufl.grad(v)) * dx
    
    A = utils.ufl2array(a).todense()
    
    return A
    

if __name__ == "__main__":
    A = check_stiffness_matrix()
    print("Original stiffness matrix gives:")
    print(A)
    print("\nJAX stiffness matrix gives:")
    print(reorder_stiffness_matrix(A, (0,1,3,2)))
    print("\nFinal stiffness matrix gives:")
    print(reorder_stiffness_matrix(A, (2,0,1,3)))
