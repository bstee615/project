#ifndef ENEMY_H
#define ENEMY_H

#include <QString>

#include "object.h"

class Enemy : public Object
{
    int damage;
    bool right;// if false, then enemy is facing left.

public:
    Enemy(): Object()
    {
        damage = 0;
        right = true;
        onPlatform = true;
        xSpeed = 3;
        ySpeed = 0;
    }

	virtual void load(QString config);
	virtual QString save();

    virtual void move();
    virtual void collide(CollisionDetails* details);

    virtual int getSpeed() { return xSpeed; }
    virtual bool isRight() { return right; }
    virtual void setRight(bool newRight) { right = newRight; }

    void setDamage(int newDamage) { damage = newDamage; }
};

class FlyingEnemy: public Enemy
{
    bool up;
    int initY;

public:
    FlyingEnemy(): Enemy(), up(true) { }

    void move();
    void collide(CollisionDetails*);

    virtual void setInitY(int newY) { initY = newY; }
    virtual int getInitY() { return initY; }
};

#endif // ENEMY_H
