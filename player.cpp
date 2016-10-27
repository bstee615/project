#include "player.h"
#include "platform.h"
#include "enemy.h"
#include "collectible.h"

void Player::jump()
{
    if (jumpOnMove)
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
    if (jumpOnMove && onPlatform) {
        jump();
    }
    ++ySpeed;
    x += xSpeed;
    y += ySpeed;

    jumpOnMove = false;
    onPlatform = false;
}

void Player::collide(CollisionDetails *details)
{
    if (dynamic_cast<Platform*>(details->getCollided()) != NULL) {
        if (details->getXStopCollide() != 0) {
            xSpeed = 0;
            x += details->getXStopCollide();
        }
        if (details->getYStopCollide() != 0) {
            ySpeed = 0;
            y += details->getYStopCollide();
            if (details->getYStopCollide() < 0) {
                onPlatform = true;
            }
        }
    } else if (dynamic_cast<Collectible*>(details->getCollided()) != NULL) {

    }
}
