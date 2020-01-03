#include <string>
#include "pgm.hh"

struct Complex
{
  double real;
  double imag;
};

class Canvas
{
public :
  // Konstruktor, erzeuge int* _pixels
  Canvas(double center_x, double center_y,
         double width, double height,
         int horPixels, int vertPixels);

  // Desktruktor, raeume int* _pixels auf
  ~Canvas();

  // gibt die Breite des Bildes zurueck
  double width();

  // gibt die Hoehe des Bildes zurueck
  double height();

  // gibt die Anzahl an horizontalen Pixeln
  int horPixels();

  // gibt die Anzahl an vertikalen Pixeln
  int vertPixels();

  // gebe die Koordinaten des Pixels (i,j) als Complex zurueck
  Complex coord(int i, int j);

  // schreibe value an den Pixel (i,j)
  // Ueberlegen Sie wie aus (i,j) den flachen Index bei row-major bekommen
  void writePixel(int i, int j, int value);

  // Zugang zum Pixel (i,j) im 1D Array
  // Ueberlegen Sie wie aus (i,j) den flachen Index bei row-major bekommen
  int operator()(int i, int j);

  // schreibe Bild mit Dateinamen filename
  void write(std::string filename);

private :
  double _center_x;
  double _center_y;
  double _width;
  double _height;
  int _horPixels;
  int _vertPixels;
  int* _pixels;
};

Canvas::Canvas(double center_x, double center_y,
               double width, double height,
               int horPixels, int vertPixels)
{
  this->_center_x = center_x;
  this->_center_y = center_y;
  this->_width = width;
  this->_height = height;
  this->_horPixels = horPixels;
  this->_vertPixels = vertPixels;
  this->_pixels = new int[(_vertPixels)*(_horPixels)];
}

Canvas::~Canvas()
{
  delete this->_pixels;
  this->_pixels = nullptr;
}

double Canvas::width()
{
  return this->_width;
}

double Canvas::height()
{
  return this->_height;
}

int Canvas::horPixels()
{
  return this->_horPixels;
}

int Canvas::vertPixels()
{
  return this->_vertPixels; 
}

Complex Canvas::coord(int i, int j)
{
  Complex cx;
  cx.real = j;
  cx.imag = i;

  return cx;
}

//row major prinzip, funktioniert nur wenn man Höhe und Breite kennt.
//Koordinaten von der Bildmitte aus
void Canvas::writePixel(int i, int j, int value)
{
  this->_pixels[(i + (int)this->_center_y)*this->_horPixels + j + (int)this->_center_x] = value;
}

//Gebe Val von row major zurück
int Canvas::operator()(int i, int j)
{
  return this->_pixels[i*this->_horPixels + j];
}

// diese Methode ist bereits implementiert
void Canvas::write(std::string filename)
{
  write_pgm(_pixels,_horPixels,_vertPixels,filename);
}
