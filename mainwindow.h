#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include "widget.h"
#include "customview.h"
#include "customscene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    Widget* myWidget = new Widget(this);
    void createMenuBar();
    void createStatusBar();

    // QWidget interface
public:
    QSize sizeHint() const override;
};

#endif // MAINWINDOW_H
