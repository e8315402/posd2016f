#include "Command.h"
#include "utils.h"

#include <iostream>

void AddCommand::execute() {

    ComboMedia * cmp = (ComboMedia *)mediaMap[object];

    cmp->add( mediaMap[objectName] );

}

void AddCommand::redo() {

    ComboMedia * cmp = (ComboMedia *)mediaMap[object];

    cmp->add( mediaMap[objectName] );

}

void AddCommand::undo() {

    ComboMedia * cmp = (ComboMedia *)mediaMap[object];

    cmp->removeMedia( mediaMap[objectName] );

}


