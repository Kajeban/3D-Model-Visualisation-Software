#include "optiondialog.h"
#include "ui_optiondialog.h"


OptionDialog::OptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::placeholderTextName()
{
    ui->lineEdit->setPlaceholderText("Enter File Name:");
}

QString OptionDialog::getFileName()
{
    return ui->lineEdit->text();
}

void OptionDialog::setFileName(QString filename)
{
    ui->lineEdit->setText(filename);
}

//--------------------------------------------------------

bool OptionDialog::getCheckBox()
{
    return ui->checkBox_3->checkState();
}

void OptionDialog::setCheckBox(bool status)
{
    ui->checkBox_3->setChecked(status);
}

//---------------------------------------------------------

int OptionDialog::getRedValue()
{
    return ui->spinBox->value();
}

void OptionDialog::setRedValue(int red_val)
{
    ui->spinBox->setValue(red_val);
}

int OptionDialog::getBlueValue()
{
    return ui->spinBox_2->value();
}

void OptionDialog::setBlueValue(int blue_val)
{
    ui->spinBox_2->setValue(blue_val);
}

int OptionDialog::getGreenValue()
{
    return ui->spinBox_3->value();
}

void OptionDialog::setGreenValue(int green_val)
{
    ui->spinBox_3->setValue(green_val);
}