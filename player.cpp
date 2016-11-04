#include "player.h"
#include "platform.h"
#include "enemy.h"
#include "coin.h"
#include "world.h"

QString Player::save()
{
	QString out = Object::save();
	out += "," + QString::number(this->getStartX());
	out += "," + QString::number(this->getStartY());
	out += "," + QString::number(this->getXSpeed());
	out += "," + QString::number(this->getYSpeed());
	return out;
}

void Player::load(QString config)
{
	Object::load(config);
	QList<QString> params = config.split(",");
	// set object properties specific to Player
	this->setStartPoint(params.at(6).toInt(), params.at(7).toInt());
	this->setXSpeed(params.at(8).toInt());
	this->setYSpeed(params.at(9).toInt());
    this->setCanMove(true);
}

void Player::jump()
{
	// player jumps if jumpOnMove is true
	if (jumpOnMove) {
		ySpeed -= 13;
        if (powerjump)
            ySpeed -= 7;
	}
}

void Player::moveRight()
{
    if (!canMove)
	{
		slowToStop();
		return;
	}

	// player accelerates up to a speed of 8 pixels per timer hit
    if (xSpeed < xSpeedLimit) {
		xSpeed += 1;
        if (powerspeed)
            xSpeed += 1;
	}

}

void Player::moveLeft()
{
    if (!canMove)
	{
		slowToStop();
		return;
	}

	// player accelerates up to a speed of 8 pixels per timer hit
    if (xSpeed > xSpeedLimit * -1) {
		xSpeed += -1;
        if (powerspeed)
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

    setWalkImage();
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
		if(c->getisCollectible() == true) {
            if (!powerScore())
                World::instance().incScore(c->getAmount());
            else
                World::instance().incScore(c->getAmount() * 2);
		}
		c->setisCollectible(false);

	}
    else if (dynamic_cast<Enemy*>(details->getCollided()) != NULL || dynamic_cast<FlyingEnemy*>(details->getCollided()) != NULL)
    {
        if (World::instance().getCheat())
        {
            return;
        }
        if (details->getYStopCollide() != 0)
        {
            World::instance().incScore(15);
            ySpeed = -10;
            if (details->getYStopCollide() > 0)
                ySpeed = 10;
            details->getCollided()->kill();
            return;
        }
        if (details->getXStopCollide() > 0 && details->getCollided()->isDead() == false)
        {
            if (kicking == true)
            {
                details->getCollided()->kill();
                xSpeed /= 2;
                return;
            }
            x += 5;
            ySpeed = -8;
            xSpeed = 12;
            canMove = false;
            details->getCollided()->setRight(false);
        }
        else if (details->getXStopCollide() < 0 && details->getCollided()->isDead() == false)
        {
            if (kicking == true)
            {
                details->getCollided()->kill();
                xSpeed /= 2;
                return;
            }
            x -= 5;
            ySpeed = -8;
            xSpeed = -12;
            canMove = false;
            details->getCollided()->setRight(true);
        }
        else
            canMove = true;
	} else if (dynamic_cast<EndGameObject*>(details->getCollided()) != NULL){
		setAtEndOfLevel(true);
	}
    else if (dynamic_cast<Collectible*>(details->getCollided()) != NULL)
    {
        Collectible* item = dynamic_cast<Collectible*>(details->getCollided());
        if (item->getType() == "jump")
            powerjump = true;
        else if (item->getType() == "speed")
            powerspeed = true;
        else if (item->getType() == "shield")
            powershield= true;
        else if (item->getType() == "score")
            powerscore = true;
    }
}

void Player::setPower(string pow, bool is)
{
    if (pow == "jump")
        powerjump = is;
    else if (pow == "speed")
        powerspeed = is;
    else if (pow == "shield")
        powershield = is;
    else if (pow == "score")
        powerscore = is;
}

void Player::setWalkImage()
{
    if (!canMove)
    {
        if (right)
            image = ":/images/maincharacter/hurt.png";
        else
            image = ":/images/maincharacter/hurtleft.png";

        return;
    }
    if (kicking)
    {
        qDebug() << "this one.";
        image = ":/images/maincharacter/kick.png";
        if (!right)
            image = ":/images/maincharacter/kickleft.png";
        return;
    }

    count ++;

    image = ":/images/maincharacter/walk";
    if (count < 7)
    {
        image += "1";
    }
    else if (count < 15)
    {
        image += "2";
    }
    else if (count == 15)
    {
        count = 0;
        image += "1";
    }

    if (!right)
        image += "left";
    image += ".png";

    if (xSpeed == 0)
    {
        if (right)
            image = ":/images/maincharacter/stand.png";
        else
            image = ":/images/maincharacter/standleft.png";
    }
}
