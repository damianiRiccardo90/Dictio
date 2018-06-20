#ifndef BOOKMARKSCONTAINER_H
#define BOOKMARKSCONTAINER_H

#include<QList>

#include"Container.h"
#include"Data.h"
#include"Bookmarks.h"

class BookmarksContainer: public Container {
    QList<Bookmarks>* list;
public:
    BookmarksContainer();
    Bookmarks* getPtr(int index) const override;
    void* getPtr() const override;
    int size() const override;
    void insert(const Data& data) override;
    ~BookmarksContainer() override;
};

#endif // BOOKMARKSCONTAINER_H
