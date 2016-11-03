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

void PauseScreen::on_btnResume_clicked()
{
	emit resumeClicked();
	deleteLater();
}

void PauseScreen::on_btnHelp_clicked()
{

}

void PauseScreen::on_btnCheat_clicked()
{

}

void PauseScreen::on_btnTitle_clicked()
{

}

void PauseScreen::on_btnExit_clicked()
{

}
