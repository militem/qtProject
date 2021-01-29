#include "newactivitydialog.h"
#include "ui_newactivitydialog.h"

NewActivityDialog::NewActivityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewActivityDialog)
{
    ui->setupUi(this);
}

NewActivityDialog::~NewActivityDialog()
{
    delete ui;
}

QString NewActivityDialog::getNameActivity()
{
    return ui->lineEdit->text();
}

void NewActivityDialog::on_buttonBox_accepted()
{
    accept();
}

void NewActivityDialog::on_buttonBox_rejected()
{
    reject();
}
