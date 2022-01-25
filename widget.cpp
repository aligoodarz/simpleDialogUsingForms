#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
#include <QList>
#include <QDebug>
#include <QPen>
#include <QPainterPath>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,400,400);
    view = new QGraphicsView(this);
    view->setScene(scene);
    ui->horizontalLayout_2->addWidget(view);
//    ui->horizontalLayout_2->addWidget(ui->visulizeButton);



}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_saveButton_clicked()
{
    //Save the user selections in the variables defined in the header file
    spaceSelection = ui->spaceComboBox->currentText();
    unitsSelection = ui->unitsComboBox->currentText();
    modelSelection = ui->modelComboBox->currentText();
    parameter1Selection = ui->parameter1LineEdit->text();
    parameter2Selection = ui->parameter2LineEdit->text();


    //If any of the fields are empty show a message asking for input
    //If they are not empty, then invoke the saveJson method
    if (ui->spaceComboBox->currentIndex()==0 ||
        ui->unitsComboBox->currentIndex()==0 ||
        ui->modelComboBox->currentIndex()==0 ||
        ui->parameter1LineEdit->text()==""   ||
        ui->parameter2LineEdit->text()=="")
    {
        warnUser();
    }else
    {
       saveJson();
       ui->emptyFieldLabel->setText("Specimen Info Has Been Successfully Saved.");
       ui->emptyFieldLabel->setStyleSheet("color:green; font-weight:bold");
       QTimer::singleShot(4000,this,[=](){ui->emptyFieldLabel->setText("");});

    }

}


void Widget::on_modelComboBox_currentIndexChanged(int index)
{
    //Create pixmaps for the 3 orientations
//    QPixmap uPixmap(":/orientations/images/u_orientation.png");
//    QPixmap bPixmap(":/orientations/images/b_orientation.png");
//    QPixmap tPixmap(":/orientations/images/t_orientation.png");
    //Change parameter 1 and parameter 2 fields based on selection
    //Also change the displayed figure based on the selection
    switch (ui->modelComboBox->currentIndex())
    {
    case 0:
        break;
    case 1:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Height");
        ui->parameter2LineEdit->setPlaceholderText("Height");
        drawModel();
//        ui->orientationPictureLabel->setPixmap(uPixmap);
        break;
    case 2:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Width");
        ui->parameter2LineEdit->setPlaceholderText("Width");
        drawModel();
//        ui->orientationPictureLabel->setPixmap(bPixmap);
        break;
    case 3:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Width");
        ui->parameter2LineEdit->setPlaceholderText("Width");
        drawModel();
//        ui->orientationPictureLabel->setPixmap(tPixmap);
    }
}

void Widget::saveJson()
{
    /* Set Everything to normal colors if they have been flagged as empty
       The labels specifically have to be turned back to normal */
    QString normalLabel = "color : black; font-weight: normal";
    ui->spaceLabel->setStyleSheet(normalLabel);
    ui->unitsLabel->setStyleSheet(normalLabel);
    ui->modelLabel->setStyleSheet(normalLabel);
    ui->parameter1Label->setStyleSheet(normalLabel);
    ui->parameter2Label->setStyleSheet(normalLabel);

    //Proceed with handling the information and saving in the JSON file
    QJsonObject userSelection;
    userSelection.insert("model",modelSelection);
    userSelection.insert("space",spaceSelection);
    userSelection.insert("units",unitsSelection);
    userSelection.insert("parameter1",parameter1Selection);
    userSelection.insert("parameter2",parameter2Selection);

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

    /* failed attempt to save th json file
    QFile file("C:/Users/gooda/OneDrive/Desktop/QtApp/simpleDialogUsingForms/specimenInfo.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll(),&jsonParseError);
    file.close();

    QJsonObject rootObject = jsonDocument.object();
    QJsonValueRef ref = rootObject.find("space").value();
    QJsonObject m_addvalue = ref.toObject();
    m_addvalue.insert("space",spaceSelection);//set the value you want to modify
    ref=m_addvalue; //assign the modified object to reference
    jsonDocument.setObject(rootObject); // set to json document
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(jsonDocument.toJson());
    file.close();
    */

}

void Widget::warnUser()
{
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

}

void Widget::drawModel()
{


}


void Widget::on_visulizeButton_clicked()
{
//    spaceSelection = ui->spaceComboBox->currentText();
//    unitsSelection = ui->unitsComboBox->currentText();
//    modelSelection = ui->modelComboBox->currentText();
    scene->clear(); //make sure everything there is deleted

    double parameter1SelectionDouble = (ui->parameter1LineEdit->text()).toDouble();
    double parameter2SelectionDouble = (ui->parameter2LineEdit->text()).toDouble();


    double ratio = parameter2SelectionDouble/parameter1SelectionDouble; //This holds the ratio for height/width to radius
    qDebug()<<ratio;
    scene->addLine(200,-100,200,600);
    scene->addLine(0,200,600,200);
    //First check to see which box is selected
    if (ui->modelComboBox->currentIndex()==1){
        QGraphicsEllipseItem* topEllipse = scene->addEllipse(150,40,100,30); //big radius is 100, and small radius is 30
        QGraphicsLineItem* leftLine =  scene->addLine(150,55,150,40+(100.0*ratio));
        QGraphicsLineItem* rightLine = scene->addLine(250,55,250,40+(100.0*ratio));
        QGraphicsEllipseItem* bottomEllipse = scene->addEllipse(150,25+(100.0*ratio),100,30);
    }else if (ui->modelComboBox->currentIndex()==2){
        QGraphicsEllipseItem* leftEllipse = scene->addEllipse(90,150,30,100);
        QGraphicsLineItem* topLine =  scene->addLine(105,150,90+(100.0*ratio),150);
        QGraphicsLineItem* bottomLine =  scene->addLine(105,250,90+(100.0*ratio),250);
        QGraphicsEllipseItem* rightEllipse = scene->addEllipse(75+(100.0*ratio),150,30,100);
    }else if (ui->modelComboBox->currentIndex()==3){
        QGraphicsRectItem* square = scene->addRect(10,10,380,380);
        QGraphicsEllipseItem* circle = scene->addEllipse(200-(380/ratio),200-(380/ratio),2*380/ratio,2*380/(ratio));
//        circle->moveBy(((380*ratio)/2)-540,
//                      ((parameter1SelectionDouble*ratio)/2)-parameter1SelectionDouble);
    }

    //This is an attempt to group everything together to do operations on
//    QPainterPath selectionPath;
//    selectionPath.addRect(0,0,600,600);
//    scene->setSelectionArea(selectionPath);
//    QGraphicsItemGroup* selectionGroup = scene->createItemGroup(scene->selectedItems());
//    selectionGroup->moveBy(100,10);



}

