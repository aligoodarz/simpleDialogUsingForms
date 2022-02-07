#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

private:
    Widget* myWidget = new Widget(this);
    void createMenuBar();
    void createStatusBar();

public slots:

};

#endif // MAINWINDOW_H
