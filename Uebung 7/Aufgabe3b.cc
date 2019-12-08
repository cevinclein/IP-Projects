#include <iostream>
#include <cstdlib>

//Doppelt verkette Liste (ist eine Queue in dem Fall), mit Eigenschaften wie in der Aufgabe gefordert
//Man kann die Liste von vorn und von hinten iterieren, wegen den zwei Zeigern

struct IntListElem
{
    IntListElem* next; //Das nächste Element
    IntListElem* previous; //Das vorherige Element
    int value;
};

struct IntList
{
    int count = 0;
    IntListElem* first; //Erstes Element
    IntListElem* last; //Letztes Element
};


void instert_int_first(IntList* list, int val)
{
    IntListElem* el = new IntListElem;
    el->value = val;

    el->next = list->first;
    list->first = el;

    //Zeigen ab count > 0 auf vorheriges Element mit previous
    if(list->count > 0)
    {
        el->next->previous = el;
    }

    list->count++;

    //Das erste Element wird dann, das letzte sein müssen
    if(list->count == 1)
    {
        list->last = el;
    }  
}

IntListElem* pop_last(IntList* list)
{
    //Wenn liste leer keine Elemente also nullptr
    //Wenn man auf Elemente einer Leeren Liste zugreift ist das ein
    //Segmentation-Fault, gibt ja nichts in der Liste.
    if(list->count == 0)
    {
        return nullptr;
    }
    //Lösche erstes und letztes Element, sind ja gleich bei einem Elemnet
    else if(list->count == 1)
    {
        IntListElem* p = list->first;
        list->last = nullptr;
        list->first = nullptr;

        delete list->last;
        delete list->first;

        list->count--;

        return p;
    }

    //Wenn mehr als 1 Element, muss der Zeiger des letzten Elements
    //auf das vorherige Zeigen, geht bei doppeltverkettenten Listen aber 
    //einfach.
    IntListElem* p = list->last;
    list->last = list->last->previous;

    list->last->next = nullptr;
    delete list->last->next;
    list->count--;

    return p;
}

//Einfach die Ausgabe der Elemente in der Liste einmal von vorne
//und von hinten.
void print_List_Elems(IntList* li)
{
    std::cout<<std::endl<< "Iteriere von vorne nach hinten:" << std::endl;

    //Wie bei einfach verketteten Listen immer das nächste Element von vorn nach hinten
    for(IntListElem* p = li->first; p != 0; p = p->next)
        std::cout << p->value << " ";

    std::cout<<std::endl <<std::endl<< "Iteriere von hinten nach vorne:" << std::endl;

    //Weil das eine doppelt verkettete Liste ist kann man auch von hinten nach vorne,
    //wegen dem Zeiger auf das vorherige Element, und dem Zeiger auf das letzte Element
    for(IntListElem* p = li->last; p != 0; p = p->previous)
        std::cout << p->value << " ";

    std::cout<<std::endl;
}

int main()
{
    IntList* li = new IntList; 

    //Wenn true wird das gemacht was in Aufgabe 3c steht, teste für große werte.
    //Ansonsten ein paar Ausgaben zum Testen der Queue.
    bool laufZeitTest = true;

    if(laufZeitTest)
    {
        for(int i = 0; i <= 100000; i++)
        {
            instert_int_first(li, rand() % 1000 + 1);
        }

        for(int i = 0; i < 100000; i++)
        {
            pop_last(li);
        }

        //Braucht 0.369s
    }
    else
    {
        //Liste mit Elementen bestücken
        for(int i = 0; i <= 7; i++)
        {
            instert_int_first(li, i);
        }
    
        print_List_Elems(li);

        std::cout<<std::endl;
        for(int i = 0; i <= 2; i++)
            std::cout<<"Lösche letztes Element: " << pop_last(li)->value <<std::endl;

        print_List_Elems(li);

        std::cout<<std::endl;
        for(int i = 0; i <= 2; i++)
        {
            std::cout <<"Füge Element zum Anfang: " << i + 42 << std::endl;
            instert_int_first(li, i + 42);
        }

        print_List_Elems(li);
        std::cout<<std::endl;
    }
}