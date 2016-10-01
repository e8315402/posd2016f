#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include <vector>
#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"

#include <iostream>
#include <typeinfo>

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
}

TEST (HW2_2, sortByDecreasingPerimeter) {
    Circle cir(2,7,9.8);
    Rectangle rect(3,8,17,18);
    Triangle tri({4,2}, {34,34}, {2,5});

}


#endif // UTSHAPES_H_INCLUDED
