#include "pausescreen.h"
#include "ui_pausescreen.h"

PauseScreen::PauseScreen(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PauseScreen)
{
	ui->setupUi(this);
//	if (World::instance().cheating())
//		ui->btnCheat->setText("Cheat Mode: ON");	// add these lines later once we have a cheat bool
//	else
		ui->btnCheat->setText("Cheat Mode: OFF");
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
	QPushButton* button = dynamic_cast<QPushButton*>(sender());
	if (button != NULL)
	{
		if (button->text() == "Cheat Mode: OFF")
		{
			button->setText("Cheat Mode: ON");
		}
		else
		{
			button->setText("Cheat Mode: OFF");
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
