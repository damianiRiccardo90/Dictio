#ifndef ACCOUNTSTABLEMODEL_H
#define ACCOUNTSTABLEMODEL_H

#include<QAbstractTableModel>
#include<QObject>
#include<QModelIndex>
#include<QVariant>
#include<QString>
#include<QModelIndex>
#include<QIcon>
#include<QRegExp>

#include"AccountsManager.h"
#include"Account.h"

class AccountsTableModel: public QAbstractTableModel {
    Q_OBJECT
private:
    AccountsManager* acc_man;
public:
    AccountsTableModel(AccountsManager* am, QObject* parent);
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    void appendRow();
    void appendRow(const Account& acc);
    bool removeRow(int row);
    int find(const QString& username) const;
public slots:
    void refreshAttachedViews();
signals:
    void sendToStatusBar(const QString& message, int timeout = 5000);
};

#endif // ACCOUNTSTABLEMODEL_H
