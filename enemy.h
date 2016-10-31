#ifndef ENEMY_H
#define ENEMY_H

#include <QString>

#include "object.h"

class Enemy : public Object
{
    int damage;
    bool right;// if false, then enemy is facing left.
    bool up;

    int initX;
    int initY;

    bool flying;

public:
    Enemy(): Object()
    {
        damage = 0;
        right = true;
        onPlatform = true;
        up = false;
        xSpeed = 3;
        ySpeed = 0;
    }

	virtual void load(QString config);
	virtual QString save();

    virtual void move();
    virtual void collide(CollisionDetails* details);

    virtual int getSpeed() { return xSpeed; }
    virtual bool isRight() { return right; }
    virtual bool isUp() { return up; }

	virtual void setInitX(int newX) { initX = newX; }
	virtual void setInitY(int newY) { initY = newY; }
    virtual int getInitX() { return initX; }
    virtual int getInitY() { return initY; }

    void setDamage(int newDamage) { damage = newDamage; }

    virtual void toggleMovingRight() { right = !right; }
    virtual void toggleMovingUp() { up = !up; }
    virtual bool isFlying() { return flying; }
    virtual void setFlying(bool fly) { flying = fly; }
};

#endif // ENEMY_H
