#include <iostream>
using namespace std;
int main()
{
    int a, b;
    double c, d,f,g;
    char h;

    a = 19.99 + 21.99;
    b = (int)19.99 + 21.99;
    c = 23 / 3;
    d = 23 / 3.0;
    f = 23 / 3.0e4;
    g = 23 / 3.0e5;
    h = 'b' - 32;

    //complete code here
    printf("%c\n",h);
    printf("%d\n",a);
    printf("%d\n",b);
    printf("%d\n",int(c));
    printf("%f\n",d);
    printf("%e\n",g);
    printf("%.9f\n",g);

    return 0; 
}
