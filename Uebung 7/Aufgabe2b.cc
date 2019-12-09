#include <iostream>

// Ein Listenelement
struct IntListElem 
{
    IntListElem* next;  // Zeiger auf nächstes Element
    int value;          // Daten zu diesem Element  
};

// Eine Liste
struct IntList 
{
    int count;          // Anzahl Elemente in der Liste
    IntListElem* first; // Zeiger auf erstes Element der Liste
};


// Initialisiere eine Listenstruktur
void empty_list (IntList* l)
{
    l->first = 0;   // 0 ist keine gueltige Adresse: Liste ist leer
    l->count = 0;
}

// Fuege ein Element nach einem gegebenem ein
void insert_in_list (IntList* list, IntListElem* where, IntListElem* ins)
{
    if (where==0) // fuege am Anfang ein
    {
        ins->next = list->first;
        list->first = ins;
        list->count = list->count + 1;
    }
    else         // fuege nach where ein
    {
        ins->next = where->next;
        where->next = ins;
        list->count = list->count + 1;
    }
}

// Entferne ein Element nach einem gegebenem
// Liefere das entfernte Element zurueck
IntListElem* remove_from_list (IntList* list, IntListElem* where)
{
    IntListElem* p;  // das entfernte Element

    // where==0 dann entferne erstes Element
    if (where==0) 
    {
        p = list->first;
        if (p!=0)
	    {
	        list->first = p->next;
	        list->count = list->count - 1;
	    }
        return p;
    }

    // entferne Element nach where
    p = where->next;
    if (p!=0)
    {
        where->next = p->next;
        list->count = list->count - 1;
    }
    return p;
}

//Erzeugt eine Liste mit Linearen Anteil k, und dem Zyklusanteil n
//Die Elementenanzahl der Liste beträgt n + k;
//Beim ersten Durchlauf wird noch der Lineare Anteil k mit ausgegeben, danach nur 
//noch der Zyklus n
void createListWithZkyl(IntList* li, int k, int n)
{
    IntListElem* beginZykl; //Ab wann soll Zyklus beginnen

    for(int i = 1; i <= n + k; i++)
    {
        IntListElem* el = new IntListElem;
        el->value = i;

        if(i == n)
        {
            beginZykl = el; //Verweis auf beginn Zyklus
        }

        insert_in_list(li, 0, el);
    }

    //Wenn letztes Element->next = nullptr, dann setzte next auf beginZykl
    for(IntListElem* p = li->first; p != 0; p = p->next)
    {
        if(p->next == nullptr)
        {
            p->next = beginZykl;
            break;
        }
    }
}

//Einfach nur eine Liste mit Werten Füllen die Linear ist
void create_linear_List(IntList* li, int n)
{
    for(int i = 0; i <= n; i++)
    {
        IntListElem* el = new IntListElem;
        el->value = i;

        insert_in_list(li, 0, el);
    }
}

int Hase_Igel_Algo(IntList* li)
{
    IntListElem* igel = li->first; //Nächstes Element
    IntListElem* hase = li->first->next; //Übernächstes Element
    int zykl_count = 0;

    //Solange Hase und Igel nicht auf die selbe Adresse zeigen
    while (hase != igel)
    {  
        //Wenne einer der Pointer null ist hat Liste keinen Zyklus
        if(hase == nullptr  || igel == nullptr || hase->next == nullptr)
        {
            return 0;
        }

        igel = igel->next;
        hase = hase->next->next;
    }

    //Wenn Liste Zyklus hat, ist igel oder hase auf jeden Fall im Zyklus
    //Also solange Zyklus durchlaufen, bis man wieder am selben Element wie
    //am Anfang war, zykl_count zählt bis dahin alle Schritte.
    //p != 0 wird niemals false 
    for(IntListElem* p = igel->next; p != 0; p = p->next)
    {
        zykl_count++;

        if(p == igel)
        {
            break;
        }
    }
    return zykl_count;
}

//Ausgabe einer Liste auf der Konsole, wenn Liste Zyklus hat, dann unendliche Ausgabe
//deswegen stop
void print_list(IntList* l, int stop)
{
    int i = 0;
    for(IntListElem* p = l->first; p != 0; p = p->next)
    {
        i++;
        std::cout << p->value << ", ";

        if(i == stop) 
            break;
    }
}


int main()
{
    //Ein paar Tests, wie in der Aufgabe

    IntList* list_linear = new IntList;
    IntList* list_zykl = new IntList;

    //Init
    empty_list(list_linear);
    create_linear_List(list_linear, 10);

    //Init
    empty_list(list_zykl);
    createListWithZkyl(list_zykl, 4, 6);

    std::cout << std::endl << "Erzeuge Liste mit 10 Elementen. Linearer Anteil k = 4" << std::endl;
    std::cout << "und der zyklische Anteil n = 6: " << std::endl;
    print_list(list_zykl, 22);
    std::cout << std::endl;

    std::cout << std::endl << "Teste Hase Igel an der Liste mit Zyklus (list_zykl)" << std::endl;
    std::cout<< "Läne Zyklus: " << Hase_Igel_Algo(list_zykl) << std::endl;

    std::cout << std::endl << "Teste Hase Igel an der Liste ohne Zyklus (list_linear)" << std::endl;
    std::cout<< "Läne Zyklus: " << Hase_Igel_Algo(list_linear) << std::endl << std::endl;

    return 0;
}