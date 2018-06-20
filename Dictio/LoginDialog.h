#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include<QMenu>
#include<QIcon>
#include<QPushButton>
#include<QDialog>
#include<QLineEdit>
#include<QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QAction>
#include<QModelIndex>
#include<QVariant>

#include"AccountsTableModel.h"
#include"InfoLabel.h"

class LoginDialog: public QDialog {
    Q_OBJECT
private:
    AccountsTableModel* acc_mod;
    QVBoxLayout* v_layout;
    QHBoxLayout* h_layout1;
    QHBoxLayout* h_layout2;
    QHBoxLayout* h_layout3;
    QLabel* usr;
    QLabel* pwd;
    InfoLabel* info;
    QLineEdit* usr_edit;
    QLineEdit* pwd_edit;
    QPushButton* reg_button;
    QPushButton* login_button;
    QPushButton* exit_button;

    void setupUI();
    void clearAll();
public:
    LoginDialog(AccountsTableModel* am, QWidget* parent);
public slots:
    void regClicked(QAction* action);
    void loginClicked();
};

#endif // LOGINDIALOG_H
