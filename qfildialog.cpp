#include "qfildialog.h"
#include "ui_qfildialog.h"
#include <QMessageBox>
QFilDialog::QFilDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QFilDialog)
{
    ui->setupUi(this);
    result=-1;
    bncl=0;
}

QFilDialog::~QFilDialog()
{
    delete ui;
}

void QFilDialog::on_lineEdit_textChanged(const QString &arg1)
{
    QString str=ui->lineEdit->text();
    result=str.toInt();
}

void QFilDialog::on_BNOK_clicked()
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

void QFilDialog::on_BNCAL_clicked()
{
    bncl=0;
    this->close();
}
