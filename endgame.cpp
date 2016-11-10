#include "endgame.h"
#include "ui_endgame.h"
#include "titlescreen.h"
#include "highscore.h"
#include "highscorepage.h"
#include "world.h"
#include <QRect>

EndGame::EndGame(QWidget *parent, bool gameOver_) :
    QWidget(parent),
	gameOver(gameOver_),
    ui(new Ui::EndGame)
{
    widgetParent = parent;
    ui->setupUi(this);
	if (!gameOver)
	{
		ui->lblTitle->setPixmap(QPixmap(":/images/LevelClear.png"));
		ui->lblBackground->setStyleSheet("");
	}
}

EndGame::~EndGame()
{
    delete ui;
}

bool EndGame::checkHighScore(){
    HighScore::instance().LoadScore(World::instance().getLevelName());
	if (World::instance().getScore() > HighScore::instance().getLowestScore()) {
		return true;
	} else {
		return false;
	}
}

void EndGame::on_PBcontinue_clicked()
{
	if (!gameOver && checkHighScore()) {
		int place = HighScore::instance().NewHighScore(World::instance().getScore());
        TitleScreen * title = new TitleScreen(widgetParent);
        title->show();
        title->raise();
        HighScorePage * highScoreScreen = new HighScorePage(title);
		highScoreScreen->setScore(World::instance().getScore());
		highScoreScreen->setPlace(place);
		for( int i = 0; i < highScoreScreen->children().size(); i++) {

			QLabel* textLabel =dynamic_cast<QLabel*>(highScoreScreen->children().at(i));

			if( textLabel != NULL ) {
				textLabel->hide();
			}
		}
		highScoreScreen->show();
		highScoreScreen->raise();
		highScoreScreen->showNameEnter(true);
	}
	else
	{
		TitleScreen* title = new TitleScreen(widgetParent);
		title->show();
		title->raise();
	}
    deleteLater();
}
