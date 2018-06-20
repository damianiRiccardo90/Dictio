#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QAction>
#include<QIcon>
#include<QMenu>
#include<QToolBar>
#include<QMenuBar>
#include<QStatusBar>
#include<QShowEvent>
#include<QHideEvent>
#include<QString>
#include<QStringList>
#include<QList>
#include<QMainWindow>
#include<QApplication>
#include<QDesktopWidget>
#include<QStyle>

#include"Account.h"
#include"AccountsDockWidget.h"
#include"DictionaryCentralWidget.h"
#include"EditDialog.h"
#include"LoginDialog.h"
#include"ManagerDispatcher.h"
#include"BookmarksDialog.h"
#include"BookmarkAction.h"
#include"HistoryDialog.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
private:
    ManagerDispatcher* dispatcher;
    AccountsDockWidget* accounts_dock;
    DictionaryCentralWidget* central_widget;
    QToolBar* tool_bar;
    QMenuBar* menu_bar;
    QStatusBar* status_bar;
    QList<QAction*>* list;
    LoginDialog* login_dialog;
    BookmarksDialog* book_dialog;
    HistoryDialog* his_dialog;

    void createActions();
    void createMenus();
    void doConnections();
    void setupUI();
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
private slots:
    void showLoginDialog();
    void showBookmarksDialog();
    void showHistoryDialog();
    void loginDialogAccepted();
    void showAdminUI();
    void showOperatorUI();
    void showGuestUI();
    void shutDownApp();
    void setDefault();
    void bookmarkClicked();
    void dictionaryUpdate(const QString& word, History::Access acc);
    void cleanLeftovers(const QStringList& usernames);
public:
    MainWindow(QWidget* parent = 0);
};

#endif // MAINWINDOW_H
