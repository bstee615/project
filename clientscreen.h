#ifndef CLIENTSCREEN_H
#define CLIENTSCREEN_H

#include <QWidget>

namespace Ui {
class ClientScreen;
}

class ClientScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ClientScreen(QWidget *parent = 0);
    ~ClientScreen();

private slots:
    void on_btnConnect_clicked();

private:
    Ui::ClientScreen *ui;
};

#endif // CLIENTSCREEN_H
