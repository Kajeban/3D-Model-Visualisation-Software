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

/** @file optiondialog.h
* 
* EEEE2046 - Software Engineering & VR Project
* 
* This file contains the declarations of all functions and constructors used for the Options Dialog Box.
* 
* Kajeban Baskaran 2022
*/

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{  
    Q_OBJECT

public:
    /**
    * Creates new Option Dialog object.
    * Default Constructor.
    * @param parent not used
    */
    explicit OptionDialog(QWidget *parent = nullptr);

    /**
    * Destructor
    */
    ~OptionDialog();

    //--------------------------------------------------
    /** Getting File Name.
    * This function gets the text the user enters in the Option Dialog box and stores it as a QString
    * @return The text the user enters
    */
    QString getFileName();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Set Placeholder Text.
    * This functions sets text that will be in the textbox when the user opens Option Dialog Box.
    */
    void placeholderTextName();
    //--------------------------------------------------

    //--------------------------------------------------
    /** Setting File Name.
    * This function sets the text the user enters in the Option Dialog Box.
    * @param file is used to store the user input.
    */
    void setFileName(QString file);
    //--------------------------------------------------

    //--------------------------------------------------
    /** Getting Red Colour Value.
    * This functions gets the colour red value (a value between 0 and 255) the user enters in the Dialog Box.
    * @return The number from the Red Spin Box.
    */
    int getRedValue();
    //--------------------------------------------------

    //--------------------------------------------------
    /** Setting Red Colour Value.
    * This function sets the colour red value (a value between 0 and 255) so it is pre-typed in the spin box.
    * @param red_val is used to store new int value of red (0-255).
    */
    void setRedValue(int red_val);
    //--------------------------------------------------

    //--------------------------------------------------
    /** Getting Blue Colour Value.
    * This functions gets the colour blue value (a value between 0 and 255) the user enters in the Dialog Box.
    * @return The number from the Blue Spin Box.
    */
    int getBlueValue();
    //--------------------------------------------------

    //--------------------------------------------------
    /** Setting Blue Colour Value.
    * This function sets the colour blue value (a value between 0 and 255) so it is pre-typed in the spin box.
    * @param blue_val is used to store new int value of blue (0-255).
    */
    void setBlueValue(int blue_val);
    //--------------------------------------------------

    //--------------------------------------------------
    /** Getting Green Colour Value.
    * This functions gets the colour green value (a value between 0 and 255) the user enters in the Dialog Box.
    * @return The number from the Green Spin Box.
    */
    int getGreenValue();
    //--------------------------------------------------

    //--------------------------------------------------
    /** Setting Green Colour Value.
    * This function sets the colour green value (a value between 0 and 255) so it is pre-typed in the spin box.
    * @param green_val is used to store new int value of green (0-255).
    */
    void setGreenValue(int green_val);
    //--------------------------------------------------

    //--------------------------------------------------
    /** Getting Check Box Status.
    * This function gets the status of the check box (checked or not checked) and stores it as a bool.
    */
    bool getCheckBox();
    //--------------------------------------------------

    //--------------------------------------------------
    /** Setting Check Box Status.
    * This function sets the Check Box Status (checked or not checked). Used to pre-set status when saving data. 
    * @param status is used to store new check status.
    */
    void setCheckBox(bool status);
    //--------------------------------------------------

    //--------------------------------------------------

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
