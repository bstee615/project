#include "highscorepage.h"
#include "ui_highscorepage.h"
#include "titlescreen.h"
#include "mainwidget.h"
#include "highscore.h"


HighScorePage::HighScorePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighScorePage)
{
     widgetParent = parent;
     ui->setupUi(this);
     HighScore::instance().LoadScore();

     ui->lblNewHighScoreInfo->hide();
     ui->ledNewName->hide();
     ui->btnEnterName->hide();

     ui->lblHighscore1->setText(QString("%1").arg(HighScore::instance().getScore(0)));
     ui->lblHighscore2->setText(QString("%1").arg(HighScore::instance().getScore(1)));
     ui->lblHighscore3->setText(QString("%1").arg(HighScore::instance().getScore(2)));
     ui->lblHighscore4->setText(QString("%1").arg(HighScore::instance().getScore(3)));
     ui->lblHighscore5->setText(QString("%1").arg(HighScore::instance().getScore(4)));
     ui->lblHighscore6->setText(QString("%1").arg(HighScore::instance().getScore(5)));
     ui->lblHighscore7->setText(QString("%1").arg(HighScore::instance().getScore(6)));
     ui->lblHighscore8->setText(QString("%1").arg(HighScore::instance().getScore(7)));
     ui->lblHighscore9->setText(QString("%1").arg(HighScore::instance().getScore(8)));
     ui->lblHighscore10->setText(QString("%1").arg(HighScore::instance().getScore(9)));

     ui->lblName1->setText(QString::fromStdString(HighScore::instance().getName(0)));
     ui->lblName2->setText(QString::fromStdString(HighScore::instance().getName(1)));
     ui->lblName3->setText(QString::fromStdString(HighScore::instance().getName(2)));
     ui->lblName4->setText(QString::fromStdString(HighScore::instance().getName(3)));
     ui->lblName5->setText(QString::fromStdString(HighScore::instance().getName(4)));
     ui->lblName6->setText(QString::fromStdString(HighScore::instance().getName(5)));
     ui->lblName7->setText(QString::fromStdString(HighScore::instance().getName(6)));
     ui->lblName8->setText(QString::fromStdString(HighScore::instance().getName(7)));
     ui->lblName9->setText(QString::fromStdString(HighScore::instance().getName(8)));
     ui->lblName10->setText(QString::fromStdString(HighScore::instance().getName(9)));

}

HighScorePage::~HighScorePage()
{
    delete ui;
}

void HighScorePage::on_btnReturnHome_clicked()
{
    TitleScreen* title = new TitleScreen(widgetParent);
    title->show();
    title->raise();
    deleteLater();
}

void HighScorePage::showNameEnter(){
    ui->btnReturnHome->hide();
    ui->lblNewHighScoreInfo->show();
    ui->ledNewName->show();
    ui->btnEnterName->show();
}


void HighScorePage::on_btnEnterName_clicked()
{
    name = ui->ledNewName->text();
    string nameInString = name.toStdString();
    HighScore::instance().NewHighScoreName(nameInString, place);
    setScoreandPlace(score, place);
    for( int i = 0; i < this->children().size(); i++) {

            QLabel* textLabel =dynamic_cast<QLabel*>(this->children().at(i));

            if( textLabel != NULL ) {
                     textLabel->show();
            }
    }
    ui->btnReturnHome->show();
    ui->lblNewHighScoreInfo->hide();
    ui->ledNewName->hide();
    ui->btnEnterName->hide();
    HighScore::instance().SaveScores("highscores.txt");
}

void HighScorePage::setScoreandPlace(int newScore, int newPlace){
    if (newPlace == 0) {
         ui->lblHighscore1->setText(QString("%1").arg(newScore));
         ui->lblName1->setText(name);
    } else if (newPlace == 1) {
        ui->lblHighscore2->setText(QString("%1").arg(newScore));
        ui->lblName2->setText(name);
    } else if (newPlace == 2) {
        ui->lblHighscore3->setText(QString("%1").arg(newScore));
        ui->lblName3->setText(name);
    } else if (newPlace == 3) {
        ui->lblHighscore4->setText(QString("%1").arg(newScore));
        ui->lblName4->setText(name);
    } else if (newPlace == 4) {
        ui->lblHighscore5->setText(QString("%1").arg(newScore));
        ui->lblName5->setText(name);
    } else if (newPlace == 5) {
        ui->lblHighscore6->setText(QString("%1").arg(newScore));
        ui->lblName6->setText(name);
    } else if (newPlace == 6) {
        ui->lblHighscore7->setText(QString("%1").arg(newScore));
        ui->lblName7->setText(name);
    } else if (newPlace == 7) {
        ui->lblHighscore8->setText(QString("%1").arg(newScore));
        ui->lblName8->setText(name);
    } else if (newPlace == 8) {
        ui->lblHighscore9->setText(QString("%1").arg(newScore));
        ui->lblName9->setText(name);
    } else {
        ui->lblHighscore10->setText(QString("%1").arg(newScore));
        ui->lblName10->setText(name);
    }
}
