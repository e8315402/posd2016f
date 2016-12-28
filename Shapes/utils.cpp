#include "utils.h"
#include <iostream>
void reOrganizeContent(std::string &content, std::string const oldStr, std::string const newStr) {

    std::string::size_type pos = 0u;

    while((pos = content.find(oldStr, pos)) != std::string::npos){
        content.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }

}

std::string getKeyByValue(std::map<std::string, Media *> & mediaMap, Media * mValue) {

    for (std::map<std::string, Media *>::iterator iter = mediaMap.begin(); iter != mediaMap.end(); iter++) {

        if(iter->second == mValue) return iter->first;

    }

    return "no found";
}


void printAllObject(std::map<std::string, Media *> & mediaMap, std::stringstream & ss, ComboMedia * cmp) {

    ss << getKeyByValue(mediaMap, cmp) << "{";

    DescriptionVisitor dv;

    for(Media * mp : cmp->getMedias()){

        mp->accept(MessageVisitor::getInstance());

        if(MessageVisitor::getInstance()->getMessage() == "ShapeMedia") {
            ss << getKeyByValue(mediaMap, mp) << " " ;
        }

        else printAllObject(mediaMap, ss, (ComboMedia *)mp);
    }

    ss << "}";
}
