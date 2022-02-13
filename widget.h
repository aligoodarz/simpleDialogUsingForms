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
#include <QComboBox>
#include <QGraphicsView>
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
#include <QList>
#include <QDebug>
#include <QPen>
#include <QPainterPath>
#include <QLabel>
#include <QToolBar>

#include "customview.h"
#include "customscene.h"

//Declare custom classes for the compiler
//This is necessary because of circular inclusions and bad dependencies
//It should be avoided in future design
class CustomView;
class CustomScene;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public: //variables
    //These are variables so they can be accessed in mainwindow and have their slots assigned
    CustomView* view;
    CustomScene* scene;

private: //variables
    Ui::Widget *ui;
    //Declare variables to hold the user selections
    QString spaceSelection;
    QString unitsSelection;
    QString modelSelection;
    QString parameter1Selection;
    QString parameter2Selection;
    double parameter1SelectionDouble;
    double parameter2SelectionDouble;
    double ratio;
    QJsonObject userSelection;
    QJsonDocument jsonDocument;
    QFile file; //Json file to be used for storing

public: //methods
    Widget(QWidget *parent = nullptr);
    ~Widget();


private: //methods
    void drawModel(); //Draws model based on the selected model
    void initUi(); //Does the necessary steps to get the Ui running
    void storeSelection(); //Stores info the user has entered

private slots:
    void setModel();
    void on_visulizeButton_clicked();


public slots:
    void saveJson(); //Saves the user inputs in the JSON format
    bool fieldIsEmpty(); //Warns users if a field is empty
    void clearJson(); //Clears the JSON file

};
#endif // WIDGET_H
