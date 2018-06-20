#include "ManagerDispatcher.h"

ManagerDispatcher::ManagerDispatcher(QObject *parent):
    QObject(parent)
{
    array[0] = new AccountsManager;
    array[1] = new DictionaryManager;
    array[2] = new BookmarksManager;
    array[3] = new HistoryManager;
}

bool ManagerDispatcher::readExternalResources() {
    bool ok = true;
    for(int i = 0; i < 4; i++) {
        ok = array[i]->parseXML();
        if(i == 0) emit refreshAccountsDock();
        //La view degli account è creata a compile-time, ma viene popolata a run-time
        //quindi bisogna fare un refresh
    }
    return ok;
}

bool ManagerDispatcher::updateExternalResources() {
    bool ok = true;
    for(int i = 0; i < 4; i++) {
        if(i == 2 && array[0]->isModified()) { //Toglie i bookmark dagli account cancellati
            for(int j = 0; j < array[2]->count(); j++) {
                QString book_name = array[2]->getPointer(j)->getData(0).toString();
                if(array[0]->find(book_name) == -1) array[2]->remove(book_name);
            }
        }
        ok = array[i]->isModified() && array[i]->writeXML();
    }
    return ok;
}

AccountsManager *ManagerDispatcher::getAccPtr() const {return static_cast<AccountsManager*>(array[0]);}

DictionaryManager *ManagerDispatcher::getDicPtr() const {return static_cast<DictionaryManager*>(array[1]);}

BookmarksManager *ManagerDispatcher::getBookPtr() const {return static_cast<BookmarksManager*>(array[2]);}

HistoryManager *ManagerDispatcher::getHisPtr() const {return static_cast<HistoryManager*>(array[3]);}

ManagerDispatcher::~ManagerDispatcher() {for(int i = 0; i < 4; i++) delete array[i];}
