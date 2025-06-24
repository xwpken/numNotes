#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include<iostream>
#include<vector>

using vector = std::vector<double>;
using matrix = std::vector<vector>;

class solution
{
    private:
        unsigned num_dofs;
        matrix* sol = nullptr;

    public:

        solution() = default;

        explicit solution(unsigned num_nodes, unsigned vec): 
        num_dofs{num_nodes * vec}, sol{new matrix(num_nodes, vector(vec, 0.))}
        {}

        // copy constructor
        solution(const solution& other):
        num_dofs{other.num_dofs}, sol{new matrix(*(other.sol))}
        {
            std::cout << "Copy constructor" << std::endl;
        }

        // copy assignment
        solution& operator=(const solution& other);


        // move constructor
        solution(solution&& other) noexcept:
        num_dofs{other.num_dofs}, sol{other.sol}
        {
            std::cout << "Move constructor" << std::endl;
            other.num_dofs = 0;
            other.sol = nullptr;
        }

        // move assignment
        solution& operator=(solution&& other) noexcept;
        
        void print_info() const;

        // destructor
        ~solution()
        {
            std::cout << "Call destructor" << std::endl;
            delete sol;
        }
};

#endif