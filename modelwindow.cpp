#include "modelwindow.h"
#include <QPainter>

ModelWindow::ModelWindow(QWidget *parent)
    : QWidget{parent}
{

}

QSize ModelWindow::sizeHint() const
{
    return QSize(400,200);
}

QSize ModelWindow::minimumSizeHint() const
{
    return QSize(500,300);
}

void ModelWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawRect(50,50,120,120);
}
