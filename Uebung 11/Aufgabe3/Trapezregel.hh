#include <iostream>
#include <cmath>

//Funktor Wurzelfunktion
class function_sqrt
{
    public:

        double operator()(double x)
        {
            //Man kann sich da eine x-beliebige Funktion 
            //zurückgeben lassen 
            return sqrt(x);
        }
};

//Funktor Quadratische Funktion
class function_square
{
    public:

        double operator()(double x)
        {
            return x * x;
        }
};

//geht für alle Funktionen welche den Operator () unterstützen.
template<class func> 
double trapezregel(func &f, double a, double b, int n)
{
    double h = (b - a) / n;

    double x1 = 0.5 * f(a) + 0.5 * f(b);
    double x2 = 0;

    for(int i = 1; i < n; i++)
    {
        x2 += f(a + i*h);
    }

    return h*(x1 + x2);
}
