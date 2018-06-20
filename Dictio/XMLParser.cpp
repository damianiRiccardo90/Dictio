#include"XMLParser.h"

XMLParser::XMLParser(Container *c):
    file(new QFile),
    cont(c)
{}

void XMLParser::closeFile() {file->close();}

Container *XMLParser::getContainer() const {return cont;}

XMLParser::~XMLParser() {
    delete file;
    delete cont;
}
