#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "Point.hpp"
#include <iostream>
#include <memory>

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void read(std::istream& in) = 0;
    
    virtual operator double() const { return area(); }
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual Figure<T>& operator=(const Figure<T>& other) = 0;
    virtual Figure<T>& operator=(Figure<T>&& other) = 0;
    
    virtual void calculateCenter() const {
        std::cout << "Center: " << center() << std::endl;
    }
};

template<Scalar T>
std::ostream& operator<<(std::ostream& out, const Figure<T>& fig) {
    fig.print(out);
    return out;
}

template<Scalar T>
std::istream& operator>>(std::istream& in, Figure<T>& fig) {
    fig.read(in);
    return in;
}

#endif
