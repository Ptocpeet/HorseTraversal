#ifndef MYCHESS_H
#define MYCHESS_H

#include <QPushButton>

class MyChess : public QPushButton
{
    Q_OBJECT
public:
    explicit MyChess(QWidget *parent = nullptr);
    bool flag=false;
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // MYCHESS_H
