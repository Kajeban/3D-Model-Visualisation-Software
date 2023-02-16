#include "optiondialog.h"
#include "ui_optiondialog.h"


OptionDialog::OptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDialog)
{
    ui->setupUi(this);

    //-----------------------------------------------
    ui->lineEdit->text();
    //-----------------------------------------------
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

QString OptionDialog::getFileName()
{
    //return ui->textEdit_5->toPlainText();
    return ui->lineEdit->text();
}


