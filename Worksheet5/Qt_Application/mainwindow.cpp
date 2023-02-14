#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    //--------------------------------------------------
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    //--------------------------------------------------

    //--------------------------------------------------
    /* Create / allocate the ModelList */
    this->partList = new ModelPartList("PartsList");

    /* Link it to the treeview in the GUI */
    ui->treeView->setModel(this->partList);

    ModelPart* rootItem = this->partList->getRootItem();

    /* Add 3 top level items */
    for (int i = 0; i < 3; i++)
    {
        /* Create strings for both data columns */
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        /* Create Child Item */
        ModelPart* childItem = new ModelPart({ name, visible });

        /* Append to tree top-level */
        rootItem->appendChild(childItem);

        /* Add 5 sub-items */
        for (int j = 0; j < 5; j++)
        {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({ name,visible });

            /* Append to parent */
            childItem->appendChild(childChildItem);
        }
    }
    //--------------------------------------------------
}



MainWindow::~MainWindow()
{
    delete ui;
}
//--------------------------------------------------
void MainWindow::handleButton()
{
    emit statusUpdateMessage(QString("Add Button was Clicked"), 0);
}

void MainWindow::handleButton2()
{
    emit statusUpdateMessage(QString("Add Button was Clicked"), 0);
}
//--------------------------------------------------


