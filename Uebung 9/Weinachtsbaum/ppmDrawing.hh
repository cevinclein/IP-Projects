#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

//Klassrn zum zeichnen von Farbbildern, selbst geschieben.
//Habe dafür PGM aus dem Programmierkurs abgeändert und erweitert
//und versucht alle STL-Container zu entfernen da das erst noch in
//der Vorlesung besprochen werden muss.
//Erstellt Bilder im ppm-Format im RGB-Fabraum


//Abstrakte Klasse zum ertsellen von sehr primitiven Formen,
//reicht für den Weinachtsbaum
//Jedes shape gibt eine 2D-Matirx mit den RGB-Farbcoordinaten zurück
//welches das ColorCanvas dann zu einem Farbbild zusammenstellt.
class shape
{
    public:
        //Überschreibe alle Methoden der Base-Klasse.
        virtual int getHeigth() = 0;
        virtual int getWidth() = 0;
        //2D-Matrix
        virtual std::string **grid() = 0;
};

//Rechteck erbt shape 
class Rect : public shape
{
    public:
        //Standartfarbe ist schwarz
        Rect(int width, int heigth, std::string initColor = "000 000 000"): 
             _width(width), _heigth(heigth), _initColor(initColor)
        {}

        ~Rect()
        {
            restult = nullptr;
            delete restult;
        }

        int getHeigth() { return _heigth; }
        int getWidth() { return _width; }

        std::string **grid()
        {
            //Init 2D-Array
            restult = new std::string*[_heigth];

            for (int i = 0; i < _heigth; i++)
            {
                restult[i] = new std::string[_width];
            }  

            for (int i = 0; i < _heigth; i++)
            {
                for (int j = 0; j < _width; j++)
                {
                    //Alle Pixel in einer Farbe
                    restult[i][j] = _initColor; 
                }       
            }

            return restult;
        }

    private:
        int _width;
        int _heigth;
        std::string _initColor;
        std::string **restult;
};

//Primitives gleichseitiges Dreieck
class r_Triangle : public shape
{
    public:
        r_Triangle(int size, std::string backgroundColor, std::string shapeColor): 
             _size(size), _backgroundColor(backgroundColor), _shapeColor(shapeColor)
        {
            //Muss sein, Zahl ungerade, sonst keine Spitze
            if (_size % 2 == 0)
            {
                _size += 1;
            }  
        }

        ~r_Triangle()
        {
            restult = nullptr;
            delete restult;
        }

        int getHeigth() { return _size; }
        int getWidth() { return _size; }

        //Der Hintergrund ist rechteckig, aber das Dreieck nicht, deswegen
        //kann man zwei Farben dafür definieren.
        std::string **grid()
        {
            restult = new std::string*[_size];

            for (int i = 0; i < _size; i++)
            {
                restult[i] = new std::string[_size];
            }  

            for (int i = 0; i < _size; i++)
            {
                for (int j = 0; j < _size; j++)
                {
                    restult[i][j] = _backgroundColor; 
                }       
            }

            //zeichne Das Dreieck, die Linie ist immer 2 Pixel weniger 
            //als die vorherige Linie.
            int a = 0;
            int b = 0;
            for (int i = (_size + 1) / 2 - 1; i >= 0; i--)
            {
                for (int j = a; j < _size - b; j++)
                {
                    restult[i][j] = _shapeColor; 
                } 
                a++;
                b++;      
            }

            return restult;
        }

    private:
        int _size;
        std::string _backgroundColor;
        std::string _shapeColor;
        std::string **restult;
};

//Farbige Ausgabe von Bildern, die Koordinaten sind eine Reihe von 
//RGB-Trippeln wobei 255 der höchste Wert ist 0 der niedriste.
//Bsp: 255 255 255 ist weiß und 000 000 000 ist schwarz.
class ColorCanvas
{
    public:
        ColorCanvas(int width, int heigth, std::string initColor);
        ~ColorCanvas();
        int getHeigth();
        int getWidht();
        void setPixel(int x, int y, std::string RGB);
        std::string getPixel(int x, int y);
        void addShape(shape &s, int x, int y);
        void draw(std::string filename);

    private:
        const int _width;
        const int _heigth;
        std::string **matirx_2D;
        std::string _initColor;
};

ColorCanvas::ColorCanvas(int width, int heigth, std::string initColor = "000 000 000"): 
                        _width(width), _heigth(heigth), _initColor(initColor)
{
    //Init der Matirx, erstelle dynamisch alle Objekte.
    this->matirx_2D = new std::string*[_heigth];
    for (int i = 0; i < _heigth; i++)
    {
        this->matirx_2D[i] = new std::string[_width];
    }  

    //Init der Matirx mit der Hintergrundfarbe initColor.
    for (int i = 0; i < _heigth; i++)
    {
        for (int j = 0; j < _width; j++)
        {
            this->matirx_2D[i][j] = _initColor; 
        }       
    }
}

//Lösche Matrix
ColorCanvas::~ColorCanvas()
{
    this->matirx_2D = nullptr;
    delete this->matirx_2D;
}

int ColorCanvas::getWidht()
{
    return this->_width;
}

int ColorCanvas::getHeigth()
{
    return this->_heigth;
}

//Zeichne einen Pixel in einer RGB-Farbe
void ColorCanvas::setPixel(int x, int y, std::string RGB)
{
    this->matirx_2D[y][x] = RGB;
}

//Zeichne shape ins ColorCanvas
void ColorCanvas::addShape(shape &s, int x, int y)
{
    for(int i = 0; i < s.getHeigth(); i++)
    {
        for (int j = 0; j < s.getWidth(); j++)
        {
            this->matirx_2D[i + y][j + x] = s.grid()[i][j];
        }    
    }
}

std::string ColorCanvas::getPixel(int x, int y)
{
    return this->matirx_2D[y][x];
}

void ColorCanvas::draw(std::string filename)
{
    //Der Headder der Datei wird hier erstellt. Mit P3 wird gesagt, dass
    //man eine Anymap also eine Farbbild davon erstellen möchte
    //255 ist der höchste Wert der also weiß sein soll
    std::ofstream myfile (filename);
    myfile << "P3" << std::endl;
    myfile << _width << " " << _heigth << std::endl;
    myfile << "255" << std::endl;

    if (myfile.is_open())
    {
        //Schreibe alle Pixel der Matrix in die Datei
        //Alle Pixel sind RGB-Codes der form xxx xxx xxx, damit kann man
        //alle möglichen Bilder erstellen die man möchte.
        for (int i = 0; i < _heigth; i++)
        {
            for (int j = 0; j < _width; j++)
            {
                myfile << matirx_2D[i][j];
                
                //Trennt die einzelnen RGB-Trippel
                myfile << "  ";
            }
            myfile << std::endl;
        }
        
        myfile.close();
    }
    else std::cout << "Datei kann nicht geöffnet werden!";
}
