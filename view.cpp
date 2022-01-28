#include "view.h"

View::View(QWidget *parent)
    : QGraphicsView{parent}
{
    setDragMode(QGraphicsView::ScrollHandDrag);
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
