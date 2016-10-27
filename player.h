#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player : public Object
{
    int xSpeed;
    int ySpeed;
    bool jumpOnMove;
public:
    Player() : Object(), xSpeed(0),ySpeed(0),jumpOnMove(false) {}
	Player(int x_, int y_, int width_, int height_, QString image_) :
        Object(x_, y_, width_, height_, image_), xSpeed(0), ySpeed(0), jumpOnMove(false) {}

    void jump();
    void moveRight();
    void moveLeft();
    void slowToStop();
    void move();
    virtual void collide(CollisionDetails *details);

    void setJumpOnMove(bool initJump) { jumpOnMove = initJump; }
};

#endif // PLAYER_H
