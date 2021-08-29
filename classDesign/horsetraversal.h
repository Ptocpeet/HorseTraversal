#ifndef HORSETRAVERSAL_H
#define HORSETRAVERSAL_H

#include <QMainWindow>
#include "countscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class HorseTraversal; }
QT_END_NAMESPACE

class HorseTraversal : public QMainWindow
{
    Q_OBJECT

public:
    HorseTraversal(QWidget *parent = nullptr);
    ~HorseTraversal();
   void paintEvent(QPaintEvent *);
   void sleep(int);
   CountScene *count=NULL;
private:
    Ui::HorseTraversal *ui;
};
#endif // HORSETRAVERSAL_H
