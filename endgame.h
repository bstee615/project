#ifndef ENDGAME_H
#define ENDGAME_H

#include <QWidget>

namespace Ui {
class EndGame;
}

class EndGame : public QWidget
{
    Q_OBJECT

public:
    explicit EndGame(QWidget *parent = 0);
    ~EndGame();

private:
    Ui::EndGame *ui;
    QWidget* widgetParent;
};

#endif // ENDGAME_H
