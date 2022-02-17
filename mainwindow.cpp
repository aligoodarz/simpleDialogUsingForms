#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setCentralWidget(myWidget);
    this->setFixedSize(800,550);
    createMenuBar(); //Creates the menuBar and adds actions to it
    createStatusBar(); //Initializes the statusBar
}


void MainWindow::createMenuBar()
{
    //Create the file menu
    QMenu* fileMenu = menuBar()->addMenu("File");

    //Create the quit action and add into file menu
    auto* quit = new QAction ("Quit",this);
    fileMenu->addAction(quit);
    connect (quit, &QAction::triggered, qApp, QApplication::quit);

    //Create the save action and add into file menu
    auto* saveJsonFile = new QAction("Save",this);
    fileMenu->addAction(saveJsonFile);
    connect(saveJsonFile, &QAction::triggered,myWidget, &Widget::saveJson);

    //Create the clearJson action and into file menu
    auto* clearJsonFile = new QAction("Clear JSON File",this);
    fileMenu->addAction(clearJsonFile);
    connect(clearJsonFile,&QAction::triggered,myWidget, &Widget::clearJson);

    //Create a view menu
    QMenu* viewMenu = menuBar()->addMenu("View");

    //Create clear view action
    auto* clearView = new QAction ("Clear View",this);
    viewMenu->addAction(clearView);
    connect(clearView, &QAction::triggered,myWidget->scene,&CustomScene::clear);


}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(""); //Initialize the empty statusBar
}

QSize MainWindow::sizeHint() const
{
    return QSize(800,500);
}




