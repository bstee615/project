#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player : public Object
{
    bool jumpOnMove;
    int numLives;
    bool movable;
    bool left;
    bool reachedEndGame;
	int startX, startY;

public:
	Player() : Object(),jumpOnMove(false), numLives(3), movable(true), reachedEndGame(false) {}
	Player(int x_, int y_, int width_, int height_, QString image_, int startX_, int startY_) :
		Object(x_, y_, width_, height_, image_), jumpOnMove(false), numLives(3), movable(true), reachedEndGame(false), startX(startX_), startY(startY_) {}

	virtual void load(QString config);
	virtual QString save();

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

    bool getIsAtEndOfLevel() { return reachedEndGame; }
    void setAtEndOfLevel(bool stateOfPlayer) { reachedEndGame = stateOfPlayer; }

	int getStartX() {return startX;}
	int getStartY() {return startY;}
	void setStartX(int newX) {startX = newX;}
	void setStartY(int newY) {startY = newY;}
	void setStartPoint(int newX, int newY) {startX = newX; startY = newY;}
};

#endif // PLAYER_H
