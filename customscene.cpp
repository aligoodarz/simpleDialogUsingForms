#include "customscene.h"
#include <QPainter>

CustomScene::CustomScene(QWidget *parent)
    : QGraphicsScene{parent}
{

}

void CustomScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    painter->drawRect(100,100,20,50);
}
