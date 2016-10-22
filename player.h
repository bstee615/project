#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player : public Object
{
    int xSpeed;
    int YSpeed;
public:
    void jump();
    void moveRight();
    void moveLeft();
};

#endif // PLAYER_H
