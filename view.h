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
    void ShowContextMenu(const QPoint &pos);
};

#endif // VIEW_H
