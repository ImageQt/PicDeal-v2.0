#ifndef QZOOMDIALOG_H
#define QZOOMDIALOG_H

#include <QDialog>

namespace Ui {
class QZoomDialog;
}

class QZoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QZoomDialog(QWidget *parent = 0);
    ~QZoomDialog();

private:
    Ui::QZoomDialog *ui;
public:
    int zoomNum;
    int bncl;
private slots:
    void on_zoomnum_textChanged(const QString &arg1);
    void on_BNOK_clicked();
    void on_BNCAL_clicked();
};

#endif // QZOOMDIALOG_H
