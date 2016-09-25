#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include <vector>

typedef struct Coordinate
{
    double x;
    double y;
}vertex;

double distanceOfVertexs(vertex vertex_1, vertex vertex_2);

class Shape {

public:

    virtual double area() const = 0;
    virtual double perimeter() const = 0;

};

class Rectangle : public Shape {

private:

    double x,y,l,w;

public:

    Rectangle(double ulcx, double ulcy, double length, double width):
        x(ulcx),y(ulcy),l(length),w(width){}

    double area() const {return l*w;}

    double perimeter() const {return (2*l)+(2*w);}

};

class Circle : public Shape{

private:

    double cx,cy,r;

public:

    Circle(double centerX,double centerY,double radius):
        cx(centerX),cy(centerY),r(radius){}

    double area() const {return M_PI*r*r;}

    double perimeter() const {return M_PI*r*2;}

};

class Triangle : public Shape {
private:

    vertex v1;
    vertex v2;
    vertex v3;

public:

    Triangle(vertex vertex_A, vertex vertex_B, vertex vertex_C):
        v1(vertex_A), v2(vertex_B), v3(vertex_C) {}

    double area() const {

        double area;
        double a,b,c,s;

        a = distanceOfVertexs(v1, v2);
        b = distanceOfVertexs(v2, v3);
        c = distanceOfVertexs(v1, v3);

        s = (a + b + c)/(double)2;

        area = std::sqrt(s * (s-a) * (s-b) * (s-c));
        return area;
    }

    double perimeter() const {

        double sumOfLenghts;
        sumOfLenghts = distanceOfVertexs(v1, v2) + distanceOfVertexs(v2, v3) + distanceOfVertexs(v1, v3);

        return sumOfLenghts;
    }

};

double sumOfArea(std::vector<Rectangle> rects) {
    double total =0;

    for (Rectangle r: rects)
        total += r.area();

    return total;
}

double sumOfArea(std::vector<Shape *> rects) {
    double total =0;

    for (Shape *r: rects)
        total += r->area();

    return total;
}

double sumOfPerimeter(std::vector<Shape *> shapes){
    double total = 0;

    for (Shape *shapePoint: shapes)
        total += shapePoint->perimeter();

    return total;
}

Shape* theLargestArea(std::vector<Shape *> shapes){
    Shape *largestShape = nullptr;
    double largestArea = 0;

    for (Shape *shapePoint: shapes)
        if(shapePoint->area() >= largestArea)
            largestShape = shapePoint;

    return largestShape;
}

double distanceOfVertexs(vertex vertex_1, vertex vertex_2) {
    double diff_X, diff_Y, distance;

    diff_X = vertex_1.x - vertex_2.x;
    diff_Y = vertex_1.y - vertex_2.y;

    distance = std::sqrt(((diff_X * diff_X) + (diff_Y * diff_Y)));

    return distance;
}

#endif // SHAPES_H_INCLUDED
