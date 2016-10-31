
#include "Media.h"
#include <iostream>

/**< ShapeMedia */
Shape * ShapeMedia::getShape(){
    return shape;
}

double ShapeMedia::area() const{
    return shape->area();
}

double ShapeMedia::perimeter() const{
    return shape->perimeter();
}

void ShapeMedia::accept(MediaVisitor * mv){
    mv->ShapeMediaVisitor(this);
}

ShapeMedia::~ShapeMedia() {
    shape->~Shape();
}

/**< TextMedia */
std::string TextMedia::getText(){
    return text;
}

double TextMedia::area() const {
    return boundingBox.area();
}

double TextMedia::perimeter() const {
    return boundingBox.perimeter();
}

void TextMedia::accept(MediaVisitor * mv){
    /* TODO */
}


/**< ComboMedia */
ComboMedia::ComboMedia() {

    std::vector<Media *> instance;
    medias = instance;
}

void ComboMedia::removeMedia(Media * ma){

    for (std::vector<Media *>::iterator it = medias.begin() ; it != medias.end() ; ++it) {
        if ((*it) == ma) {
            medias.erase(it);
            break;
        }

        /* could be better */
        (*it)->accept(MessageVisitor::getInstance());
        std::string classType = MessageVisitor::getInstance()->getMessage();

        if(!(classType.compare("ComboMedia")))
            ((ComboMedia *)(*it)) ->removeMedia(ma);
    }

}

void ComboMedia::add(Media * ma){
    medias.push_back(ma);
}

std::vector<Media *> ComboMedia::getMedias(){
    return medias;
}

double ComboMedia::area() const{
    double total = 0;

    for (Media * mp : medias)
        total += mp->area();

    return total;
}

double ComboMedia::perimeter() const{
    double total = 0;

    for (Media * mp : medias)
        total += mp->perimeter();

    return total;
}

void ComboMedia::accept(MediaVisitor * mv){
    mv->ComboMediaVisitor(this);
}

ComboMedia::~ComboMedia(){
        for (Media * mp : medias)
            mp->~Media();
}
