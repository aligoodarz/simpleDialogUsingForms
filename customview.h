#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPoint>
#include <QString>
#include <QPointF>
#include <QGraphicsItemGroup>
#include <QGraphicsEllipseItem>
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
#include <QList>
#include <QGraphicsTextItem>
#include <QString>
#include "widget.h"



class CustomView : public QGraphicsView
{
    Q_OBJECT
public: //methods
    explicit CustomView(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    enum ToolType{
        Cursor,
        Pen,
        Rect,
        Ellipse,
        Eraser,
        Pan
    };

private: //methods
    void drawLineTo(const QPointF &endPoint);
    void drawEraserAt(const QPointF &endPoint);
    void eraseStrokesUnder(QGraphicsEllipseItem* item);
    void drawShapeTo(const QPointF &endPoint);

private: //variables
    bool drawing;
    ToolType tool;
    QGraphicsItemGroup* lineGroup = nullptr;
    QPointF startingPoint;
    QPointF lastPenPoint;
    QGraphicsEllipseItem* lastEraserCircle = nullptr;
    QGraphicsItem* lastItem = nullptr;

protected: //methods
    void setupView();
    void createToolbar();
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void ShowContextMenu(const QPoint &pos);
    void zoomIn();
    void zoomOut();
    void fitToExtents();
    void fitToItem();
    void deleteSelectedItems();
    void copy();
};

#endif // CUSTOMVIEW_H
