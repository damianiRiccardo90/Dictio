#include "AccountsItemDelegate.h"

AccountsItemDelegate::AccountsItemDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{}

QWidget *AccountsItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if(index.column() != 3) return QStyledItemDelegate::createEditor(parent, option, index);
    QComboBox* editor = new QComboBox(parent);
    editor->addItem(QIcon(":/Risorse/Icons/guest.png"), "Guest");
    editor->addItem(QIcon(":/Risorse/Icons/operator.png"), "Operator");
    editor->addItem(QIcon(":/Risorse/Icons/admin.png"), "Admin");
    return editor;
}

void AccountsItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if(QComboBox* combox = qobject_cast<QComboBox*>(editor)) {
        QString tmp = index.data().toString();
        if(tmp == "Guest") combox->setCurrentIndex(0);
        else if(tmp == "Operator") combox->setCurrentIndex(1);
        else if(tmp == "Admin") combox->setCurrentIndex(2);
    }
    else QStyledItemDelegate::setEditorData(editor, index);
}

void AccountsItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    if(QComboBox* combox = qobject_cast<QComboBox*>(editor)) {
        switch(combox->currentIndex()) {
        case 0:
            model->setData(index, QVariant::fromValue<Account::Type>(Account::Guest));
            break;
        case 1:
            model->setData(index, QVariant::fromValue<Account::Type>(Account::Operator));
            break;
        case 2:
            model->setData(index, QVariant::fromValue<Account::Type>(Account::Admin));
            break;
        }
    }
    else QStyledItemDelegate::setModelData(editor, model, index);
}
