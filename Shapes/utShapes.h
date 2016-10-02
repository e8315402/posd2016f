#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include <vector>
#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"

#include <iostream>
#include <iomanip>

const double epsilon = 0.000001;

TEST (HW1_1, perimeterOfCircle) {

    Circle cir(0,0,12);
    DOUBLES_EQUAL((2*M_PI*12), cir.perimeter(), epsilon);

}

TEST (HW1_2, perimeterOfRectangle) {

    Rectangle rect(0,0,8,9);
    DOUBLES_EQUAL(34, rect.perimeter(), epsilon);

}

TEST (HW1_3, createTriangle) {

    vertex vertex_1 = {1, 4};
    vertex vertex_2 = {2, 1};
    vertex vertex_3 = {4, 3};

    try {
        // This is a triangle
        Triangle tri(vertex_1, vertex_2, vertex_3);

        CHECK(true);

        tri.~Triangle();
    } catch (const char * msg) {
        CHECK(false);
    }

    vertex vertex_4 = {1, 1};
    vertex vertex_5 = {2, 2};
    vertex vertex_6 = {3, 3};

    try {
        // This is not a triangle
        Triangle tri(vertex_4, vertex_5, vertex_6);

        CHECK(false);

        tri.~Triangle();
    } catch (const char * msg) {
        CHECK(true);
    }

}

TEST (HW1_4, perimeterOfTriangle) {

    vertex vertex_1 = {1, 4};
    vertex vertex_2 = {2, 1};
    vertex vertex_3 = {4, 3};

    Triangle tri(vertex_1, vertex_2, vertex_3);

    DOUBLES_EQUAL(9.1529824, tri.perimeter(), epsilon);

    tri.~Triangle();

}

TEST (HW1_5, areaOfTriangle) {

    vertex vertex_1 = {1, 4};
    vertex vertex_2 = {2, 1};
    vertex vertex_3 = {4, 3};

    Triangle tri(vertex_1, vertex_2, vertex_3);

    DOUBLES_EQUAL(4, tri.area(), epsilon);

    tri.~Triangle();

}

TEST (HW1_6, sumOfPerimetersOfaNumberOfShapes) {

    Circle cir(2,7,11);
    Rectangle rect(3,8,12,21);
    Triangle tri({1,1}, {3,1}, {3,4});

    std::vector<Shape *> shapes;
    shapes.push_back(&cir);
    shapes.push_back(&rect);
    shapes.push_back(&tri);

    DOUBLES_EQUAL(143.7205896, sumOfPerimeter(shapes), epsilon);

    cir.~Circle();
    rect.~Rectangle();
    tri.~Triangle();

}

TEST (HW2_1, theLargestArea) {
    Circle cir(2,7,9.8);
    Rectangle rect(3,8,17,18);
    Triangle tri({4,2}, {34,34}, {2,5});

    std::vector<Shape *> shapes;
    shapes.push_back(&cir);
    shapes.push_back(&rect);
    shapes.push_back(&tri);

    Shape *largestShape = theLargestArea(shapes);

    CHECK(!((*largestShape).getShapeName().compare("Rectangle")));

    cir.~Circle();
    rect.~Rectangle();
    tri.~Triangle();

}

TEST (HW2_2, sortByDecreasingPerimeter) {

    Circle cir_1(2,7,9.8);
    Circle cir_2(5,4,3.6);
    Rectangle rect_1(3,8,17,18);
    Triangle tri_1({4,2}, {34,34}, {2,5});

    std::vector<Shape *> shapes;
    shapes.push_back(&cir_1);
    shapes.push_back(&cir_2);
    shapes.push_back(&rect_1);
    shapes.push_back(&tri_1);

    sortByDecreasingPerimeter(shapes);

    DOUBLES_EQUAL(90.654621, shapes[0]->perimeter(), epsilon);
    DOUBLES_EQUAL(70, shapes[1]->perimeter(), epsilon);
    DOUBLES_EQUAL(61.575216, shapes[2]->perimeter(), epsilon);
    DOUBLES_EQUAL(22.619467, shapes[3]->perimeter(), epsilon);

    cir_1.~Circle();
    cir_2.~Circle();
    rect_1.~Rectangle();
    tri_1.~Triangle();

}

TEST (HW2_3, sumOfPerimetersOfMultiShape) {

    Circle cSmall(2,1,1);
    Rectangle rTall(1,10,2,8);

    std::vector<Shape *> shapes;
    shapes.push_back(&cSmall);
    shapes.push_back(&rTall);

    Combo comboExclamation(shapes);

    DOUBLES_EQUAL(26.2831853, comboExclamation.perimeter(), epsilon);

    comboExclamation.~Combo();
    cSmall.~Circle();
    rTall.~Rectangle();

}

TEST (HW2_4, sumOfAreasOfMultiShape) {

    Circle cSmall(2,1,1);
    Rectangle rTall(1,10,2,8);

    std::vector<Shape *> shapes;
    shapes.push_back(&cSmall);
    shapes.push_back(&rTall);

    Combo comboExclamation(shapes);

    DOUBLES_EQUAL(19.1415927, comboExclamation.area(), epsilon);

    comboExclamation.~Combo();
    cSmall.~Circle();
    rTall.~Rectangle();

}


#endif // UTSHAPES_H_INCLUDED
