#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "Figure.hpp"
#include <array>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <sstream>

template<Scalar T>
class Hexagon : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 6> vertices;
    
    void createRegularHexagon(Point<T> center, T radius, double startAngle = 0.0) {
        for (int i = 0; i < 6; i++) {
            double angle = startAngle + 2 * M_PI * i / 6.0;
            vertices[i] = std::make_unique<Point<T>>(
                center.x() + radius * std::cos(angle),
                center.y() + radius * std::sin(angle)
            );
        }
    }
    
public:
    Hexagon() {
        for (auto& v : vertices) v = std::make_unique<Point<T>>();
    }
    
    Hexagon(const Point<T>& center, T radius) {
        createRegularHexagon(center, radius);
    }
    
    Hexagon(const Hexagon<T>& other) {
        for (size_t i = 0; i < 6; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }
    
    Hexagon(Hexagon<T>&& other) noexcept : vertices(std::move(other.vertices)) {}
    
    Hexagon<T>& operator=(const Hexagon<T>& other) {
        if (this != &other) {
            for (size_t i = 0; i < 6; ++i) {
                *vertices[i] = *other.vertices[i];
            }
        }
        return *this;
    }
    
    Hexagon<T>& operator=(Hexagon<T>&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
        }
        return *this;
    }
    
    Figure<T>& operator=(const Figure<T>& other) override {
        const Hexagon<T>* h = dynamic_cast<const Hexagon<T>*>(&other);
        if (!h) throw std::bad_cast();
        return *this = *h;
    }
    
    Figure<T>& operator=(Figure<T>&& other) override {
        Hexagon<T>* h = dynamic_cast<Hexagon<T>*>(&other);
        if (!h) throw std::bad_cast();
        return *this = std::move(*h);
    }
    
    Point<T> center() const override {
        T cx = 0, cy = 0;
        for (const auto& v : vertices) {
            cx += v->x();
            cy += v->y();
        }
        return Point<T>(cx / 6, cy / 6);
    }
    
    double area() const override {
        double sum = 0;
        for (size_t i = 0; i < 6; i++) {
            size_t j = (i + 1) % 6;
            sum += vertices[i]->x() * vertices[j]->y() - 
                   vertices[j]->x() * vertices[i]->y();
        }
        return std::abs(sum) / 2.0;
    }
    
    void print(std::ostream& out) const override {
        out << "Hexagon vertices: ";
        for (size_t i = 0; i < vertices.size(); ++i) {
            out << *vertices[i];
            if (i < vertices.size() - 1) out << " ";
        }
    }
    
    void read(std::istream& in) override {
        Point<T> center;
        T radius;
        
        if (!(in >> center >> radius)) {
            throw std::runtime_error("Error reading hexagon data");
        }
        
        if (radius <= 0) {
            throw std::runtime_error("Radius must be positive");
        }
        
        createRegularHexagon(center, radius);
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Hexagon<T>* h = dynamic_cast<const Hexagon<T>*>(&other);
        if (!h) return false;
        
        for (size_t i = 0; i < 6; ++i) {
            if (*vertices[i] != *h->vertices[i]) return false;
        }
        return true;
    }
    
    operator double() const override {
        return area();
    }
};

#endif
