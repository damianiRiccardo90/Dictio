#ifndef BOOKMARKS_H
#define BOOKMARKS_H

#include<QString>
#include<QStringList>
#include<QVariant>
#include<QMetaType>

#include"Data.h"

class Bookmarks: public Data {
private:
    QString username;
    QStringList words_list;
public:
    explicit Bookmarks(QString usr = "", QStringList ws = QStringList());
    bool setData(int data_index, const QVariant& value) override;
    void addWord(const QString& word);
    void removeWord(const QString& word);
    int findWord(const QString& word);
    QVariant getData(int data_index) const override;
    int getDataCount() const override;
};

#endif // BOOKMARKS_H
