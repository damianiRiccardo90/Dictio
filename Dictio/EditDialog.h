#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include<QDialog>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QSpinBox>
#include<QTextEdit>
#include<QSlider>
#include<QGroupBox>
#include<QPushButton>
#include<QStatusBar>

#include"DictionaryManager.h"
#include"Term.h"
#include"History.h"
#include"LexicalCategory.h"
#include"InfoLabel.h"

class EditDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode {Add, Mod};
    explicit EditDialog(DictionaryManager* dm, QWidget* parent):
        QDialog(parent),
        dic_man(dm),
        main_v_layout(new QVBoxLayout(this)),
        word_v_layout(new QVBoxLayout),
        cat_v_layout(new QVBoxLayout),
        def_v_layout(new QVBoxLayout),
        main_h_layout(new QHBoxLayout),
        cat_h_layout(new QHBoxLayout),
        def_h_layout(new QHBoxLayout),
        word_edit(new QLineEdit),
        cat_edit(new QLineEdit),
        cat_spin(new QSpinBox),
        cat_index(0),
        def_edit(new QTextEdit),
        def_spin(new QSpinBox),
        def_index(0),
        word_gbox(new QGroupBox("Parola")),
        cat_gbox(new QGroupBox("Categorie")),
        def_gbox(new QGroupBox("Definizioni")),
        cat_add_button(new QPushButton("Aggiungi")),
        cat_del_button(new QPushButton("Rimuovi")),
        def_add_button(new QPushButton("Aggiungi")),
        def_del_button(new QPushButton("Rimuovi")),
        accept_button(new QPushButton("Ok")),
        reject_button(new QPushButton("Cancella")),
        info(new InfoLabel)
    {
        setupUI();
        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
        setWindowTitle("Modifica");
    }
    void setCurrentWord(Term word) {
        old_word = word.getData(0).toString();
        current_word = word;
        word_edit->setText(current_word.getData(0).toString());
        cat_edit->setText(current_word[0].value<LexicalCategory>().getData(0).toString());
        def_edit->setDocument(new QTextDocument(current_word[0].value<LexicalCategory>()[0], def_edit));
        def_edit->document()->setModified(false);
        cat_spin->setRange(0, current_word.getData(1).toList().size()-1);
        def_spin->setRange(0, current_word[0].value<LexicalCategory>().getData(1).toStringList().size()-1);
    }
    void setMode(Mode m) {md = m;}
private:
    DictionaryManager* dic_man;
    QString old_word;
    Term current_word;
    Mode md;
    QVBoxLayout* main_v_layout;
    QVBoxLayout* word_v_layout;
    QVBoxLayout* cat_v_layout;
    QVBoxLayout* def_v_layout;
    QHBoxLayout* main_h_layout;
    QHBoxLayout* cat_h_layout;
    QHBoxLayout* def_h_layout;
    QLineEdit* word_edit;
    QLineEdit* cat_edit;
    QSpinBox* cat_spin;
    int cat_index;
    QTextEdit* def_edit;
    QSpinBox* def_spin;
    int def_index;
    QGroupBox* word_gbox;
    QGroupBox* cat_gbox;
    QGroupBox* def_gbox;
    QPushButton* cat_add_button;
    QPushButton* cat_del_button;
    QPushButton* def_add_button;
    QPushButton* def_del_button;
    QPushButton* accept_button;
    QPushButton* reject_button;
    InfoLabel* info;

    void setupUI() {
        word_v_layout->addWidget(word_edit);
        word_gbox->setLayout(word_v_layout);
        main_v_layout->addWidget(word_gbox);
        cat_v_layout->addWidget(cat_edit);
        cat_h_layout->addWidget(cat_add_button);
        cat_h_layout->addWidget(cat_del_button);
        cat_h_layout->addWidget(cat_spin);
        cat_v_layout->addLayout(cat_h_layout);
        cat_gbox->setLayout(cat_v_layout);
        main_v_layout->addWidget(cat_gbox);
        def_v_layout->addWidget(def_edit);
        def_h_layout->addWidget(def_add_button);
        def_h_layout->addWidget(def_del_button);
        def_h_layout->addWidget(def_spin);
        def_v_layout->addLayout(def_h_layout);
        def_gbox->setLayout(def_v_layout);
        main_v_layout->addWidget(def_gbox);
        main_v_layout->addWidget(info);
        main_h_layout->addWidget(accept_button);
        main_h_layout->addWidget(reject_button);
        main_v_layout->addLayout(main_h_layout);
        setLayout(main_v_layout);
        connect(cat_spin, SIGNAL(valueChanged(int)), this, SLOT(swapCat(int)));
        connect(def_spin, SIGNAL(valueChanged(int)), this, SLOT(swapDef(int)));
        connect(cat_add_button, &QPushButton::clicked, this, &EditDialog::addCatClicked);
        connect(cat_del_button, &QPushButton::clicked, this, &EditDialog::delCatClicked);
        connect(def_add_button, &QPushButton::clicked, this, &EditDialog::addDefClicked);
        connect(def_del_button, &QPushButton::clicked, this, &EditDialog::delDefClicked);
        connect(accept_button, &QPushButton::clicked, this, &EditDialog::acceptClicked);
        connect(reject_button, &QPushButton::clicked, this, &EditDialog::rejectClicked);
    }
    void clearAll() {
        word_edit->clear();
        cat_edit->clear();
        def_edit->clear();
        cat_index = def_index = 0;
    }
    void transferToDictionary() {
        if(word_edit->isModified()) current_word.setData(0, QVariant::fromValue(word_edit->text().left(1).toUpper() + word_edit->text().mid(1)));
        if(cat_edit->isModified()) current_word.replace(cat_index, current_word[cat_index].value<LexicalCategory>().changeCat(cat_edit->text()));
        if(def_edit->document()->isModified())
            current_word.replace(cat_index, current_word[cat_index].value<LexicalCategory>().replace(def_index, def_edit->toPlainText()));
        if(md == Add) {
            dic_man->insert(current_word);
            dictionaryUpdate(word_edit->text(), History::Add);
        }
        else if(md == Mod) {
            dic_man->remove(old_word);
            dic_man->insert(current_word);
            dictionaryUpdate(word_edit->text(), History::Modify);
        }
    }
private slots:
    void swapCat(int i) {
        if(cat_edit->isModified()) current_word.replace(cat_index, current_word[cat_index].value<LexicalCategory>().changeCat(cat_edit->text()));
        cat_index = i;
        def_index = 0;
        def_spin->setValue(0);
        swapDef(0);
        def_spin->setRange(0, current_word[cat_index].value<LexicalCategory>().getData(1).toStringList().size()-1);
        cat_edit->setText(current_word[cat_index].value<LexicalCategory>().getData(0).toString());
    }
    void swapDef(int i) {
        if(def_edit->document()->isModified())
            current_word.replace(cat_index, current_word[cat_index].value<LexicalCategory>().replace(def_index, def_edit->toPlainText()));
        def_index = i;
        def_edit->setText(current_word[cat_index].value<LexicalCategory>().getData(1).toStringList().at(def_index));
    }
    void addCatClicked() {
        current_word.add(LexicalCategory("", QStringList(QString())));
        cat_spin->setMaximum(cat_spin->maximum() + 1);
        cat_spin->setValue(cat_spin->maximum());
        info->setText("Aggiunta categoria vuota", 5000);
    }
    void addDefClicked() {
        current_word.replace(cat_index, current_word[cat_index].value<LexicalCategory>().add(QString()));
        def_spin->setMaximum(def_spin->maximum() + 1);
        def_spin->setValue(def_spin->maximum());
        info->setText("Aggiunta definizione vuota", 5000);
    }
    void delCatClicked() {
        if(cat_index < current_word.getData(1).toList().size() && current_word.getData(1).toList().size() != 1) {
            if(cat_spin->value() != 0) cat_spin->setValue(cat_spin->value() - 1);
            else cat_spin->setValue(cat_spin->value() + 1);
            current_word.remove(cat_index);
            cat_index = cat_spin->value();
            info->setText("Categoria rimossa", 5000);
        }
        info->setText("Impossibile Rimuovere", 5000);
    }
    void delDefClicked() {
        if(def_index < current_word[cat_index].value<LexicalCategory>().getData(1).toStringList().size() && current_word[cat_index].value<LexicalCategory>().getData(1).toStringList().size() != 1) {
            if(def_spin->value() != 0) def_spin->setValue(def_spin->value() - 1);
            else def_spin->setValue(def_spin->value() + 1);
            current_word.replace(cat_index, current_word[cat_index].value<LexicalCategory>().remove(def_index));
            def_index = def_spin->value();
            info->setText("Definizione rimossa", 5000);
        }
        info->setText("Impossibile Rimuovere", 5000);
    }
    void acceptClicked() {
        if(word_edit->text() == QString()) {
            info->setText("Campo parola vuoto");
            return;
        }
        if((md == Add && dic_man->find(word_edit->text()) != -1) || (md == Mod && old_word != word_edit->text() && dic_man->find(word_edit->text()) != -1)) {
            info->setText("Parola: \"" + word_edit->text() + "\" già presente");
            return;
        }
        transferToDictionary();
        if(md == Add)
            sendToStatusBar("Parola: \"" + word_edit->text() + "\" aggiunta con successo");
        else
            sendToStatusBar("Parola: \"" + word_edit->text() + "\" modificata con successo");
        clearAll();
        accept();
    }
    void rejectClicked() {
        clearAll();
        sendToStatusBar("Modifiche non salvate");
        reject();
    }
signals:
    void dictionaryUpdate(const QString& word, History::Access acc);
    void sendToStatusBar(const QString& message, int timeout = 5000);
};

#endif // EDITDIALOG_H
