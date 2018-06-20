#ifndef DICTIONARYCONTAINER_H
#define DICTIONARYCONTAINER_H

#include<QMap>
#include<QString>

#include"Container.h"
#include"Data.h"
#include"Term.h"

class DictionaryContainer: public Container {
private:
    QMap<QString, Term>* map;
public:
    DictionaryContainer();
    Term* getPtr(int) const override;
    void* getPtr() const override;
    int size() const override;
    void insert(const Data&) override;
    ~DictionaryContainer() override;
};

#endif // DICTIONARYCONTAINER_H
