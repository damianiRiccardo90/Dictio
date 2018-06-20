#include "BookmarkAction.h"

BookmarkAction::BookmarkAction(const QIcon &icon, const QString &text, QObject *parent):
    QAction(icon, text, parent),
    marked(false)
{}

bool BookmarkAction::isMarked() const {return marked;}

void BookmarkAction::setMarked(bool m) {
    marked = m;
    if(m) setIcon(QIcon(":/Risorse/Icons/filledStar.png"));
    else setIcon(QIcon(":/Risorse/Icons/star.png"));
}

void BookmarkAction::unMark() {
    setMarked(false);
}
