#ifndef FIXDIALOG_H
#define FIXDIALOG_H

#include <QDialog>

namespace Ui {
class FixDialog;
}

class FixDialog : public QDialog
{
    Q_OBJECT

public:
    FixDialog(int ,int,QWidget *parent = nullptr);
    ~FixDialog();
    void paintEvent(QPaintEvent *);
    void sleep(int);
private:
    Ui::FixDialog *ui;
signals:
    void startSinal();
    void closeSinal();
};

#endif // FIXDIALOG_H
