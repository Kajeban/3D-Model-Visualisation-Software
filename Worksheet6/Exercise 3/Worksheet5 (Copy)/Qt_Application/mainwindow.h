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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//--------------------------------------------------
public slots:
    void handleButton();
    void handleButton2();
    void handleTreeClicked();
    void on_actionOpen_File_triggered();
    void on_actionItem_Options_triggered();
    void ResetCamera();
    void updateRenderFromTree(const QModelIndex& index);
    void updateRender();
    void on_actionStart_VR_triggered();
    void on_actionStop_VR_triggered();
    void on_actionAdd_New_Item_triggered();

signals:
    void statusUpdateMessage(const QString& message, int timeout);
//--------------------------------------------------

private:
    Ui::MainWindow *ui;
    ModelPartList* partList;

    //********
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    //********
};

#endif // MAINWINDOW_H
