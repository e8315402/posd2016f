#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

#include "Shapes.h"
#include "Visitor.h"

class MediaVisitor;

class Media {

public:

    virtual double area() const = 0;
    virtual double perimeter () const = 0;
    virtual void accept(MediaVisitor * mv) = 0;

};

class ShapeMedia : public Media {

private:

    Shape * shape;

public:

    ShapeMedia(Shape * sh):shape(sh){}

    Shape * getShape();

    double area() const;

    double perimeter() const;

    void accept(MediaVisitor * mv);

    ~ShapeMedia();
};

class ComboMedia : public Media {

private:

    std::vector<Media *> medias;

public:

    ComboMedia();

    ComboMedia(const std::vector<Media *> & mds): medias(mds){}

    void add(Media * ma);

    void removeMedia(Media * ma);

    std::vector<Media *> getMedias();

    double area() const;

    double perimeter() const;

    void accept(MediaVisitor * mv);

    ~ComboMedia();

};

class TextMedia : public Media {
private:
    Rectangle boundingBox;

    std::string text;

public:

    TextMedia(Rectangle boundingBox, std::string text):boundingBox(boundingBox), text(text){}

    std::string getText();

    double area() const;

    double perimeter() const;

    void accept(MediaVisitor * mv);

};


#endif // MEDIA_H_INCLUDED
