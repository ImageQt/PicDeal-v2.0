#include "picdealmain.h"
#include "ui_picdealmain.h"
#include <qfiledialog.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>
#include <QStack>
#include <QLibrary>
#include "qavgdialog.h"
#include "qfildialog.h"
#include "qcondialog.h"
#include "qcannydialog.h"
#include "qcannyshwdialog.h"
#include "qpescoldialog.h"
#include "qfftdialog.h"
#include "qroldialog.h"
#include "qzoomdialog.h"
#include "qcutdialog.h"
#include "core.h"

using namespace std;
using namespace cv;
PicDealMain::PicDealMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PicDealMain)
{
    ui->setupUi(this);
    this->setFixedSize(890,560);
    img=NULL;
    filePathName=tr("");
    charfilePathName=NULL;
    zoom=1.0;
    revoke.clear();
    redo.clear();
}

PicDealMain::~PicDealMain()
{
    delete ui;
}

QImage PicDealMain::Ipl2Q(IplImage *input){
    if(input->nChannels == 3){
    IplImage* rgb=cvCreateImage(cvSize(input->width,input->height),input->depth,input->nChannels);
    cvCvtColor(input,rgb,CV_BGR2RGB);
    uchar *imgData=(uchar *)rgb->imageData;
    QImage image(imgData,rgb->width,rgb->height,QImage::Format_RGB888);
    return image;
    }
    else if(input->nChannels == 1){
        uchar* imgData=(uchar *)input->imageData;
        QImage image(imgData,input->height,input->width,QImage::Format_Indexed8);
        return image;
    }
}

void PicDealMain::on_IDM_OPEN_triggered()
{
    if(img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("提示"));
        box.setIcon(QMessageBox::Warning);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("是否保存当前图片?"));
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int result=box.exec();
        if(result == QMessageBox::Yes){
            this->on_IDM_SAVE_triggered();
            cvReleaseImage(&img);
            revoke.clear();
            redo.clear();
        }
        else if(result == QMessageBox::No){
            cvReleaseImage(&img);
            revoke.clear();
            redo.clear();
        }
        else if(result == QMessageBox::Cancel){
            return;
        }
    }
    filePathName = QFileDialog::getOpenFileName(this,QString::fromUtf8("打开图片"), ".",QString::fromUtf8("PNG图片(*.png);;JPG图片(*.jpg);;BMP图片(*.bmp)"));
    if(!filePathName.isEmpty()){
        String ba=filePathName.toStdString();
        int si=ba.size();
        charfilePathName=new char[si];
        for(int i=0;i!=si;++i){
            charfilePathName[i]=ba[i];
        }
        charfilePathName[si]='\0';
        img=cvLoadImage(charfilePathName);
        if(img && img->imageData){
            revoke.push(img);
            qimg=Ipl2Q(img);
            width=qimg.width();
            height=qimg.height();
            zoom=1.0;
            ui->showpic->resize(qimg.width(),qimg.height());
            this->setFixedSize(qimg.width(),qimg.height());
            ui->showpic->setPixmap(QPixmap::fromImage(qimg));
        }
        else{
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setIcon(QMessageBox::Critical);
            box.setText(QString::fromUtf8("打开图片失败!"));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
    }
    else{
        return;
    }
}

void PicDealMain::on_IDM_SAVE_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
    }
    else{
        filePathName=QFileDialog::getSaveFileName(this,QString::fromUtf8("保存图片"), ".",QString::fromUtf8("PNG图片(*.png);;JPG图片(*.jpg);;BMP图片(*.bmp)"));
        if(!filePathName.isEmpty()){
            String ba=filePathName.toStdString();
            int si=ba.size();
            charfilePathName=new char[si];
            for(int i=0;i!=si;++i){
                charfilePathName[i]=ba[i];
            }
            charfilePathName[si]='\0';
            cvSaveImage(charfilePathName,img);
        }
        else{
            return;
        }
    }
}

void PicDealMain::on_IDM_EXIT_triggered()
{
    if(img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("提示"));
        box.setIcon(QMessageBox::Warning);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("是否保存当前图片?"));
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int result=box.exec();
        if(result == QMessageBox::Yes){
            this->on_IDM_SAVE_triggered();
            QMainWindow::close();
        }
        else if(result == QMessageBox::No){
            QMainWindow::close();
        }
        else if(result == QMessageBox::Cancel){
            return;
        }
    }
    else{
        QMainWindow::close();
    }
}

void PicDealMain::on_IDM_ABORT_triggered()
{
    QMessageBox box;
    box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
    box.about(this,QString::fromUtf8("关于"),QString::fromUtf8("PicDeal  v1.0.1\n简单的图片处理程序"));
    return;
}

void PicDealMain::on_IDT_ZOOM_IN_triggered()
{
    if(!img){
        return;
    }
    zoom+=0.1;
    qimg_zo=qimg.scaled(width*zoom,height*zoom);
    ui->showpic->resize(qimg_zo.width(),qimg_zo.height());
    this->setFixedSize(qimg_zo.width(),qimg_zo.height());
    ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
}

void PicDealMain::on_IDT_ZOOM_OUT_triggered()
{
    if(!img){
        return;
    }
    zoom-=0.1;
    qimg_zo=qimg.scaled(width*zoom,height*zoom);
    ui->showpic->resize(qimg_zo.width(),qimg_zo.height());
    this->setFixedSize(qimg_zo.width(),qimg_zo.height());
    ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
}

void PicDealMain::on_IDT_ZOOM_RE_triggered()
{
    if(!img){
        return;
    }
    zoom=1.0;
    qimg_zo=qimg.scaled(width*zoom,height*zoom);
    ui->showpic->resize(qimg_zo.width(),qimg_zo.height());
    this->setFixedSize(qimg_zo.width(),qimg_zo.height());
    ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
}

void PicDealMain::close(){
    if(img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("提示"));
        box.setIcon(QMessageBox::Warning);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("是否保存当前图片?"));
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int result=box.exec();
        if(result == QMessageBox::Yes){
            this->on_IDM_SAVE_triggered();
            QMainWindow::close();
        }
        else if(result == QMessageBox::No){
            QMainWindow::close();
        }
        else if(result == QMessageBox::Cancel){
            return;
        }
    }
    else{
        QMainWindow::close();
    }
}

void PicDealMain::on_IDT_REVOKE_triggered()
{
    if(!revoke.isEmpty()){
        redo.push(img);
        img=revoke.pop();
        qimg=Ipl2Q(img);
        qimg_zo=qimg.scaled(width*zoom,height*zoom);
        ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
    }
    else{
        return;
    }
}

void PicDealMain::on_IDT_REDO_triggered()
{
    if(!redo.isEmpty()){
        revoke.push(img);
        img=redo.pop();
        qimg=Ipl2Q(img);
        qimg_zo=qimg.scaled(width*zoom,height*zoom);
        ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
    }
    else{
        return;
    }
}

void PicDealMain::on_IDM_AVG_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    QAvgDialog dlg;
    dlg.exec();
    if(dlg.bncl==0){
        return;
    }
    else if(dlg.bncl==1){
            IplImage* newimg=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
            smooth(img,newimg,dlg.result,dlg.result);
            if(!newimg || !newimg->imageData){
                QMessageBox box;
                box.setWindowTitle(QString::fromUtf8("错误"));
                box.setIcon(QMessageBox::Critical);
                box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
                box.setText(QString::fromUtf8("处理失败 "));
                box.setStandardButtons(QMessageBox::Yes);
                box.exec();
                return;
            }
            else{
                revoke.push(img);
                img=newimg;
                qimg=Ipl2Q(img);
                qimg_zo=qimg.scaled(width*zoom,height*zoom);
                ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
            }
    }
}

void PicDealMain::on_IDM_FILTER_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    QFilDialog dlg;
    dlg.exec();
    if(dlg.bncl==0){
        return;
    }
    else if(dlg.bncl==1){
        IplImage* newimg=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
        filter(img,newimg,dlg.result,dlg.result);
        if(!newimg || !newimg->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败 "));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        else{
            revoke.push(img);
            img=newimg;
            qimg=Ipl2Q(img);
            qimg_zo=qimg.scaled(width*zoom,height*zoom);
            ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
        }
    }
}

void PicDealMain::on_IDM_CONTRAST_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    QConDialog dlg;
    dlg.exec();
    if(dlg.bncl==0){
        return;
    }
    else{
        int contrast=dlg.contrast;
        int lighdm=dlg.lighdm;
        IplImage* dst=connlig(img,contrast,lighdm);
        if(!dst && !dst->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败 "));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        revoke.push(img);
        img=dst;
        qimg=Ipl2Q(img);
        qimg_zo=qimg.scaled(width*zoom,height*zoom);
        ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
        qDebug()<<1;
    }
}

void PicDealMain::on_IDM_EDGEDET_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    QCannyDialog dlg;
    dlg.exec();
    if(dlg.bncl==0){
        return;
    }
    else{
        int numa,numb,numc;
        bool predeal;
        numa=dlg.numa;
        numb=dlg.numb;
        numc=dlg.numc;
        predeal=dlg.pre;
        IplImage* newimg=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
        canny(img,newimg,numa,numb,numc,predeal);
        if(!newimg || !newimg->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败 "));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        else{
            QCannyShwDialog* shwdlg=new QCannyShwDialog(this);
            shwdlg->setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            shwdlg->setModal(false);
            shwdlg->show();
            shwdlg->cannyshowpic(newimg);
        }
    }
}

void PicDealMain::on_IDM_PSECOL_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    QPescolDialog dlg;
    dlg.exec();
    if(dlg.bncl==0){
        return;
    }
    else{
        IplImage* newimg=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
        colenhance(img,newimg,dlg.result);
        if(!newimg || !newimg->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败 "));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        else{
            revoke.push(img);
            img=newimg;
            qimg=Ipl2Q(img);
            qimg_zo=qimg.scaled(width*zoom,height*zoom);
            ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
        }
    }
}

void PicDealMain::on_IDM_FFT_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    QFFTDialog* dlg1=new QFFTDialog(this);
    QFFTDialog* dlg2=new QFFTDialog(this);
    dlg1->setModal(false);
    dlg2->setModal(false);
    dlg1->show();
    dlg1->fftshowpic(img);
    dlg2->show();
    dlg2->fftshowpic(img);
}

void PicDealMain::on_IDM_SPIN_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    QRolDialog dlg;
    dlg.exec();
    if(dlg.bncl==0){
        return;
    }
    else{
        int degree=dlg.degree;
        IplImage* dst=rotate(img,degree);
        if(!dst && !dst->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败 "));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        revoke.push(img);
        img=dst;
        qimg=Ipl2Q(img);
        qimg_zo=qimg.scaled(width*zoom,height*zoom);
        ui->showpic->resize(qimg_zo.width(),qimg_zo.height());
        this->setFixedSize(qimg_zo.width(),qimg_zo.height());
        ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
    }
}

void PicDealMain::on_IDM_ZOOM_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    else{
        QZoomDialog dlg;
        dlg.exec();
        if(dlg.bncl==0){
            return;
        }
        else{
            int zoomNum=dlg.zoomNum;
            qDebug()<<zoomNum;
        }
    }
}

void PicDealMain::on_IDM_CUT_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    else{
        QCutDialog dlg;
        dlg.setWiAnHei(img);
        dlg.exec();
        if(dlg.bncl==0){
            return;
        }
        else{
            int ltx,lty,rbx,rby;
            ltx=dlg.lfx;
            lty=dlg.lfy;
            rbx=dlg.rbx;
            rby=dlg.rby;
            qDebug()<<ltx<<" "<<lty<<" "<<rbx<<" "<<rby<<" ";
        }
    }
}

void PicDealMain::on_IDM_RGB2GRAY_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    else{
        IplImage* NewImage;
        NewImage=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
        rgb2gray(img,NewImage);
        if(!NewImage || !NewImage->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败 "));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        else{
            revoke.push(img);
            img=NewImage;
            qimg=Ipl2Q(img);
            qimg_zo=qimg.scaled(width*zoom,height*zoom);
            ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
        }
    }
}

void PicDealMain::on_IDM_HISTOGRAM_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    else{
        IplImage* NewImage;
        NewImage=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
        histoequ(img,NewImage);
        if(!NewImage || !NewImage->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败 "));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        else{
            revoke.push(img);
            img=NewImage;
            qimg=Ipl2Q(img);
            qimg_zo=qimg.scaled(width*zoom,height*zoom);
            ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
        }
    }
}

void PicDealMain::on_IDM_FACE_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    else{
        IplImage* NewImage=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
        facedetect(img,NewImage);
        if(!NewImage || !NewImage->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败!"));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        else{
            revoke.push(img);
            img=NewImage;
            qimg=Ipl2Q(img);
            qimg_zo=qimg.scaled(width*zoom,height*zoom);
            ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
        }
    }
}

void PicDealMain::on_IDM_SHOWHIS_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }

    IplImage* hist=histogram(img);
        if(!hist || !hist->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败 "));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        else{
            QCannyShwDialog* shwdlg=new QCannyShwDialog(this);
            shwdlg->setWindowTitle(QString::fromUtf8("灰度直方图 "));
            shwdlg->setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            shwdlg->setModal(false);
            shwdlg->show();
            shwdlg->cannyshowpic(hist);
        }
}

void PicDealMain::on_IDM_LAPLACE_triggered()
{
    if(!img){
        QMessageBox box;
        box.setWindowTitle(QString::fromUtf8("错误"));
        box.setIcon(QMessageBox::Critical);
        box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
        box.setText(QString::fromUtf8("当前没有任何图片!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
        return;
    }
    else{
        IplImage* NewImage=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
        laplace(img,NewImage);
        if(!NewImage || !NewImage->imageData){
            QMessageBox box;
            box.setWindowTitle(QString::fromUtf8("错误"));
            box.setIcon(QMessageBox::Critical);
            box.setWindowIcon(QIcon(":/resources/PicDeal.ico"));
            box.setText(QString::fromUtf8("处理失败!"));
            box.setStandardButtons(QMessageBox::Yes);
            box.exec();
            return;
        }
        else{
            revoke.push(img);
            img=NewImage;
            qimg=Ipl2Q(img);
            qimg_zo=qimg.scaled(width*zoom,height*zoom);
            ui->showpic->setPixmap(QPixmap::fromImage(qimg_zo));
        }
    }
}
