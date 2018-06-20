#include "BookmarksManager.h"

BookmarksManager::BookmarksManager():
    Manager(new XMLBookmarksParser),
    list(static_cast<QList<Bookmarks>*>(getContainer()->getPtr())),
    modified(false)
{}

void BookmarksManager::insert(const Data &data) {
    const Bookmarks* tmp = dynamic_cast<const Bookmarks*>(&data);
    if(tmp) list->append(static_cast<const Bookmarks&>(data));
    setModified(true);
}

void BookmarksManager::remove(const QString &account) {
    list->removeAt(find(account));
}

int BookmarksManager::find(const QString &account) const {
    for(int i = 0; i < count(); i++) {
        if(account == list->at(i).getData(0).toString()) return i;
    }
    return -1;
}

int BookmarksManager::count() const {return list->count();}

void BookmarksManager::setModified(bool mod) {modified = mod;}

bool BookmarksManager::isModified() const {return modified;}

Bookmarks *BookmarksManager::getPointer(int index) const {
    int i = 0;
    for(QList<Bookmarks>::iterator it = list->begin(); it != list->end(); it++, i++) {
        if(index == i) return it.operator->();
    }
    return 0;
}
