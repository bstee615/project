#include <QTimer>
#include "titlescreen.h"
#include "ui_titlescreen.h"
#include "mainwidget.h"
#include "highscorepage.h"

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

void TitleScreen::on_lblHighScores_clicked()
{
    this->hide();
    HighScorePage * scorePage = new HighScorePage(this->parentWidget());
    scorePage->show();
    scorePage->raise();
}
