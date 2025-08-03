'''

By weipeng

Last modified: 01/09/2024

Some useful tools for fenicsx

    
'''
import os

from mpi4py import MPI
from dolfinx import mesh, fem, io
from dolfinx.io import VTXWriter

import scipy
import meshio
import numpy as onp


# TODO:
    # def reorder2jaxfem():
    #     local_dofs_coords = V.tabulate_dof_coordinates()
    #     local_vertices_coords = domain.geometry.x


def fenicsx2paraview(domain, uh, filename):
    '''
    output for paraview
    '''
    folder = os.path.dirname(filename)
    if not os.path.exists(folder):
        os.makedirs(folder)
        
    with VTXWriter(domain.comm, filename, [uh]) as vtx:
        vtx.write(0.0)
    
    return 


def input_mesh(mesh_pth, cell_type, prune_z=False):
    
    if mesh_pth[-4:] != 'xdmf':
        xdmf_path = mesh2xdmf(mesh_pth, cell_type, prune_z=False)
    else:
        xdmf_path = mesh_pth

    with io.XDMFFile(MPI.COMM_WORLD, xdmf_path, "r") as xdmf:
        domain = xdmf.read_mesh(name="Grid")
        
    return domain # dolfinx.mesh.Mesh


def mesh2xdmf(mesh_pth, cell_type, prune_z=False):
    '''
    copied from https://fenicsproject.discourse.group/t/error-while-importing-gmsh-mesh/11628/4
    
    '''
    cell_type = get_meshio_cell_type(cell_type)
    
    # Convert mesh file to .xdmf format
    mesh_origin = meshio.read(mesh_pth)
    cells = mesh_origin.get_cells_type(cell_type)
    cell_data = mesh_origin.get_cell_data("gmsh:physical", cell_type)
    points = mesh_origin.points[:,:2] if prune_z else mesh_origin.points
    out_mesh = meshio.Mesh(points=points, cells={
                         cell_type: cells}, cell_data={"name_to_read": [cell_data]})
    
    xdmf_path = mesh_pth[:-3] + 'xdmf'
    out_mesh.write(xdmf_path)
    
    return xdmf_path


def get_meshio_cell_type(ele_type):
    """
    Copied from JAX-FEM
    
    Reference:
    https://github.com/nschloe/meshio/blob/9dc6b0b05c9606cad73ef11b8b7785dd9b9ea325/src/meshio/xdmf/common.py#L36
    """
    if ele_type == 'TET4':
        cell_type = 'tetra'
    elif ele_type == 'TET10':
        cell_type = 'tetra10'
    elif ele_type == 'HEX8':
        cell_type = 'hexahedron'
    elif ele_type == 'HEX27':
        cell_type = 'hexahedron27'
    elif  ele_type == 'HEX20':
        cell_type = 'hexahedron20'
    elif ele_type == 'TRI3':
        cell_type = 'triangle'
    elif ele_type == 'TRI6':
        cell_type = 'triangle6'
    elif ele_type == 'QUAD4':
        cell_type = 'quad'
    elif ele_type == 'QUAD8':
        cell_type = 'quad8'
    else:
        raise NotImplementedError
    return cell_type


def ufl2array(ufl_expression, exp_type='matrix'):
    
    if exp_type == 'matrix':
        
        assemble_array = fem.petsc.assemble_matrix
        
        def petsc2array(mat):
            ai, aj, av = mat.getValuesCSR()
            mat = scipy.sparse.csr_matrix((av, aj, ai))
            return mat
            
    elif exp_type == 'vector':
        
        assemble_array = fem.petsc.assemble_vector
        
        def petsc2array(mat):
            return mat.getArray()
        
    else:
        raise NotImplementedError
    
    form = fem.form(ufl_expression)
    mat = assemble_array(form)
    mat.assemble()
    mat = petsc2array(mat)
    
    return mat


def get_facet_tag(domain, boundaries):
    '''
    See:
        https://jsdokken.com/dolfinx-tutorial/chapter3/robin_neumann_dirichlet.html
        
        https://jsdokken.com/dolfinx-tutorial/chapter2/hyperelasticity.html

    '''
    
    fdim = domain.topology.dim - 1
    facet_indices, facet_markers = [], []
    for (marker, locator) in boundaries:
        facets = mesh.locate_entities(domain, fdim, locator)
        facet_indices.append(facets)
        facet_markers.append(onp.full_like(facets, marker))
    facet_indices = onp.hstack(facet_indices).astype(onp.int32)
    facet_markers = onp.hstack(facet_markers).astype(onp.int32)
    sorted_facets = onp.argsort(facet_indices)
    facet_tag = mesh.meshtags(domain, fdim, facet_indices[sorted_facets], facet_markers[sorted_facets])
    
    return facet_tag

