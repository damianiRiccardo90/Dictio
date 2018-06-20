#include"MainWindow.h"

void MainWindow::createActions() {
    list->append(new QAction(QIcon(":/Risorse/Icons/addUser.png"), "Aggiungi Utente", this)); //[0] addUserAct
    list->append(new QAction(QIcon(":/Risorse/Icons/removeUser.png"), "Rimuovi Utente", this)); //[1] removeUserAct
    list->append(new QAction(QIcon(":/Risorse/Icons/changeUser.png"), "Cambia Utente", this)); //[2] changeUserAct
    list->append(new QAction(QIcon(":/Risorse/Icons/searchWord.png"), "Cerca Parola", this)); //[3] searchWordAct
    list->append(new QAction(QIcon(":/Risorse/Icons/addWord.png"), "Aggiungi Parola", this)); //[4] addWordAct
    list->append(new QAction(QIcon(":/Risorse/Icons/modifyWord.png"), "Modifica Parola", this)); //[5] modifyWordAct
    list->append(new QAction(QIcon(":/Risorse/Icons/removeWord.png"), "Rimuovi Parola", this)); //[6] removeWordAct
    list->append(new BookmarkAction(QIcon(":/Risorse/Icons/star.png"), "Segnalibro", this)); //[7] bookmarkAct
    list->append(new QAction(QIcon(":/Risorse/Icons/bookmarks.png"), "Mostra Segnalibri", this)); //[8] showBookmarksAct
    list->append(new QAction(QIcon(":/Risorse/Icons/history.png"), "Mostra History", this)); //[9] showHistoryAct
    for(int i = 0; i < list->size(); i++) tool_bar->addAction(list->at(i));
    tool_bar->insertSeparator(list->at(3));
    tool_bar->insertSeparator(list->at(7));
}

void MainWindow::createMenus() {
    QMenu* fileMenu = new QMenu("File", this);
    for(int i = 0; i < list->size(); i++) {
        fileMenu->addAction(list->at(i));
        if(i == 2 || i == 6) fileMenu->addSeparator();
    }
    fileMenu->addSeparator();
    QAction* exitAct = new QAction(QIcon(":/Risorse/Icons/exit.png"), "Esci", this);
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, this, &MainWindow::shutDownApp);
    menu_bar->addMenu(fileMenu);
}

void MainWindow::doConnections() {
    connect(list->at(0), &QAction::triggered, accounts_dock, &AccountsDockWidget::addStandardUser);
    connect(list->at(1), &QAction::triggered, accounts_dock, &AccountsDockWidget::removeUsers);
    connect(list->at(2), &QAction::triggered, this, &MainWindow::showLoginDialog);
    connect(list->at(2), &QAction::triggered, this, &MainWindow::setDefault);
    connect(list->at(2), &QAction::triggered, central_widget, &DictionaryCentralWidget::setDefault);
    connect(list->at(2), &QAction::triggered, static_cast<BookmarkAction*>(list->at(7)), &BookmarkAction::unMark);
    connect(list->at(3), &QAction::triggered, central_widget, &DictionaryCentralWidget::searchWord);
    connect(list->at(4), &QAction::triggered, central_widget, &DictionaryCentralWidget::addWord);
    connect(list->at(5), &QAction::triggered, central_widget, &DictionaryCentralWidget::modifyWord);
    connect(list->at(6), &QAction::triggered, central_widget, &DictionaryCentralWidget::removeWord);
    connect(list->at(7), &QAction::triggered, this, &MainWindow::bookmarkClicked);
    connect(list->at(8), &QAction::triggered, this, &MainWindow::showBookmarksDialog);
    connect(list->at(9), &QAction::triggered, this, &MainWindow::showHistoryDialog);
    connect(dispatcher, &ManagerDispatcher::refreshAccountsDock, accounts_dock, &AccountsDockWidget::refresh);
    connect(book_dialog, &BookmarksDialog::sendWordClicked, central_widget, &DictionaryCentralWidget::swapWord);
    connect(central_widget, &DictionaryCentralWidget::dictionaryUpdate, this, &MainWindow::dictionaryUpdate);
    connect(accounts_dock, &AccountsDockWidget::sendUsernames, this, &MainWindow::cleanLeftovers);
    connect(accounts_dock, &AccountsDockWidget::sendToStatusBar, status_bar, &QStatusBar::showMessage);
    connect(central_widget, &DictionaryCentralWidget::sendToStatusBar, status_bar, &QStatusBar::showMessage);
    connect(login_dialog, &LoginDialog::rejected, this, &MainWindow::shutDownApp);
    connect(login_dialog, &LoginDialog::accepted, this, &MainWindow::loginDialogAccepted);
}

void MainWindow::setupUI() {
    addDockWidget(Qt::TopDockWidgetArea, accounts_dock);
    setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks);
    accounts_dock->hide();
    setCentralWidget(central_widget);
    tool_bar->setMovable(false);
    addToolBar(Qt::TopToolBarArea, tool_bar);
    tool_bar->hide();
    setMenuBar(menu_bar);
    menu_bar->hide();
    status_bar->setSizeGripEnabled(false);
    status_bar->setStyleSheet("color: red");
    setStatusBar(status_bar);
    createActions();
    createMenus();
    doConnections();
}

void MainWindow::showEvent(QShowEvent *event) {
    if(!event->spontaneous()) { //Evento interno all'applicazione
        if(!dispatcher->readExternalResources()) event->ignore();
        else event->accept();
    }
    else event->accept(); //Evento proveniente dal sistema operativo (e.g. Maximize Window)
}

void MainWindow::hideEvent(QHideEvent *event) {
    if(!event->spontaneous()) dispatcher->updateExternalResources();
    event->accept();
}

void MainWindow::showLoginDialog() {
    central_widget->hideSearchWord();
    login_dialog->open();
}

void MainWindow::showBookmarksDialog() {
    Account* current = dispatcher->getAccPtr()->getCurrentPointer();
    QString current_username = current->getData(0).toString();
    Account::Type tmp = current->getData(3).value<Account::Type>();
    if(dispatcher->getBookPtr()->count() == 0) status_bar->showMessage("Segnalibri non presenti", 5000);
    else if(tmp == Account::Admin || dispatcher->getBookPtr()->find(current_username) != -1) book_dialog->open();
    else status_bar->showMessage("L'utente corrente non ha segnalibri impostati", 5000);
}

void MainWindow::showHistoryDialog() {
    Account* current = dispatcher->getAccPtr()->getCurrentPointer();
    QString current_username = current->getData(0).toString();
    Account::Type tmp = current->getData(3).value<Account::Type>();
    if(dispatcher->getHisPtr()->count() == 0) status_bar->showMessage("Nessun dato", 5000);
    else if(tmp == Account::Admin || dispatcher->getHisPtr()->find(current_username) != -1) his_dialog->open();
    else status_bar->showMessage("Nessun dato per l'utente corrente", 5000);
}

void MainWindow::loginDialogAccepted() {
    Account* current = dispatcher->getAccPtr()->getCurrentPointer();
    switch(current->getData(3).value<Account::Type>()) {
    case(Account::Admin):
        showAdminUI();
        status_bar->showMessage(QString("Benvenuto %1. Modalità Admin Attivata").arg(current->getData(0).toString()), 10000);
        break;
    case(Account::Operator):
        showOperatorUI();
        status_bar->showMessage(QString("Benvenuto %1. Modalità Operator Attivata").arg(current->getData(0).toString()), 10000);
        break;
    case(Account::Guest):
        showGuestUI();
        status_bar->showMessage(QString("Benvenuto %1. Modalità Guest Attivata").arg(current->getData(0).toString()), 10000);
        break;
    }
}

void MainWindow::showAdminUI() {
    accounts_dock->show();
    tool_bar->show();
    menu_bar->show();
    central_widget->showSearchWord();
    resize(471, 487);
    setWindowTitle("Dictio<Admin>");
    list->at(0)->setVisible(true); //Shows addUserAct
    list->at(1)->setVisible(true); //Shows removeUserAct
    list->at(4)->setVisible(true); //Shows addWordAct
    list->at(5)->setVisible(true); //Shows modifyWordAct
    list->at(6)->setVisible(true); //Shows removeWordAct
}

void MainWindow::showOperatorUI() {
    accounts_dock->hide();
    tool_bar->show();
    menu_bar->show();
    central_widget->showSearchWord();
    resize(471, 317);
    setWindowTitle("Dictio<Operator>");
    list->at(0)->setVisible(false);
    list->at(1)->setVisible(false);
    list->at(4)->setVisible(true);
    list->at(5)->setVisible(true);
    list->at(6)->setVisible(true);
}

void MainWindow::showGuestUI() {
    accounts_dock->hide();
    tool_bar->show();
    menu_bar->show();
    central_widget->showSearchWord();
    resize(471, 317);
    setWindowTitle("Dictio<Guest>");
    list->at(0)->setVisible(false);
    list->at(1)->setVisible(false);
    list->at(4)->setVisible(false);
    list->at(5)->setVisible(false);
    list->at(6)->setVisible(false);
}

void MainWindow::shutDownApp() {close();}

void MainWindow::setDefault() {
    accounts_dock->hide();
    tool_bar->hide();
    menu_bar->hide();
    resize(471, 487);
    setWindowTitle("...Waiting...");
}

void MainWindow::bookmarkClicked() {
    if(BookmarkAction* book_act = dynamic_cast<BookmarkAction*>(list->at(7))) {
        QString message;
        Term* current_term = central_widget->getCurrentWord();
        if(current_term) {
            QString current_word = current_term->getData(0).toString();
            QString current_username = dispatcher->getAccPtr()->getCurrentPointer()->getData(0).toString();
            BookmarksManager* book_man = dispatcher->getBookPtr();
            int account_index = book_man->find(current_username);
            if(!book_act->isMarked()) {
                book_act->setMarked(true);
                message = "Parola aggiunta ai Segnalibri";
                if(account_index == -1) { //Crea nuovo account nei bookmarks
                    book_man->insert(Bookmarks(current_username, QStringList(current_word)));
                }
                else book_man->getPointer(account_index)->addWord(current_word);
            }
            else {
                book_act->setMarked(false);
                message = "Parola rimossa dai Segnalibri";
                Bookmarks* current = dispatcher->getBookPtr()->getPointer(account_index);
                if(current->getData(1).toStringList().size() == 1)
                    book_man->remove(current_username);
                else
                    current->removeWord(current_word);
            }
        }
        else message = "Nessuna Parola Selezionata";
        status_bar->showMessage(message, 5000);
    }
}

void MainWindow::dictionaryUpdate(const QString &word, History::Access acc) {
    //Aggiorna la BookmarkAction
    History::AccessType act = History::Write;
    QString current_username = dispatcher->getAccPtr()->getCurrentPointer()->getData(0).toString();
    if(acc == History::Open) {
        act = History::Read;
        BookmarkAction* book_act = static_cast<BookmarkAction*>(list->at(7));
        int account_index = dispatcher->getBookPtr()->find(current_username);
        if(account_index != -1) {
            int word_index = dispatcher->getBookPtr()->getPointer(account_index)->findWord(word);
            if(word_index != -1) book_act->setMarked(true);
            else book_act->setMarked(false);
        }
        else book_act->setMarked(false);
    }
    dispatcher->getHisPtr()->insert(History(current_username, word, act, acc));
}

void MainWindow::cleanLeftovers(const QStringList &usernames) {
    for(int i = 0; i < usernames.size(); i++) {
        dispatcher->getBookPtr()->remove(usernames[i]);
        dispatcher->getHisPtr()->remove(usernames[i]);
    }
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    dispatcher(new ManagerDispatcher(this)),
    accounts_dock(new AccountsDockWidget(dispatcher->getAccPtr(), this)),
    central_widget(new DictionaryCentralWidget(dispatcher->getDicPtr(), this)),
    tool_bar(new QToolBar("Barra Degli Strumenti", this)),
    menu_bar(new QMenuBar(this)),
    status_bar(new QStatusBar(this)),
    list(new QList<QAction*>),
    login_dialog(new LoginDialog(accounts_dock->getModel(), this)),
    book_dialog(new BookmarksDialog(dispatcher->getBookPtr(), dispatcher->getAccPtr(), this)),
    his_dialog(new HistoryDialog(dispatcher->getHisPtr(), dispatcher->getAccPtr(), this))
{
    setupUI();
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));
    setDefault();
    showLoginDialog();
}
