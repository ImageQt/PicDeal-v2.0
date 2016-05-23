#ifndef QCANNYSHWDIALOG_H
#define QCANNYSHWDIALOG_H

#include <QDialog>
#include <opencv2/core.hpp>

namespace Ui {
class QCannyShwDialog;
}

class QCannyShwDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QCannyShwDialog(QWidget *parent = 0);
    ~QCannyShwDialog();

private:
    Ui::QCannyShwDialog *ui;
public:
    QImage qimg;
    IplImage* img;
    void cannyshowpic(IplImage* input);
private slots:
    void on_BNSAVE_clicked();
    void on_BNEXIT_clicked();
};

#endif // QCANNYSHWDIALOG_H
