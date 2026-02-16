#ifndef RHOMBUS_HPP
#define RHOMBUS_HPP

#include "Figure.hpp"
#include <array>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <sstream>

template<Scalar T>
class Rhombus : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 4> vertices;
    
    void validateRhombus() const {
        if (vertices[0] && vertices[1] && vertices[2] && vertices[3]) {
            auto dist = [](const Point<T>& p1, const Point<T>& p2) {
                T dx = p1.x() - p2.x();
                T dy = p1.y() - p2.y();
                return std::sqrt(dx*dx + dy*dy);
            };
            
            T side1 = dist(*vertices[0], *vertices[1]);
            T side2 = dist(*vertices[1], *vertices[2]);
            T side3 = dist(*vertices[2], *vertices[3]);
            T side4 = dist(*vertices[3], *vertices[0]);
            
            if (std::abs(side1 - side2) > 1e-6 || 
                std::abs(side2 - side3) > 1e-6 ||
                std::abs(side3 - side4) > 1e-6) {
                throw std::runtime_error("Not a valid rhombus");
            }
        }
    }
    
public:
    Rhombus() {
        for (auto& v : vertices) v = std::make_unique<Point<T>>();
    }
    
    Rhombus(const Rhombus<T>& other) {
        for (size_t i = 0; i < 4; ++i) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }
    
    Rhombus(Rhombus<T>&& other) noexcept : vertices(std::move(other.vertices)) {}
    
    Rhombus<T>& operator=(const Rhombus<T>& other) {
        if (this != &other) {
            for (size_t i = 0; i < 4; ++i) {
                *vertices[i] = *other.vertices[i];
            }
        }
        return *this;
    }
    
    Rhombus<T>& operator=(Rhombus<T>&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
        }
        return *this;
    }
    
    Figure<T>& operator=(const Figure<T>& other) override {
        const Rhombus<T>* r = dynamic_cast<const Rhombus<T>*>(&other);
        if (!r) throw std::bad_cast();
        return *this = *r;
    }
    
    Figure<T>& operator=(Figure<T>&& other) override {
        Rhombus<T>* r = dynamic_cast<Rhombus<T>*>(&other);
        if (!r) throw std::bad_cast();
        return *this = std::move(*r);
    }
    
    Point<T> center() const override {
        T cx = 0, cy = 0;
        for (const auto& v : vertices) {
            cx += v->x();
            cy += v->y();
        }
        return Point<T>(cx / 4, cy / 4);
    }
    
    double area() const override {
        T dx1 = vertices[1]->x() - vertices[3]->x();
        T dy1 = vertices[1]->y() - vertices[3]->y();
        T dx2 = vertices[2]->x() - vertices[0]->x();
        T dy2 = vertices[2]->y() - vertices[0]->y();
        
        return std::abs(dx1 * dy2 - dy1 * dx2) / 2.0;
    }
    
    void print(std::ostream& out) const override {
        out << "Rhombus vertices: ";
        for (size_t i = 0; i < vertices.size(); ++i) {
            out << *vertices[i];
            if (i < vertices.size() - 1) out << " ";
        }
    }
    
    void read(std::istream& in) override {
        for (size_t i = 0; i < 4; ++i) {
            if (!(in >> *vertices[i])) {
                throw std::runtime_error("Error reading rhombus vertex " + std::to_string(i));
            }
        }
        validateRhombus();
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Rhombus<T>* r = dynamic_cast<const Rhombus<T>*>(&other);
        if (!r) return false;
        
        for (size_t i = 0; i < 4; ++i) {
            if (*vertices[i] != *r->vertices[i]) return false;
        }
        return true;
    }
    
    operator double() const override {
        return area();
    }
};

#endif
