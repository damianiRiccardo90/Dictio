#ifndef DICTIONARYMANAGER_H
#define DICTIONARYMANAGER_H

#include<QMap>
#include<QString>

#include"Manager.h"
#include"Term.h"
#include"XMLDictionaryParser.h"

class DictionaryManager: public Manager {
private:
    QMap<QString, Term>* map;
    bool modified;
public:
    DictionaryManager();
    void insert(const Data& data) override;
    void remove(const QString& word) override;
    int find(const QString& word) const override;
    int count() const override;
    void setModified(bool mod) override;
    bool isModified() const override;
    Term* getPointer(int index) const override;
};

#endif // DICTIONARYMANAGER_H

