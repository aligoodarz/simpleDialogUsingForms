#include "mainwindow.h"
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    QToolBar *toolbar = addToolBar("main toolbar");
    toolbar->addAction("New File");
    toolbar->addAction("Open File");
    toolbar->addSeparator();
}
