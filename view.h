#ifndef VIEW_H
#define VIEW_H

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
#include "widget.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    enum ToolType{
        Cursor,
        Pen,
        Rect,
        Ellipse,
        Eraser
    };

signals:
    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void setupView();
    void createToolbar();
    void drawForeground(QPainter *painter, const QRectF &rect) override;

public slots:
    void ShowContextMenu(const QPoint &pos);
    void zoomIn();
    void zoomOut();
    void fitToExtents();

public:
    QSize sizeHint() const override;
    QString units; //Unit of the drawing

    // QWidget interface
    ToolType getTool() const;
    void setTool(ToolType newTool);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


private:
    void drawLineTo(const QPointF &endPoint);
    bool drawing;
    ToolType tool;
    QGraphicsItemGroup* lineGroup;
    QPointF startingPoint;
    QPointF lastPenPoint;
};

#endif // VIEW_H
