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

QString OptionDialog::getFileName()
{
    return ui->lineEdit->text();
}

void OptionDialog::placeholderTextName()
{
    ui->lineEdit->setPlaceholderText("Enter File Name:");
}

void OptionDialog::setFileName(QString filename)
{
    ui->lineEdit->setText(filename);
}

int OptionDialog::getRedValue(QString File)
{
    return ui->spinBox->value();
}

void OptionDialog::setRedValue(int red_val, QString File)
{
    ui->spinBox->setValue(red_val);
}

int OptionDialog::getBlueValue(QString File)
{
    return ui->spinBox_2->value();
}

void OptionDialog::setBlueValue(int blue_val, QString File)
{
    ui->spinBox_2->setValue(blue_val);
}

int OptionDialog::getGreenValue(QString File)
{
    return ui->spinBox_3->value();
}

void OptionDialog::setGreenValue(int green_val, QString File)
{
    ui->spinBox_3->setValue(green_val);
}

bool OptionDialog::getVisibility()
{
    return ui->checkBox_3->checkState();
}

void OptionDialog::setVisibility(bool status)
{
    ui->checkBox_3->setChecked(status);
}

