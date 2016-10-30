#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class MovableLabel;

namespace Ui {
class MainWindow;
}

class MovableLabel;

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void makePlatform(MovableLabel *label, QString file, bool& successful, QString& errorMSG);
    
private slots:

    void labelClicked();

    void on_PBmakeObject_clicked();

    void on_PBresize_clicked();

private:
    Ui::MainWindow *ui;
};


class MovableLabel : public QLabel
{
    Q_OBJECT

    bool mouseDragging;
    QPoint offset;

public:
    QString type;
    QString file;
    int xRange;
    int yRange;
    int xSpeed;
    int ySpeed;
    int amount;

    explicit MovableLabel(QWidget *parent): QLabel(parent) {
        setMouseTracking(true); // enable mouse move events
        mouseDragging = false;
    }
    void mouseMoveEvent(QMouseEvent *ev) {
        if (mouseDragging)
            this->move(mapToParent(ev->pos() - this->offset));
    }

    void mousePressEvent(QMouseEvent *ev) {
        mouseDragging = true;
        offset = ev->pos(); // location where mouse was clicked within the label
    }

    void mouseReleaseEvent(QMouseEvent *) {
        mouseDragging = false;
        emit clicked();
    }

signals:
    void clicked();

};

#endif // MAINWINDOW_H
