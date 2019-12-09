#include <iostream>
#include <cstdlib>

struct IntListElem
{
    IntListElem* next;
    int value;
};

struct IntList
{
    int count = 0;
    IntListElem* first;
};

//Noch aus Skript
void instert_int_first(IntList* list, int val)
{
    //Dynamische Speicherverwaltung wie gefordert.
    IntListElem* el = new IntListElem;
    el->value = val;

    el->next = list->first;
    list->first = el;
    list->count++;
}

//Lösche letztes Element.
IntListElem* pop_last(IntList* list)
{
    //Leere Liste gebe leeres Element zurück
    if(list->count == 0)
    {
        return new IntListElem;
    }
    else if(list->count == 1)
    {
        //Lösche erstes Element, bzw. einziges Element
        IntListElem* p = list->first;
        list->first = nullptr;
        delete list->first;
        list->count--;

        return p;
    }
    else if (list->count == 2)
    {
        IntListElem* get_last = list->first->next;
        list->first->next = nullptr;
        delete list->first->next;
        list->count--;
        return get_last;
    }  
    else
    {
        //Gebe letztes Element wieder
        IntListElem* get_last = list->first; 

        //Dann das zu löschende Element
        IntListElem* p = list->first;
    
        while (get_last != nullptr)
        {
            get_last = get_last->next;
            p = p->next;

            //Wenn das übernächste Element ein nullptr ist.
            if(get_last->next->next == nullptr)
            {
                get_last = get_last->next;
                
                //Lösche letztes Element
                p->next = nullptr;
                delete p->next;
                
                list->count--;
                break;
            }  
        }

        return get_last;
    }  
}


int main()
{
    //Ein paar Tests mit der einfach verketteten Liste, die ja eine Queue ist,
    //also nur löschen am Ende und hinzufügen am Anfang.
    
    IntList* li = new IntList; 

    //Wenn true wird das gemacht was in Aufgabe 3c steht, teste für große werte.
    //Ansonsten ein paar Ausgaben zum Testen der Queue.
    bool LaufZeitTest = false;

    if(LaufZeitTest)
    {
        for(int i = 0; i <= 100000; i++)
        {
            instert_int_first(li, rand() % 1000 + 1);
        }

        for(int i = 0; i < 100000; i++)
        {
            pop_last(li);
        }

        //Braucht 14.48s
    }
    else
    {
        for(int i = 0; i <= 5; i++)
        {
            instert_int_first(li, i);
        }

        for(IntListElem* p = li->first; p != nullptr; p = p->next)
        {
            std::cout << "List-Element: " << p->value << std::endl;
        }

        std::cout << "Lösche letztes Element: " << pop_last(li)->value << std::endl;
        std::cout << "Lösche letztes Element: " << pop_last(li)->value << std::endl;

        for(IntListElem* p = li->first; p != nullptr; p = p->next)
        {
            std::cout << "List-Element: " << p->value << std::endl;
        }

        std::cout << "Füge Element zum Anfang hinzu: 42" << std::endl;
        instert_int_first(li, 42);

        for(IntListElem* p = li->first; p != nullptr; p = p->next)
        {
            std::cout << "List-Element: " << p->value << std::endl;
        }
    } 

    return 0;  
}