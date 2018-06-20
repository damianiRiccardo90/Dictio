#include"AccountsTableModel.h"

AccountsTableModel::AccountsTableModel(AccountsManager* am, QObject* parent):
    QAbstractTableModel(parent),
    acc_man(am)
{
    connect(acc_man, &AccountsManager::refreshAttachedModel, this, &AccountsTableModel::refreshAttachedViews);
}

int AccountsTableModel::columnCount(const QModelIndex&) const {return 4;}

int AccountsTableModel::rowCount(const QModelIndex&) const {return acc_man->count();}

QVariant AccountsTableModel::data(const QModelIndex& index, int role) const {
    if(!index.isValid()) return QVariant();
    if(role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::DecorationRole) {
        if(role == Qt::DisplayRole && index.column() == 3) {
            Account::Type tmp = acc_man->getData(index.row(), index.column()).value<Account::Type>();
            if(tmp == Account::Guest) return QString("Guest");
            else if(tmp == Account::Operator) return QString("Operator");
            else if(tmp == Account::Admin) return QString("Admin");
        }
        if(role == Qt::DecorationRole && index.column() == 3) {
            Account::Type tmp = acc_man->getData(index.row(), index.column()).value<Account::Type>();
            if(tmp == Account::Guest) return QIcon(":/Risorse/Icons/guest.png");
            else if(tmp == Account::Operator) return QIcon(":/Risorse/Icons/operator.png");
            else if(tmp == Account::Admin) return QIcon(":/Risorse/Icons/admin.png");
        }
        else return acc_man->getData(index.row(), index.column());
    }
    return QVariant();
}

QVariant AccountsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            switch(section) {
            case(0): return QString("Nome Utente");
            case(1): return QString("Password");
            case(2): return QString("In Uso");
            case(3): return QString("Privilegi");
            }
        }
        else return QString("Account %1").arg(section);
    }
    return QVariant();
}

bool AccountsTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if(!index.isValid() || role != Qt::EditRole) return false;
    if(index.column() == 0 && acc_man->find(value.toString()) != -1) {
        emit sendToStatusBar("Nome utente già presente", 5000);
        return false;
    }
    bool all_right = acc_man->setData(index.row(), index.column(), value);
    if(all_right) emit dataChanged(index, index);
    return all_right;
}

Qt::ItemFlags AccountsTableModel::flags(const QModelIndex& index) const {
    if(!index.isValid() || index.row() == 0 || index.column() == 2) return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void AccountsTableModel::appendRow() {
    beginInsertRows(QModelIndex(), acc_man->count(), acc_man->count());
    QStringList strs = acc_man->find(QRegExp("void[0-9]+"));
    if(strs.isEmpty()) acc_man->insert(Account("void0"));
    else {
        int max = -1;
        for(int i = 0; i < strs.size(); i++) {
            QRegExp re("[0-9]+");
            re.indexIn(strs[i]);
            int j = re.capturedTexts().join("").toInt();
            if(j > max) max = j;
        }
        acc_man->insert(Account("void" + QString::number(max+1)));
    }
    endInsertRows();
}

void AccountsTableModel::appendRow(const Account &acc) {
    beginInsertRows(QModelIndex(), acc_man->count(), acc_man->count());
    acc_man->insert(acc);
    endInsertRows();
}

bool AccountsTableModel::removeRow(int row) {
    if(row < 1 || row >= acc_man->count()) return false;
    if(acc_man->isCurrentUser(row)) { //cercando di cancellare l'utente corrente
        emit sendToStatusBar("Impossibile rimuovere utente corrente", 5000);
        return false;
    }
    beginRemoveRows(QModelIndex(), row, row);
    acc_man->remove(row);
    endRemoveRows();
    return true;
}

int AccountsTableModel::find(const QString &username) const {
    return acc_man->find(username);
}

void AccountsTableModel::refreshAttachedViews() {layoutChanged();}
