#include "newtabledialog.h"
#include "ui_newtabledialog.h"

NewTableDialog::NewTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTableDialog)
{
    ui->setupUi(this);
    configureSpinBox(ui->rows, 0, INT_MAX);
    configureSpinBox(ui->cols, 0, INT_MAX);
}

NewTableDialog::~NewTableDialog()
{
    delete ui;
}

int NewTableDialog::getRowsCount() const
{
    return ui->rows->value();
}

int NewTableDialog::getColsCount() const
{
    return ui->cols->value();
}

void NewTableDialog::on_buttonBox_accepted()
{
    accept();
}

void NewTableDialog::on_buttonBox_rejected()
{
    reject();
}

void NewTableDialog::configureSpinBox(QSpinBox *spinBox, int min, int max) const
{
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
}
