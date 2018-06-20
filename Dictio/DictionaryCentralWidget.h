#ifndef DICTIONARYCENTRALWIDGET_H
#define DICTIONARYCENTRALWIDGET_H

#include<QLineEdit>
#include<QString>
#include<QXmlStreamWriter>
#include<QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QTextEdit>
#include<QTextDocument>
#include<QVariantList>

#include"DictionaryManager.h"
#include"EditDialog.h"
#include"History.h"
#include"LexicalCategory.h"

class DictionaryCentralWidget: public QWidget {
    Q_OBJECT
private:
    DictionaryManager* dic_man;
    Term* current_word;
    QVBoxLayout* v_layout;
    QHBoxLayout* h_layout;
    QLabel* search_label;
    QLineEdit* search_edit;
    QTextEdit* word_edit;
    QTextDocument* doc;
    EditDialog* edit_dialog;

    void setupUI();
    QString toHTML();
    void setImage();
public:
    DictionaryCentralWidget(DictionaryManager* dm, QWidget* parent);
    Term* getCurrentWord();
signals:
    void sendToStatusBar(const QString& message, int timeout = 5000);
    void dictionaryUpdate(const QString& word, History::Access acc);
public slots:
    void addWord();
    void removeWord();
    void searchWord();
    void showSearchWord();
    void hideSearchWord();
    void swapWord(const QString& word);
    void modifyWord();
    void setDefault();
};

#endif // DICTIONARYCENTRALWIDGET_H
