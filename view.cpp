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
    //This connects the request for a context menu to an actual context menu
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(ShowContextMenu(QPoint)));

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
    QGraphicsView::mousePressEvent(event);
}

void View::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context Menu"),this);

    //This includes the code for clearing the screen
    QAction action1(tr("Clear"), this);
    connect(&action1, SIGNAL(triggered()),this, SLOT(clearView()));
    contextMenu.addAction(&action1);

    //This is the code for annotating the figures
    QAction action2(tr("Annotate"),this);
    connect(&action2, SIGNAL(triggered()), this, SLOT(annotate()));
    contextMenu.addAction(&action2);


    contextMenu.exec(mapToGlobal(pos));
}

void View::drawForeground(QPainter *painter, const QRectF &rect)
{
//    painter->drawRect(20,20,20,20);
}

void View::clearView()
{
    this->scene()->clear();
}

void View::annotate()
{
    this->scene()->addText("Hello");
    //Can add a painting function here
    this->scene()->addRect(100,100,100,100);
}
