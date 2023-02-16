#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QDebug>
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
    //--------------------------------------------------

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
