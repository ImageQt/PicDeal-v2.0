#include "qroldialog.h"
#include "ui_qroldialog.h"
#include <QMessageBox>

QRolDialog::QRolDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRolDialog)
{
    ui->setupUi(this);
    degree=0;
    bncl=0;
}

QRolDialog::~QRolDialog()
{
    delete ui;
}

void QRolDialog::on_degreedit_textChanged(const QString &arg1)
{
    QString str=ui->degreedit->text();
    degree=str.toInt();
}

void QRolDialog::on_BNOK_clicked()
{
    if(degree<0 || degree>360){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("旋转度数应在 0-360 度之间!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
    }
    else{
        bncl=1;
        this->close();
    }
}

void QRolDialog::on_BNCAL_clicked()
{
    bncl=0;
    this->close();
}
