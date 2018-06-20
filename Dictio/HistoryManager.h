#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include<QList>
#include<QString>

#include"Manager.h"
#include"History.h"
#include"XMLHistoryParser.h"

class HistoryManager: public Manager {
private:
    QList<History>* list;
    bool modified;
public:
    HistoryManager();
    void insert(const Data& data) override;
    void remove(const QString& usr) override;
    int find(const QString& usr) const override;
    int count() const override;
    void setModified(bool mod) override;
    bool isModified() const override;
    History* getPointer(int index) const override;
};

#endif // HISTORYMANAGER_H
