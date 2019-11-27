#include <iostream>

//Benutzerdefinierte Größe des Decks, n muss gerade sein!
//Man muss die Zahlen nicht nach der Reihenfolge angeben!
//Willkürliche Zahlen sind erlaubt solange sie dem int Datentyp entsprechen.
//Der Code wurde mit diesem Array compiliert, man kann, wie gesagt Arraygröße und 
//Elemente ändern und neu compilieren.
const int deck[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int deck_size = sizeof(deck) / sizeof(int);

//Funktion die Prüft ob deck im Anfangszustand ist
bool deck_check(int _deck[], int n)
{
    bool is_equal = true;

    for (int i = 0; i < n; i++)
    {
        if(_deck[i] != deck[i])
        {
            is_equal = false;
        }
    }
    return is_equal;
}

int main()
{
    //Wenn falsche Eingabe wiederholen (goto eigentlich schlecht aber einfacher)
    repeat:

    int inShuffle_or_outShuffle;

    std::cout<< "Bitte geben sie 0 für perfect out shuffle der größe " << deck_size << " ein" << std::endl;
    std::cout<< "Bitte geben sie 1 für perfect in shuffle der größe " << deck_size << " ein" << std::endl;

    std::cin>> inShuffle_or_outShuffle;

    //Will der User ein out- oder in-shuffle
    if(inShuffle_or_outShuffle == 0 || inShuffle_or_outShuffle == 1)
    {
        //temp_deck teilt das deck in 2 Hälften, so wie man es beim Shuffle macht
        int temp_deck_1[deck_size/2];
        int temp_deck_2[deck_size/2];

        int full_deck[deck_size];
        bool _deck_ckeck = true;

        //Wie oft wurde gemischt, bis Anfangszustand erreicht wurde.
        int misch_count = 0;

        std::cout<< std::endl;
        std::cout<< "Anfangszustand: ";
        for (int i = 0; i < deck_size; i++)
        {
            //gebe Anfangsdeck aus.
            std::cout<< deck[i] << " ";
        }
        std::cout<< std::endl << std::endl;
        

        for (int i = 0; i < deck_size/2; i++)
        {
            //temp_deck_1 und temp_deck_2 bekommen jeweils die eine Hälfte des Arrays deck
            temp_deck_1[i] = deck[i];
            temp_deck_2[i] = deck[i + deck_size/2];
        }

        //Solange Ausgangs Deck nicht erreicht wurde
        while(_deck_ckeck)
        {
            int k = 0; int j = 1; int z = 0; while(k < deck_size)
            {
                //Will man in- oder out-shuffle so muss man einfach die Zuordnung der 
                //Hälften des Decks tauschen, damit mit der zweiten Hälfte angefangen 
                //wird zu mischen oder der ersten.
                if(inShuffle_or_outShuffle == 0)
                {
                    full_deck[k] = temp_deck_1[z];
                    full_deck[j] = temp_deck_2[z];
                }
                if(inShuffle_or_outShuffle == 1)
                {
                    full_deck[k] = temp_deck_2[z];
                    full_deck[j] = temp_deck_1[z];
                }
                
                k += 2;
                j += 2;
                z++;
            }

            //temp_deck_1 und temp_deck_2 bekommen die neuen Werte des n-mal gemischten Decks deck
            //(jeweils die Hälften natürlich)
            for (int i = 0; i < deck_size/2; i++)
            {
                temp_deck_1[i] = full_deck[i];
                temp_deck_2[i] = full_deck[i + deck_size/2];
            }

            _deck_ckeck = !deck_check(full_deck, deck_size);

            //zählt Mischvorgänge
            misch_count++;

            //Ausgabe des Decks nach dem n-tem Mischvorgang (Zusatz)
            std::cout<< "Deck nach dem, " << misch_count << " mischen: ";
            for (int i = 0; i < deck_size; i++)
            {
                std::cout<< full_deck[i] << " ";
            }
            std::cout<< std::endl;
        }

        //Ausgabe: Wie viel Mischvorgänge hat es benötigt, bis zum Ausgangszustand
        std::cout<< std::endl;
        std::cout<< "Man hat " << misch_count <<" Mischvorgänge gbraucht" << std::endl << std::endl; 
    }
    else
    {
        //Falsche Eingabe halt
        std::cout<< "falsche eingabe bitte nur 0 oder 1 eingeben"<< std::endl;
        goto repeat;
    }
    return 0;
}