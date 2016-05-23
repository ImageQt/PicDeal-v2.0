#include "qzoomdialog.h"
#include "ui_qzoomdialog.h"
#include <QMessageBox>

QZoomDialog::QZoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QZoomDialog)
{
    ui->setupUi(this);
    zoomNum=0;
    bncl=0;
}

QZoomDialog::~QZoomDialog()
{
    delete ui;
}

void QZoomDialog::on_zoomnum_textChanged(const QString &arg1)
{
    QString str=ui->zoomnum->text();
    zoomNum=str.toInt();
}

void QZoomDialog::on_BNOK_clicked()
{
    if(zoomNum<0.3 || zoomNum>5){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("缩放倍数只能在0.3-5之间!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
    }
    else{
        bncl=1;
        this->close();
    }
}

void QZoomDialog::on_BNCAL_clicked()
{
    bncl=0;
    this->close();
}
