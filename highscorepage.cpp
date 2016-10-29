#include "highscorepage.h"
#include "ui_highscorepage.h"
#include "titlescreen.h"
#include "mainwidget.h"

HighScorePage::HighScorePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighScorePage)
{
     widgetParent = parent;
    ui->setupUi(this);
}

HighScorePage::~HighScorePage()
{
    delete ui;
}

void HighScorePage::on_btnReturnHome_clicked()
{
    this->deleteLater();
}
