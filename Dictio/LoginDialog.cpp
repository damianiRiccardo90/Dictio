#include"LoginDialog.h"

void LoginDialog::setupUI() {
    v_layout->addLayout(h_layout1);
    h_layout1->addWidget(usr, Qt::AlignCenter);
    h_layout1->addWidget(usr_edit, Qt::AlignCenter);
    v_layout->addLayout(h_layout2);
    h_layout2->addWidget(pwd, Qt::AlignCenter);
    h_layout2->addWidget(pwd_edit, Qt::AlignCenter);
    v_layout->addWidget(info, Qt::AlignCenter);
    reg_button->setMenu(new QMenu(this));
    reg_button->menu()->addAction(QIcon(":/Risorse/Icons/guest.png"), "Guest");
    reg_button->menu()->addAction(QIcon(":/Risorse/Icons/operator.png"), "Operator");
    connect(reg_button->menu(), &QMenu::triggered, this, &LoginDialog::regClicked);
    h_layout3->addWidget(reg_button, Qt::AlignCenter);
    connect(login_button, &QPushButton::clicked, this, &LoginDialog::loginClicked);
    h_layout3->addWidget(login_button, Qt::AlignCenter);
    connect(exit_button, &QPushButton::clicked, this, &QDialog::reject);
    h_layout3->addWidget(exit_button, Qt::AlignCenter);
    v_layout->addLayout(h_layout3);
    setLayout(v_layout);
    pwd_edit->setEchoMode(QLineEdit::Password);
}

void LoginDialog::clearAll() {
    usr_edit->clear();
    pwd_edit->clear();
}

LoginDialog::LoginDialog(AccountsTableModel* am, QWidget* parent):
    QDialog(parent),
    acc_mod(am),
    v_layout(new QVBoxLayout(this)),
    h_layout1(new QHBoxLayout),
    h_layout2(new QHBoxLayout),
    h_layout3(new QHBoxLayout),
    usr(new QLabel("Nome Utente: ")),
    pwd(new QLabel("Password: ")),
    info(new InfoLabel),
    usr_edit(new QLineEdit),
    pwd_edit(new QLineEdit),
    reg_button(new QPushButton("Registrati")),
    login_button(new QPushButton("Accedi")),
    exit_button(new QPushButton("Esci"))
{
    setupUI();
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //Toglie il flag usando le operazioni bitwise (AND e NOT)
    setWindowTitle("Login");
}

void LoginDialog::regClicked(QAction* action) {
    if(usr_edit->text().isEmpty())
        info->setText("Campo nome utente vuoto");
    else if(pwd_edit->text().isEmpty())
        info->setText("Campo password vuoto");
    else if(usr_edit->text().contains(" ") || pwd_edit->text().contains(" "))
        info->setText("Il carattere \"spazio\" non è ammesso");
    else if(acc_mod->find(usr_edit->text()) != -1)
        info->setText("Utente già registrato");
    else {
        if(action->text() == "Guest") {
            acc_mod->appendRow(Account(usr_edit->text(), pwd_edit->text(), true, Account::Guest));
        }
        else if(action->text() == "Operator") {
            acc_mod->appendRow(Account(usr_edit->text(), pwd_edit->text(), true, Account::Operator));
        }
        clearAll();
        accept();
    }
}

void LoginDialog::loginClicked() {
    int index = acc_mod->find(usr_edit->text());
    if(index != -1) {
        QModelIndex pwd_index = acc_mod->index(index, 1);
        QModelIndex current_user_index = acc_mod->index(index, 2);
        if(acc_mod->data(pwd_index).toString() == pwd_edit->text()) {
            acc_mod->setData(current_user_index, QVariant(true));
            clearAll();
            accept();
        }
        else info->setText("Password Errata");
    }
    else info->setText("Utente non registrato");
}
