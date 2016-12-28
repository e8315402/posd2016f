#include <sstream>


#include "MyDocument.h"

void MyDocument::openFile(const std::string name) {
    myfile.open(name);
};

bool MyDocument::canOpenDocument(const std::string name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

std::string MyDocument::readFile() {
    std::stringstream ss;
    std::string line;

    if (myfile.is_open()) {
        while(std::getline(myfile,line)) {
        ss << line;
        }
    }

    return ss.str();
};

void MyDocument::write(std::string content) {
    if(!myfile.is_open()) std::cout << "Writing error. Document no open." << std::endl;


}
