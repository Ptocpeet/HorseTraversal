#include "mydialog.h"
#include "ui_mydialog.h"
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint
                   | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
                   | Qt::WindowMaximizeButtonHint);
    ui->infoLabel->hide();
    connect(ui->btn2,&QPushButton::clicked,[=](){
        QTimer::singleShot(100,this,[=](){
            this->close();
        });
        emit this->closeSinal();
    });
    connect(ui->btn1,&QPushButton::clicked,[=](){
        bool c1,c2;
        QString str1,str2;
        double x1,x2;
        str1=ui->lineEdit->text();
        str2=ui->lineEdit2->text();
        x1=str1.toDouble(&c1);
        x2=str2.toDouble(&c2);
        if(x1>1&&x2>1&&(x1==(int)x1)&&(x2==(int)x2)&&x1<200&&x2<200){
            getValue(str1,str2);
            QTimer::singleShot(100,this,[=](){
                this->close();
            });
            emit this->startSinal(theWidth.toInt(),theHeight.toInt());
        }
        else{
            if(!flag){
                flag=true;
                ui->infoLabel->show();
            }
        }
    });
}
void MyDialog::getValue(QString w, QString h){
    theWidth=w;
    theHeight=h;
}
MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::paintEvent(QPaintEvent *){
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


