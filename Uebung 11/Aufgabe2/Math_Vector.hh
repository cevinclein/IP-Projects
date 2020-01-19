#include <iostream>
#include <vector>
#include <cmath>
#include <string>

template<class T, int dim>
class Math_Vector
{
    public:
        //Init mit gleiche Zahle,
        Math_Vector(int INIT);
        //Init mit Liste {n1, n2, ..., nk}
        Math_Vector(std::vector<T> INIT);
        //Funktor
        T &operator() (int i);
        //Add
        template<class K> Math_Vector<T, dim> operator+(Math_Vector<K, dim> &mv);
        //Skalarprod
        template<class K> double operator*(Math_Vector<K, dim> &mv);
        //S-Mult...
        template<class K> Math_Vector<T, dim> operator*(K skl);
        //Zuweisung
        template<class K> Math_Vector<T, dim>& operator=(const Math_Vector<K, dim>&);
        
        T max() const;
        T min() const;
        double average() const;

        //Betrag
        double betr() const;

        int Dimension() const { return dim; }

        //Wichtig für const obj eines anderen Typs
        std::vector<T> rawData() const { return this->_data; }

        //Drucke alle Werte des Vektors
        void print(std::string info = "") const;
        
    private:
        std::vector<T> _data;
};


template<class T, int dim> 
Math_Vector<T, dim>::Math_Vector(int INIT)
{
    for(int i = 0; i < dim; i++)
    {
        _data.push_back(INIT);
    }
}

template<class T, int dim> 
Math_Vector<T, dim>::Math_Vector(std::vector<T> INIT)
{
    if(INIT.size() != this->Dimension())
        throw std::domain_error("Argumente stimmen nicht mit Dimension ein");
    
    this->_data = INIT;
}

//Zugriff auf Daten des Vektors, Funktor
template<class T, int dim> 
T& Math_Vector<T, dim>::operator()(int i)
{
    if(i >= this->Dimension()) 
        throw std::domain_error("Wert groesser als Dimension");

    return _data.data()[i];
}

//Addition, der Datentyp der Element ist jener, welcher Vektor am
//Anfang der Multiplikation steht
template<class T, int dim> template<class K> 
Math_Vector<T, dim> Math_Vector<T, dim>::operator+(Math_Vector<K, dim> &mv)
{
    Math_Vector<T, dim> res(0);

    if(this->Dimension() != mv.Dimension())
        throw std::invalid_argument("Vektoren muessen gleiche Dimension haben");
    
    for(int i = 0; i < this->Dimension(); i++)
        res(i) = (*this)(i) + mv(i);
    
    return res;
}


template<class T, int dim> template<class K> 
double  Math_Vector<T, dim>::operator*(Math_Vector<K, dim> &mv)
{
    double res = 0;

    if(this->Dimension() != mv.Dimension())
        throw std::invalid_argument("Vektoren muessen gleiche Dimension haben");

    for(int i = 0; i < this->Dimension(); i++)
        res += (*this)(i) * mv(i);
    
    return res;
}

//Achtung geht nur in eine Richtung vec*n. Error: n*Vec;
//Mögliche Lösung alle Operatoren mit friend überladen.
template<class T, int dim> template<class K> 
Math_Vector<T, dim> Math_Vector<T, dim>::operator*(K skl)
{
    Math_Vector<T, dim> res(0);

    for(int i = 0; i < this->Dimension(); i++)
        res(i) = (*this)(i) * skl;
    
    return res;
}

template<class T, int dim> 
T Math_Vector<T, dim>::max() const 
{
    T res = this->_data[0];
    for(auto it : this->_data)
        res = res < it ? it : res;

    return res;
}

template<class T, int dim> 
T Math_Vector<T, dim>::min() const
{
    T res = this->_data[0];
    for(auto it : this->_data)
        res = res > it ? it : res;

    return res;
}

template<class T, int dim> 
double Math_Vector<T, dim>::average() const
{
    double res = 0;
    for(auto it : this->_data)
        res+= it;

    return res / this->Dimension();
}

template<class T, int dim> 
void Math_Vector<T, dim>::print(std::string info) const
{
    std::cout << info << ", vector:" << std::endl << "{" << std::endl << "   ";
    
    for(auto it : this->_data)
        std::cout << it << "  ";
    
    std::cout << std::endl << "}" << std::endl;
}

//Vektoren mit unterschiedlichem Typ können auch zugewiesen werden.
template<class T, int dim> template<class K> 
Math_Vector<T, dim> &Math_Vector<T, dim>::operator=(const Math_Vector<K, dim> &mv)
{
    if(this->Dimension() != mv.Dimension())
        throw std::invalid_argument("Vektoren muessen gleiche Dimension haben");
    
    for(int i = 0; i < this->Dimension(); i++)
        this->_data[i] =  mv.rawData()[i];
    
    return *this;
}

template<class T, int dim>
double Math_Vector<T, dim>::betr() const
{
    double res = 0;
    for(auto it : this->_data)
        res += it*it;
    
    return sqrt(res);
}
