#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <string>
#include <cassert>

class Mesh
{   
    private:
        // property
        const std::string name;
        const int num_nodes;
        const int num_cells;
        const std::string type;
    
    public:

        // Constructors **declaration**
        Mesh(std::string name = "default_mesh", int num_nodes = 27, int num_cells = 16, std::string type = "QUAD4");

        /*
        constant member function

        here const is for the implicit parameter "self"

        won't change any member property
        */ 
        void print_info() const;
        void test_assert() const;

        /*
        return the ref of class

        the first const: cannot use the return ref to modify object

        the second const: cannot modify object in the fun
        
        */ 

        const Mesh& get_self_reference() const;
    
};

#endif