#ifndef HISTORY_H
#define HISTORY_H

#include<QString>
#include<QDate>
#include<QTime>
#include<QVariant>
#include<QMetaType>

#include"Data.h"

class History: public Data {
public:
    enum AccessType {Read, Write};
    enum Access {Add, Modify, Remove, Open};
    explicit History(QString usr = "", QString w = "", AccessType at = Read,
                     Access ac = Open, QDate d = QDate::currentDate(),
                     QTime t = QTime::currentTime());
    bool setData(int data_index, const QVariant& value) override;
    QVariant getData(int data_index) const override;
    int getDataCount() const override;
private:
    QString username;
    QString word;
    QDate date;
    QTime time;
    AccessType act;
    Access acc;
};

Q_DECLARE_METATYPE(History::AccessType)
Q_DECLARE_METATYPE(History::Access)

#endif // HISTORY_H
