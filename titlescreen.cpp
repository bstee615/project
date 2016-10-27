#include "titlescreen.h"
#include "ui_titlescreen.h"
#include "mainwidget.h"

TitleScreen::TitleScreen(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TitleScreen)
{
    widgetParent = parent;
	ui->setupUi(this);
}

TitleScreen::~TitleScreen()
{
	delete ui;
}

void TitleScreen::on_btnStart_clicked()
{
	this->hide();
    this->widgetParent->setFocus();
}
