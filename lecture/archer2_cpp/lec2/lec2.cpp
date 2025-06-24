/*

Exercise 2 of archer2-cpp course

See https://github.com/EPCCed/archer2-cpp

Last modified: 07/03/2025 by weipeng

*/

#include "mesh.hpp"


void check_mesh(Mesh const& mesh)
// initialize the reference of mesh
// const means cannot change the input object
{
    mesh.print_info();
}


int main()
{
   auto mesh_default = Mesh();
   check_mesh(mesh_default);

   const Mesh& ref = mesh_default.get_self_reference();
   ref.print_info();

   ref.test_assert();

   Mesh mesh{"archer2", 9, 4, "TET3"};
   check_mesh(mesh);  // input the object

   Mesh& mesh_ref = mesh; // reference
   check_mesh(mesh_ref); // input the reference

   auto mesh_copy = mesh; // copy, can be modified
   auto && mesh_same_const_ref = mesh; // reference with the same const-ness
   auto const & mesh_const_ref = mesh; // reference, cannot be modified

   mesh_const_ref.test_assert();

}