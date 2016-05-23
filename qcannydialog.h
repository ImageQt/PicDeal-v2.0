#ifndef QCANNYDIALOG_H
#define QCANNYDIALOG_H

#include <QDialog>

namespace Ui {
class QCannyDialog;
}

class QCannyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QCannyDialog(QWidget *parent = 0);
    ~QCannyDialog();

private:
    Ui::QCannyDialog *ui;
public:
    int numa,numb,numc;
    bool pre;
    int bncl;
private slots:
    void on_numA_textChanged(const QString &arg1);
    void on_numB_textChanged(const QString &arg1);
    void on_numC_textChanged(const QString &arg1);
    void on_predeal_clicked();
    void on_BNOK_clicked();
    void on_BNCAL_clicked();
};

#endif // QCANNYDIALOG_H
