#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QScrollArea>
#include <QRect>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QScrollArea * scrollArea = new QScrollArea;
    ui->QWworld->resize(1024,768);
    scrollArea->setWidget(ui->QWworld);
    scrollArea->resize(1024,768);
    scrollArea->setWidgetResizable(false);

    scrollArea->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlatform(MovableLabel *label, QString file, bool& successful, QString& errorMSG)
{
    if (ui->LEwidth->text() == "" || ui->LEheight->text() =="") {
        successful = false;
        errorMSG = "Please enter width and height.";
        return;
    } else {
        label->setGeometry(0,0,ui->LEwidth->text().toInt(),ui->LEheight->text().toInt());
    }
    if (ui->LExRange->text() != ""){
        label->xRange = ui->LExRange->text().toInt();
    } else {
        label->xRange = 0;
    }
    if (ui->LEyRange->text() != ""){
        label->yRange = ui->LEyRange->text().toInt();
    } else {
        label->yRange = 0;
    }
    if (ui->LExSpeed->text() != ""){
        label->xSpeed = ui->LExSpeed->text().toInt();
    } else {
        label->xSpeed = 0;
    }
    if (ui->LEySpeed->text() != ""){
        label->ySpeed = ui->LEySpeed->text().toInt();
    } else {
        label->ySpeed = 0;
    }

    label->setPixmap(QPixmap(file));
    label->type = "platform";
    label->file = file;
}

void MainWindow::labelClicked()
{
    MovableLabel *lbl = dynamic_cast<MovableLabel *>(sender());
    if (lbl != nullptr) {

    }
}

void MainWindow::on_PBmakeObject_clicked()
{
    int checkedPB = 0;
    for (int i = 0; i < this->children().size(); ++i){
        QPushButton * current = dynamic_cast<QPushButton *>(this->children().at(i));
        if (current != NULL){
            if (current->isChecked()){
                ++checkedPB;
            }
        }
    }

    if (checkedPB != 1) {
        QMessageBox::warning(this,"Error","Choose one and only one Object.");
        for (int i = 0; i < this->children().size(); ++i){
            QPushButton * current = dynamic_cast<QPushButton *>(this->children().at(i));
            if (current != NULL){
                if (current->isChecked()){
                    current->setChecked(false);
                }
            }
        }
        return;
    }
    MovableLabel *label = new MovableLabel(this->ui->QWworld);
    connect(label, SIGNAL(clicked()), this, SLOT(labelClicked()));
    bool successful = true;
    QString errorMSG = "";

    if (ui->PBplayer->isChecked()) {
        for (int i = 0; i < ui->QWworld->children().size(); ++i) {
            MovableLabel* current = dynamic_cast<MovableLabel*>(ui->QWworld->children().at(i));
            if (current!= NULL) {
                if (current->type == "player") {
                    successful = false;
                    errorMSG = "There can be only one player.";
                }
            }
        }
        label->setGeometry(0,0,25,48);
        label->setPixmap(QPixmap(":/images/maincharacter/stand.png"));
        label->type = "player";
        label->file = "images/maincharacter/stand.png";
    } else if (ui->PBcoin->isChecked()){
        label->setGeometry(0,0,32,32);
        label->setPixmap(QPixmap(":/images/goldCoin/goldCoin5.png"));
        label->type = "coin";
        label->file = "_";
        label->amount = 100;
    } else if (ui->PBwin->isChecked()){
        successful = false;
        errorMSG = "Win not implemented";
    } else if (ui->PBplatform1->isChecked()){
        makePlatform(label,":images/pavement1.png",successful,errorMSG);
    } else if (ui->PBplatform2->isChecked()){
        makePlatform(label,":images/pavement2.png",successful,errorMSG);
    } else if (ui->PBplatform3->isChecked()){
        makePlatform(label,":images/pavement3.png",successful,errorMSG);
    } else if (ui->PBplatform4->isChecked()){
        makePlatform(label,":images/pavement4.png",successful,errorMSG);
    } else if (ui->PBplatform5->isChecked()){
        makePlatform(label,":images/pavement5.png",successful,errorMSG);
    } else if (ui->PBplatform6->isChecked()){
        makePlatform(label,":images/pavement6.png",successful,errorMSG);
    } else if (ui->PBplatform7->isChecked()){
        makePlatform(label,":images/pavement7.png",successful,errorMSG);
    } else if (ui->PBplatform8->isChecked()){
        makePlatform(label,":images/pavement8.png",successful,errorMSG);
    } else if (ui->PBplatform9->isChecked()){
        makePlatform(label,":images/pavement9.png",successful,errorMSG);
    } else if (ui->PBplatform10->isChecked()){
        makePlatform(label,":images/pavement10.png",successful,errorMSG);
    } else if (ui->PBplatform11->isChecked()){
        makePlatform(label,":images/pavement11.png",successful,errorMSG);
    } else if (ui->PBplatform12->isChecked()){
        makePlatform(label,":images/pavement12.png",successful,errorMSG);
    } else if (ui->PBplatform13->isChecked()){
        makePlatform(label,":images/pavement13.png",successful,errorMSG);
    } else if (ui->PBplatform14->isChecked()){
        makePlatform(label,":images/pavement14.png",successful,errorMSG);
    } else if (ui->PBplatform15->isChecked()){
        makePlatform(label,":images/pavement15.png",successful,errorMSG);
    } else if (ui->PBplatform16->isChecked()){
        makePlatform(label,":images/pavement16.png",successful,errorMSG);
    }


    if (successful == false) {
        QMessageBox::warning(this,"Error", errorMSG);
        label->deleteLater();
        return;
    }
    label->show();

    for (int i = 0; i < this->children().size(); ++i){
        QPushButton * current = dynamic_cast<QPushButton *>(this->children().at(i));
        if (current != NULL){
            current->setChecked(false);
        }
    }
}

void MainWindow::on_PBresize_clicked()
{
    if (ui->LEresizeX->text() != "" && ui->LEresizeY->text() != ""){
        ui->QWworld->resize(ui->LEresizeX->text().toInt(),ui->LEresizeY->text().toInt());
    }
}
