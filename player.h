#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player : public Object
{
    bool jumpOnMove;
    int numLives;
    bool movable;
    bool left;

public:
    Player() : Object(),jumpOnMove(false), numLives(3) {}
    Player(int x_, int y_, int width_, int height_, QString image_) :
        Object(x_, y_, width_, height_, image_), jumpOnMove(false), numLives(3), movable(true) {}

    void jump();
    void moveRight();
    void moveLeft();
    void slowToStop();
    void move();
    virtual void collide(CollisionDetails *details);

    int getNumLives() { return numLives; }
    void setNumLives(int newNumLives) { numLives = newNumLives; }
    bool canJumpOnMove() { return jumpOnMove; }
    void setJumpOnMove(bool initJump) { jumpOnMove = initJump; }

    void setLeft(bool newDir) { left = newDir; }
    bool isLeft() { return left; }

    bool canMove() { return movable; }
    void toggleCanMove() { movable = !movable; }
};

#endif // PLAYER_H
