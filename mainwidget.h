#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>

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

private:
    Ui::MainWidget *ui;
    QTimer * timer; 
    bool right;
    bool left;
private slots:
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void timerHit();
};

class ObjectLabel : public QLabel {
    Q_OBJECT
    MainWidget * widget;
    int id;

    public:
    explicit ObjectLabel(MainWidget * parent): QLabel(parent) {
        widget = parent;
    }

    int getId() { return id; }
    void setId(int newId) { id = newId; }

    signals:
        void clicked();
};

#endif // MAINWIDGET_H
