#include "DictionaryContainer.h"

DictionaryContainer::DictionaryContainer(): map(new QMap<QString, Term>) {}

Term* DictionaryContainer::getPtr(int index) const {
    int i = 0;
    for(QMap<QString, Term>::iterator it = map->begin(); it != map->end(); it++, i++) {
        if(index == i) return it.operator->();
    }
    return 0;
}

void* DictionaryContainer::getPtr() const {return static_cast<void*>(map);}

int DictionaryContainer::size() const {return map->size();}

void DictionaryContainer::insert(const Data& data) {
    const Term* tmp = dynamic_cast<const Term*>(&data);
    if(tmp) map->insert(data.getData(0).toString(), static_cast<const Term&>(data));
}

DictionaryContainer::~DictionaryContainer() {delete map;}
