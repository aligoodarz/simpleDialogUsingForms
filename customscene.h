#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QWidget>
#include <QGraphicsScene>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QWidget *parent = nullptr);

signals:


    // QGraphicsScene interface
protected:
    void drawForeground(QPainter *painter, const QRectF &rect) override;
};

#endif // CUSTOMSCENE_H
