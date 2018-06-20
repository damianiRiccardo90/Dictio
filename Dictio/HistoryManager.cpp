#include "HistoryManager.h"

HistoryManager::HistoryManager():
    Manager(new XMLHistoryParser),
    list(static_cast<QList<History>*>(getContainer()->getPtr())),
    modified(false)
{}

void HistoryManager::insert(const Data &data) {
    const History* tmp = dynamic_cast<const History*>(&data);
    if(tmp) list->append(static_cast<const History&>(data));
    setModified(true);
}

void HistoryManager::remove(const QString &usr) {
    int index = find(usr);
    if(index != -1) setModified(true);
    while(index != -1) {
        list->removeAt(index);
        index = find(usr);
    }
}

int HistoryManager::find(const QString &usr) const {
    for(int i = 0; i < count(); i++) {
        if(usr == list->at(i).getData(0).toString()) return i;
    }
    return -1;
}

int HistoryManager::count() const {return list->size();}

void HistoryManager::setModified(bool mod) {modified = mod;}

bool HistoryManager::isModified() const {return modified;}

History *HistoryManager::getPointer(int index) const {
    int i = 0;
    for(QList<History>::iterator it = list->begin(); it != list->end(); it++, i++) {
        if(index == i) return it.operator->();
    }
    return 0;
}
