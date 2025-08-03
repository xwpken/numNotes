#include<iostream>
#include<eigen3/Eigen/Dense>
using namespace std;

int main()
{
    std::cout << "Hello World!" << std::endl;
    
    Eigen::Matrix<double, 10, 10> A;
    A.setZero();
    A(9,0) = 1.234;
    std::cout << A << std::endl;
    
    return 0;
}


