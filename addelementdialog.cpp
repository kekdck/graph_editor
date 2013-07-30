#include "addelementdialog.h"
#include "ui_addelementdialog.h"

addElementDialog::addElementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addElementDialog)
{
    ui->setupUi(this);
}

addElementDialog::~addElementDialog()
{
    delete ui;
}

void addElementDialog::on_buttonBox_accepted()
{

}
