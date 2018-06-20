#include "Bookmarks.h"

Bookmarks::Bookmarks(QString usr, QStringList ws):
    username(usr),
    words_list(ws)
{}

bool Bookmarks::setData(int data_index, const QVariant &value) {
    if(data_index >= getDataCount()) return false;
    else if(value.type() == QMetaType::QString && data_index == 0) {
        username = value.toString();
        return true;
    }
    else if(value.type() == QMetaType::QStringList && data_index == 1) {
        words_list = value.toStringList();
        return true;
    }
    else return false;
}

void Bookmarks::addWord(const QString &word) {words_list << word;}

void Bookmarks::removeWord(const QString &word) {
    int index = findWord(word);
    if(index != -1) words_list.removeAt(index);
}

int Bookmarks::findWord(const QString &word) {return words_list.indexOf(word);}

QVariant Bookmarks::getData(int data_index) const {
    if(data_index >= getDataCount()) return QVariant();
    else if(data_index == 0) return QVariant(username);
    else if(data_index == 1) return QVariant(words_list);
}

int Bookmarks::getDataCount() const {return 2;}
