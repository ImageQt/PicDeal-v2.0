#ifndef QAVGDIALOG_H
#define QAVGDIALOG_H

#include <QDialog>

namespace Ui {
class QAvgDialog;
}

class QAvgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QAvgDialog(QWidget *parent = 0);
    ~QAvgDialog();

private:
    Ui::QAvgDialog *ui;
public:
    int result;
    int bncl;
private slots:
    void on_BNOK_clicked();
    void on_BNCAL_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
};

#endif // QAVGDIALOG_H
