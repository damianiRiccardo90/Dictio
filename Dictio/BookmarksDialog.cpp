#include "BookmarksDialog.h"

QIcon BookmarksDialog::selectIcon(Account::Type type) {
    if(type == Account::Admin)
        return QIcon(":/Risorse/Icons/admin.png");
    else if(type == Account::Operator)
        return QIcon(":/Risorse/Icons/operator.png");
    return QIcon(":/Risorse/Icons/guest.png");
}

void BookmarksDialog::populateTreeWidget() {
    tree->setColumnCount(1);
    tree->setHeaderLabel("Segnalibri");
    if(acc_man->getCurrentPointer()->getData(3).value<Account::Type>() == Account::Admin) {
        for(int i = 0; i < book_man->count(); i++) {
            QStringList words = book_man->getPointer(i)->getData(1).toStringList();
            QTreeWidgetItem* top = new QTreeWidgetItem(tree, QStringList(book_man->getPointer(i)->getData(0).toString()));
            top->setIcon(0, selectIcon(book_man->getPointer(i)->getData(3).value<Account::Type>()));
            tree->addTopLevelItem(top);
            for(int j = 0; j < words.size(); j++) {
                tree->topLevelItem(i)->addChild(new QTreeWidgetItem(tree->topLevelItem(i), QStringList(words[j])));
            }
        }
    }
    else {
        QString current_username = acc_man->getCurrentPointer()->getData(0).toString();
        QStringList words = book_man->getPointer(book_man->find(current_username))->getData(1).toStringList();
        QTreeWidgetItem* top = new QTreeWidgetItem(tree, QStringList(current_username));
        top->setIcon(0, selectIcon(acc_man->getCurrentPointer()->getData(3).value<Account::Type>()));
        tree->addTopLevelItem(top);
        for(int i = 0; i < words.size(); i++) {
            tree->topLevelItem(0)->addChild(new QTreeWidgetItem(tree->topLevelItem(0), QStringList(words[i])));
        }
    }
}

void BookmarksDialog::setupUI() {
    v_layout->addWidget(tree);
    setLayout(v_layout);
    tree->setSortingEnabled(true);
    setWindowTitle("Bookmarks");
}

void BookmarksDialog::showEvent(QShowEvent *event) {
    if(!event->spontaneous()) { //Evento interno all'applicazione
        delete tree;
        tree = new QTreeWidget(this);
        connect(tree, &QTreeWidget::itemClicked, this, &BookmarksDialog::itemClicked);
        populateTreeWidget();
        setupUI();
        event->accept();
    }
    else event->accept(); //Evento proveniente dal sistema operativo (e.g. Maximize Window)
}

BookmarksDialog::BookmarksDialog(BookmarksManager *bm, AccountsManager *am, QWidget *parent):
    QDialog(parent),
    book_man(bm),
    acc_man(am),
    tree(new QTreeWidget(this)),
    v_layout(new QVBoxLayout(this))
{
    setupUI();
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Segnalibri");
}

void BookmarksDialog::itemClicked(QTreeWidgetItem *item, int column) {
    //Emetti il segnale solo se l'utente ha cliccato su una parola (e non un account)
    if(tree->indexOfTopLevelItem(item) == -1) {
        emit sendWordClicked(item->text(column));
        close();
    }
}
