#ifndef QPESCOLDIALOG_H
#define QPESCOLDIALOG_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class QPescolDialog;
}

class QPescolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QPescolDialog(QWidget *parent = 0);
    ~QPescolDialog();

private:
    Ui::QPescolDialog *ui;
private:
    QButtonGroup* grp;
public:
    int result;
    int bncl;
private slots:
    void on_RGB_clicked();
    void on_RBG_clicked();
    void on_BRG_clicked();
    void on_BGR_clicked();
    void on_GRB_clicked();
    void on_GBR_clicked();
    void on_BNOK_clicked();
    void on_BNCAL_clicked();
};

#endif // QPESCOLDIALOG_H
