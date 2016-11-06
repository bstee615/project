#ifndef ENDGAME_H
#define ENDGAME_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class EndGame;
}

class EndGame : public QWidget
{
    Q_OBJECT

public:
    EndGame(QWidget *parent = 0);
    ~EndGame();

	bool checkHighScore();

private slots:
	void on_PBcontinue_clicked();

private:
    Ui::EndGame *ui;
    QWidget* widgetParent;
};

#endif // ENDGAME_H
