#include "helpscreen.h"
#include "ui_helpscreen.h"
#include "titlescreen.h"

HelpScreen::HelpScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpScreen)
{
    widgetParent = parent;
    ui->setupUi(this);
}

HelpScreen::~HelpScreen()
{
    delete ui;
}

void HelpScreen::on_btnReturntoHome_clicked()
{
    TitleScreen* title = new TitleScreen(widgetParent);
    title->show();
    title->raise();
    this->deleteLater();
}
