#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <stack>
#include <vector>
#include <map>

#include "Shapes.h"
#include "Builder.h"
#include "Media.h"
#include "Visitor.h"
#include "MyDocument.h"

class Command;

class CommandManager {
public:
    CommandManager();
    void executeCMD(Command * cmd);
    void redoCMD();
    void undoCMD();
private:
    std::stack<Command *> stackUndoCMDs;
    std::stack<Command *> stackRedoCMDs;
};

class Command {
public:
    virtual void execute() = 0;
    virtual void redo() = 0;
    virtual void undo() = 0;
    Command(std::map<std::string, Media *> & mediaMap):mediaMap(mediaMap) {}
protected:
    std::map<std::string, Media *> & mediaMap;
};

class DefCommand : public Command{
public:
    DefCommand(std::map<std::string, Media *> & mediaMap, std::string objectName, std::string object)
            :Command(mediaMap), objectName(objectName), object(object) {};
    void execute();
    void redo();
    void undo();
private:
    std::string objectName;
    std::string object;
    Media * defMedia;
};

class AddCommand : public Command {
public:
    AddCommand(std::map<std::string, Media *> & mediaMap, std::string objectName, std::string object)
             :Command(mediaMap), objectName(objectName), object(object) {};
    void execute();
    void redo();
    void undo();
private:
    std::string objectName;
    std::string object;
};

class DeleteCommand : public Command {
public:
    DeleteCommand(std::map<std::string, Media *> & mediaMap, std::string objectName, std::string secondToken, std::string object)
            :Command(mediaMap), objectName(objectName), secondToken(secondToken), object(object) {};
    void execute();
    void redo();
    void undo();
private:
    std::string objectName;
    std::string secondToken;
    std::string object;
    std::vector<Media *> postionOfDeletedMedia;
    Media * deletedMedia;

    void getPostionOfDeletedMedia (Media * deletedMedia, ComboMedia * cm);

};


#endif // COMMAND_H_INCLUDED
