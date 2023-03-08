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
    ui->treeView->addAction(ui->actionAdd_New_Item);
    //--------------------------------------------------

    //--------------------------------------------------
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);

    //*******
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->vtkWidget->setRenderWindow(renderWindow);

    /* Add a renderer */
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    /* Create an object and add to renderer (this will change later to display a CAD Model) */
    /* Will just copy and paste cylinder example from before */
    // This creates a polygonal cylinder model with eight circumferential facets
    // (i.e, in practice an octagonal prism).
    vtkNew<vtkCylinderSource>cylinder;
    cylinder->SetResolution(8);

    //The Mapper is responsible for pushing the geometry into the graphics library.
    // It may also do colour mapping, if scalars or other attributes are defined
    vtkNew<vtkPolyDataMapper>cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    // The Actor is a grouping mechanism: besides the geometry (mapper), it also has a property,
    // transformation matrix, and/or texture map. Here we set its colour and rotate it around X and Y Axes
    vtkNew<vtkActor>cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1., 0., 0.35);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    renderer->AddActor(cylinderActor);
    //*******
    
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);
    //--------------------------------------------------

    //--------------------------------------------------
    /* Create / allocate the ModelList */
    this->partList = new ModelPartList("PartsList");

    /* Link it to the treeview in the GUI */
    ui->treeView->setModel(this->partList);

    ModelPart* rootItem = this->partList->getRootItem();

    QString name = QString("TopLevel 0");
    QString visible("true");

    // Create Child Item 
    ModelPart* childItem = new ModelPart({ name, visible });

    rootItem->appendChild(childItem);

    // Add 3 top level items 
    /* Commented out Empty Item Creations
    for (int i = 0; i < 3; i++)
    {
        // Create strings for both data columns 
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        // Create Child Item 
        ModelPart* childItem = new ModelPart({ name, visible });


        // Append to tree top-level 
        rootItem->appendChild(childItem);

        // Add 5 sub-items
        
        for (int j = 0; j < 5; j++)
        {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({ name,visible });

            // Append to parent 
            childItem->appendChild(childChildItem);
        }
    }*/
    //--------------------------------------------------
}

MainWindow::~MainWindow()
{
    delete ui;
}
//--------------------------------------------------
void MainWindow::handleButton()
{
    emit statusUpdateMessage(QString("New Item Option Triggered"), 0);

    on_actionAdd_New_Item_triggered();
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

    selectedPart->loadSTL(fileName);
    updateRender();
    ResetCamera();
}
//--------------------------------------------------
void MainWindow::on_actionItem_Options_triggered()
{
    handleButton2();
}
//--------------------------------------------------
void MainWindow::ResetCamera()
{
    // Reset Camera 
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();
}
//--------------------------------------------------
void MainWindow::updateRenderFromTree(const QModelIndex& index)
{
    if (index.isValid())
    {
        ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
        /* Retrieve actor from selected part and add to renderer */
        renderer->AddActor(selectedPart->getActor());
        renderer->ResetCamera();
        renderer->GetActiveCamera()->SetPosition(0, 0, 10);
        renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
        renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
        renderer->ResetCameraClippingRange();
    }

    /*Check to see if this part has any children */
    if (!partList->hasChildren(index) || (index.flags() & Qt::ItemNeverHasChildren))
    {
        return;
    }

    /* Loop through children and add their actors */
    int rows = partList->rowCount(index);
    for (int i = 0; i < rows; i++)
    {
        updateRenderFromTree(partList->index(i, 0, index));
    }
}
//--------------------------------------------------
void MainWindow::updateRender()
{
    renderer->RemoveAllViewProps();
    updateRenderFromTree(partList->index(0, 0, QModelIndex()));
    renderer->Render();
}
//--------------------------------------------------
void MainWindow::on_actionAdd_New_Item_triggered()
{
    emit statusUpdateMessage(QString("New Item Selection Triggered"), 0);

    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    QString name = QString("New Item");
    QString visible("true");

    ModelPart* childChildChildItem = new ModelPart({ name,visible });

    selectedPart->appendChild(childChildChildItem);
}
//--------------------------------------------------
void MainWindow::on_actionStart_VR_triggered()
{
    emit statusUpdateMessage(QString("Start VR Action Triggered"), 0);

    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    VRRenderThread* VR_Render = new VRRenderThread();

    /* Loop through children and add their actors */
    int rows = partList->rowCount(index);
    for (int i = 0; i < rows; i++)
    {
        QModelIndex newIndex = (partList->index(i, 0, index));
        ModelPart* selectedItem = static_cast<ModelPart*>(newIndex.internalPointer());

        VR_Render->addActorOffline(selectedItem->getNewActor());
    }

    VR_Render->start();

    //VRRenderThread* VR_Render = new VRRenderThread();
    //VR_Render->addActorOffline(selectedPart->getNewActor());

    VR_Render->start();

}
//--------------------------------------------------
void MainWindow::on_actionStop_VR_triggered()
{
    emit statusUpdateMessage(QString("Stop VR Action Triggered"), 0);
}
//--------------------------------------------------
void MainWindow::GetLights()
{
    light = vtkSmartPointer<vtkLight>::New();
    light->SetLightTypeToSceneLight();
    light->SetPosition(5, 5, 15);
    light->SetPositional(true);
    light->SetConeAngle(10);
    light->SetFocalPoint(0, 0, 0);
    light->SetDiffuseColor(1, 1, 1);
    light->SetAmbientColor(1, 1, 1);
    light->SetSpecularColor(1, 1, 1);
    light->SetIntensity(0.5);

    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    renderer->AddActor(selectedPart->getActor());

    renderer->AddActor(selectedPart->getActor());

    //ui->vtkWidget->GetRenderWindow()->Render();

    renderer->AddLight(light);
}
//--------------------------------------------------