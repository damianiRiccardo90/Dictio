#ifndef HISTORYCONTAINER_H
#define HISTORYCONTAINER_H

#include<QList>

#include"Container.h"
#include"History.h"

class HistoryContainer: public Container {
    QList<History>* list;
public:
    HistoryContainer();
    History* getPtr(int index) const override;
    void* getPtr() const override;
    int size() const override;
    void insert(const Data& data) override;
    ~HistoryContainer() override;
};

#endif // HISTORYCONTAINER_H
