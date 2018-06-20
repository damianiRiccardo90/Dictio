#ifndef MANAGER_H
#define MANAGER_H

#include<QString>

#include"Data.h"
#include"XMLParser.h"
#include"Container.h"

class Manager {
private:
    XMLParser* parser;
public:
    explicit Manager(XMLParser* p);
    virtual void insert(const Data&) =0;
    virtual void remove(const QString&) =0;
    virtual int find(const QString&) const =0;
    virtual int count() const =0;
    virtual void setModified(bool) =0;
    virtual bool isModified() const =0;
    Container* getContainer() const;
    bool parseXML();
    bool writeXML();
    virtual Data* getPointer(int) const =0;
    virtual ~Manager();
};

#endif // MANAGER_H
