#ifndef BUILDER_H_INCLUDED
#define BUILDER_H_INCLUDED

#include "Media.h"

class MediaBuilder
{
 public:
//    virtual void buildMedia(Media * ma) = 0;
//    virtual void buildShapeMedia(Shape * s) = 0;
    virtual Media *getMedia() = 0;

};


class ShapeMediaBuilder : public MediaBuilder {

private:
    static ShapeMediaBuilder * instance;

    ShapeMedia * sm;
    ShapeMediaBuilder();

public:
    static ShapeMediaBuilder * getInstance();

    void buildShapeMedia(Shape * shape) {
        sm = new ShapeMedia(shape);
    }

    Media * getMedia() {
        Media * ma = sm;
        sm = nullptr;
        return ma;
    }

};

ShapeMediaBuilder * ShapeMediaBuilder::instance = 0;

ShapeMediaBuilder::ShapeMediaBuilder(){}

ShapeMediaBuilder * ShapeMediaBuilder::getInstance() {
    if(!instance)
        instance = new ShapeMediaBuilder();
    return instance;
}


class ComboMediaBuilder : public MediaBuilder {
private:
    static ComboMediaBuilder * instance;

    ComboMedia * cm;
    ComboMediaBuilder();

public:

    static ComboMediaBuilder * getInstance();

    void buildComboMedia() {
        cm = new ComboMedia();
    }

    void addMedia(Media * ma) {
        if(!cm) throw std::string("ComboMedia point to null.");

        cm->add(ma);
    }

    Media * getMedia() {
        return cm;
    }

};
ComboMediaBuilder * ComboMediaBuilder::instance = 0;

ComboMediaBuilder::ComboMediaBuilder(){}

ComboMediaBuilder * ComboMediaBuilder::getInstance() {
    if (!instance)
        instance = new ComboMediaBuilder();
    return instance;
}


class TextMediaBuilder : public MediaBuilder {
private:

    static TextMediaBuilder * instance;

    TextMedia * tm;

    TextMediaBuilder();

public:

    static TextMediaBuilder * getInstance();

    void buildTextMedia(Rectangle boundingBox, std::string text) {
        tm = new TextMedia(boundingBox, text);
    }

    Media * getMedia() {
        return tm;
    }

};

TextMediaBuilder * TextMediaBuilder::instance = 0;

TextMediaBuilder::TextMediaBuilder(){}

TextMediaBuilder * TextMediaBuilder::getInstance(){
    if(!instance)
        instance = new TextMediaBuilder();
    return instance;
}

#endif // BUILDER_H_INCLUDED
