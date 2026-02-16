
#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include "Point.hpp"
#include "Figure.hpp"
#include "Rhombus.hpp"
#include "Pentagon.hpp"
#include "Hexagon.hpp"
#include "Array.hpp"

bool double_near(double a, double b, double epsilon = 1e-6) {
    return std::abs(a - b) < epsilon;
}

TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_DOUBLE_EQ(p.x(), 0.0);
    EXPECT_DOUBLE_EQ(p.y(), 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<int> p(3, 4);
    EXPECT_EQ(p.x(), 3);
    EXPECT_EQ(p.y(), 4);
}

TEST(PointTest, SettersAndGetters) {
    Point<double> p;
    p.setX(5.5);
    p.setY(6.6);
    EXPECT_DOUBLE_EQ(p.x(), 5.5);
    EXPECT_DOUBLE_EQ(p.y(), 6.6);
}

TEST(PointTest, EqualityOperators) {
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(3, 4);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
    EXPECT_FALSE(p1 != p2);
}

TEST(PointTest, StreamOperators) {
    Point<double> p(2.5, 3.5);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "(2.5, 3.5)");
    
    Point<int> p2;
    std::stringstream iss("10 20");
    iss >> p2;
    EXPECT_EQ(p2.x(), 10);
    EXPECT_EQ(p2.y(), 20);
}

TEST(RhombusTest, DefaultConstructor) {
    Rhombus<double> r;
    EXPECT_NO_THROW(r.center());
    EXPECT_TRUE(r.area() >= 0.0 || std::isnan(r.area()));
}

TEST(RhombusTest, AreaCalculationSquareRhombus) {
    Rhombus<double> r;
    std::stringstream iss("0 0 2 0 2 2 0 2");
    EXPECT_NO_THROW(iss >> r);
    
    double area = r.area();
    EXPECT_TRUE(area >= 0.0) << "Area should be non-negative, got: " << area;
    EXPECT_NEAR(area, 4.0, 1e-6) << "Expected area ~4.0, got: " << area;
}

TEST(RhombusTest, AreaCalculationRhombus) {
    Rhombus<double> r;
    std::stringstream iss("0 0 1 0 1 1 0 1");
    EXPECT_NO_THROW(iss >> r);
    
    double area = r.area();
    EXPECT_TRUE(area >= 0.0) << "Area should be non-negative, got: " << area;
    EXPECT_GT(area, 0.0);
    EXPECT_LT(area, 20.0);
}

TEST(RhombusTest, CenterCalculationSquare) {
    Rhombus<double> r;
    std::stringstream iss("0 0 2 0 2 2 0 2");
    iss >> r;
    
    Point<double> center = r.center();
    EXPECT_NEAR(center.x(), 1.0, 1e-6);
    EXPECT_NEAR(center.y(), 1.0, 1e-6);
}

TEST(RhombusTest, CopyConstructor) {
    Rhombus<double> r1;
    std::stringstream iss("0 0 2 0 2 2 0 2");
    iss >> r1;
    
    Rhombus<double> r2(r1);
    
    EXPECT_NEAR(r1.center().x(), r2.center().x(), 1e-6);
    EXPECT_NEAR(r1.center().y(), r2.center().y(), 1e-6);
    
    EXPECT_NEAR(r1.area(), r2.area(), 1e-6);
}

TEST(RhombusTest, MoveConstructor) {
    Rhombus<double> r1;
    std::stringstream iss("0 0 2 0 2 2 0 2");
    iss >> r1;
    
    double area = r1.area();
    Point<double> center = r1.center();
    
    Rhombus<double> r2(std::move(r1));
    
    EXPECT_NEAR(r2.area(), area, 1e-6);
    EXPECT_NEAR(r2.center().x(), center.x(), 1e-6);
    EXPECT_NEAR(r2.center().y(), center.y(), 1e-6);
}

TEST(RhombusTest, StreamOperatorsRhombus) {
    Rhombus<double> r;
    std::stringstream iss("0 0 2 0 2 2 0 2");
    EXPECT_NO_THROW(iss >> r);
    
    std::stringstream oss;
    EXPECT_NO_THROW(r.print(oss));
    EXPECT_FALSE(oss.str().empty());
}

TEST(PentagonTest, DefaultConstructor) {
    Pentagon<double> p;
    EXPECT_NO_THROW(p.center());
    double area = p.area();
    EXPECT_TRUE(area >= 0.0 || std::isnan(area));
}


TEST(PentagonTest, RegularPentagonArea) {
    Pentagon<double> p(Point<double>(0, 0), 1.0);
    double area = p.area();
    
    double R = 1.0;
    double side = 2 * R * sin(M_PI / 5.0);
    double apothem = R * cos(M_PI / 5.0);
    double expected_area = (5.0 * side * apothem) / 2.0;
    
    expected_area = (5.0 / 2.0) * R * R * sin(2 * M_PI / 5.0);
    
    EXPECT_GT(area, 0.0) << "Area should be positive, got: " << area;
    EXPECT_NEAR(area, expected_area, 1e-3) << "Expected area ~" << expected_area << ", got: " << area;
}

TEST(PentagonTest, RegularPentagonWithRadius2) {
    Pentagon<double> p(Point<double>(0, 0), 2.0);
    double area = p.area();
    
    double R = 2.0;
    double expected_area = (5.0 / 2.0) * R * R * sin(2 * M_PI / 5.0);
    
    EXPECT_GT(area, 0.0);
    EXPECT_NEAR(area, expected_area, 1e-2);
}

TEST(PentagonTest, CenterCalculation) {
    Pentagon<double> p(Point<double>(5, 5), 2.0);
    Point<double> center = p.center();
    
    EXPECT_NEAR(center.x(), 5.0, 1e-6);
    EXPECT_NEAR(center.y(), 5.0, 1e-6);
}

TEST(PentagonTest, CopyAndAssignment) {
    Pentagon<double> p1(Point<double>(0, 0), 3.0);
    double area1 = p1.area();
    
    Pentagon<double> p2 = p1;
    EXPECT_NEAR(p2.area(), area1, 1e-6);
    
    Pentagon<double> p3;
    p3 = p1;
    EXPECT_NEAR(p3.area(), area1, 1e-6);
    
    EXPECT_NEAR(p1.center().x(), p2.center().x(), 1e-6);
    EXPECT_NEAR(p1.center().x(), p3.center().x(), 1e-6);
}

TEST(PentagonTest, StreamOperators) {
    Pentagon<double> p;
    std::stringstream iss("0 0 2.0");
    EXPECT_NO_THROW(iss >> p);
    
    std::stringstream oss;
    EXPECT_NO_THROW(p.print(oss));
    EXPECT_FALSE(oss.str().empty());
}

TEST(HexagonTest, DefaultConstructor) {
    Hexagon<double> h;
    EXPECT_NO_THROW(h.center());
    double area = h.area();
    EXPECT_TRUE(area >= 0.0 || std::isnan(area));
}

TEST(HexagonTest, RegularHexagonArea) {
    Hexagon<double> h(Point<double>(0, 0), 1.0);
    double area = h.area();
    
    double expected_area = (3 * std::sqrt(3) / 2.0);
    
    EXPECT_GT(area, 0.0);
    EXPECT_NEAR(area, expected_area, 1e-6);
}

TEST(HexagonTest, RegularHexagonWithDifferentRadius) {
    Hexagon<double> h(Point<double>(0, 0), 2.0);
    double area = h.area();
    
    double expected_area = (3 * std::sqrt(3) / 2.0) * 4.0; // 4 = 2²
    
    EXPECT_GT(area, 0.0);
    EXPECT_NEAR(area, expected_area, 1e-6);
}

TEST(HexagonTest, CenterCalculation) {
    Hexagon<double> h(Point<double>(10, 10), 3.0);
    Point<double> center = h.center();
    
    EXPECT_NEAR(center.x(), 10.0, 1e-6);
    EXPECT_NEAR(center.y(), 10.0, 1e-6);
}

TEST(HexagonTest, OperatorDouble) {
    Hexagon<double> h(Point<double>(0, 0), 2.0);
    double area = h.area();
    double casted_area = static_cast<double>(h);
    
    EXPECT_NEAR(area, casted_area, 1e-6);
}

TEST(HexagonTest, StreamOperators) {
    Hexagon<double> h;
    std::stringstream iss("0 0 3.0");
    EXPECT_NO_THROW(iss >> h);
    
    std::stringstream oss;
    EXPECT_NO_THROW(h.print(oss));
    EXPECT_FALSE(oss.str().empty());
}

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_GE(arr.capacity(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, PushBackAndAccess) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}


TEST(ArrayTest, PushBackMoveSemantics) {
    Array<std::string> arr;
    std::string str1 = "Hello";
    std::string str2 = "World";
    
    arr.push_back(std::move(str1));
    arr.push_back(std::move(str2));
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], "Hello");
    EXPECT_EQ(arr[1], "World");
    EXPECT_TRUE(str1.empty()); 
}

TEST(ArrayTest, RemoveElement) {
    Array<int> arr;
    for (int i = 0; i < 5; ++i) {
        arr.push_back(i * 10);
    }
    
    EXPECT_EQ(arr.size(), 5);
    EXPECT_NO_THROW(arr.remove(2));
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 40);
}

TEST(ArrayTest, RemoveInvalidIndex) {
    Array<int> arr;
    arr.push_back(1);
    
    EXPECT_THROW(arr.remove(5), std::out_of_range);
    EXPECT_THROW(arr.remove(1), std::out_of_range); 
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1;
    arr1.push_back(100);
    arr1.push_back(200);
    
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.size(), arr1.size());
    EXPECT_EQ(arr2[0], arr1[0]);
    EXPECT_EQ(arr2[1], arr1[1]);
    
    arr2[0] = 300;
    EXPECT_EQ(arr1[0], 100);
    EXPECT_EQ(arr2[0], 300);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1;
    arr1.push_back(100);
    arr1.push_back(200);
    
    size_t size = arr1.size();
    Array<int> arr2(std::move(arr1));
    
    EXPECT_EQ(arr2.size(), size);
    EXPECT_EQ(arr2[0], 100);
    EXPECT_EQ(arr2[1], 200);
    EXPECT_EQ(arr1.size(), 0);
    EXPECT_EQ(arr1.capacity(), 0);
}

TEST(ArrayTest, AssignmentOperators) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    
    Array<int> arr2;
    arr2 = arr1;
    EXPECT_EQ(arr2.size(), arr1.size());
    EXPECT_EQ(arr2[0], arr1[0]);
    
    Array<int> arr3;
    arr3 = std::move(arr1);
    EXPECT_EQ(arr3.size(), 2);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(ArrayTest, Reallocation) {
    Array<int> arr;
    size_t initial_capacity = arr.capacity();
    
    for (int i = 0; i <= initial_capacity; ++i) {
        arr.push_back(i);
    }
    
    EXPECT_GT(arr.capacity(), initial_capacity);
    EXPECT_EQ(arr.size(), initial_capacity + 1);
    
    for (int i = 0; i <= initial_capacity; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(ArrayTest, IteratorAccess) {
    Array<int> arr;
    for (int i = 0; i < 5; ++i) {
        arr.push_back(i * 2);
    }
    
    int sum = 0;
    for (const auto& elem : arr) {
        sum += elem;
    }
    
    EXPECT_EQ(sum, 20); // 0+2+4+6+8 = 20
    
    for (auto& elem : arr) {
        elem += 1;
    }
    
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(IntegrationTest, ArrayOfFigurePointers) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto rhombus = std::make_shared<Rhombus<double>>();
    auto pentagon = std::make_shared<Pentagon<double>>();
    auto hexagon = std::make_shared<Hexagon<double>>();
    
    std::stringstream iss1("0 0 2 0 2 2 0 2");
    std::stringstream iss2("0 0 3.0");
    std::stringstream iss3("5 5 2.0");
    
    EXPECT_NO_THROW(iss1 >> *rhombus);
    EXPECT_NO_THROW(iss2 >> *pentagon);
    EXPECT_NO_THROW(iss3 >> *hexagon);
    
    figures.push_back(rhombus);
    figures.push_back(pentagon);
    figures.push_back(hexagon);
    
    EXPECT_EQ(figures.size(), 3);
    EXPECT_GT(figures[0]->area(), 0.0);
    EXPECT_GT(figures[1]->area(), 0.0);
    EXPECT_GT(figures[2]->area(), 0.0);
    
    for (size_t i = 0; i < figures.size(); ++i) {
        EXPECT_NO_THROW(figures[i]->center());
        EXPECT_NO_THROW(figures[i]->print(std::cout));
    }
}


TEST(IntegrationTest, FigurePolymorphism) {
    std::shared_ptr<Figure<double>> fig1 = std::make_shared<Rhombus<double>>();
    std::shared_ptr<Figure<double>> fig2 = std::make_shared<Pentagon<double>>();
    std::shared_ptr<Figure<double>> fig3 = std::make_shared<Hexagon<double>>();
    
    std::stringstream iss1("0 0 2 0 2 2 0 2");
    std::stringstream iss2("0 0 4.0");
    std::stringstream iss3("0 0 3.0");
    
    EXPECT_NO_THROW(iss1 >> *fig1);
    EXPECT_NO_THROW(iss2 >> *fig2);
    EXPECT_NO_THROW(iss3 >> *fig3);
    
    EXPECT_NE(fig1->area(), fig2->area());
    EXPECT_NE(fig2->area(), fig3->area());
    
    double area1 = static_cast<double>(*fig1);
    double area2 = static_cast<double>(*fig2);
    EXPECT_NEAR(area1, fig1->area(), 1e-6);
    EXPECT_NEAR(area2, fig2->area(), 1e-6);
}

TEST(IntegrationTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto fig1 = std::make_shared<Rhombus<double>>();
    auto fig2 = std::make_shared<Hexagon<double>>();
    
    std::stringstream iss1("0 0 2 0 2 2 0 2");
    std::stringstream iss2("0 0 1.0");
    
    iss1 >> *fig1;
    iss2 >> *fig2;
    
    figures.push_back(fig1);
    figures.push_back(fig2);
    
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += static_cast<double>(*figures[i]);
    }
    
    EXPECT_NEAR(total, fig1->area() + fig2->area(), 1e-6);
}

TEST(IntegrationTest, RemoveFigureFromArray) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto fig1 = std::make_shared<Rhombus<double>>();
    auto fig2 = std::make_shared<Pentagon<double>>();
    auto fig3 = std::make_shared<Hexagon<double>>();
    
    std::stringstream iss1("0 0 2 0 2 2 0 2");
    std::stringstream iss2("0 0 2.0");
    std::stringstream iss3("0 0 1.0");
    
    iss1 >> *fig1;
    iss2 >> *fig2;
    iss3 >> *fig3;
    
    figures.push_back(fig1);
    figures.push_back(fig2);
    figures.push_back(fig3);
    
    EXPECT_EQ(figures.size(), 3);
    
    double total_before = fig1->area() + fig2->area() + fig3->area();
    
    figures.remove(1); 
    
    EXPECT_EQ(figures.size(), 2);
    double total_after = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_after += figures[i]->area();
    }
    
    EXPECT_NEAR(total_after, fig1->area() + fig3->area(), 1e-6);
}

TEST(ExceptionTest, ArrayIndexOutOfRange) {
    Array<int> arr;
    arr.push_back(1);
    
    EXPECT_THROW(arr[5], std::out_of_range);
    EXPECT_THROW(arr[1], std::out_of_range); 
    EXPECT_NO_THROW(arr[0]);
}

TEST(ExceptionTest, InvalidFigureInputData) {
    Rhombus<double> r;
    std::stringstream iss("not a number");
    
    EXPECT_THROW(iss >> r, std::runtime_error);
}

TEST(ExceptionTest, InvalidRadiusForPentagon) {
    Pentagon<double> p;
    std::stringstream iss("0 0 -1.0"); 
    
    EXPECT_THROW(iss >> p, std::runtime_error);
}

TEST(ExceptionTest, InvalidRadiusForHexagon) {
    Hexagon<double> h;
    std::stringstream iss("0 0 0.0"); 
    
    EXPECT_THROW(iss >> h, std::runtime_error);
}

TEST(ExceptionTest, InvalidRhombusVertices) {
    Rhombus<double> r;
    std::stringstream iss("0 0 2 0 3 1 1 1");
    
    EXPECT_THROW(iss >> r, std::runtime_error);
}

TEST(ScalarConceptTest, ValidScalarTypes) {
    Point<int> p1(1, 2);
    Point<double> p2(1.5, 2.5);
    Point<float> p3(1.0f, 2.0f);
    
    EXPECT_EQ(p1.x(), 1);
    EXPECT_DOUBLE_EQ(p2.x(), 1.5);
    EXPECT_FLOAT_EQ(p3.x(), 1.0f);
}


TEST(TemplateTest, DifferentScalarTypes) {
    Rhombus<float> r_float;
    Rhombus<double> r_double;
    Rhombus<int> r_int;
    
    std::stringstream iss_float("0.5 0.5 2.5 -0.5 3.5 1.5 1.5 2.5");
    std::stringstream iss_double("0.0 0.0 2.0 0.0 2.0 2.0 0.0 2.0");
    std::stringstream iss_int("0 0 2 0 2 2 0 2");
    
    EXPECT_NO_THROW(iss_float >> r_float);
    EXPECT_NO_THROW(iss_double >> r_double);
    EXPECT_NO_THROW(iss_int >> r_int);
    
    EXPECT_GT(r_float.area(), 0.0f);
    EXPECT_GT(r_double.area(), 0.0);
    EXPECT_GE(r_int.area(), 0.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}