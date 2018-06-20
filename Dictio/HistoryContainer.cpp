#include "HistoryContainer.h"

HistoryContainer::HistoryContainer(): list(new QList<History>) {}

History *HistoryContainer::getPtr(int index) const {
    int i = 0;
    for(QList<History>::iterator it = list->begin(); it != list->end(); it++, i++) {
        if(index == i) return it.operator->();
    }
    return 0;
}

void *HistoryContainer::getPtr() const {return static_cast<void*>(list);}

int HistoryContainer::size() const {return list->size();}

void HistoryContainer::insert(const Data &data) {
    const History* tmp = dynamic_cast<const History*>(&data);
    if(tmp) list->push_back(static_cast<const History&>(data));
}

HistoryContainer::~HistoryContainer() {delete list;}
