#ifndef QROLDIALOG_H
#define QROLDIALOG_H

#include <QDialog>

namespace Ui {
class QRolDialog;
}

class QRolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QRolDialog(QWidget *parent = 0);
    ~QRolDialog();

private:
    Ui::QRolDialog *ui;
public:
    int degree;
    int bncl;
private slots:
    void on_degreedit_textChanged(const QString &arg1);
    void on_BNOK_clicked();
    void on_BNCAL_clicked();
};

#endif // QROLDIALOG_H
