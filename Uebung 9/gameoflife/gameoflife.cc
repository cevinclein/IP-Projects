#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <fstream>


const int Arr_Init = 500;
int steps = 0;
bool TwoDBoolArray[Arr_Init + 1][Arr_Init + 1];


//Die Regel, generell für alle Automaten
struct Regel
{
    //Datentyp ein 2D Array
    typedef bool Daten[Arr_Init + 1][Arr_Init + 1];
    virtual void anwenden(Daten& daten, int gridsizeY, int gridsizeX) = 0;
};

class GameOfLifeRules : public Regel
{
    public:
        typedef bool Daten[Arr_Init + 1][Arr_Init + 1];

        void anwenden(Daten& daten, int gridsizeY, int gridsizeX)
        {
            this->Display(daten, gridsizeY, gridsizeX);
            this->liveOrDie(daten, gridsizeY, gridsizeX);
        }

    private:

        //Konsolenausgabe der Game of live
        void Display(Daten& grid, int gridsizeY, int gridsizeX)
        {
            std::stringstream ss;

            for(int a = 1; a < gridsizeY; a++)
            {
                for(int b = 1; b < gridsizeX; b++)
                {
                    if(grid[a][b] == true)
                    {
                        ss << " *";
                    }
                    else
                    {
                        ss << "  ";
                    }
                    if(b == gridsizeX - 1)
                    {
                        ss << std::endl;
                    }
                }
            }
    
            //Lösche nach jedem step Konsoleninhalt
            std::cout << "\x1B[2J\x1B[H" << "Step: " << steps << std::endl << ss.str();
        }

        //Kopieren der Girds oder 2D Arrays für vergleichszwecke
        void CopyGrid (Daten& grid, Daten& grid2, int gridsizeY, int gridsizeX)
        {
            for(int a =0; a < gridsizeY; a++)
            {
                for(int b = 0; b < gridsizeX; b++)
                {
                    grid2[a][b] = grid[a][b];
                }
            }
        }

        //Regeln anwenden mit der Randbedingung
        void liveOrDie(Daten& grid, int gridsizeY, int gridsizeX)
        {
            Daten grid2;
            //Vergleiche Grid
            CopyGrid(grid, grid2, gridsizeY, gridsizeX);

            for(int a = 1; a < gridsizeY; a++)
            {
                for(int b = 1; b < gridsizeX; b++)
                {
                    int life = 0;
                    for(int c = -1; c < 2; c++)
                    {
                        for(int d = -1; d < 2; d++)
                        {
                            if(!(c == 0 && d == 0))
                            {
                                if(grid2[a+c][b+d]) 
                                {
                                    ++life;
                                }
                            }
                        }
                    }
                    if(life < 2) {grid[a][b] = false;}
                    else if(life == 3){grid[a][b] = true;}
                    else if(life > 3){grid[a][b] = false;}
                }
            }
        }
};

//generell kann damit jeder Automat gemeint sein, nicht nur das Game-of-life
class Automat
{
    public:

        typedef bool Daten[Arr_Init + 1][Arr_Init + 1];

        Automat(Daten& daten, Regel& regel) : _daten(daten) , _regel(regel)
        {}

        void doSteps(int n = 1, double speed = 1)
        {
            for (int i=0; i < n; ++i)
            {
                usleep(speed*1.e6);
                _regel.anwenden(_daten, _gridsizeY, _gridsizeX); 
                steps++;    
            }
        }

        //Lese Dateien für die Startwerte aus
        void writeDataInArray(std::string filename)
        {
            std::string line;
            std::ifstream myfile(filename);
            int y = 0;

            std::getline(myfile, line);
            std::stringstream ss;
            for(auto it : line)
            {
                if(it == ' ')
                {
                    _gridsizeY = std::stoi(ss.str());
                    ss.str("");
                    continue;
                }
                ss << it;
            }
            _gridsizeX = std::stoi(ss.str()); 

            if (myfile.is_open())
            {
                while (std::getline(myfile, line))
                {
                    int t = 0;
                    for (auto it: line)
                    {
                        if(it == '0')
                            _daten[y][t] = 0;

                        if(it == '1')
                            _daten[y][t] = 1;

                        if(it == ' ')
                            continue;
                        t++;
                    }
                    y++;
                }
                myfile.close();
            }
        }

    private:
        Daten& _daten;
        Regel& _regel;

        //Größe der Anzeigefläche
        int _gridsizeY; 
        int _gridsizeX;
};

int main()
{
    GameOfLifeRules gmfr;
    Automat a(TwoDBoolArray, gmfr);

    std::string txt;
    int n;
    double speed;

    std::cout << "Bitte Terminal so groß wie möglich machen!!!" << std::endl << std::endl;

    std::cout << "Bitte Textdatei eingeben für Game of Life" << std::endl;
    std::cin >> txt;
    std::cout << "Bitte Iterationszahl eingeben" << std::endl;
    std::cin >> n;
    std::cout << "Bitte Geschwindigkeit eingeben in Sekunden" << std::endl;
    std::cin >> speed;

    a.writeDataInArray(txt);
    a.doSteps(n, speed);
}

