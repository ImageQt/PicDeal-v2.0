#ifndef PICDEALMAIN_H
#define PICDEALMAIN_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QMouseEvent>
#include <QStack>

namespace Ui {
class PicDealMain;
}

class PicDealMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit PicDealMain(QWidget *parent = 0);
    ~PicDealMain();
public:
    QImage Ipl2Q(IplImage* input);
    void close();
private slots:
    void on_IDM_OPEN_triggered();

    void on_IDM_SAVE_triggered();

    void on_IDM_EXIT_triggered();

    void on_IDM_ABORT_triggered();

    void on_IDT_ZOOM_IN_triggered();

    void on_IDT_ZOOM_OUT_triggered();

    void on_IDT_ZOOM_RE_triggered();

    void on_IDT_REVOKE_triggered();

    void on_IDT_REDO_triggered();

    void on_IDM_AVG_triggered();

    void on_IDM_FILTER_triggered();

    void on_IDM_CONTRAST_triggered();

    void on_IDM_EDGEDET_triggered();

    void on_IDM_PSECOL_triggered();

    void on_IDM_FFT_triggered();

    void on_IDM_SPIN_triggered();

    void on_IDM_ZOOM_triggered();

    void on_IDM_CUT_triggered();

    void on_IDM_RGB2GRAY_triggered();

    void on_IDM_HISTOGRAM_triggered();

    void on_IDM_FACE_triggered();

    void on_IDM_SHOWHIS_triggered();

    void on_IDM_LAPLACE_triggered();

private:
    Ui::PicDealMain *ui;
private:
    QStack<IplImage*> revoke,redo;
    IplImage* img;
    QImage qimg,qimg_zo;
    float width,height,zoom;
    QString filePathName;
    char* charfilePathName;
};

#endif // PICDEALMAIN_H
