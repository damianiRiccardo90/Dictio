#include "AccountsContainer.h"

AccountsContainer::AccountsContainer(): list(new QList<Account>) {}

Account* AccountsContainer::getPtr(int index) const {
    int i = 0;
    for(QList<Account>::iterator it = list->begin(); it != list->end(); it++, i++) {
        if(index == i) return it.operator->();
    }
    return 0;
}

void* AccountsContainer::getPtr() const {return static_cast<void*>(list);}

int AccountsContainer::size() const {return list->size();}

void AccountsContainer::insert(const Data& data) {
    const Account* tmp = dynamic_cast<const Account*>(&data);
    if(tmp) list->push_back(static_cast<const Account&>(data));
}

AccountsContainer::~AccountsContainer() {delete list;}
