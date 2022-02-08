#include "view.h"
#include <QPoint>
#include <QMouseEvent>
#include <QMenu>
#include <QPoint>
#include <QToolBar>
#include <QVBoxLayout>
#include <QPixmap>
#include <QIcon>


View::View(QWidget *parent)
    : QGraphicsView{parent}
{
    setupView();
}

void View::setupView()
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    //This connects the request for a context menu to an actual context menu
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(ShowContextMenu(QPoint)));
    createToolbar();
}

void View::createToolbar()
{
    //Load pixmaps
    QPixmap zoomInPixmap("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/images/zoomIn.png");
    QPixmap zoomOutPixmap("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/images/zoomOut.png");
    QPixmap zoomToFitPixmap("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/images/zoomToFit.png");
    //Create Toolbar
    auto tb = new QToolBar();
    //Create actions and connect to respective slots
    auto zoomIn = tb->addAction(QIcon(zoomInPixmap),"Zoom In");
    connect(zoomIn, &QAction::triggered,this, &View::zoomIn);

    auto zoomOut = tb->addAction(QIcon(zoomOutPixmap),"Zoom Out");
    connect(zoomOut, &QAction::triggered,this, &View::zoomOut);

    auto fitToExtents = tb->addAction(QIcon(zoomToFitPixmap),"Fit To Extents");
    connect(fitToExtents, &QAction::triggered,this, &View::fitToExtents);


    auto dockLayout = new QVBoxLayout();
    dockLayout->setMenuBar(tb); //
    this->setLayout(dockLayout);
}

QSize View::sizeHint() const
{
    return QSize(400,600);
}

void View::wheelEvent(QWheelEvent *event)
{
    if (event->delta()> 0) zoomIn();
    else zoomOut();
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
    connect(&action1, SIGNAL(triggered()),this->scene(), SLOT(clear()));
    contextMenu.addAction(&action1);

    contextMenu.exec(mapToGlobal(pos));
}

void View::zoomIn()
{
    scale(1.1,1.1);

}

void View::zoomOut()
{
    scale (0.9,0.9);
}

void View::fitToExtents()
{
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
