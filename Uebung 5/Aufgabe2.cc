#include <iostream>

//Methode zur Sortierung eines int arrays in aufsteigender Reihenfolge.
void sort(int *array, int length)
{
    int i, j,tmp;

    for (i = 1; i < length ; i++) 
    {
        for (j = 0; j < length - i ; j++) 
        {
            if (array[j] > array[j+1]) 
            {
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

//Ausgabefunktion, macht dass was in der Aufgabe gefragt wurde
//Bemerkung: Elemente die nicht eingegeben wurden werden als 0 Gekennzeichnet 
//und nicht mitsortiert, wie es beim Bsp. in der Aufgabe zu sehen ist.
void printArray_10()
{
    int arr[10];

    //User muss möglichkeit haben mehr als 10 Werte einzugeben, damit Fehlermeldung kommt (deswegen true)
    for(int i = 0; true; i++)
    {
        if (i == 10)
        {
            int check_null; //prüfe ob letzte Eingabe 0 ist, dann wird ganzes Array ausgegeben

            std::cout<< "Bitte " << i + 1 << " Wert eingeben:" << std::endl;
            std::cin >> check_null;

            if (check_null == 0)
            {
                sort(arr, i); //sortiert nur die eingegeben Werte
                std::cout<< "Array = [ ";

                for(int i = 0; i < 10; i++)
                {
                    std::cout<< arr[i] << " ";
                }

                std::cout<< "]";
                std::exit(0);
                break;
            }
            else
            {
                //wenn letzte eingabe nicht null dann Fehler zu viele Elemente fürs Array arr
                std::cout<< "Fehler Arraygröße überschitten, Programm beendet."<<std::endl;
                std::exit(0);
                break;
            }
           
        }

        std::cout<< "Bitte " << i + 1 << " Wert eingeben:" <<std::endl;

        std::cin>> arr[i];

        //Keine negativen Zahlen bis auf 1
        if(arr[i] <= -2)
        {
            std::cout<< "Falsche eingabe, Programm beendet" <<std::endl;
            std::exit(0);
            break;
        }

        //Bei -1 Programm terminieren
        if(arr[i] == -1)
        {
            std::cout<< "Programm ist terminiert.";
            std::exit(0);
            break;
        }

        //Ausgabe des Arrays, von den Werten die bis zur 0-Eingabe eingegeben wurden.
        if(arr[i] == 0)
        {
            std::cout<< "Array = [ ";
            sort(arr, i); //sortiert nur die eingegeben Werte

            for(int i = 0; i < 10; i++)
            {
                std::cout<< arr[i] << " ";
            }

            std::cout<< "]";
            std::exit(0);
        }
    }
}

int main()
{
    printArray_10();
}