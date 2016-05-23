#include "qcannydialog.h"
#include "ui_qcannydialog.h"
#include <QMessageBox>

QCannyDialog::QCannyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCannyDialog)
{
    ui->setupUi(this);
    numa=0;
    numb=0;
    numc=0;
    pre=false;
    bncl=0;
}

QCannyDialog::~QCannyDialog()
{
    delete ui;
}

void QCannyDialog::on_numA_textChanged(const QString &arg1)
{
    QString str=ui->numA->text();
    numa=str.toInt();
}

void QCannyDialog::on_numB_textChanged(const QString &arg1)
{
    QString str=ui->numB->text();
    numb=str.toInt();
}

void QCannyDialog::on_numC_textChanged(const QString &arg1)
{
    QString str=ui->numC->text();
    numc=str.toInt();
}

void QCannyDialog::on_predeal_clicked()
{
    if(ui->predeal->isChecked()){
        pre=true;
    }
    else{
        pre=false;
    }
}

void QCannyDialog::on_BNOK_clicked()
{
    if(numa>=numb){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("参数A应小于参数B!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
    }
    else if(numa>255 || numb>255){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("参数A和B应处于 0-255 之间!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
    }
    else if(numc<=0 || numc>13){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("算子内核应处于 1-13 之间!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
    }
    else{
        bncl=1;
        this->close();
    }
}


void QCannyDialog::on_BNCAL_clicked()
{
    bncl=0;
    this->close();
}
