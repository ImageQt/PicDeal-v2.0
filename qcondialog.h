#ifndef QCONDIALOG_H
#define QCONDIALOG_H

#include <QDialog>

namespace Ui {
class QConDialog;
}

class QConDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QConDialog(QWidget *parent = 0);
    ~QConDialog();

private:
    Ui::QConDialog *ui;
public:
    int contrast,lighdm;
    int bncl;

private slots:
    void on_BNOK_clicked();
    void on_BNCAL_clicked();
    void on_sli_contrast_valueChanged(int value);
    void on_sli_lighdm_valueChanged(int value);
};

#endif // QCONDIALOG_H
