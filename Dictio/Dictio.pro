QT += \
    core gui \
    widgets \
    xml

TARGET = Dictio

SOURCES += main.cpp \
    AccountsDockWidget.cpp \
    AccountsTableModel.cpp \
    LoginDialog.cpp \
    MainWindow.cpp \
    XMLDictionaryParser.cpp \
    XMLAccountsParser.cpp \
    AccountsManager.cpp \
    DictionaryManager.cpp \
    EditDialog.cpp \
    DictionaryCentralWidget.cpp \
    Account.cpp \
    Term.cpp \
    AccountsContainer.cpp \
    DictionaryContainer.cpp \
    AccountsItemDelegate.cpp \
    ManagerDispatcher.cpp \
    BookmarksContainer.cpp \
    BookmarksManager.cpp \
    Bookmarks.cpp \
    XMLBookmarksParser.cpp \
    BookmarksDialog.cpp \
    BookmarkAction.cpp \
    History.cpp \
    HistoryContainer.cpp \
    HistoryManager.cpp \
    XMLHistoryParser.cpp \
    HistoryDialog.cpp \
    Manager.cpp \
    XMLParser.cpp \
    LexicalCategory.cpp \
    InfoLabel.cpp

HEADERS += \
    LoginDialog.h \
    AccountsTableModel.h \
    MainWindow.h \
    AccountsDockWidget.h \
    XMLParser.h \
    XMLDictionaryParser.h \
    XMLAccountsParser.h \
    Manager.h \
    AccountsManager.h \
    DictionaryManager.h \
    EditDialog.h \
    DictionaryCentralWidget.h \
    Data.h \
    Account.h \
    Term.h \
    Container.h \
    AccountsContainer.h \
    DictionaryContainer.h \
    AccountsItemDelegate.h \
    ManagerDispatcher.h \
    BookmarksContainer.h \
    BookmarksManager.h \
    Bookmarks.h \
    XMLBookmarksParser.h \
    BookmarksDialog.h \
    BookmarkAction.h \
    History.h \
    HistoryContainer.h \
    HistoryManager.h \
    XMLHistoryParser.h \
    HistoryDialog.h \
    LexicalCategory.h \
    InfoLabel.h

RESOURCES = \
    Risorse.qrc
