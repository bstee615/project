#ifndef ENEMY_H
#define ENEMY_H

#include <QString>

#include "object.h"

class Enemy : public Object
{
    int damage;
    int speed;
public:
    Enemy(): Object() { }
    Enemy(int x_, int y_, int width_, int height_, QString image_, int damage_, int speed_);

    void move();
    bool somethingisBelow();


};

#endif // ENEMY_H
