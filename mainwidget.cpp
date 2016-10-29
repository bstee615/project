#include <QLabel>
#include <QDebug>
#include <QDesktopWidget>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>

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
	lblPlayer->setScaledContents(true);
	lblPlayer->setObject(player);

	for (Object* worldObj : World::instance().getObjects())
	{
		ObjectLabel* label = new ObjectLabel(ui->worldWidget);
		label->setGeometry(worldObj->getX(), worldObj->getY(), worldObj->getWidth(), worldObj->getHeight());
		label->setObject(worldObj);
		label->setScaledContents(true);
		if (dynamic_cast<Platform*>(worldObj) != NULL)
		{
			label->setPixmap(QPixmap(worldObj->getImage()));
		} else if (dynamic_cast<Collectible*>(worldObj) != NULL)
		{
			label->setPixmap(QPixmap(":/images/goldCoin/goldCoin1.png"));
		}
		label->show();
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
	if (player->getCount() < 7)
	{
		imagename += "1";
	}
	else if (player->getCount() < 15)
	{
		imagename += "2";
	}
	else if (player->getCount() == 15)
	{
		player->setCount(0);
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

    player->advanceCount();

    if ((right && left) || (!right && !left)) {
        // if both right and left arrows are held down or both are released slow the player to a stop
        player->slowToStop();
        labelPlayer->setPixmap(player->getImage());
        player->setCount(0);
    } else if (right) {
        // if the right arrow is pressed the player goes right
        player->moveRight();
        setWalkImage(player);
        labelPlayer->setPixmap(player->getImage());
    } else if (left) {
        // if the left arrow is pressed the player goes left
        player->moveLeft();
        setWalkImage(player);
        labelPlayer->setPixmap(player->getImage());
    }
    // updates player's position in the model
    player->move();
    for(size_t i = 0; i < world.getObjects().size() ; ++i) {
        QCoreApplication::processEvents();
        // checks to see if player the player collides with each object
        CollisionDetails* collision = player->checkCollision(world.getObjects().at(i));
        if (collision != NULL) {
            player->collide(collision);
            delete collision;
        }
    }
    //cout << player->getX() << "," << player->getY() << endl; // enable for testing purposes.

    for (int i = 0; i < ui->lblBackground->children().length(); i++ ) {
         QCoreApplication::processEvents();
         ObjectLabel * guiObject = dynamic_cast<ObjectLabel*>(ui->lblBackground->children().at(i));
         if (guiObject != NULL) {
             // updates the position of each lable to the position of its object in the model
             guiObject->updateLabelPosition();

         }

    }
    showCoin();
    ui->lblScore->setText(QString::number(World::instance().getScore()));
    resetOnDeath(player);
}

// PoC ONLY! needs serious revamping when we implement scrolling/moving screen.
void MainWidget::resetOnDeath(Player* player)
{
    if (player->getBottomPoint() > World::instance().getHeight())
    {
        player->setX(29);
        player->setY(212);
        ui->lblScore->setText("0");
        World::instance().setScore(0);
        for (Object* worldObj : World::instance().getObjects()) {

            Coin * coin = dynamic_cast<Coin*>(worldObj);
            if (coin != NULL) {
                coin->setVisibility(true);
                coin->setisCollectible(true);
            }
        }
       showCoin();

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

void MainWidget::showCoin() {
    for (Object* worldObj : World::instance().getObjects()) {

        Coin * coin = dynamic_cast<Coin*>(worldObj);
        if (coin != NULL) {

            int coinId = worldObj->getId();
            ObjectLabel * lbl;

            for (int i = 0; i < ui->lblBackground->children().length(); i++ ) {
               lbl = dynamic_cast<ObjectLabel*>(ui->lblBackground->children().at(i));
               if (lbl->getId() == coinId){
                  if (coin->getVisibility() == true) {
                      lbl->show();
                  } else {
                      lbl->hide();
                  }
              }
            }
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
		player->setJumpOnMove(true);
	}
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
	Player* player = World::instance().getPlayer();
	if (event->key() == Qt::Key_Left) {
		this->left = false;
		player->setImage(":/images/maincharacter/standleft.png");
	} else if (event->key() == Qt::Key_Right) {
		this->right = false;
		player->setImage(":/images/maincharacter/stand.png");
	}
}

