#ifndef ACCOUNTSMANAGER_H
#define ACCOUNTSMANAGER_H

#include<QList>
#include<QString>
#include<QVariant>
#include<QObject>
#include<QStringList>
#include<QRegExp>

#include"Manager.h"
#include"XMLAccountsParser.h"
#include"Account.h"
#include"Data.h"

class AccountsManager: public QObject, public Manager {
    Q_OBJECT
private:
    QList<Account>* list;
    bool modified;
public:
    AccountsManager(QObject* parent = 0);
    void insert(const Data& data) override;
    void remove(const QString& usr) override;
    void remove(int index);
    int find(const QString& usr) const override;
    QStringList find(QRegExp re) const;
    int count() const override;
    void setModified(bool mod) override;
    bool isModified() const override;
    Account* getPointer(int index) const override;
    Account* getCurrentPointer() const;
    QVariant getData(int account_index, int data_index) const;
    bool setData(int account_index, int data_index, const QVariant& value);
    void setCurrent(int index);
    void resetCurrentUser();
    bool isCurrentUser(int index) const;
signals:
    void refreshAttachedModel();
};

#endif // ACCOUNTSMANAGER_H
