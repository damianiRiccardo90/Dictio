#ifndef MANAGERDISPATCHER_H
#define MANAGERDISPATCHER_H

#include<QObject>
#include<QString>

#include"Manager.h"
#include"AccountsManager.h"
#include"DictionaryManager.h"
#include"BookmarksManager.h"
#include"HistoryManager.h"

class ManagerDispatcher: public QObject {
    Q_OBJECT
private:
    Manager* array[4];
public:
    explicit ManagerDispatcher(QObject* parent);
    bool readExternalResources();
    bool updateExternalResources();
    AccountsManager* getAccPtr() const;
    DictionaryManager* getDicPtr() const;
    BookmarksManager* getBookPtr() const;
    HistoryManager* getHisPtr() const;
    ~ManagerDispatcher();
signals:
    void refreshAccountsDock();
};

#endif // MANAGERDISPATCHER_H
