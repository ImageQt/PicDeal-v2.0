#ifndef QCUTDIALOG_H
#define QCUTDIALOG_H

#include <QDialog>
#include <opencv2/core.hpp>

namespace Ui {
class QCutDialog;
}

class QCutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QCutDialog(QWidget *parent = 0);
    ~QCutDialog();

private:
    Ui::QCutDialog *ui;
public:
    int lfx,lfy,rbx,rby;
    int bncl;
    int width,height;
    void setWiAnHei(IplImage* input);
private slots:
    void on_LT_X_textChanged(const QString &arg1);
    void on_LT_Y_textChanged(const QString &arg1);
    void on_RB_X_textChanged(const QString &arg1);
    void on_RB_Y_textChanged(const QString &arg1);
    void on_BNOK_clicked();
    void on_BNCAL_clicked();
};

#endif // QCUTDIALOG_H
