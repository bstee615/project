
#include "serverscreen.h"
#include "ui_serverscreen.h"
#include "mainwidget.h"
#include "QMessageBox"
#include <QTcpServer>

serverscreen::serverscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverscreen)
{
    ui->setupUi(this);
    MainWidget* main = dynamic_cast<MainWidget*>(parent);
    if (!main->getServer().listen(QHostAddress::Any, 5000)) {
            QMessageBox::critical(this, "Uh oh", "Cannot start socket.");
            deleteLater();
        }
}

serverscreen::~serverscreen()
{
    delete ui;
}

void serverscreen::on_btnEasy_clicked()
{
    ui->btnCustomda->setChecked(false);
    ui->btnHard->setChecked(false);
    ui->btnMedium->setChecked(false);
    ui->leCustom->setText("");
    ui->leCustom->setDisabled(true);
}

void serverscreen::on_btnMedium_clicked()
{
    ui->btnCustomda->setChecked(false);
    ui->btnHard->setChecked(false);
    ui->btnEasy->setChecked(false);
    ui->leCustom->setText("");
    ui->leCustom->setDisabled(true);
}

void serverscreen::on_btnHard_clicked()
{
    ui->btnCustomda->setChecked(false);
    ui->btnEasy->setChecked(false);
    ui->btnMedium->setChecked(false);
    ui->leCustom->setText("");
    ui->leCustom->setDisabled(true);
}

void serverscreen::on_btnCustomda_clicked()
{
    ui->btnEasy->setChecked(false);
    ui->btnHard->setChecked(false);
    ui->btnMedium->setChecked(false);

    if (ui->btnCustomda->isChecked()) {
        ui->leCustom->setDisabled(false);
    } else {
        ui->leCustom->setDisabled(true);
    }
}
