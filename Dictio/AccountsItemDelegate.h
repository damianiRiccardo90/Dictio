#ifndef ACCOUNTSITEMDELEGATE_H
#define ACCOUNTSITEMDELEGATE_H

#include<QStyledItemDelegate>
#include<QObject>
#include<QWidget>
#include<QStyleOptionViewItem>
#include<QModelIndex>
#include<QComboBox>
#include<QAbstractItemModel>
#include<QVariant>
#include<QIcon>

#include"Account.h"

class AccountsItemDelegate: public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit AccountsItemDelegate(QObject* parent);
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

#endif // ACCOUNTSITEMDELEGATE_H
