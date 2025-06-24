/*

Exercise 5 of archer2-cpp course

See https://github.com/EPCCed/archer2-cpp

Last modified: 14/03/2025 by weipeng

*/

#include "solution.hpp"

int main()
{   
    // RALL
    // new vector
    std::vector<int>* vec = new std::vector<int> (3);

    (*vec)[0] = 1;
    vec -> push_back(2);

    for (auto i: *vec)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    // new default array
    int* array = new int[4]{1,2,3,4};

    for (int i = 0; i < 4; ++i)
    {
        std::cout << array[i] << " ";
    }

    std::cout << std::endl;

    delete vec;
    delete[] array;

    // Direct initialization
    solution sol{100,2};
    sol.print_info();

    // Copy initialization
    solution sol_copy1{sol};
    sol_copy1.print_info();
    solution sol_copy2 = sol;
    sol_copy2.print_info();

    // Copy assignment
    sol_copy2 = sol;
    sol_copy2.print_info();

    // Be careful about the shallow copy!

    // move initialization
    solution sol_move1 = std::move(sol);
    sol.print_info();
    sol_move1.print_info();

    // move assignment
    sol_move1 = std::move(sol_copy1);
    sol_copy1.print_info();
    sol_move1.print_info();

}