#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

private:
    Widget* myWidget = new Widget(this);

public slots:
    void saveJson();

};

#endif // MAINWINDOW_H
