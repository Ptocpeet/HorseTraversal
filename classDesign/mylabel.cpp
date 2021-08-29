#include "mylabel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QCursor>
MyLabel::MyLabel(int wid,int hei)
{
    theWidth=wid;
    theHeight=hei;
    QPixmap  BackPix;
    BackPix.load(":/res/play.jpg");
    BackPix=BackPix.scaled(BackPix.width(),BackPix.height());
    this->setGeometry(40,50,745,660);
    this->setFrameShape (QFrame::Box);
    this->setStyleSheet("QLabel{border:5px solid rgb(0,0,0);}");
    this->setPixmap(BackPix);
    setMouseTracking(true);
}
void MyLabel::mouseMoveEvent(QMouseEvent *){
    QPixmap pix;
    pix.load(":/res/horse.png");
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    QCursor *myCursor=new QCursor(pix,-1,-1);
    this->setCursor(*myCursor);
}
