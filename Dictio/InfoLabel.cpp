#include "InfoLabel.h"

void InfoLabel::setText(const QString &text, int timeout) {
    QTimer::singleShot(timeout, this, SLOT(clear()));
    QLabel::setText("<font color='Red'>" + text + "</font>");
}
