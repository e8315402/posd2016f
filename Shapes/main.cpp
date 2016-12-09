#include "..\cppunitlite\TestHarness.h"
#include "utShapes.h"

#include <iostream>
#include <map>
#include <queue>

void def(std::string objectName, std::string object);
void add(std::string objectName, std::string object);
void deleted(std::string objectName, std::string secondToken, std::string object);
void save(std::string objectName, std::string secondToken, std::string object);
void load(std::string objectName);

void getMethod(std::string firstToken);
void reOrganizeContent(std::string &content, std::string const oldStr, std::string const newStr);
Shape * createShape(std::string const token);
void show();
void printAllObject(std::stringstream & ss, ComboMedia * cmp);
std::string getKeyByValue (Media * mValue);
void preOrderTraversal(std::queue<Media *> * mediaQueue, ComboMedia * cmp);

std::map<std::string, Media *> mediaMap;

int main()
{
    //TestResult tr;
    //TestRegistry::runAllTests(tr);

    std::stringstream ss;

    std::string commandString;

    std::string firstToken, objectName, secondToken, object;

    while(1) {

        std::cout << ":- ";

        getline(std::cin, commandString);

        if(commandString == "exit") break;

        if(commandString == "") continue;

        if(commandString == "show") {
            show();
            continue;
        }

        ss << commandString;

        ss >> firstToken >> objectName >> secondToken >> object;

        if(firstToken == "def") def(objectName, object);

        else if(firstToken == "add") add(objectName, object);

        else if(firstToken == "delete") deleted(objectName, secondToken, object);

        else if(firstToken == "save") save(objectName, secondToken, object);

        else if(firstToken == "load")  load(objectName);

        else getMethod(firstToken);

        ss.str("");
        ss.clear();

        firstToken = "";
        objectName = "";
        secondToken = "";
        object = "";

    }

    return 0;
}


void def(std::string objectName, std::string object){

    std::cout << ">> " << object << std::endl;

    if(object.at(0) == 'c') {
        ComboMediaBuilder::getInstance()->buildComboMedia();

        unsigned int preBracketsIndex = object.find("{");
        unsigned int postBracketsIndex = object.find("}") - 1;
        std::string subObjectsNameString = object.substr(preBracketsIndex + 1, postBracketsIndex - preBracketsIndex);

        std::stringstream ss(subObjectsNameString);
        std::string subObjectName;

        while(getline(ss, subObjectName, ',')){
            ComboMediaBuilder::getInstance()->addMedia(mediaMap[subObjectName]);
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

}

void add(std::string objectName, std::string object){

    ComboMedia * cmp = (ComboMedia *)mediaMap[object];
    cmp->add( mediaMap[objectName] );

    std::stringstream ss;
    printAllObject(ss, cmp);

    DescriptionVisitor dv;
    cmp->accept(&dv);
    std::cout << ">> " << object << " = ";
    std::cout << ss.str() << " = " ;
    std::cout << dv.getDescription() << std::endl;

}

void deleted(std::string objectName, std::string secondToken, std::string object){

    if (secondToken == "from") {

        ((ComboMedia *)mediaMap[object])->removeMedia(mediaMap[objectName]);

    } else {

        std::map<std::string, Media *>::iterator iter;

        for (iter = mediaMap.begin(); iter != mediaMap.end(); iter++) {

            iter->second->accept(MessageVisitor::getInstance());

            if (MessageVisitor::getInstance()->getMessage() == "ComboMedia")
                ((ComboMedia *)iter->second)->removeMedia(mediaMap[objectName]);
        }

        iter = mediaMap.find(objectName);
        mediaMap.erase(iter);

    }
}

void save(std::string objectName, std::string secondToken, std::string object){

    unsigned int preBracketsIndex = object.find("\"");
    unsigned int postBracketsIndex = object.find("\"", preBracketsIndex + 1) - 1;
    std::string fileName = object.substr(preBracketsIndex + 1, postBracketsIndex - preBracketsIndex);

    std::cout << ">> " << objectName << " saved to " << fileName << std::endl;

    std::string argString; // r(0,0,1)
    std::string argNameString; // rTall

    DescriptionVisitor dv;
    mediaMap[objectName]->accept(&dv);
    argString = dv.getDescription();
    dv.~DescriptionVisitor();

    mediaMap[objectName]->accept(MessageVisitor::getInstance());

    if(MessageVisitor::getInstance()->getMessage() == "ComboMedia") {

        std::stringstream ss;

        printAllObject(ss, (ComboMedia *)mediaMap[objectName]);

        argNameString = ss.str();

    } else {

        argNameString = getKeyByValue(mediaMap[objectName]);

    }

    std::string content = argString + std::string("\n") + argNameString;

    Document doc;

    try {

        doc.openDocument(fileName);
        doc.write(content);
        doc.saveDocument();
        doc.~Document();

    } catch (std::string msg) {

        std::cout << msg << std::endl;

    }

}

void load(std::string objectName){

    unsigned int preBracketsIndex = objectName.find("\"");
    unsigned int postBracketsIndex = objectName.find("\"", preBracketsIndex + 1) - 1;
    std::string fileName = objectName.substr(preBracketsIndex + 1, postBracketsIndex - preBracketsIndex);

    std::cout << ">> loading " << fileName << " ..." << std::endl;

    Document doc;
    doc.openDocument(fileName);
    std::stringstream content(doc.readFile());

    std::string argString, argNameString;
    std::getline(content, argString, '\n');
    std::getline(content, argNameString, '\n');

    MediaDirector md;
    std::stack<Media *> mediaStack;
    md.setMediaStack(&mediaStack);
    md.concrete(argString);

    Media * mp = mediaStack.top();
    mediaStack.pop();

    mp->accept(MessageVisitor::getInstance());
    if(MessageVisitor::getInstance()->getMessage() == "ShapeMedia"){

        mediaMap[argNameString] = mp;
        return;

    } else {

        std::queue<Media *> mediaQueue;
        preOrderTraversal(&mediaQueue, (ComboMedia *)mp);

        reOrganizeContent(argNameString, "{", " ");
        reOrganizeContent(argNameString, "}", " ");

        std::stringstream sstemp(argNameString);
        std::string argName;
        while(std::getline(sstemp, argName, ' ')){
            if(argName == "") continue;
            mediaMap[argName] = mediaQueue.front();
            mediaQueue.pop();
        }

    }

    doc.~Document();
}

void getMethod(std::string firstToken){

    reOrganizeContent(firstToken, ".", " ");

    std::stringstream ss(firstToken);
    std::string objectName, method;
    ss >> objectName >> method;

    if (method == "area?") std::cout << ">> " << mediaMap[objectName]->area() << std::endl;

    else if (method == "perimeter?") std::cout << ">> " <<mediaMap[objectName]->perimeter() <<std::endl;

    else std::cout << ">> " << "Command does not exist." << std::endl;

}

void show() {

    if(mediaMap.size() == 0) return;

    DescriptionVisitor dv;
    std::stringstream ss;

    std::cout << "[Show]" << std::endl;

    for (std::map<std::string, Media *>::iterator iter = mediaMap.begin(); iter != mediaMap.end(); iter++) {
        iter->second->accept(MessageVisitor::getInstance());
        if (MessageVisitor::getInstance()->getMessage() == "ComboMedia"){

            printAllObject(ss, (ComboMedia*)iter->second);

            std::cout << iter->first << " = " << ss.str() << " = ";

            iter->second->accept(&dv);

            std::cout<< dv.getDescription() << std::endl;

            ss.str(""); ss.clear();
        } else {
            iter->second->accept(&dv);
            std::cout<< iter->first << " = " << dv.getDescription() << std::endl;
        }
    }

}

std::string getKeyByValue(Media * mValue) {

    for (std::map<std::string, Media *>::iterator iter = mediaMap.begin(); iter != mediaMap.end(); iter++) {

        if(iter->second == mValue) return iter->first;

    }

    return "no found";
}

void preOrderTraversal(std::queue<Media *> * mediaQueue, ComboMedia * cmp){

    mediaQueue->push(cmp);

    for(Media * mp : cmp->getMedias()){

        mp->accept(MessageVisitor::getInstance());

        if(MessageVisitor::getInstance()->getMessage() == "ShapeMedia")
            mediaQueue->push(mp);

        else preOrderTraversal(mediaQueue, (ComboMedia *)mp);
    }

}

void printAllObject(std::stringstream & ss, ComboMedia * cmp){

    ss << getKeyByValue(cmp) << "{";

    for(Media * mp : cmp->getMedias()){

        mp->accept(MessageVisitor::getInstance());

        if(MessageVisitor::getInstance()->getMessage() == "ShapeMedia")
            ss << getKeyByValue(mp) << " " ;

        else printAllObject(ss, (ComboMedia *)mp);
    }

    ss << "}";
}
