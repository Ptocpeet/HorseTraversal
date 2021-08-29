#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(int wid,int hei);
//    void paintEvent(QPaintEvent*);
    int theWidth;
    int theHeight;
    void mouseMoveEvent(QMouseEvent *ev) ;
signals:

};

#endif // MYLABEL_H
