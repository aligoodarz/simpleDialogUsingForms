#include "view.h"
#include <QPoint>
#include <QMouseEvent>
#include <QMenu>
#include <QPoint>


View::View(QWidget *parent)
    : QGraphicsView{parent}
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
}

void View::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
        scale(1.1,1.1);
    else
        scale(0.9,0.9);
}

void View::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        rotate(-1);
    else if(event->key() == Qt::Key_Right)
        rotate(1);
}

void View::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::RightButton)
    {
        ShowContextMenu(event->pos());
    }
}

void View::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context Menu"),this);

    QAction action1("Clear", this);
    connect(&action1, SIGNAL(triggered()),this, SLOT(clearView()));
    contextMenu.addAction(&action1);

    contextMenu.exec(mapToGlobal(pos));
}

void View::clearView()
{
    this->scene()->clear();
}
