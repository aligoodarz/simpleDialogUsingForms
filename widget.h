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

private:
    Ui::Widget *ui;
    //Declare variables to hold the user selections
    QString spaceSelection;
    QString unitsSelection;
    QString modelSelection;
    QString parameter1Selection;
    QString parameter2Selection;
    //Declare a list to hold the final selections
    QList <QString> selectionList;
    //Create Graphics
    void saveJson();
    void warnUser(); //Warns users if a field is empty

};
#endif // WIDGET_H
