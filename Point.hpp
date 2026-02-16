#ifndef POINT_HPP
#define POINT_HPP

#include <concepts>
#include <iostream>
#include <memory>
#include <type_traits>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<typename T>
requires Scalar<T>
class Point {
private:
    T x_, y_;
    
public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}
    
    T x() const { return x_; }
    T y() const { return y_; }
    
    void setX(T x) { x_ = x; }
    void setY(T y) { y_ = y; }
    
    bool operator==(const Point<T>& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
    
    bool operator!=(const Point<T>& other) const {
        return !(*this == other);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
        os << "(" << p.x_ << ", " << p.y_ << ")";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Point<T>& p) {
        is >> p.x_ >> p.y_;
        return is;
    }
};


#endif
