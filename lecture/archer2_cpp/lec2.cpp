/*

Exercise 2 of archer2-cpp course

See https://github.com/EPCCed/archer2-cpp

Last modified: 05/03/2025 by weipeng

*/

#include "lec2.hpp"

// Define the constructor
Mesh::Mesh(std::string name, int a, int b, std::string type): 
name{name}, num_nodes{a}, num_cells{b}, type{type}
{
    std::cout << "Processing " << " Mesh object " + name << std::endl;
}

void Mesh::print_info() const
{   
    std::cout << "Name: " << name << std::endl;
    std::cout << "Num of nodes: " << num_nodes << std::endl;
    std::cout << "Num of cells: " << num_cells << std::endl;
    std::cout << "Element type: " << type << std::endl << std::endl;
}


int main()
{
   auto mesh_default = Mesh();
   mesh_default.print_info();
   assert(mesh_default.num_cells == 16);

   Mesh mesh{"archer2", 9, 4, "QUAD8"};
   mesh.print_info();
   std::cout << "The length of element type is " << mesh.type.size() << std::endl;

}