#ifndef MYDOCUMENT_H_INCLUDED
#define MYDOCUMENT_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>

#include "Document.h"

class MyDocument : public Document {
private:
    std::fstream myfile;

protected:
    void openFile(const std::string name);
    bool canOpenDocument(const std::string name);
    std::string readFile();
    void write(std::string content);

public:
    ~MyDocument() {
        if(myfile.is_open())
            myfile.close();
    }
};


#endif // MYDOCUMENT_H_INCLUDED
