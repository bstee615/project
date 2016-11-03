#include "endgame.h"
#include "ui_endgame.h"
#include "titlescreen.h"
#include "world.h"
#include <QRect>

EndGame::EndGame(QWidget *parent)  :
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

void EndGame::on_PBbackToTitle_clicked()
{
    TitleScreen* title = new TitleScreen(widgetParent);
    title->show();
    title->raise();
    deleteLater();
}
