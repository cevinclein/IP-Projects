#include <iostream>
#include <cmath>


void primfakt(int zahl)
{
    int t = zahl;

    //Man muss ja nur bis Wurzel n absuchen.
    for(int i = 2; i <= int(sqrt(t)) + 1; i++)
    {
        if(i == int(sqrt(t)) + 1)
        {
            std::cout<< t;
            break;
        }

        if(t % i == 0)
        {
            std::cout<< i << "*";
            t /= i;
            i = 1;
        }    
    }
}

int main()
{
    loop:
        int eingabe;
        std::cin>> eingabe;

        if(eingabe == 0)
        {
            std::cout<< "Programm beendet."<< std::endl;
            std::exit(0);
        }

        std::cout<<"Die Primfaktoren der Zahl: " << eingabe << " sind: ";
        primfakt(eingabe);
        std::cout<< std::endl;
    goto loop;

    return 0;
}