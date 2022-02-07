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
#include <QMainWindow>

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
    QJsonObject userSelection;
    QJsonDocument jsonDocument;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QFile file; //Json file to be used for storing

    void drawModel(); //Draws model based on the selected model
    void initUi();

public slots:
    void saveJson();
    void storeSelection();
    bool fieldIsEmpty(); //Warns users if a field is empty
    void clearJson();



};
#endif // WIDGET_H
