#ifndef ENEMY_H
#define ENEMY_H

#include <QString>


#include "object.h"
#include "platform.h"

class Enemy : public Object
{
protected:
    Platform* currentPlatform;// used to tell the Enemy when it has reached a ledge.

public:
    Enemy();
    Enemy(int x_, int y_, int width_, int height_, QString image_);

	virtual void load(QString config);
	virtual QString save();

    virtual void move();
    virtual void collide(CollisionDetails* details);
};

class FlyingEnemy: public Enemy
{
    bool up;
    int xCount;
	int startX, startY;

public:
    FlyingEnemy(): Enemy(), up(true), xCount(0) { ySpeed = 2; }
    FlyingEnemy(int x_, int y_, int width_, int height_, QString image_): Enemy(x_,y_,width_,height_,image_), up(true), xCount(0) { ySpeed = 2; }

    void move();
    void collide(CollisionDetails*);

	virtual void load(QString config);
	virtual QString save();

	int getStartX() {return startX;}
	int getStartY() {return startY;}

	void setStartX(int x) {startX = x;}
	void setStartY(int y) {startY = y;}
};

#endif // ENEMY_H
