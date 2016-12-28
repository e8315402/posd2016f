#include "Command.h"
#include "utils.h"

#include <queue>

void DeleteCommand::execute() {

    deletedMedia = mediaMap[objectName];

    if (secondToken == "from") {

        getPostionOfDeletedMedia(deletedMedia, (ComboMedia *)mediaMap[object]);

        ((ComboMedia *)mediaMap[object])->removeMedia( deletedMedia );


    } else {

        std::map<std::string, Media *>::iterator it;

        for (it = mediaMap.begin(); it != mediaMap.end(); it++) {

            it->second->accept(MessageVisitor::getInstance());

            if (MessageVisitor::getInstance()->getMessage() == "ComboMedia") {

                getPostionOfDeletedMedia(deletedMedia, (ComboMedia *)it->second);
                ((ComboMedia *)it->second)->removeMedia( deletedMedia );

            }

        }

        it = mediaMap.find(objectName);
        if(it != mediaMap.end()) mediaMap.erase(it);

    }

}

void DeleteCommand::redo() {

    for(unsigned int index = 0; index != postionOfDeletedMedia.size(); index++)
        ((ComboMedia *)postionOfDeletedMedia[index])->removeMedia( deletedMedia );

    if(secondToken != "from") {

        std::map<std::string, Media *>::iterator it;

        it = mediaMap.find(objectName);

        if(it != mediaMap.end()) mediaMap.erase(it);

    }

}

void DeleteCommand::undo() {

    mediaMap[objectName] = deletedMedia;

    for(unsigned int index = 0; index != postionOfDeletedMedia.size(); index++)
        ((ComboMedia *)postionOfDeletedMedia[index])->add( deletedMedia );

}

void DeleteCommand::getPostionOfDeletedMedia (Media * deletedMedia, ComboMedia * cm) {

    for(Media * mp : cm->getMedias()) {

        if(mp == deletedMedia) {
            postionOfDeletedMedia.push_back(cm);
            continue;
        }

        mp->accept(MessageVisitor::getInstance());

        if(MessageVisitor::getInstance()->getMessage() == "ComboMedia")
            return getPostionOfDeletedMedia(deletedMedia, (ComboMedia *)mp);

    }

}

