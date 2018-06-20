#ifndef DATA_H
#define DATA_H

#include<QObject>
#include<QVariant>

class Data {
public:
    virtual bool setData(int data_index, const QVariant& value) =0;
    virtual QVariant getData(int data_index) const =0;
    virtual int getDataCount() const =0;
    virtual ~Data() {}
};

#endif // DATA_H
