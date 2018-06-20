#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<QString>
#include<QVariant>
#include<QMetaType>

#include"Data.h"

class Account: public Data {
public:
    enum Type {Admin, Operator, Guest};
    explicit Account(QString usr = "void", QString pwd = "void", bool c_usr = false, Type t = Guest);
    bool setData(int data_index, const QVariant& value) override;
    QVariant getData(int data_index) const override;
    int getDataCount() const override;
private:
    QString username;
    QString password;
    bool current_user;
    Type type;
};

Q_DECLARE_METATYPE(Account::Type)

#endif // ACCOUNT_H
