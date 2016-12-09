#ifndef BUILDER_H_INCLUDED
#define BUILDER_H_INCLUDED

#include <stack>

#include "Media.h"

class MediaDirector {

public :
    void setMediaStack(std::stack<Media *> *mediaStack);
	void concrete(std::string content);

private :
    std::stack<Media *> *mediaStack = nullptr;

};

class MediaBuilder
{
 public:

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



#endif // BUILDER_H_INCLUDED
