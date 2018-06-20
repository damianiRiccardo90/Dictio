#ifndef BOOKMARKACTION_H
#define BOOKMARKACTION_H

#include<QAction>
#include<QIcon>
#include<QObject>
#include<QString>

class BookmarkAction: public QAction {
    Q_OBJECT
private:
    bool marked;
public:
    BookmarkAction(const QIcon& icon, const QString& text, QObject* parent = 0);
    bool isMarked() const;
    void setMarked(bool m);
public slots:
    void unMark();
};

#endif // BOOKMARKACTION_H
