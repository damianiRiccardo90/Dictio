#ifndef INFOLABEL_H
#define INFOLABEL_H

#include<QWidget>
#include<QLabel>
#include<QTimer>

class InfoLabel: public QLabel {
    Q_OBJECT
public:
    InfoLabel(QWidget* parent = Q_NULLPTR): QLabel(parent) {}
public slots:
    void setText(const QString& text, int timeout = 5000);
};

#endif // INFOLABEL_H
