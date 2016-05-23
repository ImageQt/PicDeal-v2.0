#include "qavgdialog.h"
#include "ui_qavgdialog.h"
#include <QMessageBox>

QAvgDialog::QAvgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QAvgDialog)
{
    ui->setupUi(this);
    result=-1;
    bncl=0;
}

QAvgDialog::~QAvgDialog()
{
    delete ui;
}

void QAvgDialog::on_BNOK_clicked()
{
    if(!(result>0 && result<14)){
        QMessageBox box;
        box.setWindowTitle(tr("错误"));
        box.setWindowIcon(QIcon("F:\\PicDeal\\PicDeal\\resources\\PicDeal.ico"));
        box.setIcon(QMessageBox::Critical);
        box.setText(QString::fromUtf8("参数必须处于 1-13 之间!"));
        box.setStandardButtons(QMessageBox::Yes);
        box.exec();
    }
    else{
        bncl=1;
        this->close();
    }
}

void QAvgDialog::on_BNCAL_clicked()
{
    bncl=0;
    this->close();
}



void QAvgDialog::on_lineEdit_textChanged(const QString &arg1)
{
    QString str=ui->lineEdit->text();
    result=str.toInt();
}
