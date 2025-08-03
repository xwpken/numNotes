#include<iostream>
#include<iomanip>

int main()
{
    double f1 = 0.12345678;
    std::cout << f1 << std::endl;

    // print with cout

    //member function
    std::cout.width(12);
    std::cout.fill('+');
    std::cout << f1 << std::endl;

    std::cout.precision(4);
    std::cout << f1 << std::endl;

    std::cout.setf(std::ios::boolalpha);
    std::cout << true <<std::endl;

    std::cout.unsetf(std::ios::boolalpha);
    std::cout << true <<std::endl;

    //iomanip
    std::cout.precision(10);
    std::cout << std::right << std::setw(16) << std::setfill('+') << f1 << std::endl;
    std::cout << std::left << std::setw(16) << std::setfill('+') << f1 << std::endl;

    // C style
    printf("%10.2f\n", f1);
    printf("%2c\n", 'a');

    // data type
    std::cout << sizeof(f1) <<std::endl;

    return 0;
}