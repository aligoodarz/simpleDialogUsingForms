#include "mainwindow.h"
#include <QToolBar>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include "widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
//    QToolBar *toolbar = addToolBar("main toolbar");
//    toolbar->addAction("New File");
//    toolbar->addAction("Open File");
//    toolbar->addSeparator();
    statusBar()->showMessage(""); //Initialize the statusBar

    this->setCentralWidget(myWidget);

    auto* quit = new QAction ("&Quit",this);
    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(quit);
    connect (quit, &QAction::triggered, qApp, QApplication::quit);

    auto* saveJsonFile = new QAction("Save",this);
    file->addAction(saveJsonFile);
    connect(saveJsonFile, SIGNAL(triggered()),myWidget, SLOT(saveJson()));

    auto* clearJsonFile = new QAction("Clear JSON File",this);
    file->addAction(clearJsonFile);
    connect(clearJsonFile,SIGNAL(triggered()),myWidget, SLOT(clearJson()));
}

void MainWindow::createMenuBar()
{

}


