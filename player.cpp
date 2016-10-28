#include "player.h"
#include "platform.h"
#include "enemy.h"
#include "coin.h"
#include "world.h"

void Player::jump()
{
    // player jumps if jumpOnMove is true
    if (jumpOnMove) {
        ySpeed -= 10;
    }
}

void Player::moveRight()
{
    // player accelerates up to a speed of 8 pixels per timer hit
    if (xSpeed < 9) {
        xSpeed += 1;
    }
}

void Player::moveLeft()
{
    // player accelerates up to a speed of 8 pixels per timer hit
    if (xSpeed > -9) {
        xSpeed += -1;
    }
}

void Player::slowToStop()
{
    // slows the player down to an xSpeed of zero
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
    // if a player is on a platform and jumpmove is true the player jumps
    if (jumpOnMove && onPlatform) {
        jump();
    }
    // gravity accelerates the player down 1 pixel per timer hit
    ++ySpeed;

    // updates the x and y coordinates for the player
    x += xSpeed;
    y += ySpeed;

    // sets to false so that a player cannot jump while not on a platform
    jumpOnMove = false;
    onPlatform = false;
}

void Player::collide(CollisionDetails *details)
{
    if (dynamic_cast<Platform*>(details->getCollided()) != NULL) {
        //BUG: when the player jumps into the right side of a platform, he pops back on top instead of getting blocked.
        //^Small issue, but something to fix pre-production.^

        // if it the Object from the collision is a Platform update the position of the
        // player based on the xStopCollide and yStopCollide values
        if (details->getXStopCollide() != 0) {
            xSpeed = 0;
            x += details->getXStopCollide();
        }
        if (details->getYStopCollide() != 0) {
            ySpeed = 0;
            y += details->getYStopCollide();
            if (details->getYStopCollide() < 0) {
                // the player is on a platform so onPlatform is true
                onPlatform = true;
            }
        }
    } else if (dynamic_cast<Coin*>(details->getCollided()) != NULL) {
        //set coin visibility to false and add to high score in world
        Coin * c = dynamic_cast<Coin*>(details->getCollided());
        c->setVisibility(false);
        World::instance().incScore(c->getAmount());

    }
}
