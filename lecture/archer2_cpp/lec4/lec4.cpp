/*

Exercise 4 of archer2-cpp course

See https://github.com/EPCCed/archer2-cpp

Last modified: 14/03/2025 by weipeng

*/

#include "lec4.hpp"

void process(int x, int& x_ref)
{
    std::cout << "\n ===== Check the reference ===== " << std::endl;
    std::cout << "\nx (" << typeid(x).name() << "): " << x << " " << &x << std::endl;
    std::cout << "x_ref (" << typeid(x_ref).name() << "): " << x_ref << " " << &x_ref << std::endl;

}

void process(int* x)
{   
    std::cout << "\n ===== Change value through int ptr ===== " << std::endl;

    print_ptr_info(x);

    std::cout << "\n *x += 1; " << std::endl;
    *x += 1;
    
    print_ptr_info(x);

}

void process(int* x0, int* x1)
{   
    std::cout << "\n ===== Move the array ptr ===== " << std::endl;

    print_ptr_info(x0);
    print_ptr_info(x1);
    
    std::cout<< "\nvalue of ++&ptr_array[0]: " << *(++x0) << std::endl;
    std::cout<< "array[1]: " << *(x1) << std::endl;

    print_ptr_info(x0);
    print_ptr_info(x1);
}

void print_ptr_info(int* x)
{
    std::cout << "\nx (" << typeid(x).name() << "): " << x << " " << &x << std::endl;
    std::cout << "*x (" << typeid(*x).name() << "): " << *x << " " << &(*x) << std::endl;
}

int main()
{
    int x = 10;

    // reference
    int& x_ref = x;
    process(x, x_ref);

    // pointer

    int* ptr_x = &x;
    process(ptr_x);

    std::array<int, 5> array = {1,1000,3,4,5};
    process(&array[0], &array[1]);
    
}
