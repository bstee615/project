#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player : public Object
{
    int xSpeed;
    int YSpeed;
public:
	Player() : Object() {};
	Player(int x_, int y_, int width_, int height_, QString image_) :
		Object(x_, y_, width_, height_, image_) {}

    void jump();
    void moveRight();
    void moveLeft();
};

#endif // PLAYER_H
