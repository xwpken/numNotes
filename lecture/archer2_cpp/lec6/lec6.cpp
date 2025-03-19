/*

Exercise 6 of archer2-cpp course

See https://github.com/EPCCed/archer2-cpp

Last modified: 19/03/2025 by weipeng

*/

#include "lec6.hpp"

int main()
{
    float a = 1.;
    float b = 2.;

    std::cout << sum<float>(a,b) << std::endl; // instantiate
    std::cout << sum(a,b) << std::endl;  // deduce type

}