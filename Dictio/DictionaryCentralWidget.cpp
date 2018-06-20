#include "DictionaryCentralWidget.h"

void DictionaryCentralWidget::setupUI() {
    h_layout->addWidget(search_label);
    h_layout->addWidget(search_edit);
    v_layout->addLayout(h_layout);
    v_layout->addWidget(word_edit);
    setLayout(v_layout);
    word_edit->setReadOnly(true);
    word_edit->setDocument(doc);
    setMinimumSize(470, 232);
    setImage();
    connect(search_edit, &QLineEdit::returnPressed, this, &DictionaryCentralWidget::searchWord);
    connect(edit_dialog, &EditDialog::sendToStatusBar, this, &DictionaryCentralWidget::sendToStatusBar);
    connect(edit_dialog, &EditDialog::dictionaryUpdate, this, &DictionaryCentralWidget::dictionaryUpdate);
}

QString DictionaryCentralWidget::toHTML() {
    QString output;
    QXmlStreamWriter wrt(&output);
    wrt.writeStartElement("html");
    wrt.writeStartElement("body");
    wrt.writeTextElement("h1", current_word->getData(0).toString());
    QVariantList vl = current_word->getData(1).toList();
    for(int i = 0; i < vl.size(); i++) {
        LexicalCategory lc = vl[i].value<LexicalCategory>();
        wrt.writeStartElement("i");
        wrt.writeTextElement("p", lc.getData(0).toString());
        wrt.writeEndElement();
        QStringList sl = lc.getData(1).toStringList();
        for(int j = 0; j < sl.size(); j++) {
            wrt.writeTextElement("p", QString::number(j+1) + ") " + sl[j]);
        }
    }
    wrt.writeEndElement();
    wrt.writeEndElement();
    return output;
}

void DictionaryCentralWidget::setImage() {
    word_edit->setStyleSheet("background-image: url(:/Risorse/Icons/background.png); background-repeat;");
}

DictionaryCentralWidget::DictionaryCentralWidget(DictionaryManager *dm, QWidget *parent):
    QWidget(parent),
    dic_man(dm),
    current_word(0),
    v_layout(new QVBoxLayout(this)),
    h_layout(new QHBoxLayout),
    search_label(new QLabel("Cerca Parola: ")),
    search_edit(new QLineEdit),
    word_edit(new QTextEdit),
    doc(new QTextDocument(word_edit)),
    edit_dialog(new EditDialog(dm, this))
{
    setupUI();
}

Term *DictionaryCentralWidget::getCurrentWord() {return current_word;}

void DictionaryCentralWidget::addWord() {
    QVariantList tmp1;
    QStringList tmp2;
    tmp2 << QString();
    tmp1 << QVariant::fromValue(LexicalCategory("", tmp2));
    edit_dialog->setCurrentWord(Term("", tmp1));
    edit_dialog->setMode(EditDialog::Add);
    edit_dialog->open();
}

void DictionaryCentralWidget::removeWord() {
    if(current_word) {
        QString rm = current_word->getData(0).toString();
        dic_man->remove(rm);
        setDefault();
        emit dictionaryUpdate(rm, History::Remove);
        emit sendToStatusBar("Parola: \"" + rm + "\" Rimossa Con Successo");
    }
    else emit sendToStatusBar("Parola Non Presente");
}

void DictionaryCentralWidget::searchWord() {
    if(current_word && current_word->getData(0).toString() == search_edit->text())
        return;
    if(!search_edit->text().isEmpty() && !search_edit->text().at(0).isUpper())
        search_edit->setText(search_edit->text().left(1).toUpper() + search_edit->text().mid(1));
    int index = dic_man->find(search_edit->text());
    if(index == -1) {
        emit sendToStatusBar("Parola Non Trovata");
    }
    else {
        current_word = dic_man->getPointer(index);
        doc->setHtml(toHTML());
        emit dictionaryUpdate(current_word->getData(0).toString(), History::Open);
    }
}

void DictionaryCentralWidget::showSearchWord() {
    search_label->show();
    search_edit->show();
}

void DictionaryCentralWidget::hideSearchWord() {
    search_label->hide();
    search_edit->hide();
}

void DictionaryCentralWidget::swapWord(const QString &word) {
    current_word = dic_man->getPointer(dic_man->find(word));
    doc->setHtml(toHTML());
    emit dictionaryUpdate(current_word->getData(0).toString(), History::Open);
}

void DictionaryCentralWidget::modifyWord() {
    if(!current_word) emit sendToStatusBar("Nessuna Parola Selezionata");
    else {
        edit_dialog->setCurrentWord(*current_word);
        edit_dialog->setMode(EditDialog::Mod);
        edit_dialog->open();
        setDefault();
    }
}

void DictionaryCentralWidget::setDefault() {
    doc->clear();
    search_edit->clear();
    current_word = 0;
    setImage();
}
