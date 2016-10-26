#include "player.h"
#include "platform.h"

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
        image = ":/images/maincharacter/stand.png";
        return;
    } else if(xSpeed > 0) {
        --xSpeed;
        image = ":/images/maincharacter/jump4.png";
        return;
    } else {
        ++xSpeed;
    }
}

void Player::move()
{
    ++ySpeed;
    x += xSpeed;
    y += ySpeed;
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
        }
    }
}
