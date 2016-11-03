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
	QPushButton* pushed = dynamic_cast<QPushButton*>(sender());
	if (pushed != NULL)
	{
		if (pushed->text() == "Cheat Mode: OFF")
		{
			pushed->setText("Cheat Mode: ON");
		}
		else
		{
			pushed->setText("Cheat Mode: OFF");
		}
	}
}

void PauseScreen::on_btnRestart_clicked()
{

}

void PauseScreen::on_btnSaveState_clicked()
{

}

void PauseScreen::on_btnTitle_clicked()
{

}

void PauseScreen::on_btnExit_clicked()
{

}
