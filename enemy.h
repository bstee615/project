#ifndef ENEMY_H
#define ENEMY_H

#include <QString>

#include "object.h"

class Enemy : public Object
{
    int damage;
    int speed;
    bool right;// if false, then enemy is facing left.
    bool flying;

public:
    Enemy(): Object() { }
    Enemy(int x_, int y_, int width_, int height_, QString image_, int damage_, int speed_);

    void move();
    bool isOnPlatform();
    void collide(CollisionDetails* details);

    bool isRight() { return right; }
    bool isFlying() { return flying; }
};

#endif // ENEMY_H
