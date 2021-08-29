#ifndef MYPAIR_H
#define MYPAIR_H

#include <QWidget>

class Mypair : public QWidget
{
    Q_OBJECT
public:
    explicit Mypair(QWidget *parent = nullptr);
    int x,y;
signals:

};

#endif // MYPAIR_H
