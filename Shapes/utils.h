#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "Media.h"

#include <map>
#include <sstream>
#include <string>

void reOrganizeContent(std::string &content, std::string const oldStr, std::string const newStr);

void printAllObject(std::map<std::string, Media *> & mediaMap, std::stringstream & ss, ComboMedia * cmp);

std::string getKeyByValue(std::map<std::string, Media *> & mediaMap, Media * mValue);

#endif // UTILS_H_INCLUDED
