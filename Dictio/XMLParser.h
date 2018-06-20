#ifndef XMLPARSER_H
#define XMLPARSER_H

#include<QFile>

#include"Container.h"

class XMLParser {
protected:
    QFile* file;
    Container* cont;
public:
    explicit XMLParser(Container* c);
    virtual void open4reading() =0;
    virtual void open4writing() =0;
    void closeFile();
    Container* getContainer() const;
    virtual bool parseXML() =0;
    virtual bool writeXML() =0;
    virtual ~XMLParser();
};

#endif // XMLPARSER_H
