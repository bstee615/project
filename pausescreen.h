#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <QWidget>

namespace Ui {
class PauseScreen;
}

class PauseScreen : public QWidget
{
	Q_OBJECT

public:
	explicit PauseScreen(QWidget *parent = 0);
	~PauseScreen();

private:
	Ui::PauseScreen *ui;
};

#endif // PAUSESCREEN_H
