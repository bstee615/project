#include <QLabel>
#include <QDebug>
#include <QDesktopWidget>
#include <QTimer>
#include <QKeyEvent>
#include <cmath>

#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "world.h"
#include "titlescreen.h"
#include "endgame.h"


MainWidget::MainWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainWidget)
{
	ui->setupUi(this);
	ui->lblLife1->raise();
	ui->lblLife2->raise();
	ui->lblLife3->raise();
	ui->lblScore->raise(); // these components should not be under the world objects

	timer = new QTimer(this);
	timer->setInterval(33);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
	loadLevel(":/easy.lv");
	right = false;
	left = false;
	TitleScreen* titleScn = new TitleScreen(ui->worldWidget);
	titleScn->show();
	titleScn->raise();
	timer->start();
}

void MainWidget::loadLevel(QString filename)
{
	ObjectLabel* lblPlayer = NULL;

	World::instance().loadLevel(filename);
	World::instance().getScreen()->setScreenSize(ui->worldWidget->geometry().width(), ui->worldWidget->geometry().height());

	Player* player = World::instance().getPlayer();
	lblPlayer = new ObjectLabel(ui->worldWidget);
	lblPlayer->setObject(player);
	lblPlayer->setPixmap(QPixmap(player->getImage()));
	lblPlayer->setScaledContents(true);
	lblPlayer->show();
	lblPlayer->updateLabelPosition();

	for (Object* worldObj : World::instance().getObjects())
	{
		ObjectLabel* label = new ObjectLabel(ui->worldWidget);
		label->setObject(worldObj);
		label->updateLabelPosition();
		label->setScaledContents(true);
		if (dynamic_cast<Platform*>(worldObj) != NULL)
		{
			label->setPixmap(QPixmap(worldObj->getImage()));
        } else if (dynamic_cast<Coin*>(worldObj) != NULL)
		{
            label->setPixmap(QPixmap(worldObj->getImage()));
		}
        else if (dynamic_cast<Enemy*>(worldObj) != NULL)
        {
            label->setPixmap(QPixmap(worldObj->getImage()).scaled(42,48));
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
	if (player->getX() < 0)
	{
		player->setX(0);
		player->setXSpeed(0);
	}
	if (player->getRightPoint() > World::instance().getScreen()->getLevelWidth())
	{
		player->setX(World::instance().getScreen()->getLevelWidth() - player->getWidth());
		player->setXSpeed(0);
	}
	// update screen location based on player location
	PlayingScreen* screen = World::instance().getScreen();
	if (player->getX() - screen->getX() > screen->getCenterX(player->getWidth())
		&& (screen->getX() + screen->getScreenWidth()) < screen->getLevelWidth())
	{
		screen->setX(min(player->getX() - screen->getCenterX((player->getWidth())), screen->getLevelWidth() - screen->getScreenWidth()));
	}
	else if (player->getX() - screen->getX() < screen->getCenterX(player->getWidth())
		&& screen->getX() > 0)
	{
		screen->setX(max(player->getX() - screen->getCenterX((player->getWidth())), 0));
	}

	if (player->getY() - screen->getY() > screen->getCenterY(player->getHeight())
		&& (screen->getY() + screen->getScreenHeight()) < screen->getLevelHeight())
	{
		screen->setY(min(player->getY() - screen->getCenterY((player->getHeight())), screen->getLevelHeight() - screen->getScreenHeight()));
	}
	else if (player->getY() - screen->getY() < screen->getCenterY(player->getHeight())
		&& screen->getY() > 0)
	{
		screen->setY(max(player->getY() - screen->getCenterY((player->getHeight())), 0));
	}

	for(size_t i = 0; i < world.getObjects().size(); ++i) {
        QCoreApplication::processEvents();
        // checks to see if player the player collides with each object
        CollisionDetails* collision = player->checkCollision(world.getObjects().at(i));
        if (collision != NULL) {
            player->collide(collision);
            delete collision;
        }
    }
    //qDebug() << player->getX() << "," << player->getY(); // enable for testing purposes.

	for (size_t i = 0; i < world.getObjects().size(); ++i)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(world.getObjects().at(i));
        if (enemy != NULL)
        {
            enemy->move();
        }
    }

    for (int i = 0; i < ui->worldWidget->children().length(); i++)
    {
        QCoreApplication::processEvents();
        ObjectLabel * guiObject = dynamic_cast<ObjectLabel*>(ui->worldWidget->children().at(i));
        if (guiObject != NULL) {
            // updates the position of each label to the position of its object in the model
            guiObject->updateLabelPosition();
        }
    }

    for (int i = 0; i < ui->lblBackground->children().length(); i++ ) {
         QCoreApplication::processEvents();
         ObjectLabel * guiObject = dynamic_cast<ObjectLabel*>(ui->lblBackground->children().at(i));
         if (guiObject != NULL) {
			 // updates the position of each label to the position of its object in the model
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

    if (player->getBottomPoint() > World::instance().getScreen()->getLevelHeight())
	{
		player->setNumLives(player->getNumLives() - 1);
		if (player->getNumLives() > 0) {
			if (player->getNumLives() == 2){
				ui->lblLife3->hide();
			} else if (player->getNumLives() == 1){
				ui->lblLife2->hide();
			}
			player->setX(29);
			player->setY(212);
			ui->lblScore->setText("0");
			World::instance().setScore(0);
			World::instance().getScreen()->setLocation(0, 0);
			for (Object* worldObj : World::instance().getObjects()) {

				Coin * coin = dynamic_cast<Coin*>(worldObj);
				if (coin != NULL) {
					coin->setVisibility(true);
					coin->setisCollectible(true);
				}
			}
			showCoin();
		} else {
			ui->lblLife1->hide();
			EndGame * e = new EndGame(ui->worldWidget);
			e->show();
			timer->stop();
		}
    }
}

//displays all the coins in the world if the player has lives left
void MainWidget::showCoin() {
	for (Object* worldObj : World::instance().getObjects()) {

		Coin * coin = dynamic_cast<Coin*>(worldObj);
		if (coin != NULL) {

			int coinId = worldObj->getId();
			ObjectLabel * lbl;

			for (int i = 0; i < ui->worldWidget->children().length(); i++ ) {
				lbl = dynamic_cast<ObjectLabel*>(ui->worldWidget->children().at(i));

				if (lbl != NULL) {
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

