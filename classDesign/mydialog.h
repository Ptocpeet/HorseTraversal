#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPushButton>
namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();
    void paintEvent(QPaintEvent *);
    QString theWidth;
    QString theHeight;
    void getValue(QString w,QString h);
    bool flag=false;
private:
    Ui::MyDialog *ui;
signals:
    void closeSinal();
    void startSinal(int wid,int hei);
};

#endif // MYDIALOG_H
