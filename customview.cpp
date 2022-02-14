#include "customview.h"
#include <customscene.h>


CustomView::CustomView(QWidget *parent)
    : QGraphicsView{parent},
      drawing(false),
      tool(Cursor)
{
    setupView();
}

void CustomView::setupView()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //This connects the request for a context menu to an actual context menu
//    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
//            this, SLOT(ShowContextMenu(QPoint)));
    createToolbar(); //Create the toolbar and add actions to it
}

void CustomView::createToolbar()
{
    //Load pixmaps
    QString defaultDir = "C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/images/";
    QPixmap zoomInPixmap(defaultDir+"zoomIn.png");
    QPixmap zoomOutPixmap(defaultDir+"zoomOut.png");
    QPixmap zoomToFitPixmap(defaultDir+"zoomToFit.png");
    QPixmap zoomToItemPixmap(defaultDir+"fitToItem.png");
    QPixmap drawPixmap(defaultDir+"draw.png");
    QPixmap mousePixmap(defaultDir+"mouse_pointer.png");
    QPixmap eraserPixmap(defaultDir+"eraser.png");
    QPixmap deleteSelectionPixmap (defaultDir+"deleteSelection.png");
    QPixmap rectanglePixmap (defaultDir+"rectangle.png");
    //Create Toolbar
    auto tb = new QToolBar();
    //Create actions and connect to respective slots
    auto zoomIn = tb->addAction(QIcon(zoomInPixmap),"Zoom In");
    connect(zoomIn, &QAction::triggered,this, &CustomView::zoomIn);

    auto zoomOut = tb->addAction(QIcon(zoomOutPixmap),"Zoom Out");
    connect(zoomOut, &QAction::triggered,this, &CustomView::zoomOut);

    auto fitToExtents = tb->addAction(QIcon(zoomToFitPixmap),"Fit To Extents");
    connect(fitToExtents, &QAction::triggered,this, &CustomView::fitToExtents);

    auto fitToItem = tb->addAction(QIcon(zoomToItemPixmap),"Fit To Item");
    connect(fitToItem, &QAction::triggered,this, &CustomView::fitToItem);

    auto deleteSelection = tb->addAction(QIcon(deleteSelectionPixmap),"Delete Selection");
    connect(deleteSelection, &QAction::triggered,this,&CustomView::deleteSelectedItems);

    auto penActive = tb->addAction(drawPixmap,"Pen");
    connect(penActive, &QAction::triggered,this,[this](){
        tool = Pen;
        setDragMode(QGraphicsView::NoDrag);
        setStatusTip("Pen Selected");
    });

    auto drawRect = tb->addAction(rectanglePixmap,"Draw Rect");
    connect(drawRect, &QAction::triggered, this,[this](){
        tool = Rect;
        setDragMode(QGraphicsView::NoDrag);
        setStatusTip("Rect Selected");
    });

    auto cursorActive = tb->addAction(mousePixmap,"Cursor");
    connect(cursorActive, &QAction::triggered,this,[this](){
        tool = Cursor;
        setDragMode(QGraphicsView::ScrollHandDrag);
        setStatusTip("Cursor Selected");
    });

    auto eraserActive = tb->addAction(eraserPixmap,"Eraser");
    connect(eraserActive, &QAction::triggered,this,[this](){
        tool = Eraser;
        setDragMode(QGraphicsView::NoDrag);
        setStatusTip("Eraser Selected");
    });

    //add menu to the view
    auto dockLayout = new QVBoxLayout();
    dockLayout->setMenuBar(tb); //
    this->setLayout(dockLayout);
}

QSize CustomView::sizeHint() const
{
    return QSize(400,600);
}

void CustomView::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::RightButton)
    {
        ShowContextMenu(event->pos()); //Show context menu
    }if(event->button() == Qt::LeftButton){
        if (tool == ToolType::Pen || tool == ToolType::Eraser
                || tool == Rect || tool == Ellipse){
            setInteractive(false); //Added to disable selection when drawing
            startingPoint = mapToScene(event->pos()); //Pick the starting position
            drawing = true;
        }else{
            setInteractive(true); //Added to enable selection when not drawing
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void CustomView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing){
        if (tool == ToolType::Pen){
            drawLineTo(mapToScene(event->pos()));
        }else if ( tool == ToolType::Eraser){
            drawEraserAt(mapToScene(event->pos()));
        }else if (tool == ToolType::Rect) {
            drawShapeTo(mapToScene(event->pos()));
        }
    }else
        QGraphicsView::mouseMoveEvent(event);
}

void CustomView::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton) && drawing){
        if (tool == ToolType::Pen){
            lineGroup = nullptr;
            drawing = false;   

        }if(tool == ToolType::Eraser){
            scene()->removeItem(lastEraserCircle);
            delete lastEraserCircle;
            lastEraserCircle = nullptr;
            drawing = false;

        }if (lastItem && (tool == Rect)){
            this->scene()->removeItem(lastItem);
            delete lastItem; //Free memory

        }if (tool == Rect) {
            QGraphicsRectItem* mRect = new QGraphicsRectItem();
            mRect->setRect(QRectF(startingPoint, mapToScene(event->pos())).normalized());
            mRect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            this->scene()->addItem(mRect);
            lastItem = nullptr;
            drawing = false;
        }
        else
            QGraphicsView::mouseReleaseEvent(event);
    }
    QGraphicsView::mouseReleaseEvent(event);
}


void CustomView::drawLineTo(const QPointF &endPoint)
{
    if (!lineGroup){
        lineGroup = new QGraphicsItemGroup();
        lineGroup->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
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

void CustomView::drawEraserAt(const QPointF &endPoint)
{
    if (lastEraserCircle == nullptr){
        lastEraserCircle = this->scene()->addEllipse(0,0,20,20);
    }
    lastEraserCircle->setPos(endPoint - QPointF(lastEraserCircle->boundingRect().width()/2,
                                                lastEraserCircle->boundingRect().height()/2));
    eraseStrokesUnder(lastEraserCircle);
}

void CustomView::eraseStrokesUnder(QGraphicsEllipseItem *item)
{
    QList<QGraphicsItem *> itemsToErase = item->collidingItems();
    QList<QGraphicsItemGroup *> groupItems;

    foreach (QGraphicsItem* myItem, itemsToErase){
        QGraphicsItemGroup* group = dynamic_cast<QGraphicsItemGroup *>(myItem);
        if (group){
            groupItems.append(group);
        }

        //Cast o QGraphicsLineItem
        QGraphicsItem* line = dynamic_cast<QGraphicsItem *>(myItem);
        if(line){
            this->scene()->removeItem(line);
            delete line;
        }
    }
    //Remove the group items without any children
    foreach(QGraphicsItemGroup* group, groupItems){
        if( group->childItems().count()==0){
            scene()->removeItem(group);
            delete group;
        }
    }

}

void CustomView::drawShapeTo(const QPointF &endPoint)
{
    if (lastItem){
       this->scene()->removeItem(lastItem); //remove the lastItem from the scene
       delete lastItem; //Free up the memory
    }
    QRectF itemRect(startingPoint, endPoint); //Bounding Rect of various shapes

    if (tool == Rect){
        QGraphicsRectItem* mRect = new QGraphicsRectItem();
        mRect->setRect(itemRect.normalized());
        this->scene()->addItem(mRect);
        mRect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        lastItem = mRect;
    }
}


void CustomView::wheelEvent(QWheelEvent *event)
{
    if (event->delta()> 0) zoomIn();
    else zoomOut();
}

void CustomView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        rotate(-1);
    else if(event->key() == Qt::Key_Right)
        rotate(1);
    else
        QGraphicsView::keyPressEvent(event);
}


void CustomView::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context Menu"),this);

    //This includes the code for clearing the screen
    QAction action1(tr("Clear"), this);
    connect(&action1, SIGNAL(triggered()),this->scene(), SLOT(clear()));
    contextMenu.addAction(&action1);

    contextMenu.exec(mapToGlobal(pos));
}

void CustomView::zoomIn()
{
    scale(1.1,1.1);
}

void CustomView::zoomOut()
{
    scale (0.9,0.9);
}

void CustomView::fitToExtents()
{
    fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);

    qDebug()<<scene()->itemsBoundingRect();
}

void CustomView::fitToItem()
{
    QGraphicsItemGroup * selectedGroup = scene()->createItemGroup(scene()->selectedItems());
    selectedGroup->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    fitInView(selectedGroup->boundingRect(),Qt::KeepAspectRatio);
    scene()->destroyItemGroup(selectedGroup);
}

void CustomView::deleteSelectedItems()
{
    QGraphicsItemGroup * selectedGroup = scene()->createItemGroup(scene()->selectedItems());
    scene()->removeItem(selectedGroup);
    scene()->destroyItemGroup(selectedGroup);
}
