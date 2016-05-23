#ifndef QFILDIALOG_H
#define QFILDIALOG_H

#include <QDialog>

namespace Ui {
class QFilDialog;
}

class QFilDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QFilDialog(QWidget *parent = 0);
    ~QFilDialog();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_BNOK_clicked();

    void on_BNCAL_clicked();

private:
    Ui::QFilDialog *ui;
public:
    int result;
    int bncl;
};

#endif // QFILDIALOG_H
