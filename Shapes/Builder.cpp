#include <sstream>
#include <iostream>
#include <string>

#include "Builder.h"
#include "utils.h"

Shape * createShape(std::string const token) {

    // "r(0 0 3 2)" to "0 0 3 2"
    unsigned int preBracketsIndex = token.find("(");
    unsigned int postBracketsIndex = token.find(")") - 1;
    std::string argsString = token.substr(preBracketsIndex + 1, (postBracketsIndex - preBracketsIndex));

    std::stringstream argsStringStream(argsString);

    if(token[0] == 'r') {

        double ulcx, ulcy, length, width;

        argsStringStream >> ulcx >> ulcy >> length >> width;

        return new Rectangle(ulcx, ulcy, length, width);
    }

    if(token[0] == 'c') {

        double centerX, centerY, radius;

        argsStringStream >> centerX >> centerY >> radius;

        return new Circle(centerX, centerY, radius);

    }

    if(token[0] == 't') {
        /**< TODO */
    }

    return nullptr;
}

void MediaDirector::setMediaStack(std::stack<Media *> *mediaStack) {
    this->mediaStack = mediaStack;
}

void MediaDirector::concrete(std::string content) {

    reOrganizeContent(content, ") ", ")");

    std::string fineContent = content;

    std::stringstream ss;

    for (char p : fineContent) {

        ss << p;

        if(ss.str() == std::string("combo(")) {

            ComboMediaBuilder::getInstance()->buildComboMedia();
            this->mediaStack->push(ComboMediaBuilder::getInstance()->getMedia());

            ss.str("");

            continue;
        }

        if(p == ')') {

            if(ss.str().length() == 1) { // token = ')'

                std::stack<Media *> swapMediaStack;

                while(!this->mediaStack->empty()) {

                    this->mediaStack->top()->accept(MessageVisitor::getInstance());

                    if(MessageVisitor::getInstance()->getMessage() == "ShapeMedia") {

                        swapMediaStack.push(this->mediaStack->top());


                        this->mediaStack->pop();
                        continue;
                    }

                    if(MessageVisitor::getInstance()->getMessage() == "ComboMedia") {

                        ComboMedia * cm = (ComboMedia*)this->mediaStack->top();
                        if(cm->getMedias().size() != 0){ //swapMediaStack.empty()
                            swapMediaStack.push(this->mediaStack->top());

                            this->mediaStack->pop();
                            continue;
                        }

                        while(!swapMediaStack.empty()) {
                            cm->add(swapMediaStack.top());
                            swapMediaStack.pop();
                        }

                        break;
                    }
                }

                if(!swapMediaStack.empty()){
                     std::cout << "swapMediaStack is not empty __ swapMediaStack size : "<< swapMediaStack.size() << "\n";

                     while(!swapMediaStack.empty()){

                        swapMediaStack.top()->accept(MessageVisitor::getInstance());

                        std::cout << MessageVisitor::getInstance()->getMessage() << "\n";

                        swapMediaStack.pop();

                     }
                }

            } else { // token = "r(1 2 3 4)" or "c(1 2 3)"

                Shape *sp = createShape(ss.str());
                ShapeMediaBuilder::getInstance()->buildShapeMedia(sp);

                this->mediaStack->push(ShapeMediaBuilder::getInstance()->getMedia());

            }

            ss.str("");

            continue;

        }

    }

}



ShapeMediaBuilder * ShapeMediaBuilder::instance = 0;

ShapeMediaBuilder::ShapeMediaBuilder(){}

ShapeMediaBuilder * ShapeMediaBuilder::getInstance() {
    if(!instance)
        instance = new ShapeMediaBuilder();
    return instance;
}

void ShapeMediaBuilder::buildShapeMedia(Shape * shape) {
    sm = new ShapeMedia(shape);
}

Media * ShapeMediaBuilder::getMedia() {
    Media * ma = sm;
    sm = nullptr;
    return ma;
}


ComboMediaBuilder * ComboMediaBuilder::instance = 0;

ComboMediaBuilder::ComboMediaBuilder(){}

ComboMediaBuilder * ComboMediaBuilder::getInstance() {
    if (!instance)
        instance = new ComboMediaBuilder();
    return instance;
}

void ComboMediaBuilder::buildComboMedia() {
    cm = new ComboMedia();
}

void ComboMediaBuilder::addMedia(Media * ma) {
    if(!cm) throw std::string("ComboMedia point to null.");
    cm->add(ma);
}

Media * ComboMediaBuilder::getMedia() {
    Media * ma = cm;
    cm = nullptr;
    return ma;
}


TextMediaBuilder * TextMediaBuilder::instance = 0;

TextMediaBuilder::TextMediaBuilder(){}

TextMediaBuilder * TextMediaBuilder::getInstance(){
    if(!instance)
        instance = new TextMediaBuilder();
    return instance;
}

void TextMediaBuilder::buildTextMedia(Rectangle boundingBox, std::string text) {
    tm = new TextMedia(boundingBox, text);
}

Media * TextMediaBuilder::getMedia() {
    return tm;
}
