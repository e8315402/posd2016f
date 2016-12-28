#include "Command.h"

CommandManager::CommandManager() {}

void CommandManager::executeCMD(Command * cmd) {

    while(!stackRedoCMDs.empty()) stackRedoCMDs.pop();

    stackUndoCMDs.push(cmd);

    cmd->execute();

}

void CommandManager::undoCMD() {

    if(stackUndoCMDs.empty()) return;

    stackUndoCMDs.top()->undo();

    stackRedoCMDs.push( stackUndoCMDs.top() );

    stackUndoCMDs.pop();

}

void CommandManager::redoCMD() {

    if(stackRedoCMDs.empty()) return;

    stackRedoCMDs.top()->redo();

    stackUndoCMDs.push( stackRedoCMDs.top() );

    stackRedoCMDs.pop();

}
