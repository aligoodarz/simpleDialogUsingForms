#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
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
        QMessageBox::warning(this, "Empty Fields",
                             "At least one input field is empty, please fill out everything to proceed");
    }else
    {
       saveJson();
       QMessageBox::information(this,"Success!","Specimen Info has been saved to the JSON file");

    }

}


void Widget::on_modelComboBox_currentIndexChanged(int index)
{
    //Create pixmaps for the 3 orientations
    QPixmap uPixmap(":/orientation_images/images/u_orientation.png");
    QPixmap bPixmap(":/orientation_images/images/b_orientation.png");
    QPixmap tPixmap(":/orientation_images/images/t_orientation.png");
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
        ui->orientationPictureLabel->setPixmap(uPixmap);
        break;
    case 2:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Width");
        ui->parameter2LineEdit->setPlaceholderText("Width");
        ui->orientationPictureLabel->setPixmap(bPixmap);
        break;
    case 3:
        ui->parameter1Label->setText("Radius");
        ui->parameter1LineEdit->setPlaceholderText("Radius");
        ui->parameter2Label->setText("Width");
        ui->parameter2LineEdit->setPlaceholderText("Width");
        ui->orientationPictureLabel->setPixmap(tPixmap);
    }



}

void Widget::saveJson()
{
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
    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
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

