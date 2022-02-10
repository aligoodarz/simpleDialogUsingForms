#include "view.h"
#include <QPoint>
#include <QMouseEvent>
#include <QMenu>
#include <QPoint>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QIcon>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <customscene.h>


View::View(QWidget *parent)
    : QGraphicsView{parent}, tool(Cursor),
      drawing(false)
{
    setupView();
}

void View::setupView()
{
//    setDragMode(QGraphicsView::ScrollHandDrag);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    //This connects the request for a context menu to an actual context menu
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(ShowContextMenu(QPoint)));
    createToolbar();
    this->setFrameShape(QGraphicsView::NoFrame);
}

void View::createToolbar()
{
    //Load pixmaps
    QPixmap zoomInPixmap("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/images/zoomIn.png");
    QPixmap zoomOutPixmap("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/images/zoomOut.png");
    QPixmap zoomToFitPixmap("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/images/zoomToFit.png");
    QPixmap drawPixmap("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/images/draw.png");
    QPixmap mousePixmap("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/images/mouse_pointer.png");
    //Create Toolbar
    auto tb = new QToolBar();
    //Create actions and connect to respective slots
    auto zoomIn = tb->addAction(QIcon(zoomInPixmap),"Zoom In");
    connect(zoomIn, &QAction::triggered,this, &View::zoomIn);

    auto zoomOut = tb->addAction(QIcon(zoomOutPixmap),"Zoom Out");
    connect(zoomOut, &QAction::triggered,this, &View::zoomOut);

    auto fitToExtents = tb->addAction(QIcon(zoomToFitPixmap),"Fit To Extents");
    connect(fitToExtents, &QAction::triggered,this, &View::fitToExtents);

    auto penActive = tb->addAction(drawPixmap,"Pen");
    connect(penActive, &QAction::triggered,[this](){
        tool = Pen;
        setDragMode(QGraphicsView::NoDrag);
        setStatusTip("Pen Selected");
    });

    auto cursorActive = tb->addAction(mousePixmap,"Cursor");
    connect(cursorActive, &QAction::triggered,[this](){
        tool = Cursor;
        setDragMode(QGraphicsView::ScrollHandDrag);
        setStatusTip("Cursor Selected");
    });



    auto dockLayout = new QVBoxLayout();
    dockLayout->setMenuBar(tb); //
    this->setLayout(dockLayout);
}

QSize View::sizeHint() const
{
    return QSize(400,600);
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton) && drawing){
        if (tool == ToolType::Pen){
            lineGroup = nullptr;
            drawing = false;
        }else
            QGraphicsView::mouseReleaseEvent(event);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing){
        if (tool == ToolType::Pen){
            drawLineTo(mapToScene(event->pos()));
        }
    }else
        QGraphicsView::mouseMoveEvent(event);
}

void View::drawLineTo(const QPointF &endPoint)
{
    if (!lineGroup){
        lineGroup = new QGraphicsItemGroup();
        lineGroup->setFlags(QGraphicsItem::ItemIsMovable /*| QGraphicsItem::ItemIsSelectable*/);
        this->scene()->addItem(lineGroup);
        lastPenPoint = startingPoint;
    }
    auto localLine = new QGraphicsLineItem(QLineF(lastPenPoint,endPoint));
    QPen mPen;
    mPen.setWidth(3);
    mPen.setColor(Qt::red);
    localLine->setPen(mPen);
    lineGroup->addToGroup(localLine);

    lastPenPoint = endPoint;
}


View::ToolType View::getTool() const
{
    return tool;
}

void View::setTool(ToolType newTool)
{
    tool = newTool;
}

void View::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    painter->resetTransform();

    painter->drawText(300,460,"Units: ");
    painter->drawText(329,460,units);
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
    else
        QGraphicsView::keyPressEvent(event);
}

void View::mousePressEvent(QMouseEvent *event)
{
//    s
    if (event->button()==Qt::RightButton)
    {
        ShowContextMenu(event->pos());
    }if(event->button() == Qt::LeftButton){
        if (tool == ToolType::Pen){
            startingPoint = mapToScene(event->pos());
            drawing = true;
        }

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
