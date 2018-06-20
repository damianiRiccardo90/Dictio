#ifndef LEXICALCATEGORY_H
#define LEXICALCATEGORY_H

#include<QString>
#include<QStringList>
#include<QVariant>
#include<QMetaType>

#include"Data.h"

class LexicalCategory: public Data {
private:
    QString category;
    QStringList semantics;
public:
    explicit LexicalCategory(QString cat = "", QStringList sem = QStringList());
    bool setData(int data_index, const QVariant& value);
    QVariant getData(int data_index) const;
    int getDataCount() const;
    LexicalCategory& add(QString semantic);
    LexicalCategory& remove(int index);
    LexicalCategory& changeCat(QString cat);
    LexicalCategory& replace(int index, QString sem);
    QString& operator[](int index);
};

Q_DECLARE_METATYPE(LexicalCategory)

#endif // LEXICALCATEGORY_H
