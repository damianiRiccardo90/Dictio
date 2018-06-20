#ifndef ACCOUNTSCONTAINER_H
#define ACCOUNTSCONTAINER_H

#include<QList>

#include"Container.h"
#include"Data.h"
#include"Account.h"

class AccountsContainer: public Container {
private:
    QList<Account>* list;
public:
    AccountsContainer();
    Account* getPtr(int) const override;
    void* getPtr() const override;
    int size() const override;
    void insert(const Data&) override;
    ~AccountsContainer() override;
};

#endif // ACCOUNTSCONTAINER_H
