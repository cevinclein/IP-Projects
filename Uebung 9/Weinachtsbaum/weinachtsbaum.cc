#include "ppmDrawing.hh"

//Erstelle Weinachtsbaum, hat zwar keinen Schmuck, dafür schneit es auf
//dem Bild.
class Tree
{
    public:
        Tree(int x, int y);
        void show(ColorCanvas &cc);
    
    private:
        int _x;
        int _y;
};

Tree::Tree(int x, int y): _x(x), _y(y) {}

//Weinachtsbaum verwendet primitive Formen des ColorCanvas.
void Tree::show(ColorCanvas &cc)
{
    r_Triangle r(56, "051 080 117", "045 123 099");
    r_Triangle r1(100, "051 080 117", "045 123 099");
    r_Triangle r2(150, "051 080 117", "045 123 099");
    Rect rec(20, 75, "183 107 074");
    Rect bottom(cc.getWidht(), 20, "081 042 042");

    cc.addShape(r,50 + _x, 0 + _y);
    cc.addShape(r1,28 + _x, 29 + _y);
    cc.addShape(r2,0 + _x, 80 + _y);
    cc.addShape(rec,65 + _x, 156 + _y);
    cc.addShape(bottom, 0, cc.getHeigth() - 20);
}


int main()
{
    ColorCanvas c(600, 400, "051 080 117");
    Tree t(225,149);

    std::cout << "Dauert etwas bis das Bild erstellt ist. Weniger als 1Min" << std::endl;

    //Zeichne Schnee, auf dem Bild schneit es also.
    for (int i = 0; i < 300; i++)
    {
        c.setPixel(std::rand() % 600, std::rand() % 400, "255 255 255");
    }
    
    //Zeichne Baum.
    t.show(c);
    
    //Erstelle Datei.
    c.draw("Weinachtsbaum.ppm"); 
}