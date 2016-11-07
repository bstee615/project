#include <QTimer>
#include "titlescreen.h"
#include "ui_titlescreen.h"
#include "mainwidget.h"
#include "highscorepage.h"
#include "highscore.h"
#include "mapmaker.h"
#include <QMessageBox>
#include <exception>
#include <stdexcept>
#include "serverscreen.h"
#include "clientscreen.h"


TitleScreen::TitleScreen(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::TitleScreen)
{
    widgetParent = parent;
	ui->setupUi(this);
    playing = false;
    ui->btnStart->setFocus();
    World::instance().setIsPlaying(false);
}

TitleScreen::~TitleScreen()
{
	delete ui;
}

void TitleScreen::on_btnStart_clicked()
{
	this->hide();
    this->widgetParent->setFocus();
    MainWidget * prnt = dynamic_cast<MainWidget *>(widgetParent);
    World::instance().setIsPlaying(true);
    if (prnt != NULL) {
        prnt->loadLevel(":/easy.lv");
        prnt->getTimer()->start();
        prnt->getClock()->start();
    }
    deleteLater();
}

void TitleScreen::on_lblHighScores_clicked()
{
    HighScorePage * scorePage = new HighScorePage(this->parentWidget());
    scorePage->show();
    scorePage->raise();

}

void TitleScreen::on_pushButton_clicked()
{
    MapMaker * maker = new MapMaker();
    maker->show();
    maker->raise();
}

void TitleScreen::on_btnMedium_clicked()
{
    this->hide();
    this->widgetParent->setFocus();
    MainWidget * prnt = dynamic_cast<MainWidget *>(widgetParent);
    if (prnt != NULL) {
        prnt->loadLevel(":/medium.lv");
        prnt->getTimer()->start();
        prnt->getClock()->start();
    }
    deleteLater();
}

void TitleScreen::on_btnOtherMap_clicked()
{
    if (ui->leOtherMap->text() == ""){
        QMessageBox::warning(this,"No File Specified", "Please enter a map to load.");
        return;
    }
    MainWidget * prnt = dynamic_cast<MainWidget *>(widgetParent);
    if (prnt != NULL) {
        try{
            prnt->loadLevel(ui->leOtherMap->text());
        } catch(exception error) {
            return;
        }
        prnt->getTimer()->start();
        prnt->getClock()->start();
    }
    this->hide();
    this->widgetParent->setFocus();
    deleteLater();
}

void TitleScreen::on_btnHard_clicked()
{
    this->hide();
    this->widgetParent->setFocus();
    MainWidget * prnt = dynamic_cast<MainWidget *>(widgetParent);
    if (prnt != NULL) {
        prnt->loadLevel(":/hard.lv");
        prnt->getTimer()->start();
        prnt->getClock()->start();
    }
    deleteLater();
}

void TitleScreen::on_pushButton_2_clicked()
{
    HelpScreen * help = new HelpScreen(this->parentWidget());
    help->show();
    help->raise();

    deleteLater();
}

void TitleScreen::on_btnServer_clicked()
{
    serverscreen* screen = new serverscreen(widgetParent);
    screen->show();
    screen->raise();

}

void TitleScreen::on_btnClient_clicked()
{
    ClientScreen* screen = new ClientScreen(widgetParent);
    screen->show();
    screen->raise();
}
