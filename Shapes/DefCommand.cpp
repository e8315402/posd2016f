#include "Command.h"
#include "utils.h"

#include <iostream>

Shape * createShape(std::string const token);

void DefCommand::execute() {

    std::string object = this->object;

    if(object.at(0) == 'c') {
        ComboMediaBuilder::getInstance()->buildComboMedia();

        unsigned int preBracketsIndex = object.find("{");
        unsigned int postBracketsIndex = object.find("}") - 1;
        std::string subObjectsNameString = object.substr(preBracketsIndex + 1, postBracketsIndex - preBracketsIndex);

        std::stringstream ss(subObjectsNameString);
        std::string subObjectName;

        while(getline(ss, subObjectName, ',')){
            ComboMediaBuilder::getInstance()->addMedia( mediaMap[subObjectName] );
        }

        mediaMap[objectName] = ComboMediaBuilder::getInstance()->getMedia();

    } else {
        // "Circle(1,1,2)" to "c(1 1 2)"
        reOrganizeContent(object, ",", " ");
        switch (object.at(0))
        {
            case 'C':
                reOrganizeContent(object, "Circle", "c");
                break;
            case 'R':
                reOrganizeContent(object, "Rectangle", "r");
                break;
            case 'T':
                reOrganizeContent(object, "Triangle", "t");
                break;
        }

        ShapeMediaBuilder::getInstance()->buildShapeMedia(createShape(object));

        mediaMap[objectName] = ShapeMediaBuilder::getInstance()->getMedia();
    }

    defMedia = mediaMap[objectName];
}

void DefCommand::redo() {

    mediaMap[objectName] = defMedia;

}

void DefCommand::undo() {

    std::map<std::string, Media *>::iterator it;

    it = mediaMap.find(objectName);

    mediaMap.erase(it);

}
