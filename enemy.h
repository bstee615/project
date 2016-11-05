#ifndef ENEMY_H
#define ENEMY_H

#include <QString>

#include "object.h"
#include "platform.h"

class Enemy : public Object
{
    int damage;// if false, then enemy is facing left.
    Platform* currentPlatform;

public:
    Enemy(): Object()
    {
        damage = 0;
        right = true;
        onPlatform = true;
        xSpeed = 3;
        ySpeed = 1;
        count = 0;
        currentPlatform = new Platform();
	}

	virtual void load(QString config);
	virtual QString save();

    virtual void move();
    virtual void collide(CollisionDetails* details);

    virtual int getSpeed() { return xSpeed; }

    void setDamage(int newDamage) { damage = newDamage; }
};

class FlyingEnemy: public Enemy
{
    bool up;
    int xCount;

public:
    FlyingEnemy(): Enemy(), up(true), xCount(0) { ySpeed = 2; }

    void move();
    void collide(CollisionDetails*);
};

#endif // ENEMY_H
