#ifndef TERM_H
#define TERM_H

#include<QString>
#include<QVariant>
#include<QVariantList>
#include<QMetaType>

#include"Data.h"
#include"LexicalCategory.h"

class Term: public Data {
private:
    QString word;
    QVariantList var_list;
public:
    explicit Term(QString w = "", QVariantList vl = QVariantList());
    bool setData(int data_index, const QVariant& value);
    QVariant getData(int data_index) const;
    int getDataCount() const;
    int indexOf(QString category) const;
    void add(const LexicalCategory& lc);
    void remove(int index);
    void replace(int index, const LexicalCategory& lc);
    QVariant& operator[](int index);
};

#endif // TERM_H
