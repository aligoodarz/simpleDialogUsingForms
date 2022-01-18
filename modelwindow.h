#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class ModelWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ModelWindow(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QBrush brush;


};

#endif // MODELWINDOW_H
