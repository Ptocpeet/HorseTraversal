#include "mychess.h"

MyChess::MyChess(QWidget *parent) : QPushButton(parent)
{
    setMouseTracking(true);
}
void MyChess::mouseMoveEvent(QMouseEvent *){
    QPixmap pix;
    pix.load(":/res/horse.png");
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    QCursor *myCursor=new QCursor(pix,-1,-1);
    this->setCursor(*myCursor);
}
void MyChess::mousePressEvent(QMouseEvent *e){
    if(flag) return;
    else QPushButton::mousePressEvent(e);
}
