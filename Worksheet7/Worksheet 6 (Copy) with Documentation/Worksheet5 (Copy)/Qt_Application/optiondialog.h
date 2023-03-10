#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <qmessagebox.h>
#include "ModelPart.h"
#include "ModelPartList.h"

/** @file
* This file contains the declarations of all functions and constructors used for the Options Dialog Box.
*/

/*
* @brief OptionDialog class used for Option Dialog Box Manipulations
*/

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{  
    Q_OBJECT

public:
    /**
    * Creates new Option Dialog object
    * @brief Default Constructor
    */
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();

    //--------------------------------------------------
    /** Getting File Name
    * This function gets the text the user enters in the Option Dialog box and stores it as a QString 
    * @return The text the user enters
    */
    QString getFileName();

    /**
    * Set Placeholder Text 
    * This functions sets text that will be in the textbox when the user opens Option Dialog Box
    */

    void placeholderTextName();
    void setFileName(QString file);

    int getRedValue();
    void setRedValue(int red_val);
    int getBlueValue();
    void setBlueValue(int red_val);
    int getGreenValue();
    void setGreenValue(int red_val);
    bool getCheckBox();
    void setCheckBox(bool status);

    //--------------------------------------------------

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
