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

    int getRedValue(QString File);
    void setRedValue(int red_val, QString File);
    int getBlueValue(QString File);
    void setBlueValue(int red_val, QString File);
    int getGreenValue(QString File);
    void setGreenValue(int red_val, QString File);
    bool getVisibility();
    void setVisibility(bool status);

    //--------------------------------------------------

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
