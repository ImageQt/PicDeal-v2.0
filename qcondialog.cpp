#include "qcondialog.h"
#include "ui_qcondialog.h"

QConDialog::QConDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QConDialog)
{
    ui->setupUi(this);
    ui->sli_contrast->setMaximum(10);
    ui->sli_contrast->setMinimum(0);
    ui->sli_lighdm->setMaximum(10);
    ui->sli_lighdm->setMinimum(0);
    contrast=-1;
    lighdm=-1;
    bncl=0;
}

QConDialog::~QConDialog()
{
    delete ui;
}

void QConDialog::on_BNOK_clicked()
{
    bncl=1;
    this->close();
}

void QConDialog::on_BNCAL_clicked()
{
    bncl=0;
    this->close();
}

void QConDialog::on_sli_contrast_valueChanged(int value)
{
    contrast=value;
}

void QConDialog::on_sli_lighdm_valueChanged(int value)
{
    lighdm=value;
}
