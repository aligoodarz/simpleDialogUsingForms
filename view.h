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
#include "widget.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

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



};

#endif // VIEW_H
