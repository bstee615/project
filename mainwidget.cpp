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
//	lblPlayer->show();
//	lblPlayer->setGeometry(0, 0, 25, 48);
//	lblPlayer->setPixmap(QPixmap(":/images/maincharacter/maincharacterstand.png"));

//	Platform* plat = new Platform(0, ui->worldWidget->geometry().height() - 60, 150, 60, "");
//	World::instance().add(plat);
//	Platform* plat2 = new Platform(100, 120, 150, 20, "");
//	World::instance().add(plat2);
//	Platform* plat3 = new Platform(200, ui->worldWidget->geometry().height() - 60, ui->worldWidget->geometry().width() - 200, 60, "");
//	World::instance().add(plat3);

	World::instance().loadLevel(":/easy.lv");

	qDebug() << World::instance().getObjects().size();

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
			lblPlatform->setStyleSheet(QStringLiteral("background-color: orange;"));
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
