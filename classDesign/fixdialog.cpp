#include "fixdialog.h"
#include "ui_fixdialog.h"
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QTime>
#include <QSound>
FixDialog::FixDialog(int w,int h,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FixDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint
                   | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
                   | Qt::WindowMaximizeButtonHint);
    QLabel *info=new QLabel;
    info->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(15);
    QString str1=QString("是否确定将点 (%1,%2) 设为起点").arg(w+1).arg(h+1);
    info->setText(str1);
    info->setFont(font);
    info->setGeometry(this->width()*0.5-160,this->height()*0.5-40,400,50);
    connect(ui->btn2,&QPushButton::clicked,[=](){
        this->close();
        sleep(100);
        emit closeSinal();
    });
    connect(ui->btn1,&QPushButton::clicked,[=](){
        this->close();
        sleep(100);
        emit startSinal();
    });
}
void FixDialog::paintEvent(QPaintEvent *){
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QRect rect = QRect(0, 0, this->width(), this->height());
    path.addRoundedRect(rect,10,10);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
    painter.setPen(Qt::gray);
    painter.drawPath(path);

    painter.drawLine(rect.left()+40, 60, rect.right()-40, 60);
    painter.drawLine(rect.left()+40, rect.bottom()-70, rect.right()-40, rect.bottom()-70);
}
FixDialog::~FixDialog()
{
    delete ui;
}
void FixDialog::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime ){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
