#include "horsetraversal.h"
#include "ui_horsetraversal.h"
#include <QPushButton>
#include <QPainter>
#include "mypushbutton.h"
#include "countscene.h"
#include <QTimer>
#include <QLabel>
#include <QDialog>
#include <QTime>
#include <mydialog.h>
#include <QSound>
HorseTraversal::HorseTraversal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HorseTraversal)
{
    //主界面设置
    ui->setupUi(this);
    setFixedSize(1224,768);
    setWindowIcon(QIcon(":/res/horse.png"));
    setWindowTitle("马的遍历");

    QSound *quit=new QSound(":/res/BackButtonSound2.wav",this);
    //退出按钮
    MyPushButton *closeBtn=new MyPushButton(":/res/CloseButton2.png",0.7);
    closeBtn->setParent(this);
    closeBtn->move(this->width()-closeBtn->width()+70,this->height()-closeBtn->height()+40);
    connect(closeBtn,&QPushButton::clicked,[=](){
        quit->play();
        closeBtn->zoom1();
        closeBtn->zoom2();
        QTimer::singleShot(300,[=](){
            this->close();
        });
    });

    QSound *start=new QSound(":/res/TapButtonSound.wav",this);
    //开始按钮及返回按钮
    MyPushButton *startBtn=new MyPushButton(":/res/StartButton.png",0.08);
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.5);
    connect(startBtn,&QPushButton::clicked,[=](){
        start->play();
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(300,[=](){
            this->hide();
            //设置棋盘大小
            MyDialog dlg(this);
            connect(&dlg,&MyDialog::closeSinal,[=](){
                QTimer::singleShot(104,this,[=](){
                    this->show();
                });
            });
            connect(&dlg,&MyDialog::startSinal,[=](int wid,int hei){
                count=new CountScene(wid,hei);
            });
            dlg.exec();
            if(count!=NULL){
                connect(count,&CountScene::chooseBack,this,[=](){
                    count->HasBack=1;
                    count->hide();
                    this->setGeometry(count->geometry());
                    this->show();
                    delete  count;
                    count=NULL;
                });
                count->setGeometry(this->geometry());
                count->show();
                emit  count->startSinal();
            }
        });
    });

    //标签排序
    QLabel *info=new QLabel;
    info->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(28);
    QString str1=QString("数据结构课程设计第41题");
    info->setText(str1);
    info->setFont(font);
    info->setGeometry(50,this->height()-470,520,50);

    QLabel *info1=new QLabel;
    info1->setParent(this);
    font.setPointSize(27);
    str1=QString("18AI ");
    info1->setText(str1);
    info1->setFont(font);
    info1->setGeometry(50,this->height()-350,320,50);

    QLabel *info2=new QLabel;
    info2->setParent(this);
    font.setPointSize(30);
    str1=QString("陈阳");
    info2->setText(str1);
    info2->setFont(font);
    info2->setGeometry(200,this->height()-350,120,50);
}
void HorseTraversal::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Tital2.png");
    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
    painter.drawPixmap((this->width()-pix.width())*0.5,100,pix);
}

void HorseTraversal::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


HorseTraversal::~HorseTraversal()
{
    delete ui;
}

