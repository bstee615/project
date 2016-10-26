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

    countWalk = 0;
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
    {
        lblPlayer->raise();
        labelPlayer = lblPlayer;
    }
}

void MainWidget::setWalkImage(Player* player)
{
    QString imagename = ":/images/maincharacter/walk";
    if (countWalk < 7)
    {
        imagename += "1";
    }
    else if (countWalk < 15)
    {
        imagename += "2";
    }
    else if (countWalk == 15)
    {
        countWalk = 0;
        imagename += "1";
    }

    if (left)
        imagename += "left";
    imagename += ".png";
    player->setImage(imagename);
}

void MainWidget::timerHit(){

    //program 4 code below (for reference)
    World& world = World::instance();
    Player* player = world.getPlayer();

    countWalk++;

    if ((right && left) || (!right && !left)) {
        player->slowToStop();
        player->setImage(":/images/maincharacter/stand.png");
        labelPlayer->setPixmap(player->getImage());
        countWalk = 0;
    } else if (right) {
        player->moveRight();
        setWalkImage(player);
        labelPlayer->setPixmap(player->getImage());
    } else if (left) {
        player->moveLeft();
        setWalkImage(player);
        labelPlayer->setPixmap(player->getImage());
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
    //cout << player->getY() << endl; // enable for testing purposes.

    for (int i = 0; i < ui->lblBackground->children().length(); i++ ) {
         QCoreApplication::processEvents();
         ObjectLabel * guiObject = dynamic_cast<ObjectLabel*>(ui->lblBackground->children().at(i));
         if (guiObject != NULL) {
            guiObject->updateLabelPosition();

         }

    }

    resetOnDeath(player);
}

// PoC ONLY! needs serious revamping when we implement scrolling/moving screen.
void MainWidget::resetOnDeath(Player* player)
{
    if (player->getBottomPoint() > World::instance().getHeight())
    {
        player->setX(29);
        player->setY(212);
    }
    if (player->getX() < ui->lblBackground->x())
    {
        player->setX(ui->lblBackground->width() - player->getWidth());
    }
    if (player->getRightPoint() > ui->lblBackground->width())
    {
        player->setX(ui->lblBackground->x());
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
        if (canJump(player))
            player->jump();
        player->setJumpOnMove(true);
    }
}

// returns true if the player can jump (read:is on an object), false if not.
bool MainWidget::canJump(Player* player)
{
    World& world = World::instance();

    for(size_t i = 0; i < world.getObjects().size() ; ++i) {
        QCoreApplication::processEvents();

        if (player->isOnObject(world.getObjects().at(i)))
        {
            return true;
        }
    }
    return false;
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        this->left = false;
    } else if (event->key() == Qt::Key_Right) {
        this->right = false;
    }
}

