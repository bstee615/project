#ifndef HIGHSCOREPAGE_H
#define HIGHSCOREPAGE_H

#include <QWidget>

namespace Ui {
class HighScorePage;
}

class HighScorePage : public QWidget
{
    Q_OBJECT

public:
    explicit HighScorePage(QWidget *parent = 0);
    ~HighScorePage();

private slots:
    void on_btnReturnHome_clicked();

private:
    Ui::HighScorePage *ui;
    QWidget * widgetParent;
};

#endif // HIGHSCOREPAGE_H
