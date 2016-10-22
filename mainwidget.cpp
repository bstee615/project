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

	QLabel* lblPlayer = new QLabel(ui->worldWidget);
	lblPlayer->show();
	lblPlayer->setGeometry(0, 0, 25, 48);
	lblPlayer->setPixmap(QPixmap(":/images/maincharacter/maincharacterstand.png"));

	Platform* plat = new Platform(0, ui->worldWidget->geometry().height() - 60, 150, 60, "");
	World::instance().add(plat);
	Platform* plat2 = new Platform(100, 120, 150, 20, "");
	World::instance().add(plat2);
	Platform* plat3 = new Platform(200, ui->worldWidget->geometry().height() - 60, ui->worldWidget->geometry().width() - 200, 60, "");
	World::instance().add(plat3);

	for (Object* worldObj : World::instance().getObjects())
	{
		Platform* platform = dynamic_cast<Platform*>(worldObj);
		if (platform != NULL)
		{
			QLabel* lblPlatform = new QLabel(ui->worldWidget);
			lblPlatform->setGeometry(platform->getX(), platform->getY(), platform->getWidth(), platform->getHeight());
			lblPlatform->setStyleSheet(QStringLiteral("background-color: black;"));
			lblPlatform->show();
		}
	}
	lblPlayer->raise();
}

MainWidget::~MainWidget()
{
	delete ui;
}
