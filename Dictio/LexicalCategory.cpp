#include "LexicalCategory.h"

LexicalCategory::LexicalCategory(QString cat, QStringList sem):
    category(cat),
    semantics(sem)
{}

bool LexicalCategory::setData(int data_index, const QVariant &value) {
    if(data_index >= getDataCount()) return false;
    if(value.type() == QMetaType::QString) {
        category = value.toString();
        return true;
    }
    else if(value.type() == QMetaType::QStringList) {
        semantics = value.toStringList();
        return true;
    }
    else return false;
}

QVariant LexicalCategory::getData(int data_index) const {
    switch(data_index) {
    case 0: return QVariant(category);
    case 1: return QVariant(semantics);
    default: return QVariant();
    }
}

int LexicalCategory::getDataCount() const {return 2;}

LexicalCategory& LexicalCategory::add(QString semantic) {
    semantics << semantic;
    return *this;
}

LexicalCategory &LexicalCategory::remove(int index) {
    semantics.removeAt(index);
    return *this;
}

LexicalCategory &LexicalCategory::changeCat(QString cat) {
    category = cat;
    return *this;
}

LexicalCategory &LexicalCategory::replace(int index, QString sem) {
    if(index < semantics.size()) {
        semantics[index] = sem;
    }
    return *this;
}

QString &LexicalCategory::operator[](int index) {return semantics[index];}
