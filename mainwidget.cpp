#include <QLabel>
#include <QDebug>
#include <QDesktopWidget>
#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "world.h"
#include <QTimer>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(17);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
    LoadLevel("easy.lv");
}

void MainWidget::LoadLevel(string filename)
{
    QLabel* lblPlayer = NULL;

    World::instance().loadLevel(filename);

    for (Object* worldObj : World::instance().getObjects())
    {
        if (dynamic_cast<Player*>(worldObj) != NULL)
        {
            Player* player = dynamic_cast<Player*>(worldObj);
            lblPlayer = new QLabel(ui->worldWidget);
            lblPlayer->show();
            lblPlayer->setGeometry(player->getX(), player->getY(), player->getWidth(), player->getHeight());
            lblPlayer->setPixmap(QPixmap(player->getImage()));
        }
        else if (dynamic_cast<Platform*>(worldObj) != NULL)
        {
            Platform* platform = dynamic_cast<Platform*>(worldObj);
            QLabel* lblPlatform = new QLabel(ui->worldWidget);
            lblPlatform->setGeometry(platform->getX(), platform->getY(), platform->getWidth(), platform->getHeight());
            lblPlatform->setStyleSheet(QStringLiteral("background-color: gray;"));
            lblPlatform->show();
        }
    }
    if (lblPlayer != NULL)
        lblPlayer->raise();
}

void MainWidget::timerHit(){

    //program 4 code below (for reference)
    ObjectLabel * guiObject;
    Object * modelObject;
    for (int i = 0; i < ui->lblBackground->children().length(); i++ ) {
         guiObject = dynamic_cast<ObjectLabel*>(ui->lblBackground->children().at(i));
         int id = guiObject->getId();
         modelObject = World::instance().getById(id);
         //update position of each object in GUI and in the model

    }

}


MainWidget::~MainWidget()
{
	delete ui;
}
