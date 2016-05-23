#include "qcannyshwdialog.h"
#include "ui_qcannyshwdialog.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QFileDialog>
#include <QMessageBox>

using namespace std;
using namespace cv;

QCannyShwDialog::QCannyShwDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCannyShwDialog)
{
    ui->setupUi(this);
}

QCannyShwDialog::~QCannyShwDialog()
{
    delete ui;
}

void QCannyShwDialog::cannyshowpic(IplImage *input){
    if(!input || !input->imageData){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("Canny检测处理失败!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    img=input;
    uchar *imgData=(uchar *)img->imageData;
    QImage m_qimg;
    if(img->nChannels==1) m_qimg=QImage(imgData,img->width,img->height,QImage::Format_Indexed8);
    else if(img->nChannels==3) m_qimg=QImage(imgData,img->width,img->height,QImage::Format_RGB888);
    qimg=m_qimg;
    ui->cannyshow->resize(qimg.width(),qimg.height());
    this->resize(qimg.width(),qimg.height());
    ui->cannyshow->setPixmap(QPixmap::fromImage(qimg));
}

void QCannyShwDialog::on_BNSAVE_clicked()
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

void QCannyShwDialog::on_BNEXIT_clicked()
{
    this->close();
}
