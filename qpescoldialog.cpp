#include "qpescoldialog.h"
#include "ui_qpescoldialog.h"

QPescolDialog::QPescolDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPescolDialog)
{
    ui->setupUi(this);
    grp=new QButtonGroup(this);
    grp->addButton(ui->RGB);
    grp->addButton(ui->RBG);
    grp->addButton(ui->BRG);
    grp->addButton(ui->BGR);
    grp->addButton(ui->GRB);
    grp->addButton(ui->GBR);
    result=0;
    bncl=0;
}

QPescolDialog::~QPescolDialog()
{
    delete ui;
}

void QPescolDialog::on_RGB_clicked()
{
    result=1;
}

void QPescolDialog::on_RBG_clicked()
{
    result=2;
}

void QPescolDialog::on_BRG_clicked()
{
    result=3;
}

void QPescolDialog::on_BGR_clicked()
{
    result=4;
}

void QPescolDialog::on_GRB_clicked()
{
    result=5;
}

void QPescolDialog::on_GBR_clicked()
{
    result=6;
}

void QPescolDialog::on_BNOK_clicked()
{
    bncl=1;
    this->close();
}

void QPescolDialog::on_BNCAL_clicked()
{
    bncl=0;
    this->close();
}
