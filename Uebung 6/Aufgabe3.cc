#include "fcpp.hh"
#include <string.h> // fuer strlen, Laenge eines C-Strings

//Stack und Funktionen (im Folgenden)
struct Stack_Int
{
  int stack_elements[100];
  int size = 0;
};
Stack_Int stin;


void push(int element)
{
  stin.stack_elements[stin.size] = element;
  stin.size++;
}

int pop()
{
  stin.size--;
  return stin.stack_elements[stin.size];
}

//Wandelt char-Array in int-Nummer um
int make_number(char* val)
{
  int result = 0;
  for (int i = 0; i < strlen(val); i++)
  {
    result += (int(val[i]) - 48) * pow(10, strlen(val) - i - 1);
  }
  return result;
}

int main(int argc, char* argv[])
{
  // fange kein Kommandozeilenargument ab
  if(argc < 2)
  {
    print("Eingabe für den Taschenrechner erwartet!");
    return 1;
  }

  // arg enthaelt die als Eingabe von der Kommandozeile uebergebene Zeichenfolge
  char* arg = argv[1];

  //Jede zusammenhängende Zahl von arg wird darin zwischengespeichert
  char temp_number[20] = "";

  //War letzter Wert von arg eine Zahl?
  bool isNumber = false;

  //Keine Operanten im Ausdruck
  bool noOperation = true;

  // Schleife, die die Zeichen der Eingabe nacheinander ablaeuft
  // strlen gibt die Anzahl der Zeichen in der Zeichenkette
  for (int i = 0, j = 0; i <= strlen(arg); i = i+1)
  {
    char zeichen = arg[i];

    //Zeichen-Zahlen von temp_Number werden mit strncpy hier her kopiert.
    //strncpy passt nähmlich die größe des Arrays auf die Anzahl der Zeichen an.
    char des_temp_number[20] = "";
    
    //zahlen 0-9 in char 48-57
    if((int)zeichen >= 48 && (int)zeichen <= 57)
    {
      temp_number[j] = zeichen;
      isNumber = true;
      j++;  
    } 
    else if (zeichen == '*' || zeichen == '/' || zeichen == '+' || zeichen == '-')
    {
      //Auf dem Stack müssen vor der Operation immer zwei Werte vorhanden sein,
      //da ja immer zwei Werte verrechnet werden.
      if(stin.size < 2)
      {
        std::cout<<"Fehler, falsche eingabe!!!"<< std::endl;
        exit(0);
        break;
      }

      if (zeichen == '*'){ push(pop()*pop()); } 
      if (zeichen == '+'){ push(pop()+pop()); }
      if (zeichen == '-'){ push(-(pop()-pop())); }

      if(zeichen == '/')
      {
        int a = pop();
        int b = pop();
        push(b / a);
      }

      isNumber = false; 
      noOperation = false;
    } 
    else if (arg[i] == ' ' && isNumber == true)
    {
      //Übergibt gefundene char-Nummer mit der Größe j an des_temp_Number
      //Wir brauchen ja ein char Array mit der Göße welche so groß ist 
      //wie die Anzahl der Ziffern, wichtig für make_number Funktion
      strncpy(des_temp_number, temp_number, j);
      //Neue Zahl auf Stapel legen
      push(make_number(des_temp_number));
      j = 0;
      isNumber = false;
    }  
    else if(isNumber == true)
    {
      //Alle anderen Zeichen und zusätzliche Leerzeichen ignorieren, isNumber
      //dann auch am Ende false
      strncpy(des_temp_number, temp_number, j);
      push(make_number(des_temp_number));
      j = 0;
      isNumber = false;
    }     
  }

  //Es kann keine Operation ohne Operanten durchgeführt werden!
  if(noOperation)
  {
    std::cout<< "Keine Operanten, nichts berechnet:" <<std::endl;
    std::cout<< arg <<std::endl;
    exit(0);
  }

  //Am Ende muss Stapel nur noch ein Element haben!
  if(stin.size > 1)
  {
    std::cout<<"Fehler, falsche eingabe!!!"<< std::endl;
    exit(0);
  }

  //Wenn alles passt gebe Ergebnis aus.
  std::cout<< "Das Ergebnis von: " << arg << " lautet: " << pop() <<std::endl;
}
