#include <QLabel>
#include <QDebug>
#include <QDesktopWidget>
#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "world.h"

MainWidget::MainWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainWidget)
{
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
