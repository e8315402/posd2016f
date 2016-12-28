#include "..\cppunitlite\TestHarness.h"
#include "utShapes.h"
#include "utils.h"

#include <iostream>
#include <map>
#include <queue>
#include <thread>
#include <chrono>
#include <windows.h>

#define HIGH_ORDER_BIT 0x8000
#define VK_Z 0x5A
#define VK_Y 0x59

void def(CommandManager & cmdM, std::string objectName, std::string object);
void add(CommandManager & cmdM, std::string objectName, std::string object);
void deleted(CommandManager & cmdM, std::string objectName, std::string secondToken, std::string object);
void save(std::string objectName, std::string secondToken, std::string object);
void load(std::string objectName);
void getMethod(std::string firstToken);

void show();
void preOrderTraversal(std::queue<Media *> * mediaQueue, ComboMedia * cmp);
Shape * createShape(std::string const token);

std::map<std::string, Media *> mediaMap;

inline bool isKeyDown(int VirtualCode) {
    return (GetKeyState(VirtualCode) & HIGH_ORDER_BIT);
}

void keyevent(CommandManager & cmdM) {

    while(1) {
        if(isKeyDown(VK_CONTROL)) {
            //Control has been pressed
            if(isKeyDown(VK_Z)) {
                cmdM.undoCMD();
                std::cout << "\b\bUndo\n:- ";
                std::cin.clear();
            }

            if(isKeyDown(VK_Y)) {
                cmdM.redoCMD();
                std::cout << "\b\bRedo\n:- ";
                std::cin.clear();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}

int main()
{
//    TestResult tr;

    std::stringstream ss;

    std::string commandString;

    std::string firstToken, objectName, secondToken, object;

    CommandManager cmdM;

    std::thread t1(keyevent, std::ref(cmdM));

    while(1) {

        std::cout << ":- ";

        getline(std::cin, commandString);

        //prevent from loop-hell
        if(commandString.empty()) std::cin.clear();

        if(commandString == "exit") {
            t1.detach();
            break;
        }

        if(commandString == "") continue;

        if(commandString == "show") {
            show();
            continue;
        }

//        if(commandString == "test") {
//            TestRegistry::runAllTests(tr);
//            continue;
//        }

        ss << commandString;

        ss >> firstToken >> objectName >> secondToken >> object;

        if(firstToken == "def") def(cmdM, objectName, object);

        else if(firstToken == "add") add(cmdM, objectName, object);

        else if(firstToken == "delete") deleted(cmdM, objectName, secondToken, object);

        else if(firstToken == "save") save(objectName, secondToken, object);

        else if(firstToken == "load") load(objectName);

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

void def(CommandManager & cmdM, std::string objectName, std::string object) {

//    DefCommand * defCMD = ;

    cmdM.executeCMD(new DefCommand(mediaMap, objectName, object));

    std::cout << ">> " << object << std::endl;

}

void add(CommandManager & cmdM, std::string objectName, std::string object) {

//    AddCommand * addCMD = ;

    cmdM.executeCMD(new AddCommand(mediaMap, objectName, object));

    ComboMedia * cmp = (ComboMedia *)mediaMap[object];
    std::stringstream ss;
    printAllObject(mediaMap, ss, cmp);

    DescriptionVisitor dv;
    cmp->accept(&dv);
    std::cout << ">> " << object << " = ";
    std::cout << ss.str() << " = " ;
    std::cout << dv.getDescription() << std::endl;

}

void deleted(CommandManager & cmdM, std::string objectName, std::string secondToken, std::string object) {

//    DeleteCommand * delCMD = ;

    cmdM.executeCMD(new DeleteCommand(mediaMap, objectName, secondToken, object));

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

        printAllObject(mediaMap, ss, (ComboMedia *)mediaMap[objectName]);

        argNameString = ss.str();

    } else {

        argNameString = getKeyByValue(mediaMap, mediaMap[objectName]);

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

    if(mediaMap.size() == 0) {
        std::cout << "mediaMap Size: 0" << std::endl;
        return;
    }

    DescriptionVisitor dv;
    std::stringstream ss;

    std::cout << "[Show]" << std::endl;

    for (std::map<std::string, Media *>::iterator iter = mediaMap.begin(); iter != mediaMap.end(); iter++) {
        iter->second->accept(MessageVisitor::getInstance());
        if (MessageVisitor::getInstance()->getMessage() == "ComboMedia"){

            printAllObject(mediaMap, ss, (ComboMedia*)iter->second);

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

void preOrderTraversal(std::queue<Media *> * mediaQueue, ComboMedia * cmp){

    mediaQueue->push(cmp);

    for(Media * mp : cmp->getMedias()){

        mp->accept(MessageVisitor::getInstance());

        if(MessageVisitor::getInstance()->getMessage() == "ShapeMedia")
            mediaQueue->push(mp);

        else preOrderTraversal(mediaQueue, (ComboMedia *)mp);
    }

}

