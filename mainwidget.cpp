#include <QLabel>
#include <QDebug>
#include <QDesktopWidget>
#include <QTimer>
#include <QKeyEvent>
#include <cmath>
#include <QTime>

#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "world.h"
#include "titlescreen.h"
#include "endgame.h"
#include "highscore.h"
#include "highscorepage.h"
#include "loadsave.h"


MainWidget::MainWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainWidget)
{
	ui->setupUi(this);
	ui->lblLife1->raise();
	ui->lblLife2->raise();
	ui->lblLife3->raise();
	ui->lblScore->raise(); // these components should not be under the world objects
	ui->lblTimeLeft->raise();

	timer = new QTimer(this);
	timer->setInterval(50);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));

	clock = new QTimer(this);
	clock->setInterval(1000);
	connect(clock, SIGNAL(timeout()), this, SLOT(clockHit()));

	right = false;
	left = false;
	TitleScreen* titleScrn = new TitleScreen(this);
	titleScrn->show();
	titleScrn->raise();
}

void MainWidget::loadLevel(QString filename)
{
	ui->lblBackground->setPixmap(QString(":/images/easybackground.png"));

	ObjectLabel* lblPlayer = NULL;
	ObjectLabel* lblEndLevel = NULL;

	//Deletes all objects from the last game
	for (int i = 0; i < ui->worldWidget->children().size(); ++i) {
		if (dynamic_cast<ObjectLabel*>(ui->worldWidget->children().at(i)) != NULL){
			ui->worldWidget->children().at(i)->deleteLater();
		}
	}


	LoadSave::instance().load(filename);
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
		label->setPixmap(QPixmap(worldObj->getImage()));
		label->show();
		label->getObject()->setVisibility(true);
	}

	if (lblPlayer != NULL)
	{
		lblPlayer->raise();
		labelPlayer = lblPlayer;
	}
	ui->lblLife1->show();
	ui->lblLife2->show();
	ui->lblLife3->show();

	World::instance().setSeconds(World::instance().getStartSeconds());

	if (World::instance().getSeconds() < 10) {
		int i = World::instance().getSeconds();
		QString timeFormated = QString("0:0%1").arg(i);
		ui->lblTimeLeft->setText(timeFormated);
	} else {
		int i = World::instance().getSeconds();
		QString timeFormated = QString("0:%1").arg(i);
		ui->lblTimeLeft->setText(timeFormated);
	}
}

void MainWidget::setWalkImage(Player* player)
{
	if (!player->canMove())
		return;
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

	labelPlayer->setPixmap(player->getImage());
	player->advanceCount();

	if ((right && left) || (!right && !left)) {
		// if both right and left arrows are held down or both are released slow the player to a stop
		player->slowToStop();
		player->setCount(0);
		normalImage();
	} else if (right) {
		// if the right arrow is pressed the player goes right
		player->moveRight();
		setWalkImage(player);
	} else if (left) {
		// if the left arrow is pressed the player goes left
		player->moveLeft();
		setWalkImage(player);
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

	vector<MoveThread*> moveThreads;
	for (size_t i = 0; i < world.getObjects().size(); i ++)
	{
		QCoreApplication::processEvents();
		moveThreads.push_back(new MoveThread(world.getObjects().at(i)));
		moveThreads.at(i)->start();
	}

	for (size_t i = 0; i < moveThreads.size(); ++i) {
		QCoreApplication::processEvents();
		MoveThread* currentThread = moveThreads.at(i);
		currentThread->wait();
		delete currentThread;
	}

	for(size_t i = 0; i < world.getObjects().size(); ++i) {
		QCoreApplication::processEvents();
		// checks to see if player the player collides with each object
		CollisionDetails* collision = player->checkCollision(world.getObjects().at(i));
		if (collision != NULL) {
			player->collide(collision);
			if (dynamic_cast<Enemy*>(collision->getCollided()))
				death(player);
		}
		delete collision;
	}

	if (!player->canMove())
	{
		player->setImage(":/images/maincharacter/hurt.png");
		if (player->isLeft())
			player->setImage(":/images/maincharacter/hurtleft.png");

		QTimer::singleShot(10, this, SLOT(normalMove()));
		QTimer::singleShot(500, this, SLOT(normalImage()));
	}

	for (int i = 0; i < ui->worldWidget->children().length(); i++)
	{
		QCoreApplication::processEvents();
		ObjectLabel * guiObject = dynamic_cast<ObjectLabel*>(ui->worldWidget->children().at(i));
		if (guiObject != NULL) {
			// updates the position of each label to the position of its object in the model
			guiObject->updateLabelPosition();
			// showCoin method replacement
			if (dynamic_cast<Coin *>(guiObject->getObject()) != NULL) {
				if (guiObject->getObject()->getVisibility() == true) {
					guiObject->show();
				} else {
					guiObject->hide();
				}
			}
		}
	}


	// Andrew - I think I eliminated the need for this showCoin method 10 lines up.
	//showCoin();
	ui->lblScore->setText(QString::number(World::instance().getScore()));

	if (player->getIsAtEndOfLevel()) {
		EndGame * e = new EndGame(this);
		e->show();
		timer->stop();
		//checkhighscores();
		clock->stop();
	}

	if (player->getBottomPoint() > World::instance().getScreen()->getLevelHeight() || World::instance().getSeconds() == 0 )
	{
		death(player);
		resetPlayer(player);
	}
}

void MainWidget::clockHit()
{
	World::instance().setSeconds(World::instance().getSeconds() - 1);
	if (World::instance().getSeconds() < 10) {
		int i = World::instance().getSeconds();
		QString timeFormated = QString("0:0%1").arg(i);
		ui->lblTimeLeft->setText(timeFormated);
	} else {
		int i = World::instance().getSeconds();
		QString timeFormated = QString("0:%1").arg(i);
		ui->lblTimeLeft->setText(timeFormated);
	}
	if (World::instance().getSeconds() == 0)
	{
		death(World::instance().getPlayer());
		resetPlayer(World::instance().getPlayer());
	}
	//ui->lblTimeLeft->setText(QString::number(World::instance().getSeconds()));
}

void MainWidget::resetPlayer(Player* player)
{
	player->setX(29);
	player->setY(212);
	World::instance().setScore(0);
	ui->lblScore->setText("0");
	World::instance().getScreen()->setLocation(0, 0);
	clock->stop();
	World::instance().setSeconds(World::instance().getStartSeconds() + 1);
	clockHit();
	clock->start();

	for (Object* worldObj : World::instance().getObjects()) {

		Coin * coin = dynamic_cast<Coin*>(worldObj);
		if (coin != NULL) {
			coin->setVisibility(true);
			coin->setisCollectible(true);
		}
	}
	//showCoin();
}

void MainWidget::death(Player* player)
{

	player->setNumLives(player->getNumLives() - 1);

	if (player->getNumLives() > 0 && !player->getIsAtEndOfLevel()) {

		if (player->getNumLives() == 2){
			ui->lblLife3->hide();
		} else if (player->getNumLives() == 1){
			ui->lblLife2->hide();
		}

		//will need to split this to display different screens
	} else {
		ui->lblLife1->hide();
		EndGame * e = new EndGame(this);
		e->show();
		timer->stop();
		//checkhighscores();
		clock->stop();
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
				QCoreApplication::processEvents();
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
/*
 * void MainWidget::checkHighScore(){
 * if (World::instance.getScore() > HighScore::instance().getScore(9)) {
 *        //write up the HighScore::instance().NewHighScore(); method to return where the new score was entered in the array
 *        highScoreScreen = new HighScorePage(ui->worldWidget);
		  highScoreScreen->show();
		  highScoreScreen->raise();
		  //access the label on the screen based on where the score was entered
 *        HighScore::instance().SaveScores();
 * }
 */


MainWidget::~MainWidget() {
	ui->worldWidget->deleteLater();
	delete ui;
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
	Player* player = World::instance().getPlayer();

	if (event->key() == Qt::Key_Left) {
		this->left = true;
		player->setLeft(true);
	} else if (event->key() == Qt::Key_Right) {
		this->right = true;
		player->setLeft(false);
	} else if (event->key() == Qt::Key_Space) {
		Player* player = World::instance().getPlayer();
		player->setJumpOnMove(true);
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

void MainWidget::normalMove()
{
	Player* player = World::instance().getPlayer();
	player->toggleCanMove();

}

void MainWidget::normalImage()
{
	Player* player = World::instance().getPlayer();
	if (player->canMove())
	{
		player->setImage(":/images/maincharacter/stand.png");
		if (player->isLeft())
			player->setImage(":/images/maincharacter/standleft.png");
	}
}


void MoveThread::run()
{
	object->move();
}
