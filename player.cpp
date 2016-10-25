#include "player.h"

void Player::jump()
{
    ySpeed -= 10;
}

void Player::moveRight()
{
    if (xSpeed < 5) {
        xSpeed += 1;
    }
    x += xSpeed;
}

void Player::moveLeft()
{
    if (xSpeed > -5) {
        xSpeed += -1;
    }
    x += xSpeed;
}

void Player::slowToStop()
{
    if (xSpeed == 0) {
        return;
    } else if(xSpeed > 0) {
        --xSpeed;
        return;
    } else {
        ++xSpeed;
    }
}

void Player::move()
{
    //++ySpeed;
    x += xSpeed;
    y += ySpeed;
}
