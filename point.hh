#include <iostream>
#include <array>
#include <cmath>

template<typename Coord, int dim>
class Point
{
    public:
        Point();
        Point(std::array<Coord, dim> arr);
        using Coordinate = Coord;
        Coord& x(int i);
        static const int dimension = dim;
        Coord norm() const;

        Coord& operator[](int i);
        const Coord& operator[](int i) const;

    private:
        std::array<Coord, dim> _arr;

};

template<typename Coord, int dim> Point<Coord, dim>::Point()
{
    for(int i = 0; i < dim; i++)
    {
        this->_arr[i] = 0;
    }
}

template<typename Coord, int dim> Point<Coord, dim>::Point(std::array<Coord, dim> arr)
{
    this->_arr = arr;
}

template<typename Coord, int dim> Coord& Point<Coord, dim>::x(int i)
{
    return this->_arr[i];
}

template<typename Coord, int dim> Coord Point<Coord, dim>::norm() const
{
    Coord d = 0;

    for(auto it : this->_arr)
    {
        d += it*it;
    }

    return sqrt(d);

}

template<typename Coord, int dim> const Coord& Point<Coord, dim>::operator[](int i) const
{
    return this->_arr[i];
}

template<typename Coord, int dim> Coord& Point<Coord, dim>::operator[](int i)
{
    return this->_arr[i];
}