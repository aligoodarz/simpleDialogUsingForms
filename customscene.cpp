#include "customscene.h"
#include <QPainter>


CustomScene::CustomScene(QWidget *parent)
    : QGraphicsScene{parent}
{
    initScene();
}

void CustomScene::initScene()
{
    this->setSceneRect(0,0,380,410);
}

void CustomScene::createUModel(const double ratio)
{
    this->clear(); //make sure everything there is deleted
    this->addEllipse(150,40,100,30); //big radius is 100, and small radius is 30, top ellipse
    this->addLine(150,55,150,40+(100.0*ratio)); //left line
    this->addLine(250,55,250,40+(100.0*ratio)); //right line
    this->addEllipse(150,25+(100.0*ratio),100,30); //bottom ellipse
}

void CustomScene::createBModel(const double ratio)
{
    this->clear(); //make sure everything there is deleted
    this->addEllipse(90,150,30,100); //left ellipse
    this->addLine(105,150,90+(100.0*ratio),150); //top line
    this->addLine(105,250,90+(100.0*ratio),250); //bottom line
    this->addEllipse(75+(100.0*ratio),150,30,100); //right ellipse

}

void CustomScene::createTModel(const double ratio)
{
    this->clear(); //make sure everything there is deleted
    this->addRect(10,10,380,380); //Square
    this->addEllipse(200-(380/ratio),200-(380/ratio),2*380/ratio,2*380/(ratio)); //circle
}




