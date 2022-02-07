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


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void clearView();
    void annotate();
    void ShowContextMenu(const QPoint &pos);
    void zoom(const int &delta);


    // QGraphicsView interface
protected:
    void drawForeground(QPainter *painter, const QRectF &rect) override;
    void setupView();
};

#endif // VIEW_H
