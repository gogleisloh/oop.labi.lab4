#include <iostream>
#include <memory>
#include <limits>
#include <sstream>
#include "Point.hpp"
#include "Figure.hpp"
#include "Rhombus.hpp"
#include "Pentagon.hpp"
#include "Hexagon.hpp"
#include "Array.hpp"
#include <string>

template<Scalar T>
double totalArea(const Array<std::shared_ptr<Figure<T>>>& figures) {
    double sum = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        sum += static_cast<double>(*figures[i]);
    }
    return sum;
}

template<Scalar T>
void printAllFigures(const Array<std::shared_ptr<Figure<T>>>& figures) {
    std::cout << "\n=== Все фигуры в массиве ===\n";
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "\nФигура " << i << ":\n";
        
        std::cout << "Вершины: ";
        figures[i]->print(std::cout);
        std::cout << "\n";
        
        std::cout << "Геометрический центр: " << figures[i]->center() << "\n";
        
        std::cout << "Площадь: " << figures[i]->area() << "\n";
    }
}

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    std::cout << "=== Лабораторная работа №4: Основы метапрограммирования ===\n";
    std::cout << "Вариант 13: Ромб, Пятиугольник, Шестиугольник\n\n";
    
    std::cout << "Введите количество фигур для создания: ";
    size_t count;
    std::cin >> count;
    
    for (size_t i = 0; i < count; ++i) {
        std::cout << "\n=== Фигура " << i + 1 << " ===\n";
        std::cout << "Выберите тип фигуры:\n";
        std::cout << "1 - Ромб\n";
        std::cout << "2 - Пятиугольник\n";
        std::cout << "3 - Шестиугольник\n";
        std::cout << "Ваш выбор (1-3): ";
        
        int type;
        std::cin >> type;
        
        std::shared_ptr<Figure<double>> figure;
        
        try {
            switch (type) {
                case 1: {
                    figure = std::make_shared<Rhombus<double>>();
                    std::cout << "Введите 8 координат вершин ромба (x1 y1 x2 y2 x3 y3 x4 y4): ";
                    break;
                }
                case 2: {
                    figure = std::make_shared<Pentagon<double>>();
                    std::cout << "Введите центр и радиус пятиугольника (x_центра y_центра радиус): ";
                    break;
                }
                case 3: {
                    figure = std::make_shared<Hexagon<double>>();
                    std::cout << "Введите центр и радиус шестиугольника (x_центра y_центра радиус): ";
                    break;
                }
                default: {
                    std::cout << "Неверный тип фигуры! Пропускаем...\n";
                    --i;
                    continue;
                }
            }
            
            std::cin >> *figure;
            figures.push_back(figure);
            std::cout << "✓ Фигура успешно добавлена в массив\n";
            
        } catch (const std::exception& e) {
            std::cout << "✗ Ошибка: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            --i;
        }
    }
    
    printAllFigures(figures);
    
    std::cout << "\n=== Вычисление общей площади ===\n";
    std::cout << "Общая площадь всех фигур: " << totalArea(figures) << "\n";
    
    if (!figures.empty()) {
        std::cout << "\n=== Удаление фигуры по индексу ===\n";
        std::cout << "Введите индекс фигуры для удаления (0-" << figures.size() - 1 << "): ";
        size_t index;
        std::cin >> index;
        
        if (index < figures.size()) {
            figures.remove(index);
            std::cout << "✓ Фигура с индексом " << index << " удалена\n";
            std::cout << "Осталось фигур: " << figures.size() << "\n";
            
            printAllFigures(figures);
            std::cout << "Новая общая площадь: " << totalArea(figures) << "\n";
        } else {
            std::cout << "✗ Неверный индекс!\n";
        }
    }
    
    std::cout << "\n=== Демонстрация работы шаблона Array<T> ===\n";
    
    std::cout << "\n1. Демонстрация Array<Figure<int>*> (по требованию задания):\n";
    {
        Array<Figure<int>*> demoArray1;
        
        Rhombus<int>* rh = new Rhombus<int>();
        Pentagon<int>* pent = new Pentagon<int>();
        
        std::stringstream iss1("0 0 2 0 2 2 0 2");
        std::stringstream iss2("0 0 5");
        
        iss1 >> *rh;  
        iss2 >> *pent;
        
        demoArray1.push_back(rh);
        demoArray1.push_back(pent);
        
        std::cout << "   Размер массива: " << demoArray1.size() << "\n";
        std::cout << "   Площадь первой фигуры: " << demoArray1[0]->area() << "\n";
        std::cout << "   Площадь второй фигуры: " << demoArray1[1]->area() << "\n";
        
        for (size_t i = 0; i < demoArray1.size(); ++i) {
            delete demoArray1[i];
        }
    }
    
    std::cout << "\n2. Демонстрация Array<Hexagon<double>> (тип-наследник):\n";
    {
        Array<Hexagon<double>> demoArray2;
        
        Hexagon<double> h1;
        std::stringstream iss3("0 0 3.0");
        iss3 >> h1;
        
        Hexagon<double> h2;
        std::stringstream iss4("5.0 5.0 2.5");
        iss4 >> h2;
        
        demoArray2.push_back(h1);
        demoArray2.push_back(std::move(h2));
        
        std::cout << "   Размер массива: " << demoArray2.size() << "\n";
        std::cout << "   Площадь первого шестиугольника: " << demoArray2[0].area() << "\n";
        std::cout << "   Площадь второго шестиугольника: " << demoArray2[1].area() << "\n";
        
        std::cout << "   Добавляем элементы для вызова reallocate...\n";
        for (int i = 0; i < 15; ++i) {
            Hexagon<double> temp;
            std::stringstream ss;
            ss << i << " " << i << " 1.0";
            ss >> temp;
            demoArray2.push_back(temp);
        }
        std::cout << "   Новый размер: " << demoArray2.size() << "\n";
        std::cout << "   Емкость: " << demoArray2.capacity() << "\n";
    }
    
    std::cout << "\n3. Проверка concept Scalar:\n";
    std::cout << "   Array<double> - компилируется (double - скалярный тип)\n";
    std::cout << "   Array<int> - компилируется (int - скалярный тип)\n";
    
    std::cout << "\n✓ Программа успешно завершена\n";
    return 0;
}
