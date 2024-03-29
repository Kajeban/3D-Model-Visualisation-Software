#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    //--------------------------------------------------
    ui->treeView->addAction(ui->actionItem_Options);
    //--------------------------------------------------

    //--------------------------------------------------
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);
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

    OptionDialog dialog(this);
    dialog.placeholderTextName();

    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    QString SelectedFileName = selectedPart->data(0).toString();
    
    dialog.setFileName(SelectedFileName);

    bool Visibility = selectedPart->visible();
    dialog.setCheckBox(Visibility);

    dialog.setRedValue(selectedPart->getColourR());
    dialog.setBlueValue(selectedPart->getColourB());
    dialog.setGreenValue(selectedPart->getColourG());

    if (dialog.exec() == QDialog::Accepted) 
    {
        // call a function in dialog to get information (string, colour)
        QString UserInput = dialog.getFileName();
   
        selectedPart->set(0, UserInput);
        QString FileName = selectedPart->data(0).toString();

        bool CheckBoxStatus = dialog.getCheckBox();
        selectedPart->setVisible(CheckBoxStatus);

        selectedPart->setColour(dialog.getRedValue(), dialog.getGreenValue(), dialog.getBlueValue());
        
        // Add that information to status update
        emit statusUpdateMessage(QString("File Name: ") + FileName, 0); 
    }
    else {
        emit statusUpdateMessage(QString("Dialog Rejected "), 0);
    }
}

void MainWindow::handleTreeClicked()
{

    /* Get the index of the selected item */
    QModelIndex index = ui->treeView->currentIndex();

    /* Get a pointer to the item from the index */
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    /* In this case, we will retrieve the name string from the internal QVariant data array */
    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);  

}
//--------------------------------------------------

//--------------------------------------------------
void MainWindow::on_actionOpen_File_triggered() {

    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    QString SelectedFileName = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("Open File action triggered"),0);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("STL Files(*.stl);;Text Files(*.txt)"));
    emit statusUpdateMessage(QString("File Name: ") + fileName, 0);
    QFileInfo info(fileName);
    QString FileNameNoPath = info.fileName();

    OptionDialog dialog(this);
    dialog.setFileName(FileNameNoPath);

    selectedPart->set(0, FileNameNoPath);
}
//--------------------------------------------------
void MainWindow::on_actionItem_Options_triggered()
{
    handleButton2();
}
//--------------------------------------------------

//--------------------------------------------------

//--------------------------------------------------
