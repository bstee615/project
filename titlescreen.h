#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QWidget>

namespace Ui {
class TitleScreen;
}

class TitleScreen : public QWidget
{
	Q_OBJECT

public:
	explicit TitleScreen(QWidget *parent = 0);
    ~TitleScreen();

private slots:
	void on_btnStart_clicked();

    void on_lblHighScores_clicked();

private:
	Ui::TitleScreen *ui;
    QWidget* widgetParent;
};

#endif // TITLESCREEN_H
