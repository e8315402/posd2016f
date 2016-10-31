#ifndef VISITOR_H_INCLUDED
#define VISITOR_H_INCLUDED

#include "Media.h"

class Media;
class ComboMedia;
class ShapeMedia;

class MediaVisitor {

public:

    virtual void ShapeMediaVisitor(ShapeMedia * ma) = 0;
    virtual void ComboMediaVisitor(ComboMedia * ma) = 0;

};

class AreaVisitor : public MediaVisitor{

private:

    double area;

public:

    AreaVisitor():area(0.0) {}

    void ShapeMediaVisitor(ShapeMedia * sm);

    void ComboMediaVisitor(ComboMedia * cm);

    double getArea();

};

class PerimeterVisitor : public MediaVisitor{
private:

    double perimeter;

public:

    PerimeterVisitor():perimeter(0.0) {}

    void ShapeMediaVisitor(ShapeMedia * sm);

    void ComboMediaVisitor(ComboMedia * cm);

    double getPerimeter();

};

class DescriptionVisitor : public MediaVisitor {
private:
    std::string desc;

public:

    DescriptionVisitor():desc(std::string("")) {}

    void ShapeMediaVisitor(ShapeMedia * sm);

    void ComboMediaVisitor(ComboMedia * cm);

    std::string getDescription();
};

class MessageVisitor : public MediaVisitor {
private:
    static MessageVisitor * instance;

    std::string message;

    MessageVisitor();

public:

    static MessageVisitor * getInstance();

    void ShapeMediaVisitor(ShapeMedia * sm);

    void ComboMediaVisitor(ComboMedia * cm);

    std::string getMessage();

};

#endif // VISITOR_H_INCLUDED
