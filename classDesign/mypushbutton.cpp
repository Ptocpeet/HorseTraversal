#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
MyPushButton::MyPushButton(QString nomalImag,double bl,QString pressImag){
    this->nomalImagpath=nomalImag;
    this->pressImagpath=pressImag;
    QPixmap pix;
    bool check=pix.load(nomalImag);
    if(!check){
        qDebug()<<"加载图片失败";
        return;
    }
    pix=pix.scaled(pix.width()*bl,pix.height()*bl);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void MyPushButton::zoom1(){
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(251);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::zoom2(){
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(251);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton:: mousePressEvent(QMouseEvent *e){
    if(this->pressImagpath != ""){
        QPixmap pix;
        bool check=pix.load(this->pressImagpath);
        if(!check){
            qDebug()<<"加载图片失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton:: mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImagpath != ""){
        QPixmap pix;
        bool check=pix.load(this->nomalImagpath);
        if(!check){
            qDebug()<<"加载图片失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}

