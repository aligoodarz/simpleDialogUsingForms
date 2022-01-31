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


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,400,400);
    view = new View(this);
    view->setScene(scene);
    ui->horizontalLayout_2->addWidget(view);

    ui->horizontalLayout_5->addWidget(ui->saveButton);
    ui->horizontalLayout_5->addWidget(ui->visulizeButton);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_saveButton_clicked()
{
    storeSelection(); //This stores all the fields in respective variables

    //If any of the fields are empty show a message asking for input
    //If they are not empty, then invoke the saveJson method

    if (!fieldIsEmpty()){
       saveJson();
    }
}


void Widget::on_modelComboBox_currentIndexChanged(int index)
{
    switch (ui->modelComboBox->currentIndex())
    {
    case 0:
        break;
    case 1:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Height");
        ui->parameter2LineEdit->setPlaceholderText("Height");
//        ui->orientationPictureLabel->setPixmap(uPixmap);
        break;
    case 2:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Width");
        ui->parameter2LineEdit->setPlaceholderText("Width");
//        ui->orientationPictureLabel->setPixmap(bPixmap);
        break;
    case 3:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Width");
        ui->parameter2LineEdit->setPlaceholderText("Width");
//        ui->orientationPictureLabel->setPixmap(tPixmap);
    }
}

void Widget::saveJson()
{

    //Proceed with handling the information and saving in the JSON file
    QJsonObject userSelection;
    userSelection.insert("model",modelSelection);
    userSelection.insert("space",spaceSelection);
    userSelection.insert("units",unitsSelection);
    userSelection.insert("parameter1",parameter1SelectionDouble);
    userSelection.insert("parameter2",parameter2SelectionDouble);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(userSelection);
    QByteArray bytes = jsonDocument.toJson(QJsonDocument::Indented);
    QFile file("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/specimenInfo.json");
    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append ) )
        {
            QTextStream iStream( &file );
            iStream.setCodec( "utf-8" );
            iStream << bytes;
            file.close();
        }
    else
        {
            qDebug() << "file open failed";
        }
    ui->emptyFieldLabel->setText("Specimen Info Has Been Successfully Saved.");
    ui->emptyFieldLabel->setStyleSheet("color:green; font-weight:bold");
    QTimer::singleShot(4000,this,[=](){ui->emptyFieldLabel->setText("");});
}

bool Widget::fieldIsEmpty()
{
    //returns true if any field is empty and returns false if no field is empty
    bool isEmpty = false;
    if (ui->spaceComboBox->currentIndex()==0 ||
        ui->unitsComboBox->currentIndex()==0 ||
        ui->modelComboBox->currentIndex()==0 ||
        ui->parameter1LineEdit->text()==""   ||
        ui->parameter2LineEdit->text()=="")
    {
        isEmpty = true;
    }

    /* Set Everything to normal colors if they have been flagged as empty
       The labels specifically have to be turned back to normal */
    QString normalLabel = "color : black; font-weight: normal";
    ui->spaceLabel->setStyleSheet(normalLabel);
    ui->unitsLabel->setStyleSheet(normalLabel);
    ui->modelLabel->setStyleSheet(normalLabel);
    ui->parameter1Label->setStyleSheet(normalLabel);
    ui->parameter2Label->setStyleSheet(normalLabel);

    // Set any field to red that has an empty entry and warn the user.
    QString errorStyle = "color : red; font-weight: bold";

    ui->emptyFieldLabel->setText("At Least One Field Is Empty, Fill out everything to proceed");
    ui->emptyFieldLabel->setStyleSheet(errorStyle);

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
}


void Widget::on_visulizeButton_clicked()
{

    scene->clear(); //make sure everything there is deleted
    storeSelection(); //This stores all the fields in respective variable
    double ratio = parameter2SelectionDouble/parameter1SelectionDouble;

    //First check to see which box is selected
    if (!fieldIsEmpty()){
        if (ui->modelComboBox->currentIndex()==1){ //U orientation
            scene->addEllipse(150,40,100,30); //big radius is 100, and small radius is 30, top ellipse
            scene->addLine(150,55,150,40+(100.0*ratio)); //left line
            scene->addLine(250,55,250,40+(100.0*ratio)); //right line
            scene->addEllipse(150,25+(100.0*ratio),100,30); //bottom ellipse
        }else if (ui->modelComboBox->currentIndex()==2){ //B orientation
            scene->addEllipse(90,150,30,100); //left ellipse
            scene->addLine(105,150,90+(100.0*ratio),150); //top line
            scene->addLine(105,250,90+(100.0*ratio),250); //bottom line
            scene->addEllipse(75+(100.0*ratio),150,30,100); //right ellipse
        }else if (ui->modelComboBox->currentIndex()==3){ //T orientation
            scene->addRect(10,10,380,380); //Square
            scene->addEllipse(200-(380/ratio),200-(380/ratio),2*380/ratio,2*380/(ratio)); //circle
        }
    }
}


