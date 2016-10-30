#include "endgame.h"
#include "ui_endgame.h"

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
