#include "Term.h"

Term::Term(QString w, QVariantList vl):
    word(w),
    var_list(vl)
{}

bool Term::setData(int data_index, const QVariant &value) {
    if(data_index >= getDataCount()) return false;
    if(value.type() == QMetaType::QString) {
        word = value.toString();
        return true;
    }
    else if(value.type() == QMetaType::QVariantList) {
        var_list = value.toList();
        return true;
    }
    else return false;
}

QVariant Term::getData(int data_index) const {
    switch(data_index) {
    case 0: return QVariant(word);
    case 1: return QVariant(var_list);
    default: return QVariant();
    }
}

int Term::getDataCount() const {return 2;}

int Term::indexOf(QString category) const {
    for(int i = 0; i < var_list.size(); i++) {
        if(var_list[i].value<LexicalCategory>().getData(0).toString() == category)
            return i;
    }
    return -1;
}

void Term::add(const LexicalCategory &lc) {
    int category_index = indexOf(lc.getData(0).toString());
    if(category_index != -1) { //Categoria presente
        LexicalCategory tmp = var_list[category_index].value<LexicalCategory>();
        tmp.add(lc.getData(1).toStringList().at(0));
        var_list[category_index] = QVariant::fromValue(tmp);
    }
    else { //Categoria non presente
        var_list << QVariant::fromValue(lc);
    }
}

void Term::remove(int index) {var_list.removeAt(index);}

void Term::replace(int index, const LexicalCategory &lc) {
    if(index < var_list.size()) {
        var_list.replace(index, QVariant::fromValue(lc));
    }
}

QVariant &Term::operator[](int index) {return var_list[index];}
