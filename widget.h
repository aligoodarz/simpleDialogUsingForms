#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_saveButton_clicked();

    void on_modelComboBox_currentIndexChanged(int index);

    void on_visulizeButton_clicked();

private:
    Ui::Widget *ui;
    //Declare variables to hold the user selections
    QString spaceSelection;
    QString unitsSelection;
    QString modelSelection;
    QString parameter1Selection;
    QString parameter2Selection;
    double parameter1SelectionDouble;
    double parameter2SelectionDouble;
    //Create Graphics
    void saveJson();
    void warnUser(); //Warns users if a field is empty
    void drawModel(); //Draws model based on the selected model
    void storeSelection();
    QGraphicsView* view;
    QGraphicsScene* scene;



};
#endif // WIDGET_H
