#include "countscene.h"
#include <QPainter>
#include <QTimer>
#include "mypushbutton.h"
#include <QPaintEvent>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTime>
#include <QDebug>
#include <QCoreApplication>
#include <QPushButton>
#include <fixdialog.h>
#include <QMovie>
#include <stack>
#include <algorithm>
#include <QApplication>
#include <iostream>
#include <stdio.h>
#include <QSound>
#include <queue>
#include <cmath>
using namespace std;
int Width, Height, chessSize;
int** vis;
int dx[8] = { -1,1,-1,1,-2,-2,2,2 };//列坐标
int dy[8] = { -2,-2,2,2,-1,1,-1,1 };//横坐标
stack<info> q;
int getSteps(int tx,int ty) {
    int s = 0;
    int x, y;
    for (int i = 0; i < 8; i++) {
        x = tx + dx[i];
        y = ty + dy[i];
        if (x < 0 || x >= Width || y < 0 || y >= Height || vis[y][x] == 1) continue;
        s++;
    }
    return s;
}
void CountScene:: dfs(info st) {
    queue<info> ChessQueue;
    ChessQueue.push(st);
    int tx, ty, nextSteps;
    info t, NextT;
    while (!ChessQueue.empty()) {
        t = ChessQueue.front();
        ChessQueue.pop();
        q.push(t);
        vis[t.y][t.x] = 1;
        int minSteps = 8;
        bool isFirst = 1;
        for (int i = 0; i < 8; i++) {
            tx = t.x + dx[i];
            ty = t.y + dy[i];
            if (tx < 0 || tx >= Width || ty < 0 || ty >= Height || vis[ty][tx] == 1) continue;
            nextSteps = getSteps(tx, ty);
            if (nextSteps <= minSteps) {
                minSteps = nextSteps;
                NextT.x = tx;
                NextT.y = ty;
                NextT.step = t.step + 1;
                if (isFirst == 0) ChessQueue.pop();
                ChessQueue.push(NextT);
                isFirst = 0;
            }
        }
    }
}
void CountScene::dfs2(int posx,int posy,int step) {
    if (HasFinish == 1) return;
    if (step == chessSize) {
        HasFinish = 1;
        return;
    }
    int tx, ty;
    info t;
    for (int i = 0; i < 8; i++) {
        tx = posx + dx[i];
        ty = posy + dy[i];
        if (tx < 0 || tx >= Width || ty < 0 || ty >= Height || vis[ty][tx] == 1) continue;
        t.x = tx;
        t.y = ty;
        t.step = step + 1;
        vis[ty][tx] = 1;
        q.push(t);
        dfs2(tx, ty, step + 1);
        if (HasFinish == 1) break;
        vis[ty][tx] = 0;
        q.pop();
    }
}
void del(int** a, int h) {
    for (int i = 0; i < h; i++)
        delete[]a[i];
    delete[]a;
}

void CountScene:: TheMain(int widt,int heigh,int sx,int sy){
    movie->start();
    Width=widt;
    Height=heigh;
    chessSize = Width * Height;

    vis = new int* [Height];
    for (int i = 0; i < Height; i++)
        vis[i] = new int[Width];
    for (int i = 0; i < Height; i++)
        for (int j = 0; j < Width; j++)
            vis[i][j] = 0;

    info o;
    o.step = 1;
    o.x = sx;
    o.y = sy;
    sleep(1000);
    if(abs(Width-Height)<=2&&Width>=6&&Height>=6)
        dfs(o);
    else{
        q.push(o);
        vis[sy][sx] = 1;
        dfs2(sx, sy, 1);
    }
    movie->stop();
    movieLabel->hide();
    int Size = q.size();
    if (Size == chessSize || HasFinish == 1) {
        QSound *win=new QSound(":/res/Finish2.wav",this);
        info t;
        for (int i = 0; i < Size; i++) {
            t = q.top();
            out.push(t);
            q.pop();
        }
        succeed->show();
        win->play();
        sleep(2000);
        succeed->hide();
        showPoint();
    }
    else  {
        while(!q.empty()) q.pop();
        if(HasBack == 0){
            QSound *fal=new  QSound(":/res/Failed.wav",this);
            failed->show();
            fal->play();
            sleep(2000);
            failed->hide();
        }
    }
    del(vis, Height);
}


CountScene::CountScene(int wid,int hei)
{
    TheWidth=wid;
    TheHeight=hei;

    chessMan=new QSound(":/res/chessManM2.wav",this);
    //设置背景
    setFixedSize(1224,768);
    setWindowIcon(QIcon(":/res/horse.png"));
    setWindowTitle("马的遍历");

    QSound *backSound=new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",0.06);
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width()-20,this->height()-backBtn->height()-20);
    connect(backBtn,&QPushButton::clicked,[=](){
        backSound->play();
        HasBack=1;
        backBtn->zoom1();
        backBtn->zoom2();
        QTimer::singleShot(251,this,[=](){
            emit this->chooseBack();
        });
    });

    chessBack=new MyLabel(TheWidth,TheHeight);
    chessBack->setParent(this);
    chessBack->show();

    //标签创建棋盘//(40,50,745,660)
    QPen pen2(Qt::black);
    pen2.setWidth(3);
    QPixmap  BackPix;
    BackPix.load(":/res/line.png");
    BackPix=BackPix.scaled(BackPix.width(),BackPix.height());
    //横向
    if(TheWidth>2){
        int num=TheWidth-2;
        double x=40;
        double wid=745*1.0/(num+1);
        for(int i=0;i<num;i++){
            x+=wid;
            QLabel *label=new QLabel;
            label->setParent(this);
            label->setGeometry(x,50,3,660);
            label->setPixmap(BackPix);
            label->setAttribute(Qt::WA_TransparentForMouseEvents);
        }
    }
    //竖向
    if(TheHeight>2){
        int num=TheHeight-2;
        double y=50;
        double wid=660*1.0/(num+1);
        for(int i=0;i<num;i++){
            y+=wid;
            QLabel *label=new QLabel;
            label->setParent(this);
            label->setGeometry(40,y,745,3);
            label->setPixmap(BackPix);
            label->setAttribute(Qt::WA_TransparentForMouseEvents);
        }
    }
    //设置各点图画和数字
    int TheX=TheWidth;
    int TheY=TheHeight;
    double dx=40,dy=50;
    double dwid=745*1.0/(TheX-1);
    double dhei=660*1.0/(TheY-1);
    BackPix.load(":/res/horse.png");
    BackPix=BackPix.scaled(BackPix.width()*1.0,BackPix.height()*1.0);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    QFont font2;
    font2.setBold(true);
    font2.setFamily("新宋体");
    font2.setPointSize(15);
    for(int i=0;i<TheY;i++){
        dx=40;
        for(int j=0;j<TheX;j++){
            //设置图画
            QLabel *lab=new QLabel;
            lab->setParent(this);
            lab->setFixedSize(BackPix.width(),BackPix.height());
            lab->move(dx-27,dy-27);
            lab->setPixmap(BackPix);
            lab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            lab->setAttribute(Qt::WA_TransparentForMouseEvents);
            lab->hide();
            picture[i][j]=lab;

            //设置数字
            QLabel *lab2=new QLabel;
            lab2->setParent(this);
            lab2->setFixedSize(70,70);
            lab2->move(dx-35,dy-35);
            lab2->setFont(font2);
            lab2->setPalette(pa);
            lab2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            lab2->setAttribute(Qt::WA_TransparentForMouseEvents);
            lab2->hide();
            number[i][j]=lab2;

            dx+=dwid;
        }
        dy+=dhei;
    }

    //创建按钮信息
    dy=0;
    double twid,thei;
    for(int i=0;i<TheY;i++){
        dx=0;
        for(int j=0;j<TheX;j++){
            MyChess *btn=new MyChess;
            btn->setParent(chessBack);
            btn->setStyleSheet("QPushButton{border:0px}");
            if(j==0||j==TheX-1) twid=dwid/2.0;
            else twid=dwid;
            if(i==0||i==TheY-1) thei=dhei/2.0;
            else thei=dhei;
            btn->move(dx,dy);
            btn->setFixedSize(twid,thei);
            if(j==0||j==TheX-1) dx+=dwid/2.0;
            else dx+=dwid;
            btn->setFlat(true);
            MychessArray[i][j]=btn;
            connect(btn,&MyChess::clicked,[=](){
                picture[i][j]->show();
                chessMan->play();
                //信息框
                FixDialog dlg(j,i,this);
                connect(&dlg,&FixDialog::startSinal,[=](){
                    for(int i=0;i<TheY;i++)
                        for(int j=0;j<TheX;j++) MychessArray[i][j]->flag=1;
                    TheMain(TheWidth,TheHeight,j,i);
                });
                connect(&dlg,&FixDialog::closeSinal,[=](){
                    picture[i][j]->hide();
                });
                dlg.exec();
            });
        }
        if(i==0||i==TheY-1) dy+=dhei/2.0;
        else dy+=dhei;
    }


    //设置等待动图
    movie=new QMovie(":/res/loading4.gif");
    movie->setParent(this);
    movie->setScaledSize(QSize(70,70));
    movieLabel=new QLabel(this);
    movieLabel->setMovie(movie);
    movieLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    movieLabel->setGeometry(this->width()*0.5-40,this->height()*0.5-100,200,200);

    //设置是否生成路径提示图片
    QPixmap  pix2;
    pix2.load(":/res/succeed.png");
    pix2=pix2.scaled(pix2.width()*0.5,pix2.height()*0.5);
    succeed=new QLabel(this);
    succeed->setGeometry((this->width()-pix2.width())*0.5,(this->height()-pix2.height())*0.5-150,550,550);
    succeed->setPixmap(pix2);
    succeed->setAttribute(Qt::WA_TransparentForMouseEvents);
    succeed->hide();

    pix2.load(":/res/failed.png");
    pix2=pix2.scaled(pix2.width()*0.5,pix2.height()*0.5);
    failed=new QLabel(this);
    failed->setGeometry((this->width()-pix2.width())*0.5,(this->height()-pix2.height())*0.5-150,550,550);
    failed->setPixmap(pix2);
    failed->setAttribute(Qt::WA_TransparentForMouseEvents);
    failed->hide();
}

void CountScene::showPoint(){
    pEdit=new QTextEdit;
    pEdit->setParent(this);
    pEdit->setGeometry(850,40,350,580);
    pEdit->setReadOnly(true);
    pEdit->setStyleSheet("background-color:darkgrey;");
    QFont font;
    font.setFamily("新宋体");
    font.setPointSize(13);
    pEdit->setFont(font);
    pEdit->show();
    int Size=out.size();
    info t,TheBack;
    TheBack=out.top();
    out.pop();
    QString str1=QString(" 第%1步坐标为:  (%2,%3)").arg(1).arg(TheBack.x+1).arg(TheBack.y+1);
    picture[TheBack.y][TheBack.x]->show();
    pEdit->append(str1);
    for(int i=1;i<Size;i++){
        if(HasBack==1) break;
        t=out.top();
        out.pop();
        sleep(500);
        //上一个留下步骤数
        number[TheBack.y][TheBack.x]->setText(QString::number(i));
        //图像显示及隐藏
        picture[TheBack.y][TheBack.x]->hide();
        sleep(100);
        picture[t.y][t.x]->show();
        number[TheBack.y][TheBack.x]->show();
        chessMan->play();
        //右侧显示坐标信息
        str1=QString(" 第%1步坐标为:  (%2,%3)").arg(i+1).arg(t.x+1).arg(t.y+1);
        if(HasBack==1) break;
        pEdit->append(str1);

        TheBack=t;
    }
    number[TheBack.y][TheBack.x]->setText(QString::number(Size));
    sleep(500);
    picture[TheBack.y][TheBack.x]->hide();
    sleep(100);
    number[TheBack.y][TheBack.x]->show();
    sleep(100);
}

void CountScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background2.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画分割线
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QRect rect = QRect(0, 0, this->width(), this->height());
    path.addRoundedRect(rect,10,10);

    QPen pen(Qt::white);
    pen.setWidth(3);
    QPainter painter2(this);
    painter2.setRenderHint(QPainter::Antialiasing, true);
    painter2.setPen(pen);
    painter2.drawLine(rect.right()-400, 0, rect.right()-400, this->height()-100);
}

void CountScene::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime ){
        if(HasBack==1) break;
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

