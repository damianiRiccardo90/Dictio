#ifndef CONTAINER_H
#define CONTAINER_H

#include"Data.h"
#include"Account.h"
#include"Term.h"

class Container {
public:
    virtual Data* getPtr(int index) const =0;
    virtual void* getPtr() const =0;
    virtual int size() const =0;
    virtual void insert(const Data& obj) =0;
    virtual ~Container() {}
};

#endif // CONTAINER_H
