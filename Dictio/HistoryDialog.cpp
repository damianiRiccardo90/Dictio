#include "HistoryDialog.h"

QIcon HistoryDialog::selectWordIcon(History::Access acc) {
    if(acc == History::Add)
        return QIcon(":/Risorse/Icons/addWord.png");
    else if(acc == History::Remove)
        return QIcon(":/Risorse/Icons/removeWord.png");
    else if(acc == History::Modify)
        return QIcon(":/Risorse/Icons/modifyWord.png");
    return QIcon(":/Risorse/Icons/searchWord.png");
}

QIcon HistoryDialog::selectAccountIcon(Account::Type type) {
    if(type == Account::Admin)
        return QIcon(":/Risorse/Icons/admin.png");
    else if(type == Account::Operator)
        return QIcon(":/Risorse/Icons/operator.png");
    return QIcon(":/Risorse/Icons/guest.png");
}

void HistoryDialog::readColumns(QStringList &strs, int i) {
    strs << his_man->getPointer(i)->getData(1).toString();
    strs << his_man->getPointer(i)->getData(2).toDate().toString("dd/MM/yy");
    strs << his_man->getPointer(i)->getData(3).toTime().toString("H:m");
    History::AccessType at = his_man->getPointer(i)->getData(4).value<History::AccessType>();
    if(at == History::Read) strs << "Lettura";
    else if(at == History::Write) strs << "Scrittura";
    History::Access ac = his_man->getPointer(i)->getData(5).value<History::Access>();
    if(ac == History::Add) strs << "Inserimento";
    else if(ac == History::Modify) strs << "Modifica";
    else if(ac == History::Remove) strs << "Rimozione";
    else if(ac == History::Open) strs << "Apertura";
}

void HistoryDialog::populateTreeWidget() {
    tree->setColumnCount(5);
    QStringList headers;
    headers << "Parola" << "Data" << "Ora" << "Tipo" << "Accesso";
    tree->setHeaderLabels(headers);
    if(acc_man->getCurrentPointer()->getData(3).value<Account::Type>() == Account::Admin) {
        for(int i = 0; i < his_man->count(); i++) {
            QString username = his_man->getPointer(i)->getData(0).toString();
            Account::Type type = acc_man->getPointer(acc_man->find(username))->getData(3).value<Account::Type>();
            History::Access acc = his_man->getPointer(i)->getData(5).value<History::Access>();
            QStringList strs;
            readColumns(strs, i);
            int index = -1;
            for(int j = 0; j < tree->topLevelItemCount(); j++) {
                if(username == tree->topLevelItem(j)->text(0)) index = j;
            }
            if(index != -1) {//Ho trovato l'account nell'albero
                QTreeWidgetItem* child = new QTreeWidgetItem(tree->topLevelItem(index), strs);
                child->setIcon(0, selectWordIcon(acc));
                tree->topLevelItem(index)->addChild(child);
            }
            else {//Non ho trovato l'account, creo un nuovo nodo topLevel
                int top_index = tree->topLevelItemCount();
                QTreeWidgetItem* top = new QTreeWidgetItem(tree, QStringList(username));
                top->setIcon(0, selectAccountIcon(type));
                tree->addTopLevelItem(top);
                QTreeWidgetItem* child = new QTreeWidgetItem(tree->topLevelItem(top_index), strs);
                child->setIcon(0, selectWordIcon(acc));
                tree->topLevelItem(top_index)->addChild(child);
            }
        }
    }
    else {
        QString current_username = acc_man->getCurrentPointer()->getData(0).toString();
        for(int i = 0; i < his_man->count(); i++) {
            QString username = his_man->getPointer(i)->getData(0).toString();
            if(username == current_username) {
                QStringList strs;
                readColumns(strs, i);
                int index = -1;
                for(int j = 0; j < tree->topLevelItemCount(); j++) {
                    if(username == tree->topLevelItem(j)->text(0)) index = j;
                }
                if(index != -1) {//Ho trovato l'account nell'albero
                    tree->topLevelItem(index)->addChild(new QTreeWidgetItem(tree->topLevelItem(index), strs));
                }
                else {//Non ho trovato l'account, creo un nuovo nodo topLevel
                    int top_index = tree->topLevelItemCount();
                    tree->addTopLevelItem(new QTreeWidgetItem(tree, QStringList(username)));
                    tree->topLevelItem(top_index)->addChild(new QTreeWidgetItem(tree->topLevelItem(top_index), strs));
                }
            }
        }
    }
}

void HistoryDialog::setupUI() {
    v_layout->addWidget(tree);
    setLayout(v_layout);
    tree->setSortingEnabled(true);
    setWindowTitle("History");
}

void HistoryDialog::showEvent(QShowEvent *event) {
    if(!event->spontaneous()) { //Evento interno all'applicazione
        delete tree;
        tree = new QTreeWidget(this);
        populateTreeWidget();
        setupUI();
        event->accept();
    }
    else event->accept(); //Evento proveniente dal sistema operativo (e.g. Maximize Window)
}

HistoryDialog::HistoryDialog(HistoryManager *hm, AccountsManager *am, QWidget *parent):
    QDialog(parent),
    his_man(hm),
    acc_man(am),
    tree(new QTreeWidget(this)),
    v_layout(new QVBoxLayout(this))
{
    setupUI();
    setMinimumSize(515, 214);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("History");
}
