#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void LoadLevel(std::string filename);
private slots:
      void timerHit();
private:
    Ui::MainWidget *ui;
    QTimer * timer;
};

class ObjectLabel {
    private:
    int id;

    public:
    int getId() { return id; }
    void setId(int newId) { id = newId; }
};

#endif // MAINWIDGET_H
