#include"AccountsManager.h"

AccountsManager::AccountsManager(QObject* parent):
    QObject(parent),
    Manager(new XMLAccountsParser),
    list(static_cast<QList<Account>*>(getContainer()->getPtr())),
    modified(false)
{}

void AccountsManager::insert(const Data& data) {
    const Account* tmp = dynamic_cast<const Account*>(&data);
    if(tmp) {
        if(tmp->getData(2).toBool()) resetCurrentUser();
        list->append(static_cast<const Account&>(data));
    }
    setModified(true);
}

void AccountsManager::remove(const QString& usr) {
    int index = find(usr);
    if(index != -1) remove(find(usr));
    setModified(true);
}

void AccountsManager::remove(int index) {
    if(index < count()) list->removeAt(index);
    setModified(true);
}

int AccountsManager::find(const QString& usr) const {
    for(int i = 0; i < count(); i++) {
        if(usr == list->at(i).getData(0).toString()) return i;
    }
    return -1;
}

QStringList AccountsManager::find(QRegExp re) const {
    QString str;
    for(int i = 0; i < count(); i++) {
        str += list->at(i).getData(0).toString();
    }
    QStringList list;
    int i = 0;
    while((i = re.indexIn(str, i)) != -1) {
        list << re.cap(0);
        i += re.matchedLength();
    }
    return list;
}

int AccountsManager::count() const {return list->size();}

void AccountsManager::setModified(bool mod) {
    modified = mod;
}

bool AccountsManager::isModified() const {return modified;}

Account* AccountsManager::getPointer(int index) const {
    int i = 0;
    for(QList<Account>::iterator it = list->begin(); it != list->end(); it++, i++) {
        if(index == i) return it.operator->();
    }
    return 0;
}

Account *AccountsManager::getCurrentPointer() const {
    for(QList<Account>::iterator it = list->begin(); it != list->end(); it++) {
        if(it->getData(2).toBool()) return it.operator->();
    }
    return 0;
}

QVariant AccountsManager::getData(int account_index, int data_index) const {
    return list->at(account_index).getData(data_index);
}

bool AccountsManager::setData(int account_index, int data_index, const QVariant& value) {
    if(data_index != 2) setModified(true);
    else if(value.toBool()) resetCurrentUser();
    return (*list)[account_index].setData(data_index, value);
}

void AccountsManager::setCurrent(int index) {
    resetCurrentUser();
    setData(index, 2, true);
}

void AccountsManager::resetCurrentUser() {
    for(int i = 0; i < count(); i++) {
        setData(i, 2, false);
    }
}

bool AccountsManager::isCurrentUser(int index) const {
    return list->at(index).getData(2).toBool();
}
