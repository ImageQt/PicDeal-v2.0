#include "qfftdialog.h"
#include "ui_qfftdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

QFFTDialog::QFFTDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QFFTDialog)
{
    ui->setupUi(this);
}

QFFTDialog::~QFFTDialog()
{
    delete ui;
}

void QFFTDialog::fftshowpic(IplImage *input){
    if(!input || !input->imageData){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("傅里叶变换处理失败!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    img=input;
    IplImage* rgb=cvCreateImage(cvSize(input->width,input->height),input->depth,input->nChannels);
    cvCvtColor(input,rgb,CV_BGR2RGB);
    uchar *imgData=(uchar *)rgb->imageData;
    QImage m_qimg(imgData,rgb->width,rgb->height,QImage::Format_RGB888);
    qimg=m_qimg;
    ui->fftshow->resize(qimg.width(),qimg.height());
    this->resize(qimg.width(),qimg.height());
    ui->fftshow->setPixmap(QPixmap::fromImage(qimg));
}

void QFFTDialog::on_BNSAVE_clicked()
{
    QString filePathName=QFileDialog::getSaveFileName(this,QString::fromUtf8("保存图片"), ".",QString::fromUtf8("PNG图片(*.png);;JPG图片(*.jpg);;BMP图片(*.bmp)"));
    if(!filePathName.isEmpty()){
        String ba=filePathName.toStdString();
        int si=ba.size();
        char* charfilePathName=new char[si];
        for(int i=0;i!=si;++i){
            charfilePathName[i]=ba[i];
        }
        charfilePathName[si]='\0';
        cvSaveImage(charfilePathName,img);
    }
}

void QFFTDialog::on_BNEXIT_clicked()
{
    this->close();
}
