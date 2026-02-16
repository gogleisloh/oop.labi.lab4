#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "Figure.hpp"
#include <array>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <sstream>

template<Scalar T>
class Pentagon : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 5> vertices;
    
    void createRegularPentagon(Point<T> center, T radius, double startAngle = 0.0) {
        for (int i = 0; i < 5; i++) {
            double angle = startAngle + 2 * M_PI * i / 5.0;
            vertices[i] = std::make_unique<Point<T>>(
                center.x() + radius * std::cos(angle),
                center.y() + radius * std::sin(angle)
            );
        }
    }
    
public:
    Pentagon() {
        for (auto& v : vertices) v = std::make_unique<Point<T>>();
    }
    
    Pentagon(const Point<T>& center, T radius) {
        createRegularPentagon(center, radius);
    }
    
    Pentagon(const Pentagon<T>& other) {
        for (size_t i = 0; i < 5; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }
    
    Pentagon(Pentagon<T>&& other) noexcept : vertices(std::move(other.vertices)) {}
    
    Pentagon<T>& operator=(const Pentagon<T>& other) {
        if (this != &other) {
            for (size_t i = 0; i < 5; ++i) {
                *vertices[i] = *other.vertices[i];
            }
        }
        return *this;
    }
    
    Pentagon<T>& operator=(Pentagon<T>&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
        }
        return *this;
    }
    
    Figure<T>& operator=(const Figure<T>& other) override {
        const Pentagon<T>* p = dynamic_cast<const Pentagon<T>*>(&other);
        if (!p) throw std::bad_cast();
        return *this = *p;
    }
    
    Figure<T>& operator=(Figure<T>&& other) override {
        Pentagon<T>* p = dynamic_cast<Pentagon<T>*>(&other);
        if (!p) throw std::bad_cast();
        return *this = std::move(*p);
    }
    
    Point<T> center() const override {
        T cx = 0, cy = 0;
        for (const auto& v : vertices) {
            cx += v->x();
            cy += v->y();
        }
        return Point<T>(cx / 5, cy / 5);
    }
    
    double area() const override {
        double sum = 0;
        for (size_t i = 0; i < 5; i++) {
            size_t j = (i + 1) % 5;
            sum += vertices[i]->x() * vertices[j]->y() - 
                   vertices[j]->x() * vertices[i]->y();
        }
        return std::abs(sum) / 2.0;
    }
    
    void print(std::ostream& out) const override {
        out << "Pentagon vertices: ";
        for (size_t i = 0; i < vertices.size(); ++i) {
            out << *vertices[i];
            if (i < vertices.size() - 1) out << " ";
        }
    }
    
    void read(std::istream& in) override {
        Point<T> center;
        T radius;
        
        if (!(in >> center >> radius)) {
            throw std::runtime_error("Error reading pentagon data");
        }
        
        if (radius <= 0) {
            throw std::runtime_error("Radius must be positive");
        }
        
        createRegularPentagon(center, radius);
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Pentagon<T>* p = dynamic_cast<const Pentagon<T>*>(&other);
        if (!p) return false;
        
        for (size_t i = 0; i < 5; ++i) {
            if (*vertices[i] != *p->vertices[i]) return false;
        }
        return true;
    }
    
    operator double() const override {
        return area();
    }
};

#endif
