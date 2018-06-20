#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include<QIcon>
#include<QDialog>
#include<QStringList>
#include<QString>
#include<QTreeWidgetItem>
#include<QShowEvent>
#include<QWidget>
#include<QVBoxLayout>
#include<QTreeWidget>

#include"AccountsManager.h"
#include"HistoryManager.h"
#include"Account.h"
#include"History.h"

class HistoryDialog: public QDialog {
private:
    HistoryManager* his_man;
    AccountsManager* acc_man;
    QTreeWidget* tree;
    QVBoxLayout* v_layout;

    QIcon selectWordIcon(History::Access acc);
    QIcon selectAccountIcon(Account::Type type);
    void readColumns(QStringList& strs, int i);
    void populateTreeWidget();
    void setupUI();
    void showEvent(QShowEvent* event) override;
public:
    HistoryDialog(HistoryManager* hm, AccountsManager* am, QWidget* parent);
};

#endif // HISTORYDIALOG_H
