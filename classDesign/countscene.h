#ifndef COUNTSCENE_H
#define COUNTSCENE_H

#include <QMainWindow>
#include <QLabel>
#include "mylabel.h"
#include <QTextEdit>
#include "mychess.h"
#include "mypair.h"
#include <stack>
#include <QSound>
#include <QTimer>
using namespace  std;
struct info {
    int x, y, step;
};
class CountScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit CountScene(int wid,int hei);
//    ~CountScene();
    void paintEvent(QPaintEvent*);
    int TheWidth=0;
    int TheHeight=0;
    bool HasBack=NULL;
    bool HasFinish=false;
    void drawLine();
    void showPoint();
    void dfs(info);
    void dfs2(int,int,int);
    void sleep(int);
    void TheMain(int,int,int,int);
    QSound *chessMan;
    stack<info>out;
    MyLabel *chessBack=NULL;
    QTextEdit *pEdit;
    MyChess *MychessArray[200][200];
    QLabel *picture[200][200];
    QLabel *number[200][200];
    QLabel *movieLabel;
    QMovie *movie;
    QLabel *succeed;
    QLabel *failed;
signals:
    void chooseBack();
    void startSinal();
};

#endif // COUNTSCENE_H
