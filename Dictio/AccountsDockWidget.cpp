#include"AccountsDockWidget.h"

void AccountsDockWidget::setupUI() {
    view->setModel(model);
    view->setItemDelegateForColumn(3, new AccountsItemDelegate(this));
    setWidget(view);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    setMinimumSize(471, 164);
    connect(model, &AccountsTableModel::sendToStatusBar, this, &AccountsDockWidget::sendToStatusBar);
}

AccountsDockWidget::AccountsDockWidget(AccountsManager* am, QWidget* parent):
    QDockWidget("Gestione degli account", parent),
    model(new AccountsTableModel(am, this)),
    view(new QTableView(this))
{
    setupUI();
}

AccountsTableModel *AccountsDockWidget::getModel() const {return model;}

void AccountsDockWidget::addStandardUser() {
    model->appendRow();
    emit sendToStatusBar("Nuovo Account Aggiunto", 5000);
}

void AccountsDockWidget::removeUsers() {
    if(!view->selectionModel()->hasSelection()) emit sendToStatusBar("Nessun Utente Selezionato", 5000);
    else {
        QModelIndexList index_list = view->selectionModel()->selectedRows();
        QStringList usernames;
        QVector<int> index_array;
        for(int i = 0; i < index_list.size(); i++) {
            usernames << model->data(index_list[i]).toString();
            index_array.append(index_list[i].row());
        }
        emit sendUsernames(usernames);
        for(int i = 0; i < index_array.size(); i++) {
            if(model->removeRow(index_array[i])) {
                for(int j = i + 1; j < index_array.size(); j++) {
                    if(index_array[j] > index_array[i]) {
                        index_array[j]--;
                    }
                }
            }
            else return;
        }
        emit sendToStatusBar(QString::number(index_list.size()) + " Cancellati", 5000);
    }
}

void AccountsDockWidget::refresh() {model->refreshAttachedViews();}
