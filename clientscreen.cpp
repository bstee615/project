#include "clientscreen.h"
#include "ui_clientscreen.h"
#include "mainwidget.h"
#include <QMessageBox>

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

void ClientScreen::on_btnConnect_clicked()
{
    QString hostname = ui->btnConnect->text();
    MainWidget* main = dynamic_cast<MainWidget*>(parentWidget());
    delete main->getSocket();
    QTcpSocket* socket = main->getSocket();
    socket = new QTcpSocket();
    socket->connectToHost(hostname, 5000);
    if(!socket->waitForConnected()) {
        QMessageBox::warning(main,"Error","The connection failed.");
    }
}
