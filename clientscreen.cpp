#include "clientscreen.h"
#include "ui_clientscreen.h"

ClientScreen::ClientScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientScreen)
{
    ui->setupUi(this);
}

ClientScreen::~ClientScreen()
{
    delete ui;
}
