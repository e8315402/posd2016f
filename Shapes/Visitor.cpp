
#include "Visitor.h"

void AreaVisitor::ShapeMediaVisitor(ShapeMedia * sm){

    area += sm->getShape()->area();

}

void AreaVisitor::ComboMediaVisitor(ComboMedia * cm){

    for (Media * mp : cm->getMedias())
        mp->accept(this);

}

double AreaVisitor::getArea(){

    double total = area;

    area = 0.0;

    return total;

}

void PerimeterVisitor::ShapeMediaVisitor(ShapeMedia * sm){

    perimeter += sm->getShape()->perimeter();

}

void PerimeterVisitor::ComboMediaVisitor(ComboMedia * cm){

    for (Media * mp : cm->getMedias())
        mp->accept(this);

}

double PerimeterVisitor::getPerimeter(){

    double total = perimeter;

    perimeter = 0.0;

    return total;

}

void DescriptionVisitor::ShapeMediaVisitor(ShapeMedia * sm){
    desc += sm->getShape()->toString();
}

void DescriptionVisitor::ComboMediaVisitor(ComboMedia * cm){

    desc += std::string("Combo(");

    for (Media * mp : cm->getMedias())
        mp->accept(this);

    desc += std::string(") ");

}

std::string DescriptionVisitor::getDescription(){

    std::string tamp = desc;

    desc.clear();

    return tamp;

}

MessageVisitor * MessageVisitor::instance = 0;

MessageVisitor::MessageVisitor():message(std::string("")) {}

MessageVisitor * MessageVisitor::getInstance() {
    if(!instance)
        instance = new MessageVisitor();
    return instance;
}

void MessageVisitor::ShapeMediaVisitor(ShapeMedia * sm){
    message = std::string("ShapeMedia");
}

void MessageVisitor::ComboMediaVisitor(ComboMedia * cm){
    message = std::string("ComboMedia");
}

std::string MessageVisitor::getMessage(){
    return message;
}

