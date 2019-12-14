#include <iostream>

//Enhält Aufgabe 2a und 2b, habe private Methoden definiert, auch Listen-Elemente 
//sind privat, sowie Variablen eben. Alles andere wie gefordert in die Klasse 
//geschrieben

//Signatur Interface, nur Definitionen
class IntList 
{
    public:
        // Konstruktor, erzeugt eine leere Liste
        IntList();
        //Copy-Konstruktor
        IntList(const IntList& il);
        //Zuweisung
        IntList& operator=(const IntList& other);
        // Destruktor, loescht gesamten Listeninhalt
        ~IntList();
        // Gibt Anzahl der Elemente zurueck
        int getCount();
        // Gibt zurueck, ob die Liste leer ist
        bool isEmpty();
        // Gibt die Liste aus
        void print();
        // Fuegt die Zahl 'element' an der (beliebigen) Position 'position' ein
        void insert(int element, int position);
        // Loescht das Element an der Position 'position'
        void remove(int position);
        // Gibt den Wert des Elements an der Position 'position' zurueck
        int getElement(int position); 
 
    private:
        int _count;
        struct IntListElem; 
        IntListElem* first;
            
};

//Im Folgenden Implementierung der Methoden, man kann Signatur und
//Implementierung auch in Dateien auslagern wenn man will oder wenn es
//Sinn macht.

//Listenelement, in Klasse definiert
struct IntList::IntListElem
{
    IntListElem* next;
    int value;
};

//Init
IntList::IntList()
{
    this->_count = 0;
    this->first = nullptr;
}

//Destruktor, löscht alle dynamisch erzeugten Elemente der
//Liste, wenn Umgebung verlassen wird
IntList::~IntList()
{
    while(this->first != nullptr)
    {
        this->remove(0);
    }

    std::cout << "Destruktor: Liste gelöscht!" << std::endl;
}

int IntList::getCount()
{
    return this->_count;
}

//Standart-Position 0, wenn position nicht angegeben wird!
void IntList::insert(int element, int position = 0)
{
    //position nur kleiner gleich als Liste, größer Null
    if(position <= this->_count && position >= 0)
    {
        //Alle Listenelemente dynamisch erzeugt.
        IntListElem* el = new IntListElem;
        el->value = element;
        
        //Aus Skript
        if (position == 0)
        {
            el->next = this->first;
            this->first = el;
        }
        else
        {
            //Listenelement an Position i finden, Zeiger umbiegen, p einfügen
            //insert aus Skript
            int i = 0;
            for(IntListElem* p = this->first; p != nullptr; p = p->next)
            {
                i++;
                if(position == i)
                {
                    el->next = p->next;
                    p->next = el;
                    break;
                }
            }
        }

        this->_count++; 
    }
    else
    {
        std::cout << "Falsch!" << std::endl;
    }  
}

void IntList::remove(int position)
{
    //position mit erlaubten Werten
    if(position <= this->_count && position >= 0)
    {
        //zu löschendes Element
        IntListElem* p;

        //Aus Skript
        if(position == 0)
        {
            p = this->first;

            if(p != nullptr)
            {
                this->first = p->next;
                p = nullptr;
                delete p;
                this->_count--;
            }
        }
        else
        {
            int i = 0;
            //Gehe solange next bis i = position, lösche p mit der
            //dynamischen Speicherverwaltung, biege Zeiger um
            for(p = this->first; p != nullptr; p = p->next)
            {
                i++;
                if(position == i)
                {
                    p->next = p->next->next;
                    p = nullptr;
                    delete p;
                    this->_count--;
                    break;
                }
            }
        }     
    }
    else
    {
        std::cout << "Falsch!" << std::endl;
    }  
}

//Ausgabe der gesamten Liste
void IntList::print()
{
    std::cout << "IntList" << std::endl << "{" << std::endl;
    int i = 0;
    for(IntListElem* p = this->first; p != nullptr; p = p->next)
    {
        std::cout << "    " << i << ": " << p->value << std::endl;
        i++;
    }
    std::cout << "}" << std::endl;
}

//Ausgabe einzelnes Element
int IntList::getElement(int position)
{
    int i = 0;
    for(IntListElem* p = this->first; p != nullptr; p = p->next)
    {
        if(position == i)
        {
            return p->value;
        }

        i++;
    }

    return 0;
}

bool IntList::isEmpty()
{
    return this->_count == 0 ? true : false;
}

//Zuweisung
IntList& IntList::operator=(const IntList& other)
{
    //Nicht sich selbst zuweisen
    if(this != &other)
    {
        //Liste Leeren, alle dyn. erzeugten Elemente löschen
        while(this->first != nullptr)
        {
            this->remove(0);
        }

        //Elemente von other übergeben
        int i = 0; for (IntListElem* p = other.first; p != 0; p = p->next)
        {
            this->insert(p->value, i);
            i++;
        }
    }

    return *this;
}

//Copy-Konstruktor, für neue Instanzen usw...
IntList::IntList(const IntList& il)
{
    int i = 0; for (IntListElem* p = il.first; p != 0; p = p->next)
    {
        this->insert(p->value, i);
        i++;
    }

    this->_count = il._count;
}

int main()
{
    IntList list; 

    list.insert(30); 
    list.insert(20); 
    list.insert(10); 
    list.print();

    list.remove(2); 
    std::cout << "Element auf index[2] entfernt" << std::endl;
    list.print();

    list.insert(30, 2); 
    std::cout << "Element 30 auf index[2] gesetzt" << std::endl;
    list.print();

    list.insert(40, 3); 
    std::cout << "Element 40 auf index[3] gesetzt" << std::endl;
    list.print();

    IntList copy(list);

    std::cout << "Copy-Konstrukt. Kopieren von list in copy" << std::endl;
    std::cout << "copy, ";
    copy.print();

    copy.remove(0); 
    std::cout << "Element auf index[0] entfernt, von copy" << std::endl;
    std::cout << "copy, ";
    copy.print(); 
    list.print();

    copy = list; 
    std::cout << "copy = list" << std::endl;
    std::cout << "copy, ";
    copy.print();

    return 0;
}