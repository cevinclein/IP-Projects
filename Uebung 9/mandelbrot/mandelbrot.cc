#include <iostream>
#include <cmath>
#include <string>

/*
Wenn kompilieren, bitte Kompileroptimierung -O3 oder -Ofast benutzen,
sonst dauert die Rechenzeit länger!!
*/

// Datentyp Complex in der Datei canvas.hh
#include "canvas.hh"

// Summiert zwei komplexe Zahlen z und c und schreibt das Ergebnis in z
void add_complex(Complex &z, Complex &c)
{
  z.imag += c.imag;
  z.real += c.real;
}

// Multipliziert zwei komplexe Zahlen z und c und schreibt das Ergebnis in z
void multiply_complex(Complex &z, Complex &c)
{
  double z_real;
  double z_imag;

  z_real = z.real*c.real - z.imag*c.imag;
  z_imag = z.real*c.imag + z.imag*c.real;

  z.real = z_real;
  z.imag = z_imag;
}

// Betrag einer komplexen Zahl
double betrag(Complex z)
{
  return sqrt(z.real*z.real + z.imag*z.imag);
}

//Will man die Auflösung des Bildes ändern so muss man natürlich center_x
//und center_y anpassen. Außerdem muss auch scale angepasst werden
//sonst hätte man segmentation fault oder Bus error. In der Aufgabe war nur
//ein Bild mit der Auflösung 4000*3000px gefordert.
void mandelbrot(Canvas &canvas, double threshold, int maxIt, std::string filename)
{
  //Alle komplexen Zahlen in diesem Intervall absuchen, mathematisch
  //gesehen reicht das Intervall von -2 bis 2 sowohl beim Realteil als
  //auch beim Imag-Teil
  using intervall = double;
  intervall imagRange[2] = {-2.0, 2.0}; 
  intervall realRange[2] = {-2.668, 2.668}; 

  //Schrittweite, es gäbe eigentlich unendlich viele Komplexe Zahlen
  //geht aber nicht deswegen kleine Schrittweite.
  double steps = 0.0002;

  //Wie groß soll das Bild sein. Der Computer kann nur ganze Pixel
  //darstellen, wir müssen also einen großen Faktor wählen um
  //alle Pixel anzeigen zu können um also alles Ganzahlig zu machen
  int scale = 750;

  //Wir fangen mit der kleinsten komplexen Zahl an im Intervall, die wir dann
  //testen, ob sie zur Mandelbrotmenge gehört oder nicht.
  Complex c = canvas.coord(imagRange[0], realRange[0]);
  
  //Iteriere jede möglich komplexe Zahl im intervall durch
  //mit der Schrittweite steps
  while(c.imag <= imagRange[1])
  {
    c.real += steps;

    //speichere die konstante, also die Zahl die man testen will
    Complex z = c;

    //Iteriere durch den Realteil bis zum ende des Intervalls vom Realteil
    if (c.real >= realRange[1])
    {
      //c "zurücksetzen"
      c = z; 
      c.real = realRange[0];
      c.imag += steps;
      continue;
    }
  
    //Iterationen zum Testen ob Zahl zu Mandelbrotmenge gehört
    for (int k = 0; k <= maxIt; k++)
    {
      //Ist Betrag kleiner nach k iterationen als threshold füge zur
      //Mandelbrotmege hinzu, durch schwarfärben der Pixel
      if (betrag(c) <= threshold && k == maxIt)
      {
        canvas.writePixel(z.imag*scale, z.real*scale, 0);
        c = z;
        break;
      }

      //Wird Betrag größer als threshold kommt es darauf an nach welcher
      //iteration, dem-entsprechend wird die Farbe des Pixels wie in der
      //Aufgabe gesetzt
      if(betrag(c) > threshold)
      {
        k += 2;
        canvas.writePixel(z.imag*scale, z.real*scale, log(k)*100);
        c = z;
        break;
      }

      //Führe Iterationsformel aus
      multiply_complex(c, c);
      add_complex(c, z);
    }
  }

  //Erstelle das Bild
  canvas.write(filename);
}

int main()
{
  //Erstelle Bild mit der Auflösung 4000 * 3000 Pixel
  Canvas c(2000, 1500, 4000, 3000, 4000, 3000);

  std::cout<< "Erstellen eines pgm-Bildes der Auflösung 4000*3000px von der Mandelbrotmenge." << std::endl;
  std::cout << "Der Vorgang kann je nach PC etwa 1 Min dauern..." << std::endl;
  
  //Mathematisch bewiesen Reicht ein Flucht-Radius von 2
  mandelbrot(c, 2, 50, "mandelbrot.pgm");

  std::cout << "Bild wurde erstellt." << std::endl;
  return 0;
}
