#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player : public Object
{
    int xSpeed;
    int ySpeed;
public:
    Player() : Object(), xSpeed(0),ySpeed(0) {}
	Player(int x_, int y_, int width_, int height_, QString image_) :
        Object(x_, y_, width_, height_, image_), xSpeed(0), ySpeed(0) {}

    void jump();
    void moveRight();
    void moveLeft();
    void slowToStop();
    void move();
};

#endif // PLAYER_H
