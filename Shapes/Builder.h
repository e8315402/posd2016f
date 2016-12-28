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

    void buildShapeMedia(Shape * shape);

    Media * getMedia();
};




class ComboMediaBuilder : public MediaBuilder {
private:
    static ComboMediaBuilder * instance;

    ComboMedia * cm;
    ComboMediaBuilder();

public:

    static ComboMediaBuilder * getInstance();

    void buildComboMedia();

    void addMedia(Media * ma);

    Media * getMedia();

};


class TextMediaBuilder : public MediaBuilder {
private:

    static TextMediaBuilder * instance;

    TextMedia * tm;

    TextMediaBuilder();

public:

    static TextMediaBuilder * getInstance();

    void buildTextMedia(Rectangle boundingBox, std::string text);

    Media * getMedia();

};

#endif // BUILDER_H_INCLUDED
