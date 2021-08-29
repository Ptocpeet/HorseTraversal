#include "horsetraversal.h"
#include <QDebug>
#include <stack>
#include <algorithm>
#include <QApplication>
#include <iostream>
#include <stdio.h>
#include <QTimer>
#include <QTime>
void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HorseTraversal w;
    w.show();
    return a.exec();
}
