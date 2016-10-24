#include <QLabel>
#include <QDebug>
#include <QDesktopWidget>
#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "world.h"
#include "QKeyEvent"

MainWidget::MainWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainWidget)
{
    right = false;
    left = false;
	ui->setupUi(this);

	QLabel* lblPlayer = NULL;

    World::instance().loadLevel("easy.lv");

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
