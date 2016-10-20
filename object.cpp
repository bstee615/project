#include "object.h"

Object::Object()
{

}

void Object::CheckCollision(Object *that)
{

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
