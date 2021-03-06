#include "customview.h"
#include <customscene.h>

#include <QGraphicsPathItem>


CustomView::CustomView(QWidget *parent)
    : QGraphicsView{parent},
      drawing(false),
      tool(Cursor),
      undoStack (new QUndoStack(this->scene()))
{
    setupView();
}

void CustomView::setupView()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    undoStack->setUndoLimit(10); //To make sure the memory doesn't get filled

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
    QPixmap mouseSelectionPixmap(defaultDir+"mouse_selection.png");
    QPixmap panIcon(defaultDir+"pan.png");
    QPixmap eraserPixmap(defaultDir+"eraser.png");
    QPixmap deleteSelectionPixmap (defaultDir+"deleteSelection.png");
    QPixmap rectanglePixmap (defaultDir+"rectangle.png");
    QPixmap undoPixmap (defaultDir + "undo.png");
    QPixmap redoPixmap (defaultDir + "redo.png");
    QPixmap copyPixmap (defaultDir + "copy.png");
    QPixmap linePixmap (defaultDir + "line.png");
    //Create Toolbar
    auto tb = new QToolBar();
    tb->setIconSize(QSize(20,20));
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

    auto drawLine = tb->addAction(linePixmap,"Line");
    connect(drawLine, &QAction::triggered, this, [this](){
        tool = Line;
        setDragMode(QGraphicsView::NoDrag);
        setStatusTip("Line Selected");
    });

    auto cursorActive = tb->addAction(mouseSelectionPixmap,"Cursor");
    connect(cursorActive, &QAction::triggered,this,[this](){
        tool = Cursor;
        setDragMode(QGraphicsView::RubberBandDrag);
        setStatusTip("Cursor Selected");
    });

    auto panActive = tb->addAction(panIcon,"Pan");
    connect(panActive, &QAction::triggered,this,[this](){
        tool = Pan;
        setDragMode(QGraphicsView::ScrollHandDrag);
        setStatusTip("Pan Tool Selected");
    });

    auto eraserActive = tb->addAction(eraserPixmap,"Eraser");
    connect(eraserActive, &QAction::triggered,this,[this](){
        tool = Eraser;
        setDragMode(QGraphicsView::NoDrag);
        setStatusTip("Eraser Selected");
    });

    auto copy = tb->addAction(copyPixmap,"Copy");
    connect(copy, &QAction::triggered, this, &CustomView::copy);

    auto undo = tb->addAction(undoPixmap,"Undo");
    connect(undo, &QAction::triggered,this, &CustomView::undo);

    auto redo = tb->addAction(redoPixmap,"Redo");
    connect(redo, &QAction::triggered,this, &CustomView::redo);

    //add menu to the view
    auto dockLayout = new QVBoxLayout();
    dockLayout->setMenuBar(tb); //
    this->setLayout(dockLayout);
}

QSize CustomView::sizeHint() const
{
    return QSize(400,600);
}

void CustomView::undo()
{
    undoStack->undo();
}

void CustomView::redo()
{
    undoStack->redo();
}

void CustomView::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::RightButton)
    {
        ShowContextMenu(event->pos()); //Show context menu
    }if(event->button() == Qt::LeftButton){
        if (tool == ToolType::Pen || tool == ToolType::Eraser
                || tool == Rect || tool == Ellipse || tool == Line){
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
        if (tool == Pen){
            drawLineTo(mapToScene(event->pos()));
        }else if ( tool == Eraser){
            drawEraserAt(mapToScene(event->pos()));
        }else if (tool == Rect || tool == Line) {
            drawShapeTo(mapToScene(event->pos()));
        }
    }else
        QGraphicsView::mouseMoveEvent(event);
}

void CustomView::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton) && drawing){
        if (tool == Pen){
            lineGroup = nullptr;
            drawing = false;

        }if(tool == Eraser){
            scene()->removeItem(lastEraserCircle);
            delete lastEraserCircle;
            lastEraserCircle = nullptr;
            drawing = false;

        }if (lastItem && (tool == Rect || tool == Line)){
            this->scene()->removeItem(lastItem);
            delete lastItem; //Free memory

        }if (tool == Rect) {
            //Create the final rectangle and set flags
            QGraphicsRectItem* mRect = new QGraphicsRectItem();
            mRect->setRect(QRectF(startingPoint, mapToScene(event->pos())).normalized());
            mRect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            //Create an add command and add it to the undo stack
            AddCommand * addCommand = new AddCommand(mRect, this->scene());
            undoStack->push(addCommand);
            //Clear previous lastItem and set drawing to false
            lastItem = nullptr;
            drawing = false;
        }if (tool == Line){
            //Same as Rect but with a line
            QGraphicsLineItem* mLine = new QGraphicsLineItem(startingPoint.x(), startingPoint.y(),
                                                             mapToScene(event->pos()).x(), mapToScene(event->pos()).y());
            mLine->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            AddCommand * addCommand = new AddCommand(mLine, this->scene());
            undoStack->push(addCommand);
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
        AddCommand * addCommand = new AddCommand(lineGroup, this->scene());
        undoStack->push(addCommand);
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
        QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem *>(myItem);
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
        lastItem = mRect;
    }else if (tool == Line){
        QGraphicsLineItem* mLine = new QGraphicsLineItem(startingPoint.x(),startingPoint.y(),
                                                         endPoint.x(), endPoint.y());
        this->scene()->addItem(mLine);
        lastItem = mLine;
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
    else if (event->key() == Qt::Key_Delete) //Delete button can delete selected items
        deleteSelectedItems();
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
}

void CustomView::fitToItem()
{
    QGraphicsItemGroup * selectedGroup = scene()->createItemGroup(scene()->selectedItems());
    if (selectedGroup){
        selectedGroup->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        fitInView(selectedGroup->boundingRect(),Qt::KeepAspectRatio);
        scene()->destroyItemGroup(selectedGroup);
    }
}

void CustomView::deleteSelectedItems()
{
    QGraphicsItemGroup * selectedGroup = scene()->createItemGroup(scene()->selectedItems());;
    if (selectedGroup){
        RemoveCommand * removeCommand = new RemoveCommand(selectedGroup, this->scene());
        undoStack->push(removeCommand);
        delete selectedGroup;
    }
}

void CustomView::copy()
{
    QList <QGraphicsItem*> selItems = this->scene()->selectedItems();
    if (selItems.size() == 0){
        //Nothing is selected
        return;
    }

    foreach(QGraphicsItem* selItem, selItems){ //Iterate to copy all items
        //Try to cast it to rect item and then check if it is indeed a rect item
        QGraphicsRectItem* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(selItem);
        if (rectItem){ //if not null it is a rectItem
            QRectF size = rectItem->rect();
            QGraphicsRectItem* copiedRect = new QGraphicsRectItem(size);
            AddCommand * addCommand = new AddCommand(copiedRect, this->scene());
            undoStack->push(addCommand);
            copiedRect->moveBy(rectItem->x()+15,rectItem->y()+15);
            copiedRect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        }

        //Try to cast the item to lineItem and then check if it is indded a line item
        QGraphicsLineItem* lineItem = qgraphicsitem_cast<QGraphicsLineItem*>(selItem);
        if (lineItem){
            QGraphicsLineItem* copiedLine = new QGraphicsLineItem();
            copiedLine->setLine(lineItem->line());
            AddCommand * addCommand = new AddCommand(copiedLine, this->scene());
            undoStack->push(addCommand);
            copiedLine->moveBy(lineItem->x()+15,lineItem->y()+15);
            copiedLine->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        }

        //Fix this later on, try to find a way to draw the path
        QGraphicsItemGroup* handDrawnItem = qgraphicsitem_cast<QGraphicsItemGroup*>(selItem);
        if (handDrawnItem){
            qDebug()<<"Item Group";
            QPainterPath path = handDrawnItem->opaqueArea();
            QGraphicsPathItem* copiedItem = this->scene()->addPath(path);
            //        copiedItem->paint(painter);
        }
    }

}


