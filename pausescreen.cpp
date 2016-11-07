#include "pausescreen.h"
#include "ui_pausescreen.h"
#include "world.h"
#include "loadsave.h"
#include "helpscreen.h"


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
    HelpScreen * h = new HelpScreen();
    h->raise();
    h->show();
}

void PauseScreen::on_btnCheat_clicked()
{
	QPushButton* button = dynamic_cast<QPushButton*>(sender());
	if (button != NULL)
	{
		if (button->text() == "Cheat Mode: OFF")
		{
			button->setText("Cheat Mode: ON");
            World::instance().setCheat(true);
            World::instance().getPlayer()->setPower("shield",true);
            World::instance().getPlayer()->setPower("jump",true);
		}
		else
		{
			button->setText("Cheat Mode: OFF");
            World::instance().setCheat(true);
            World::instance().getPlayer()->setPower("shield",false);
            World::instance().getPlayer()->setPower("jump",false);
		}
	}
}

void PauseScreen::on_btnRestart_clicked()
{
	emit restartClicked();
	deleteLater();
}

void PauseScreen::on_btnSaveState_clicked()
{
	LoadSave::instance().save("saveState.save");
}

void PauseScreen::on_btnTitle_clicked()
{

}

void PauseScreen::on_btnExit_clicked()
{
	QApplication::exit(0);
}
