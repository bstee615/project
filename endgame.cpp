#include "endgame.h"
#include "ui_endgame.h"
#include "titlescreen.h"
#include "highscore.h"
#include "highscorepage.h"
#include "world.h"
#include <QRect>

EndGame::EndGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndGame)
{
    widgetParent = parent;
    ui->setupUi(this);
}

EndGame::~EndGame()
{
    delete ui;
}

bool EndGame::checkHighScore(){
	HighScore::instance().LoadScore();
	if (World::instance().getScore() > HighScore::instance().getLowestScore()) {
		return true;
	} else {
		return false;
	}
}

void EndGame::on_PBbackToTitle_clicked()
{
	if (checkHighScore()) {
		int place = HighScore::instance().NewHighScore(World::instance().getScore());
		HighScorePage * highScoreScreen = new HighScorePage(widgetParent);
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
