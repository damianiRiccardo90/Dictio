#include "Account.h"

Account::Account(QString usr, QString pwd, bool c_usr, Account::Type t):
    username(usr),
    password(pwd),
    current_user(c_usr),
    type(t)
{}

bool Account::setData(int data_index, const QVariant &value) {
    if(data_index >= getDataCount()) return false;
    else if(value.type() == QMetaType::QString) {
        if(data_index == 0) {
            username = value.toString();
            return true;
        }
        else if(data_index == 1) {
            password = value.toString();
            return true;
        }
    }
    else if(value.type() == QMetaType::Bool && data_index == 2) {
        current_user = value.toBool();
        return true;
    }
    else if(value.type() == QMetaType::User && data_index == 3) {
        type = value.value<Type>();
        return true;
    }
    else return false;
}

QVariant Account::getData(int data_index) const {
    switch(data_index) {
    case 0: return QVariant(username);
    case 1: return QVariant(password);
    case 2: return QVariant(current_user);
    case 3: return QVariant::fromValue<Type>(type);
    default: return QVariant();
    }
}

int Account::getDataCount() const {return 4;}
