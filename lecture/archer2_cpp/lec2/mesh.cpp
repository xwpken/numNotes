#include "mesh.hpp"

// Define the constructor
Mesh::Mesh(std::string name, int a, int b, std::string type): 
name{name}, num_nodes{a}, num_cells{b}, type{type}
{
    std::cout << std::endl << "Processing " << " Mesh object " + name << std::endl;
}

void Mesh::print_info() const
{   
    std::cout << "Name: " << name << std::endl;
    std::cout << "Num of nodes: " << num_nodes << std::endl;
    std::cout << "Num of cells: " << num_cells << std::endl;
    std::cout << "Element type: " << type << std::endl << std::endl;
}

void Mesh::test_assert() const
{
    assert(num_cells > 0);
    std::cout << "Element type: " << type << "(" <<type.size() << ")" << std::endl;
}



const Mesh& Mesh::get_self_reference() const
{
    return *this;
}