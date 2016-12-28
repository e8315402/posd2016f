
#include "Document.h"

void Document::openDocument(const std::string name) {

	if(!canOpenDocument(name)) {
        std::cout << "File: \"" << name << "\" does not exit. Create a new one? Y/n: " ;

        char ans;
        std::cin >> ans;
        if(ans != 89 && ans != 121) return;
        std::cout << "Create a new file: \"" << name << "\"" << std::endl;
        file.open(name, std::ios_base::out);
        file.close();
	}

	file.open(name);
	std::cout << "File: \"" << name << "\" exist. Open file." << std::endl;
}

void Document::saveDocument() {
    file.close();
}

std::string Document::readFile() {

    std::stringstream ss;

    std::string line;

    if (file.is_open()) {
        while(getline(file, line, '\n')) {
            ss << line << '\n';
        }
    }

    return ss.str();
}

void Document::write(std::string content) {
    if(file.is_open()) {
        file << content;
        return ;
    }
    std::cout << "Writing error. Document no open." << std::endl;
}

bool Document::canOpenDocument(const std::string name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

Document::~Document() {
    if(file.is_open()) file.close();
}

