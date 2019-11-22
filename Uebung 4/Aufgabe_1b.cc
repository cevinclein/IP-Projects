#include <iostream>
#include <cmath>
using namespace std;

int main()
{

    float a;
    float b;
    float c;
    int i;
    int n;
    float res1;
    float res2;
    cout.precision(16);

    cout << "Bitte Startwert für n (Default 6)  eingeben: " << flush;
    cin >> i;
    if(cin.fail()){cout << "Ungültige eingabe!" << endl; return 0;}
    cout << "Bitte Endwert (Default 14) eingeben: " << flush;
    cin >> n;
    if(cin.fail()){cout << "Ungültige eingabe!" << endl; return 0;}

   for (i; i <= n; i++)
   {
        a = pow(10, i);
        b = -1*pow(10, i);
        c = pow(10, -1*i);

        res1 = (a + b) + c;
        res2 = a + (b + c);

        cout << "(a + b) + c mit n" << i << " = " << res1 << endl;
        cout << "a + (b + c) mit n" << i << " = " << res2 << endl << endl;
   }
   

    return 0;
}