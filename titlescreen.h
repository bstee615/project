#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QWidget>
#include "mainwidget.h"

namespace Ui {
class TitleScreen;
}

class TitleScreen : public QWidget
{
	Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = 0);
    ~TitleScreen();

    bool isPlaying() { return playing; }

private slots:
	void on_btnStart_clicked();

    void on_lblHighScores_clicked();

    void on_pushButton_clicked();

    void on_btnMedium_clicked();

private:
	Ui::TitleScreen *ui;
    QWidget* widgetParent;

    bool playing;
};

#endif // TITLESCREEN_H
