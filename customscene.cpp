#include "customscene.h"
#include <QDataStream>

CustomScene::CustomScene(QWidget *parent)
    : QGraphicsScene{parent}
{
    initScene();
}

void CustomScene::initScene()
{
    this->setSceneRect(-400,-400,10000,10000);//These are set so the scene is pannable everywhere
}

void CustomScene::createUModel(const double ratio)
{
    this->clear(); //make sure everything there is deleted
    QGraphicsItemGroup* group = new QGraphicsItemGroup();
    group->addToGroup(addEllipse(150,40,100,30));
    group->addToGroup(addLine(150,55,150,40+(100.0*ratio)));
    group->addToGroup(addLine(250,55,250,40+(100.0*ratio)));
    group->addToGroup(addEllipse(150,25+(100.0*ratio),100,30));
//    group->setFlag(QGraphicsItem::ItemIsMovable);
    this->addItem(group);

}

void CustomScene::createBModel(const double ratio)
{
    this->clear(); //make sure everything there is deleted
    QGraphicsItemGroup* group = new QGraphicsItemGroup();
    group->addToGroup(addEllipse(90,150,30,100));
    group->addToGroup(addLine(105,150,90+(100.0*ratio),150));
    group->addToGroup(addLine(105,250,90+(100.0*ratio),250));
    group->addToGroup(addEllipse(75+(100.0*ratio),150,30,100));
    this->addItem(group);

}

void CustomScene::createTModel(const double ratio)
{
    this->clear(); //make sure everything there is deleted
    QGraphicsItemGroup* group = new QGraphicsItemGroup();
    group->addToGroup(addRect(10,10,380,380)); //Square
    group->addToGroup(addEllipse(200-(380/ratio),200-(380/ratio),2*380/ratio,2*380/(ratio))); //circle
    this->addItem(group);

}











