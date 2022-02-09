#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
#include <QList>
#include <QDebug>
#include <QPen>
#include <QPainterPath>
#include "view.h"
#include "customscene.h"
#include <QToolBar>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUi(); //This adds the necessary elemnts to the UI of the application
}

Widget::~Widget()
{
    delete ui;
}


void Widget::initUi()
{
    scene = new CustomScene(this);
    view = new View(this);
    view->setScene(scene);
    ui->horizontalLayout_2->addWidget(view);

    //This puts the save and visualize in a horizontal layout together for a cleaner look
    ui->horizontalLayout_5->addWidget(ui->saveButton);
    ui->horizontalLayout_5->addWidget(ui->visulizeButton);
    connect(ui->saveButton, SIGNAL(clicked()),this, SLOT(saveJson()));//Connect the save button to the saveJson slot

    file.setFileName(("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/specimenInfo.json")); //Set destination to JsonFile
}


void Widget::on_modelComboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        break;
    case 1:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Height");
        ui->parameter2LineEdit->setPlaceholderText("Height");
        break;
    case 2:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Width");
        ui->parameter2LineEdit->setPlaceholderText("Width");
        break;
    case 3:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Width");
        ui->parameter2LineEdit->setPlaceholderText("Width");
    }
}

void Widget::saveJson()
{

    //Proceed with handling the information and saving in the JSON file
    storeSelection(); //This stores all the fields in respective variables

    //If any of the fields are empty show a message asking for input
    //If they are not empty, then invoke the saveJson method

    if (!fieldIsEmpty()){

        userSelection.insert("model",modelSelection);
        userSelection.insert("space",spaceSelection);
        userSelection.insert("units",unitsSelection);
        userSelection.insert("parameter1",parameter1SelectionDouble);
        userSelection.insert("parameter2",parameter2SelectionDouble);

        QJsonDocument jsonDocument;
        jsonDocument.setObject(userSelection);
        QByteArray bytes = jsonDocument.toJson(QJsonDocument::Indented);
        if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append ) )
            {
                QTextStream iStream( &file );
                iStream.setCodec( "utf-8" );
                iStream << bytes;
                file.close();
                this->setStatusTip("Info Saved Succesfully");
            }
        else
            {
                qDebug() << "file open failed";
            }

    }
}

bool Widget::fieldIsEmpty()
{
    //returns true if any field is empty and returns false if no field is empty
    bool isEmpty = false;

    /* Set Everything to normal colors if they have been flagged as empty
       The labels specifically have to be turned back to normal */
    QString normalLabel = "color : black; font-weight: normal";
    ui->spaceLabel->setStyleSheet(normalLabel);
    ui->unitsLabel->setStyleSheet(normalLabel);
    ui->modelLabel->setStyleSheet(normalLabel);
    ui->parameter1Label->setStyleSheet(normalLabel);
    ui->parameter2Label->setStyleSheet(normalLabel);
    ui->emptyFieldLabel->clear(); //clear the error field since all fields are full

    // Set any field to red that has an empty entry and warn the user.
    QString errorStyle = "color : red; font-weight: bold";

    if (ui->spaceComboBox->currentIndex()==0 ||
        ui->unitsComboBox->currentIndex()==0 ||
        ui->modelComboBox->currentIndex()==0 ||
        ui->parameter1LineEdit->text()==""   ||
        ui->parameter2LineEdit->text()=="")
    {
        isEmpty = true;
        this->setStatusTip("At Least One Field Is Empty, Fill out everything to proceed");
    }

    if (ui->spaceComboBox->currentIndex()==0) { ui->spaceLabel->setStyleSheet(errorStyle);
                                                /*ui->spaceComboBox->setStyleSheet(errorStyle);*/}
    if (ui->unitsComboBox->currentIndex()==0) { ui->unitsLabel->setStyleSheet(errorStyle);
                                                /*ui->unitsComboBox->setStyleSheet(errorStyle);*/}
    if (ui->modelComboBox->currentIndex()==0) { ui->modelLabel->setStyleSheet(errorStyle);
                                                /*ui->modelComboBox->setStyleSheet(errorStyle);*/}
    if (ui->parameter1LineEdit->text()=="") { ui->parameter1Label->setStyleSheet(errorStyle);
                                              /*ui->parameter1LineEdit->setStyleSheet(errorStyle)*/;}
    if (ui->parameter2LineEdit->text()=="") { ui->parameter2Label->setStyleSheet(errorStyle);
                                              /*ui->parameter2LineEdit->setStyleSheet(errorStyle)*/;}

    return isEmpty;

}

void Widget::clearJson()
{
    if (file.resize(0)){
        this->setStatusTip("File Emptied Successfully");
    }
}

void Widget::storeSelection()
{
    //Save the user selections in the variables defined in the header file
    spaceSelection = ui->spaceComboBox->currentText();
    unitsSelection = ui->unitsComboBox->currentText();
    modelSelection = ui->modelComboBox->currentText();
    parameter1Selection = ui->parameter1LineEdit->text();
    parameter2Selection = ui->parameter2LineEdit->text();
    parameter1SelectionDouble = ui->parameter1LineEdit->text().toDouble();
    parameter2SelectionDouble = ui->parameter2LineEdit->text().toDouble();
    ratio = parameter2SelectionDouble/parameter1SelectionDouble; //This holds the ratio needed to make the figures
}


void Widget::on_visulizeButton_clicked()
{
    storeSelection(); //This stores all the fields in respective variable
    //First check to see which box is selected
    if (!fieldIsEmpty()){
        if (ui->modelComboBox->currentIndex()==1){ //U orientation
            scene->createUModel(ratio);
        }else if (ui->modelComboBox->currentIndex()==2){ //B orientation
            scene->createBModel(ratio);
        }else if (ui->modelComboBox->currentIndex()==3){ //T orientation
            scene->createTModel(ratio);
        }
        this->setStatusTip("Visualization Successfull");
    }
}



void Widget::on_unitsComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    //This is used to pass on the units to the view
    //It can be done in a better way but the current architecture does not allow for it.
    view->units = ui->unitsComboBox->currentText();
    //The normal update function would not update immediately so viewport had to be used
    auto vp = view->viewport();
    vp->update();
}

