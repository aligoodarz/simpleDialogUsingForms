#include "mainwindow.h"
#include <QToolBar>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include "widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setCentralWidget(myWidget);
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
    connect(saveJsonFile, SIGNAL(triggered()),myWidget, SLOT(saveJson()));

    //Create the clearJson action and into file menu
    auto* clearJsonFile = new QAction("Clear JSON File",this);
    fileMenu->addAction(clearJsonFile);
    connect(clearJsonFile,SIGNAL(triggered()),myWidget, SLOT(clearJson()));

    //Create a view menu
    QMenu* viewMenu = menuBar()->addMenu("View");

    //Create fit to extents action
    auto* fitToExtents = new QAction ("Fit To Extents",this);
    viewMenu->addAction(quit);


}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(""); //Initialize the statusBar
}


