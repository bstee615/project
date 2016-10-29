#ifndef ENEMY_H
#define ENEMY_H

#include <QString>

#include "object.h"

class Enemy : public Object
{
    int damage;
    int speed;
    bool facingRight;// if false, then enemy is facing left.

public:
    Enemy(): Object() { }
    Enemy(int x_, int y_, int width_, int height_, QString image_, int damage_, int speed_);

    virtual void move();
    bool isOnPlatform();
    virtual void collide(CollisionDetails* details);

    virtual int getSpeed() { return speed; }
    virtual bool isRight() { return facingRight; }
    virtual bool isFlying() { return false; }

    void setDamage(int newDamage) { damage = newDamage; }
    void setSpeed(int newSpeed) { speed = newSpeed; }
    void setRight(bool newRight) { facingRight = newRight; }
};

class FlyingEnemy:public Enemy
{
    bool movingUp;
public:
    FlyingEnemy(): Enemy() { }
    FlyingEnemy(int x_, int y_, int width_, int height_, QString image_, int damage_, int speed_): Enemy(x_, y_, width_, height_, image_, damage_, speed_), movingUp(true) { }

    void move();
    void collide(CollisionDetails* details);

    bool isUp() { return movingUp; }
    bool isFlying() { return true; }
};

#endif // ENEMY_H
