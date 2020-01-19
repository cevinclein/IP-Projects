#include "SimpleArray.hh"

//Aus Skript Umwandlung mit SimpleArray und ein paar Änderungen.

template <class T>
class Polynomial : public SimpleArray<T>
{

    public:
        // konstruiere Polynom vom Grad n
        Polynomial (int n);

        // Default-Destruktor ist ok
        // Default-Copy-Konstruktor ist ok
        // Default-Zuweisung ist ok

        // Grad des Polynoms
        int degree ();

        // Auswertung
        float eval (T x);

        // Addition von Polynomen
        Polynomial operator+ (Polynomial q);

        // Multiplikation von Polynomen
        Polynomial operator* (Polynomial q);

        // Gleichheit
        bool operator== (Polynomial q);

        // drucke Polynom
        void print (); 
};
template<class T> Polynomial<T>::Polynomial (int n) : SimpleArray<T>(n + 1, 0.0) 
{}

template<class T> bool Polynomial<T>::operator== (Polynomial q)
{
    if (q.degree()>degree())
    {
        for (int i=0; i<=degree(); i=i+1)
            if ((*this)[i]!=q[i]) return false;
        for (int i=degree()+1; i<=q.degree(); i=i+1)
            if (q[i]!=0.0) return false;
    }
    else
    {
        for (int i=0; i<=q.degree(); i=i+1)
            if ((*this)[i]!=q[i]) return false;
        for (int i=q.degree()+1; i<=degree(); i=i+1)
            if ((*this)[i]!=0.0) return false;
    }

    return true;
}

// Auswertung
template<class T> float Polynomial<T>::eval(T x)
{
    float sum=0.0;

    // Hornerschema
    for (int i=this->maxIndex(); i>=0; i=i-1)
        sum = sum*x + this->operator[](i);
    return sum;
}

// Grad auswerten
template <class T> 
int Polynomial<T>::degree ()
{
    return this->maxIndex();
}

// Addition von Polynomen
template <class T> 
Polynomial<T> Polynomial<T>::operator+ (Polynomial q)
{
    int nr=degree(); // mein grad

    if (q.degree()>nr) nr=q.degree();

    Polynomial r(nr); // Ergebnispolynom

    for (int i=0; i<=nr; i=i+1)
    {
        if (i<=degree())
            r[i] = r[i]+(*this)[i]; // add me to r
        if (i<=q.degree())
            r[i] = r[i]+q[i];       // add q to r
    }

  return r;
}

// Multiplikation von Polynomen
template <class T>
Polynomial<T> Polynomial<T>::operator* (Polynomial q)
{
    Polynomial r(degree()+q.degree()); // Ergebnispolynom

    for (int i=0; i<=degree(); i=i+1)
        for (int j=0; j<=q.degree(); j=j+1)
            r[i+j] = r[i+j] + (*this)[i]*q[j];

  return r;
}

// Drucken
//Habe Ausgabe etwas abgeändert, damit das Monom mit dem Koeffizienten 0
//Nicht angezeigt wird.
template <class T> 
void Polynomial<T>::print ()
{
    if (degree() < 0)
        std::cout << 0;
    else
        std::cout << (*this)[0];
    

    for (int i=1; i<=this->maxIndex(); i=i+1) 
    {
        if((*this)[i] == 0)
        {
            continue;
        }

        if((*this)[i] < 0)
        {
            std::cout << (*this)[i] << "*x^" << i;
        }
        else
        {
           std::cout << "+" << (*this)[i] << "*x^" << i;
        }   
    }
    
    std::cout << std::endl;
}