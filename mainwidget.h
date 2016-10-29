#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QImage>
#include <QObject>

#include"object.h"
#include "player.h"

class ObjectLabel : public QLabel {
    Q_OBJECT
    Object* object;
    QWidget * widget;
    int id;

    public:
    explicit ObjectLabel(QWidget * parent): QLabel(parent) {
        widget = parent;
        object = NULL;
    }

    int getId() { return id; }
    void setId(int newId) { id = newId; }
	void setObject(Object* initObject)
	{
		object = initObject;
		this->id = initObject->getId();
	}
    Object* getObject(){ return object; }

    // Updates the lable possistion to the position recoreded in the model
    void updateLabelPosition() {setGeometry(object->getX(),object->getY(),object->getWidth(),object->getHeight());}

    signals:
        void clicked();
};

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void loadLevel(std::string filename);

    bool canJump(Player* player);
    void resetOnDeath(Player* player);
    void setWalkImage(Player* player);
    void setJumpImage(Player* player);

private:
    Ui::MainWidget *ui;
    QTimer * timer; 
    bool right;
    bool left;

    ObjectLabel* labelPlayer;

private slots:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerHit();
};

#endif // MAINWIDGET_H
