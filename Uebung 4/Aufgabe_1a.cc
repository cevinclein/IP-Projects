#include <iostream>
using namespace std;

float determinante(float a, float b, float c, float d)
{

    return ((a*d) - (b*c));

}

double ddeterminante(double a, double b, double c, double d)
{

    return ((a*d) - (b*c));

}

int main(){

    double a;
    double b;
    double c;
    double d;
    cout.precision(16);

    cout << "Bitte a eingeben: " << flush;
    cin >> a;
    if(cin.fail()){return 0;}
    cout << "Bitte b eingeben: " << flush;
    cin >> b;
    if(cin.fail()){return 0;}
    cout << "Bitte c eingeben: " << flush;
    cin >> c;
    if(cin.fail()){return 0;}
    cout << "Bitte d eingeben: " << flush;
    cin >> d;
    if(cin.fail()){return 0;}

    cout << "Das Ergebnis für float lautet: " << determinante(a,b,c,d) << endl << "Das Ergebnis für double lautet: " << ddeterminante(a,b,c,d) << endl;
    
    return 0;

}