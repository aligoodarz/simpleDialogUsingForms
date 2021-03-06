#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>
#include <QPen>

#include "widget.h"


class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QWidget *parent = nullptr);

    void initScene();//This initializies what needs to be done for the scene
    void createUModel(const double ratio);
    void createBModel(const double ratio);
    void createTModel(const double ratio);


};

#endif // CUSTOMSCENE_H
