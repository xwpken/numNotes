/*

Exercise 1 of archer2-cpp course

See https://github.com/EPCCed/archer2-cpp

Last modified: 05/03/2025 by weipeng

*/

#include <iostream>
#include <string>

// Function overloading
int sum(int a, int b)
{
    std::string info = "int sum fun is called";
    std::cout << info << std::endl;
    return a + b;
}

auto sum(double a, double b) -> double
{   
    std::string info = "double sum fun is called";
    return a + b;
}

void sayhello(std::string name)
{
    std::cout << "Hi, " + name + ". How are you?"<< std::endl;
}


// main
auto main(int para, char* ch[]) -> int
{
    printf("Hello World\n"); 

    std::cout << "Please input your name..." << std::endl;
    
    auto name = std::string{};
    std::cin >> name;
    sayhello(name);
    
    // Function overloading
    std::cout << sum(10,10) << std::endl;
    std::cout << sum(10.,10.) << std::endl;

    // return 0;

}
 
