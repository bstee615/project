#ifndef SERVERSCREEN_H
#define SERVERSCREEN_H

#include <QWidget>

namespace Ui {
class serverscreen;
}

class serverscreen : public QWidget
{
    Q_OBJECT

public:
    explicit serverscreen(QWidget *parent = 0);
    ~serverscreen();

private slots:
    void on_btnEasy_clicked();

    void on_btnMedium_clicked();

    void on_btnHard_clicked();

    void on_btnCustomda_clicked();

private:
    Ui::serverscreen *ui;
};

#endif // SERVERSCREEN_H
