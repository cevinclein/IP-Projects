#include "Polynomial.hh"

int main()
{
    Polynomial<float> p(2); 
    p[0] = 1.0;
    p[1] = 1.0;

    p.print();
    p = p*p; 
    p.print();

    Polynomial<double> q(3); 
    q[0] = 2.0;
    q[1] = -3.1415926;
    q[3] = 4.0;

    q.print();
}