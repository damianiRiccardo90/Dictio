#ifndef ACCOUNTSDOCKWIDGET_H
#define ACCOUNTSDOCKWIDGET_H

#include<QDockWidget>
#include<QTableView>
#include<QWidget>
#include<QString>
#include<QStringList>
#include<QVector>
#include<QAbstractItemView>
#include<QModelIndexList>

#include"AccountsTableModel.h"
#include"AccountsManager.h"
#include"AccountsItemDelegate.h"

class AccountsDockWidget: public QDockWidget {
    Q_OBJECT
private:
    AccountsTableModel* model;
    QTableView* view;
    void setupUI();
public:
    AccountsDockWidget(AccountsManager* am, QWidget* parent);
    AccountsTableModel* getModel() const;
signals:
    void sendToStatusBar(const QString& message, int timeout = 0);
    void sendUsernames(const QStringList& usernames);
public slots:
    void addStandardUser();
    void removeUsers();
    void refresh();
};

#endif // ACCOUNTSDOCKWIDGET_H
