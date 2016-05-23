#ifndef QFFTDIALOG_H
#define QFFTDIALOG_H

#include <QDialog>
#include <opencv2/core.hpp>

namespace Ui {
class QFFTDialog;
}

class QFFTDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QFFTDialog(QWidget *parent = 0);
    ~QFFTDialog();

private:
    Ui::QFFTDialog *ui;
public:
    IplImage* img;
    QImage qimg;
    void fftshowpic(IplImage* input);
private slots:
    void on_BNSAVE_clicked();
    void on_BNEXIT_clicked();
};

#endif // QFFTDIALOG_H
