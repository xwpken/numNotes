#include <iostream> 
#include <cmath>
using namespace std;

int main() 
{
    cout << fixed;
    
    float f1 = 1.0f;
    cout << "f1 = " << f1 <<endl;
    
    float a = 0.1f;
    float f2 = a+a+a+a+a+a+a+a+a+a;
    cout << "f2 = " << f2<< endl;

    if(abs(f1-f2) < 1e-6) 
        cout << "f1 == f2" << endl;
        else
        cout << "f1 != f2" << endl;
    return 0;
}