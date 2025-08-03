"""

Cook beam-like example to validate stiffness matrix

Last modified: 23/02/25 by weipeng

"""

import numpy as onp
import jax.numpy as np

from jax_fem.problem import Problem
from jax_fem.solver import solver
from jax_fem.generate_mesh import get_meshio_cell_type, Mesh


# weak form
class Poisson(Problem):
    def get_tensor_map(self):
        return lambda x: 5 * x


# mesh
def generate_cook_beam_mesh():
    
    # abaqus order (1,2,3,0)
    points = onp.array([[0., 0.],
                        [2., 0.5],
                        [2., 1.],
                        [0., 1.]])
    
    cells = onp.arange(4).reshape(-1,4)
    
    return points, cells

ele_type = 'QUAD4'
cell_type = get_meshio_cell_type(ele_type)
Lx, Ly = 1., 1.
points, cells = generate_cook_beam_mesh()
mesh = Mesh(points, cells, ele_type)


# boundary conditions
def left(point):
    return np.isclose(point[0], 0., atol=1e-5)

def dirichlet_val_left(point):
    return 0.

location_fns = [left] * 2
value_fns = [dirichlet_val_left] * 2
vecs = [0, 1]
dirichlet_bc_info = [location_fns, vecs, value_fns]


# define problem
problem = Poisson(mesh=mesh, vec=1, dim=2, 
                  ele_type=ele_type, 
                  dirichlet_bc_info=dirichlet_bc_info)


# solve
sol = solver(problem)

print("Finished!")