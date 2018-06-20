#include"DictionaryManager.h"

DictionaryManager::DictionaryManager():
    Manager(new XMLDictionaryParser),
    map(static_cast<QMap<QString, Term>*>(getContainer()->getPtr())),
    modified(false)
{}

void DictionaryManager::insert(const Data& data) {
    const Term* tmp = dynamic_cast<const Term*>(&data);
    if(tmp) map->insert(data.getData(0).toString(), static_cast<const Term&>(data));
    setModified(true);
}

void DictionaryManager::remove(const QString &word) {
    map->remove(word);
    setModified(true);
}

int DictionaryManager::find(const QString &word) const {
    QMap<QString, Term>::const_iterator iter = map->find(word);
    if(iter == map->end()) {
        return -1;
    }
    else {
        int i = 0;
        for(QMap<QString, Term>::const_iterator it = map->cbegin(); it != iter; it++, i++);
        return i;
    }
}

int DictionaryManager::count() const {return map->size();}

void DictionaryManager::setModified(bool mod) {modified = mod;}

bool DictionaryManager::isModified() const {return modified;}

Term *DictionaryManager::getPointer(int index) const {
    int i = 0;
    for(QMap<QString, Term>::iterator it = map->begin(); it != map->end(); it++, i++) {
        if(index == i) return it.operator->();
    }
    return 0;
}
