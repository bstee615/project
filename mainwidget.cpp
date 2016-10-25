#include <QLabel>
#include <QDebug>
#include <QDesktopWidget>
#include <QTimer>
#include "QKeyEvent"
#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "world.h"
#include "titlescreen.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(17);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
	loadLevel("easy.lv");
    right = false;
    left = false;
	TitleScreen* titleScn = new TitleScreen(ui->worldWidget);
	titleScn->show();
	titleScn->raise();
}

void MainWidget::loadLevel(string filename)
{
    ObjectLabel* lblPlayer = NULL;

    World::instance().loadLevel(filename);

    for (Object* worldObj : World::instance().getObjects())
    {
        if (dynamic_cast<Player*>(worldObj) != NULL)
        {
            Player* player = dynamic_cast<Player*>(worldObj);
			lblPlayer = new ObjectLabel(ui->worldWidget);
            lblPlayer->setParent(ui->lblBackground);
            lblPlayer->show();
            lblPlayer->setGeometry(player->getX(), player->getY(), player->getWidth(), player->getHeight());
            lblPlayer->setPixmap(QPixmap(player->getImage()));
        }
        else if (dynamic_cast<Platform*>(worldObj) != NULL)
        {
            Platform* platform = dynamic_cast<Platform*>(worldObj);
			ObjectLabel* lblPlatform = new ObjectLabel(ui->worldWidget);
            lblPlatform->setParent(ui->lblBackground);
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

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        this->left = true;
    } else if (event->key() == Qt::Key_Right) {
        this->right = true;
    } else if (event->key() == Qt::Key_Space) {
        //World::instance().getPlayer()->jump();
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        this->left = false;
    } else if (event->key() == Qt::Key_Right) {
        this->right = false;
    }
}
