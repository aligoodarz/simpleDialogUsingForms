#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include "widget.h"

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QWidget *parent = nullptr);

public:
    void initScene();//This initializies what needs to be done for the scene
    void createUModel(const double ratio);
    void createBModel(const double ratio);
    void createTModel(const double ratio);
signals:

};

#endif // CUSTOMSCENE_H
