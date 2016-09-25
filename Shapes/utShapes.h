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

    Triangle tri(vertex_1, vertex_2, vertex_3);

    DOUBLES_EQUAL(3.1622777, distanceOfVertexs(vertex_1, vertex_2), epsilon);
    DOUBLES_EQUAL(3.1622777, distanceOfVertexs(vertex_3, vertex_1), epsilon);
    DOUBLES_EQUAL(2.8284271, distanceOfVertexs(vertex_3, vertex_2), epsilon);

    tri.~Triangle();
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

//TEST (HW2_1, theLargestArea) {
//    Circle cir(2,7,9.8);
//    Rectangle rect(3,8,17,18);
//    Triangle tri({4,2}, {34,34}, {2,5});
//
//    std::vector<Shape *> shapes;
//    shapes.push_back(&cir);
//    shapes.push_back(&rect);
//    shapes.push_back(&tri);
//
//    std::cout<<cir.area()<<"\n";
//    std::cout<<rect.area()<<"\n";
//    std::cout<<tri.area()<<"\n";
//
//    Shape *largestShape = theLargestArea(shapes);
//
//    std::cout<<typeid(*largestShape).name()<<"\n";
//}


//TEST (first, Rectangle) {
//    Rectangle rect(0,0,4,2);
//    DOUBLES_EQUAL(8,rect.area(),epsilon);
//}

//TEST(sencond,Circle) {
//    Circle circ(0,0,10);
//    DOUBLES_EQUAL((M_PI*10*10),circ.area(),epsilon);
//}

//TEST (third, sumOfArea) {
//    Rectangle r1(0,0,4,2);
//    Rectangle r2(0,0,3,3);
//    std::vector<Rectangle> rects;
//    rects.push_back(r1);
//    rects.push_back(r2);
//    DOUBLES_EQUAL(17, sumOfArea(rects),epsilon);
//}

//TEST (fourth, sumOfArea) {
//    std::vector<Rectangle> rects;
//    DOUBLES_EQUAL(0, sumOfArea(rects),epsilon);
//}

//TEST (fifth, sumOfArea) {
//    Rectangle r1(0,0,4,2);
//    Circle c1(0,0,10);
//    std::vector<Shape *> ss;
//    ss.push_back(&r1);
//    ss.push_back(&c1);
//    DOUBLES_EQUAL(308,sumOfArea(ss),epsilon);
//}

#endif // UTSHAPES_H_INCLUDED
