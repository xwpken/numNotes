#ifndef LEC2_HPP
#define LEC2_HPP

#include <iostream>
#include <string>
#include <cassert>

class Mesh
{   
    public:

        // property
        const std::string name;
        const int num_nodes;
        const int num_cells;
        const std::string type;

        // Constructors **declaration**
        Mesh(std::string name = "default_mesh", int num_nodes = 27, int num_cells = 16, std::string type = "QUAD4");

        /*
        constant member function

        won't change any member property
        */ 
        void print_info() const;
    
};

#endif