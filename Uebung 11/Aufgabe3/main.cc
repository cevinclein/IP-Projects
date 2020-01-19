#include "Trapezregel.hh"

int main()
{
    //Teste Funktion

    function_sqrt f1;
    function_square f2;

    for(int i = 1; i <= 1201; i += 2)
    {
        //f1 = f(x) = sqrt(x)
        //Man kann auch f2 einsetzen für die Funktion f(x) = x^2
        std::cout << "n = " << i << ": " << trapezregel(f1, 0, 1.5, i) << std::endl;
    }
}

//Aufgabe 3b
/*
    Vorteil:
        Man ist mit statischem Polymorphismus sehr flexibel und auch
        schnell. Man muss keine Base-Klasse schreiben die irgendeine
        Referenz übergeben muss, die Klasse muss lediglich den Operator ()
        unterstützen. Jedes Funktionstemplate kann dann eine Klasse mit
        Operator () nutzen, ohne auf den Typ zu achten. Man kann also 
        verschiedene Klassen mit Operator () innerhalb der Funktion
        nutzen (flexibel).
    
    Nachteil:
        Ist eben diese große Flexibilität. Jede Klasse, die den Operator ()
        unterstützt wird ausgewertet, auch wenn man das vielleicht nicht 
        möchte. Es könnte Ergebnisse geben, die keinen Sinn ergeben.
        Der Code wird außerden sehr unübersichtlich. Treten Fehler auf
        oder Ergebnisse stimmen nicht, ist es schwerer zu erkennen an welcher
        stelle, weil man es am Parameter nich direkt ablesen kann, weil der
        Template-Parameter ja beliebig ist.
*/