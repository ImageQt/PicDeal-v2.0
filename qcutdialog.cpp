#include "qcutdialog.h"
#include "ui_qcutdialog.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <QMessageBox>

using namespace std;
using namespace cv;

QCutDialog::QCutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCutDialog)
{
    ui->setupUi(this);
    lfx=-1;
    lfy=-1;
    rbx=-1;
    rby=-1;
    bncl=0;
    width=0;
    height=0;
}

QCutDialog::~QCutDialog()
{
    delete ui;
}

void QCutDialog::on_LT_X_textChanged(const QString &arg1)
{
    QString str=ui->LT_X->text();
    lfx=str.toInt();
}

void QCutDialog::on_LT_Y_textChanged(const QString &arg1)
{
    QString str=ui->LT_Y->text();
    lfy=str.toInt();
}

void QCutDialog::on_RB_X_textChanged(const QString &arg1)
{
    QString str=ui->RB_X->text();
    rbx=str.toInt();
}

void QCutDialog::on_RB_Y_textChanged(const QString &arg1)
{
    QString str=ui->RB_Y->text();
    rby=str.toInt();
}

void QCutDialog::setWiAnHei(IplImage *input){
    if(!input || !input->imageData){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("图片数据错误!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
    }
    else{
        width=input->width;
        height=input->height;
    }
}

void QCutDialog::on_BNOK_clicked()
{
    if(lfx<0 || lfy<0 || rbx>width || rby>height){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("所输入范围超出图片大小!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
    }
    else{
        bncl=1;
        this->close();
    }
}

void QCutDialog::on_BNCAL_clicked()
{
    bncl=0;
    this->close();
}
