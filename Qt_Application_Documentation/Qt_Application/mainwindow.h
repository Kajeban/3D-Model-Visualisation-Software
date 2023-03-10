#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAction>
#include <QFileInfo>
#include "ModelPart.h"
#include "ModelPartList.h"
#include "QFileDialog.h"
#include "optiondialog.h"
#include "vtkRenderer.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkCamera.h"
#include "vtkPolyDataMapper.h"
#include "vtkCylinderSource.h"
#include "vtkProperty.h"
#include "VRRenderThread.h"

/** @file mainwindow.h
*
* EEEE2046 - Software Engineering & VR Project
*
* This file contains the declarations of all functions and constructors used for the Options Dialog Box.
*
* Kajeban Baskaran 2022
*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
    * Creates new Option Dialog object.
    * Default Constructor.
    * @param parent is the parent of this item (one level up in tree)
    */
    MainWindow(QWidget *parent = nullptr);

    /**
    * Destructor.
    */
    ~MainWindow();
//--------------------------------------------------
public slots:
    //--------------------------------------------------
    /**
    * Calls Push Button Function.
    * Used to run program when a push button is pressed.
    */
    void handleButton();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Calls Push Button Function.
    * Used to run program when a push button is pressed.
    */
    void handleButton2();
    //--------------------------------------------------

    //--------------------------------------------------
    void handleTreeClicked();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Open File Function.
    * Used to run program when the Open File open is triggered.
    */
    void on_actionOpen_File_triggered();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Open Item Options.
    * Used to run program when the Item Options Button is triggered.
    */
    void on_actionItem_Options_triggered();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Reset Camera Angle.
    * Used to reset camera angle when a new file is loaded from files.
    */
    void ResetCamera();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Update Items from Tree.
    * Used to refresh files from Tree and load it up to render.
    * @param index is used get the information of item selected
    */
    void updateRenderFromTree(const QModelIndex& index);
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Update Render View.
    * Used to update CAD view when a new file is opened.
    */
    void updateRender();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Start VR Button.
    * Used to run program when the Start VR button is pressed.
    */
    void on_actionStart_VR_triggered();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Stop VR Button.
    * Used to run program when the Stop VR button is pressed.
    */
    void on_actionStop_VR_triggered();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Adds new Item to the Tree.
    * Used to create new child item when this button is pushed.
    */
    void on_actionAdd_New_Item_triggered();
    //--------------------------------------------------

    //--------------------------------------------------
    /**
    * Get lights Function.
    * Used to add light to the scene.
    */
    void GetLights();
    //--------------------------------------------------

signals:
    //--------------------------------------------------
    /**
    * Status Message Updates.
    * Function to display text at the button to provide user with status updates.
    * @param message is the text outputted to the user.
    * @param timeout is the duration of the update message being displayed on the GUI.
    */
    void statusUpdateMessage(const QString& message, int timeout);
    //--------------------------------------------------
//--------------------------------------------------

private:
    Ui::MainWindow *ui;
    ModelPartList* partList;

    //********
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkLight> light;

    VRRenderThread* VR_Render;
    //********
};

#endif // MAINWINDOW_H
