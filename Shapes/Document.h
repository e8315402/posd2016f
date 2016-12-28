#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sys/stat.h>

class Document {
public :
    std::fstream file;

     void openDocument(const std::string name);
     void saveDocument();

     std::string readFile();
     void write(std::string content);

     ~Document();

private :
    bool canOpenDocument(const std::string name);

};

#endif // DOCUMENT_H_INCLUDED
