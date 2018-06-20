#ifndef BOOKMARKSMANAGER_H
#define BOOKMARKSMANAGER_H

#include<QList>
#include<QString>

#include"Manager.h"
#include"Bookmarks.h"
#include"Data.h"
#include"XMLBookmarksParser.h"

class BookmarksManager: public Manager {
private:
    QList<Bookmarks>* list;
    bool modified;
public:
    BookmarksManager();
    void insert(const Data& data) override;
    void remove(const QString& account) override;
    int find(const QString& account) const override;
    int count() const override;
    void setModified(bool mod) override;
    bool isModified() const override;
    Bookmarks* getPointer(int index) const override;
};

#endif // BOOKMARKSMANAGER_H
