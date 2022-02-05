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
    this->setCentralWidget(myWidget);

    auto* quit = new QAction ("&Quit",this);
    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(quit);
    connect (quit, &QAction::triggered, qApp, QApplication::quit);

    auto* save = new QAction("Save",this);
    file->addAction(save);
    connect(save, SIGNAL(triggered()),this, SLOT(saveJson()));
}

void MainWindow::saveJson()
{
    myWidget->storeSelection(); //This stores all the fields in respective variables

    //If any of the fields are empty show a message asking for input
    //If they are not empty, then invoke the saveJson method

    if (!(myWidget->fieldIsEmpty())){
       myWidget->saveJson();
    }
}
