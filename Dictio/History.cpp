#include "History.h"

History::History(QString usr, QString w, History::AccessType at, History::Access ac, QDate d, QTime t):
    username(usr),
    word(w),
    date(d),
    time(t),
    act(at),
    acc(ac)
{}

bool History::setData(int data_index, const QVariant &value) {
    if(data_index >= getDataCount()) return false;
    else if(value.type() == QMetaType::QString) {
        if(data_index == 0) {
            username = value.toString();
            return true;
        }
        else if(data_index == 1) {
            word = value.toString();
            return true;
        }
    }
    else if(value.type() == QMetaType::QDate && data_index == 2) {
        date = value.toDate();
        return true;
    }
    else if(value.type() == QMetaType::QTime && data_index == 3) {
        time = value.toTime();
        return true;
    }
    else if(value.type() == QMetaType::User) {
        if(data_index == 4) {
            act = value.value<AccessType>();
            return true;
        }
        else if(data_index == 5) {
            acc = value.value<Access>();
            return true;
        }
    }
    return false;
}

QVariant History::getData(int data_index) const {
    switch(data_index) {
    case 0: return QVariant(username);
    case 1: return QVariant(word);
    case 2: return QVariant(date);
    case 3: return QVariant(time);
    case 4: return QVariant::fromValue<AccessType>(act);
    case 5: return QVariant::fromValue<Access>(acc);
    default: return QVariant();
    }
}

int History::getDataCount() const {return 6;}
