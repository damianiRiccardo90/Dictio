#ifndef BOOKMARKSDIALOG_H
#define BOOKMARKSDIALOG_H

#include<QDialog>
#include<QWidget>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include<QStringList>
#include<QString>
#include<QVBoxLayout>
#include<QShowEvent>

#include"BookmarksManager.h"
#include"AccountsManager.h"
#include"Account.h"

class BookmarksDialog: public QDialog {
    Q_OBJECT
private:
    BookmarksManager* book_man;
    AccountsManager* acc_man;
    QTreeWidget* tree;
    QVBoxLayout* v_layout;

    QIcon selectIcon(Account::Type type);
    void populateTreeWidget();
    void setupUI();
    void showEvent(QShowEvent* event) override;
public:
    BookmarksDialog(BookmarksManager* bm, AccountsManager* am, QWidget* parent);
public slots:
    void itemClicked(QTreeWidgetItem* item, int column);
signals:
    void sendWordClicked(const QString& word);
};

#endif // BOOKMARKSDIALOG_H
