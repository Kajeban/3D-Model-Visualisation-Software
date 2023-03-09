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

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{  
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();

    //--------------------------------------------------
    QString getFileName();
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
