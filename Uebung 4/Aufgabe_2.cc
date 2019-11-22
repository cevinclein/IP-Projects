#include <iostream>
#include <cmath>
#include <string>
using namespace std;

float zins(float z, int n)
{
    z = (pow(1+(z / n), n)) - 1;
    return z;
}

double dzins(double dz, int n)
{
    dz = (pow(1+(dz / n), n)) -1;
    return dz;
}

int result(int n, float z, double dz, string t)
{

    cout << "n = " << n << endl;
    cout << "Der Zinssatz (float) ist: " << zins(z, n) << t << endl;
    cout << "Die Differenz zu exp(z)-1 für (float) ist: " << (zins(z, n) - (exp(z)-1)) << endl;
    cout << "Der Zinssatz (double) ist: " << dzins(z, n) << t << endl;
    cout << "Die Differenz zu exp(z)-1 für (double) ist: " << (dzins(dz, n) - (exp(dz)-1)) << endl << endl;
    return 0;

}

int main()
{

    float z = 0.06;
    double dz = 0.06;
    int n;
    cout.precision(16);
    string t;

    n = 1;        
    t = " für jährliche Abrechnung.";
    result(n, z, dz, t);

    n = 4;
    t = " für quartalsweise Abrechnung.";
    result(n, z, dz, t);

    n = 12;
    t = " für monatliche Abrechnung.";
    result(n, z, dz, t);

    n = 365;
    t = " für tägliche Abrechnung.";
    result(n, z, dz, t);

    n = 365*24;
    t = " für stündliche Abrechnung.";
    result(n, z, dz, t);

    n = 365*24*60;
    t = " für minütliche Abrechnung.";
    result(n, z, dz, t);

    n = 365*24*60*2;
    t = " für Abrechnung alle 30 Sekunden.";
    result(n, z, dz, t);

    n = 365*24*60*60;
    t = " für sekündliche Abrechnung.";
    result(n, z, dz, t);
    return 0;
}