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

public slots:
    void ShowContextMenu(const QPoint &pos);
    void zoomIn();
    void zoomOut();
    void fitToExtents();

    // QGraphicsView interface
protected:
    void setupView();
    void createToolbar();

    // QWidget interface
public:
    QSize sizeHint() const override;
};

#endif // VIEW_H
