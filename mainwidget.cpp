#include <QLabel>
#include <QDebug>
#include <QDesktopWidget>
#include <QTimer>
#include "QKeyEvent"
#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "world.h"
#include "titlescreen.h"
#include <iostream>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(33);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
	loadLevel("easy.lv");
    right = false;
    left = false;
	TitleScreen* titleScn = new TitleScreen(ui->worldWidget);
	titleScn->show();
	titleScn->raise();
    timer->start();
}

void MainWidget::loadLevel(string filename)
{
    ObjectLabel* lblPlayer = NULL;

    World::instance().loadLevel(filename);
    World& world = World::instance();

    Player* player = world.getPlayer();
    lblPlayer = new ObjectLabel(ui->worldWidget);
    lblPlayer->setParent(ui->lblBackground);
    lblPlayer->show();
    lblPlayer->setGeometry(player->getX(), player->getY(), player->getWidth(), player->getHeight());
    lblPlayer->setPixmap(QPixmap(player->getImage()));
    lblPlayer->setObject(player);

    for (Object* worldObj : World::instance().getObjects())
    {

        if (dynamic_cast<Platform*>(worldObj) != NULL)
        {
            Platform* platform = dynamic_cast<Platform*>(worldObj);
			ObjectLabel* lblPlatform = new ObjectLabel(ui->worldWidget);
            lblPlatform->setParent(ui->lblBackground);
            lblPlatform->setGeometry(platform->getX(), platform->getY(), platform->getWidth(), platform->getHeight());
            lblPlatform->setStyleSheet(QStringLiteral("background-color: gray;"));
            lblPlatform->show();
            lblPlatform->setObject(platform);
        }
    }
    if (lblPlayer != NULL)
        lblPlayer->raise();
}

void MainWidget::timerHit(){

    //program 4 code below (for reference)
    World& world = World::instance();
    Player* player = world.getPlayer();
    if ((right && left) || (!right && !left)) {
        player->slowToStop();
    } else if (right) {
        player->moveRight();
    } else if (left) {
        player->moveLeft();
    }

    player->move();
    for(size_t i = 0; i < world.getObjects().size() ; ++i) {
        QCoreApplication::processEvents();
        CollisionDetails* collision = player->checkCollision(world.getObjects().at(i));
        if (collision != NULL) {
            player->collide(collision);
            delete collision;
        }
    }
    cout << player->getY() << endl;

    for (int i = 0; i < ui->lblBackground->children().length(); i++ ) {
         QCoreApplication::processEvents();
         ObjectLabel * guiObject = dynamic_cast<ObjectLabel*>(ui->lblBackground->children().at(i));
         if (guiObject != NULL) {
            guiObject->updateLabelPosition();

         }

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
        Player* player = World::instance().getPlayer();
        checkJump(player);
    }
}
void MainWidget::checkJump(Player* player)
{
    World& world = World::instance();

    for(size_t i = 0; i < world.getObjects().size() ; ++i) {
        QCoreApplication::processEvents();

        if (player->isOnObject(world.getObjects().at(i)))
        {
            player->jump();
        }
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

