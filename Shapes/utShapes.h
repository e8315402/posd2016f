#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"

#include "Shapes.h"
#include "Media.h"
#include "Builder.h"
#include "Visitor.h"
#include "MyDocument.h"

#include <vector>
#include <iostream>
#include <iomanip>

const double epsilon = 0.000001;


/**< previous test */


TEST (1_perimeterOfCircle, HW1) {

    Circle cir(0,0,12);
    DOUBLES_EQUAL((2*M_PI*12), cir.perimeter(), epsilon);

}

TEST (2_perimeterOfRectangle, HW1) {

    Rectangle rect(0,0,8,9);
    DOUBLES_EQUAL(34, rect.perimeter(), epsilon);

}

TEST (3_createTriangle, HW1) {

    vertex vertex_1 = {1, 4};
    vertex vertex_2 = {2, 1};
    vertex vertex_3 = {4, 3};

    try {
        // This is a triangle
        Triangle tri(vertex_1, vertex_2, vertex_3);

        CHECK(true);

        tri.~Triangle();
    } catch (std::string msg) {

        FAIL("It's a triangle.");

    }

    vertex vertex_4 = {1, 1};
    vertex vertex_5 = {2, 2};
    vertex vertex_6 = {3, 3};

    try {
        // This is not a triangle
        Triangle tri(vertex_4, vertex_5, vertex_6);

        FAIL("It's not a triangle.");

    } catch (std::string msg) {

        CHECK(msg ==  std::string("It's not a triangle."));

    }

}

TEST (4_perimeterOfTriangle, HW1) {

    vertex vertex_1 = {1, 4};
    vertex vertex_2 = {2, 1};
    vertex vertex_3 = {4, 3};

    Triangle tri(vertex_1, vertex_2, vertex_3);

    DOUBLES_EQUAL(9.1529824, tri.perimeter(), epsilon);

    tri.~Triangle();

}

TEST (5_areaOfTriangle, HW1) {

    vertex vertex_1 = {1, 4};
    vertex vertex_2 = {2, 1};
    vertex vertex_3 = {4, 3};

    Triangle tri(vertex_1, vertex_2, vertex_3);

    DOUBLES_EQUAL(4, tri.area(), epsilon);

    tri.~Triangle();

}

TEST (6_sumOfPerimetersOfaNumberOfShapes, HW1) {

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

TEST (1_theLargestArea, HW2) {
    Circle cir(2,7,9.8,"middleCir");
    Rectangle rect(3,8,17,18,"largestRect");
    Triangle tri({4,2}, {34,34}, {2,5}, "smallTir");

    std::vector<Shape *> shapes;
    shapes.push_back(&cir);
    shapes.push_back(&rect);
    shapes.push_back(&tri);

    Shape *largestShape = theLargestArea(shapes);

    CHECK(!((*largestShape).getShapeName().compare("largestRect")));

    cir.~Circle();
    rect.~Rectangle();
    tri.~Triangle();

}

TEST (1_createShapeMedia, Composite) {

    Circle c1(2,1,8);
    ShapeMedia smC1(&c1);

    DOUBLES_EQUAL(50.265482, smC1.perimeter(), epsilon);
    DOUBLES_EQUAL(201.06193, smC1.area(), epsilon);

    smC1.~ShapeMedia();

}

TEST (2_createComboMedia, Composite) {

    Circle c1(2,1,8);
    Rectangle r1(3,2,5,7);
    Triangle t1({0,0}, {0,3}, {4,0});

    ShapeMedia smC1(&c1);
    ShapeMedia smR1(&r1);
    ShapeMedia smT1(&t1);

    std::vector<Media *> medias;
    medias.push_back(&smC1);
    medias.push_back(&smR1);
    medias.push_back(&smT1);

    ComboMedia cb(medias);

    DOUBLES_EQUAL(242.06193, cb.area(), epsilon);
    DOUBLES_EQUAL(86.265482, cb.perimeter(), epsilon);

    cb.~ComboMedia();

}

TEST (1_addShapeMediaIntoComboMedia, HW3) {

    Triangle t1({0,0}, {-1,1.732}, {0,3.464});
    Rectangle r1(0,3.464,3.464,2);
    Triangle t2({2,0}, {3,1.732}, {2,3.464});

    ShapeMedia smT1(&t1);
    ShapeMedia smR1(&r1);
    ShapeMedia smT2(&t2);

    ComboMedia cb1;
    ComboMedia cb2;

    cb1.add(&smT1);
    cb1.add(&smR1);

    cb2.add(&cb1);
    cb2.add(&smT2);

    DOUBLES_EQUAL(10.392, cb2.area(), epsilon);
    DOUBLES_EQUAL(25.855824, cb2.perimeter(), epsilon);

    cb2.~ComboMedia();

}

TEST (2_visitMediaForArea, HW3) {

    AreaVisitor av;

    Triangle t1({0,0}, {-1,1.732}, {0,3.464});
    Rectangle r1(0,3.464,3.464,2);
    Triangle t2({2,0}, {3,1.732}, {2,3.464});

    ShapeMedia smT1(&t1);
    ShapeMedia smR1(&r1);
    ShapeMedia smT2(&t2);

    smT1.accept(&av);
    DOUBLES_EQUAL(1.732, av.getArea(), epsilon);

    smR1.accept(&av);
    DOUBLES_EQUAL(6.928, av.getArea(), epsilon);

    ComboMedia cb1;
    ComboMedia cb2;

    cb1.add(&smT1);
    cb1.add(&smR1);

    cb1.accept(&av);
    DOUBLES_EQUAL(8.660, av.getArea(), epsilon);

    cb2.add(&cb1);
    cb2.add(&smT2);

    cb2.accept(&av);
    DOUBLES_EQUAL(10.392, av.getArea(), epsilon);

    cb2.~ComboMedia();
    av.~AreaVisitor();

}

TEST (3_visitMediaForPerimeter, HW3) {

    PerimeterVisitor pv;

    Triangle t1({0,0}, {-1,1.732}, {0,3.464});
    Rectangle r1(0,3.464,3.464,2);
    Triangle t2({2,0}, {3,1.732}, {2,3.464});

    ShapeMedia smT1(&t1);
    ShapeMedia smR1(&r1);
    ShapeMedia smT2(&t2);

    smT1.accept(&pv);
    DOUBLES_EQUAL(7.463912, pv.getPerimeter(), epsilon);

    smR1.accept(&pv);
    DOUBLES_EQUAL(10.928, pv.getPerimeter(), epsilon);

    ComboMedia cb1;
    ComboMedia cb2;

    cb1.add(&smT1);
    cb1.add(&smR1);

    cb1.accept(&pv);
    DOUBLES_EQUAL(18.391912, pv.getPerimeter(), epsilon);

    cb2.add(&cb1);
    cb2.add(&smT2);

    cb2.accept(&pv);
    DOUBLES_EQUAL(25.855824, pv.getPerimeter(), epsilon);

    cb2.~ComboMedia();
    pv.~PerimeterVisitor();

}

TEST (1_ShapeMediaBuilder, HW4){

    Circle c0(0,0,5);
    ShapeMediaBuilder::getInstance()->buildShapeMedia(&c0);
    Media * ma = ShapeMediaBuilder::getInstance()->getMedia();

    DOUBLES_EQUAL(31.415927, ma->perimeter(),epsilon);
    DOUBLES_EQUAL(78.539816, ma->area(), epsilon);

    ma->~Media();
}

TEST (2_BuildTheHouse, HW4){

    ShapeMediaBuilder * smBuilder = ShapeMediaBuilder::getInstance();
    ComboMediaBuilder * cmBuilder = ComboMediaBuilder::getInstance();

    DescriptionVisitor dv;
    AreaVisitor av;

    Media * maTamp = nullptr;

    Circle c1(12,5,2);
    Rectangle r1(10,0,15,5);
    Rectangle r2(0,0,25,20);
    Triangle t1({0,20}, {16,32}, {25,20});

    smBuilder->buildShapeMedia(&c1);
    cmBuilder->buildComboMedia();
    cmBuilder->addMedia(smBuilder->getMedia());

    smBuilder->buildShapeMedia(&r1);
    cmBuilder->addMedia(smBuilder->getMedia());

    smBuilder->buildShapeMedia(&r2);

    maTamp = cmBuilder->getMedia();
    cmBuilder->buildComboMedia();
    cmBuilder->addMedia(maTamp);
    cmBuilder->addMedia(smBuilder->getMedia());

    smBuilder->buildShapeMedia(&t1);

    maTamp = cmBuilder->getMedia();
    cmBuilder->buildComboMedia();
    cmBuilder->addMedia(maTamp);
    cmBuilder->addMedia(smBuilder->getMedia());

    maTamp = cmBuilder->getMedia();
    maTamp->accept(&dv);

    std::string ans("combo(combo(combo(c(12 5 2)r(10 0 15 5)) r(0 0 25 20)) t(0 20 16 32 25 20)) ");
    CHECK(!(ans.compare(dv.getDescription())));

}

TEST (3_BuildTextMedia, HW4){

    TextMediaBuilder * txBuilder = TextMediaBuilder::getInstance();

    txBuilder->buildTextMedia(Rectangle(0,0,5,5), std::string("Text Box"));

    TextMedia * txTamp = (TextMedia *)txBuilder->getMedia();

    DOUBLES_EQUAL(20.0, txTamp->perimeter(), epsilon);
    CHECK(!(txTamp->getText().compare(std::string("Text Box"))));

}

TEST(4_RemoveShapeMedia, HW4) {

    ShapeMediaBuilder * smBuilder = ShapeMediaBuilder::getInstance();
    ComboMediaBuilder * cmBuilder = ComboMediaBuilder::getInstance();

    DescriptionVisitor dv;
    AreaVisitor av;

    Media * maTamp = nullptr;
    Media * toBeRemoved = nullptr;

    Circle c1(12,5,2);
    Rectangle r1(10,0,15,5);
    Rectangle r2(0,0,25,20);
    Triangle t1({0,20}, {16,32}, {25,20});

    smBuilder->buildShapeMedia(&c1);
    cmBuilder->buildComboMedia();
    cmBuilder->addMedia(smBuilder->getMedia());

    smBuilder->buildShapeMedia(&r1);
    cmBuilder->addMedia(smBuilder->getMedia());

    smBuilder->buildShapeMedia(&r2);
    toBeRemoved = smBuilder->getMedia();

    maTamp = cmBuilder->getMedia();
    cmBuilder->buildComboMedia();
    cmBuilder->addMedia(maTamp);
    cmBuilder->addMedia(toBeRemoved);

    smBuilder->buildShapeMedia(&t1);

    maTamp = cmBuilder->getMedia();
    cmBuilder->buildComboMedia();
    cmBuilder->addMedia(maTamp);
    cmBuilder->addMedia(smBuilder->getMedia());

    maTamp = cmBuilder->getMedia();
    maTamp->accept(&dv);

    std::string ans("combo(combo(combo(c(12 5 2)r(10 0 15 5)) r(0 0 25 20)) t(0 20 16 32 25 20)) ");
    CHECK(!(ans.compare(dv.getDescription())));

    ((ComboMedia *)maTamp)->removeMedia(toBeRemoved);
    maTamp->accept(&dv);

    ans = std::string("combo(combo(combo(c(12 5 2)r(10 0 15 5)) ) t(0 20 16 32 25 20)) ");
    CHECK(!(ans.compare(dv.getDescription())));

}

//
//TEST (1_readFileFromTXT, HW5) {
//
//    MyDocument myShape;
//
//    try {
//        std::string content = myShape.openDocument(std::string("./txt/myShape.txt"));
//
//        CHECK(!(content.compare(std::string("combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))"))));
//
//    } catch (std::string msg) {
//        FAIL(msg.c_str());
//    }
//
//    myShape.~MyDocument();
//
//}

//TEST (2_buildMediaByDirector, HW5) {
//
//    Document myShape;
//    MediaDirector mediaDirector;
//
//    std::stack<Media *> mediaStack;
//
//    mediaDirector.setMediaStack(&mediaStack);
//
//    myShape.openDocument(std::string("./txt/myShape.txt"));
//    std::string content = myShape.readFile();
//
//    mediaDirector.concrete(content);
//
//    Media *mp;
//    DescriptionVisitor dv;
//
//    mp = mediaStack.top();
//    mediaStack.pop();
//
//    mp->accept(&dv);
//
//    std::string strLine = dv.getDescription();
//
//    CHECK(strLine == "combo(r(0 0 3 2)c(0 0 5)combo(r(0 0 5 4)c(0 0 10)) combo(r(0 1 8 7)c(0 1 10)) ) ");
//
//    myShape.~Document();
//    dv.~DescriptionVisitor();
//}


#endif // UTSHAPES_H_INCLUDED

