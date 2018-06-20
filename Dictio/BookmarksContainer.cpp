#include "BookmarksContainer.h"

BookmarksContainer::BookmarksContainer(): list(new QList<Bookmarks>) {}

Bookmarks *BookmarksContainer::getPtr(int index) const {
    int i = 0;
    for(QList<Bookmarks>::iterator it = list->begin(); it != list->end(); it++, i++) {
        if(index == i) return it.operator->();
    }
    return 0;
}

void *BookmarksContainer::getPtr() const {return static_cast<void*>(list);}

int BookmarksContainer::size() const {return list->size();}

void BookmarksContainer::insert(const Data &data) {
    const Bookmarks* tmp = dynamic_cast<const Bookmarks*>(&data);
    if(tmp) list->push_back(static_cast<const Bookmarks&>(data));
}

BookmarksContainer::~BookmarksContainer() {delete list;}
