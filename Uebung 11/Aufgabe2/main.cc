#include "Math_Vector.hh"

//Test Funktion für Operator ()
template<class T, int dim> void func(Math_Vector<T, dim> r)
{
   for (size_t i = 0; i < r.Dimension(); i++)
   {
       std::cout << r(i) * 100 << "  ";
   }   

   std::cout << std::endl;
}

int main()
{
    //Teste Vektoren-Klasse

    Math_Vector<int, 4> v0({4,3,4,5});
    Math_Vector<float, 4> v1({4,8,12.5,18.73});
    Math_Vector<double, 4> v2({2,2,2,2});
    Math_Vector<double, 7> v3({2.5,3.5,-13,0,34,123.1,122.54});

    (v0 + v1).print("v0 + v1");
    (v1 + v0).print("v1 + v0");

    std::cout << "v0 * v2 = " << v0 * v2 << std::endl;
    std::cout << "v2 * v1 = " << v2 * v1 << std::endl;

    (v0 * 2.54).print("v0 * 2.54");
    (v2 * 2.5).print("v2 * 2.5");

    v2(3) = 270;
    v2.print("v2(3) = 270");

    std::cout << "v2(3) = " << v2(3) << std::endl;
    std::cout << "Mittelwert v0 = " << v0.average() << std::endl;
    std::cout << "Betrag v0 = " << v0.betr() << std::endl;

    std::cout << "v3.min() = " << v3.min() << std::endl;
    std::cout << "v3.max() = " << v3.max() << std::endl;

    v1 = v2;

    v1.print("v1 = v2"); 

    std::cout << "Funktion func von v0 = ";
    func(v0);
}

