#include "solution.hpp"

solution& solution::operator=(const solution& other)
{
    if (this != &other)
    {   
        std::cout << "Copy assignment" << std::endl;
        num_dofs = other.num_dofs;
        delete sol;
        sol = new matrix(*(other.sol));
    }

    return *this;
}


solution& solution::operator=(solution&& other) noexcept
{     
    if (this != &other)
    {   
        std::cout << "Move assignment" << std::endl;
        delete sol;
        num_dofs = other.num_dofs;
        sol = other.sol;
        other.num_dofs = 0;
        other.sol = nullptr;
    }

    return *this;
}

void solution::print_info() const
{
    if (sol != nullptr)
    {
        std::cout << "Solution - Size (" << (*sol).size() << ", " << (*sol)[0].size() << ") ";
        std::cout << "- Address " << &(*sol); 
        std::cout << "- Ptr address " << &sol << std::endl; 
    }
    else
    {
        std::cout << "null ptr" << std::endl;
    }

}