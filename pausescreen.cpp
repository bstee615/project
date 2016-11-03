#include "pausescreen.h"
#include "ui_pausescreen.h"

PauseScreen::PauseScreen(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PauseScreen)
{
	ui->setupUi(this);
}

PauseScreen::~PauseScreen()
{
	delete ui;
}
