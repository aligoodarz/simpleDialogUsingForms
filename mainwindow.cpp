#include "mainwindow.h"
#include <QToolBar>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
//    QToolBar *toolbar = addToolBar("main toolbar");
//    toolbar->addAction("New File");
//    toolbar->addAction("Open File");
//    toolbar->addSeparator();

    auto* quit = new QAction ("&Quit",this);
    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(quit);
    connect (quit, &QAction::triggered, qApp, QApplication::quit);

//    auto* save = new QAction()
}
