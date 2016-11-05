#include "enemy.h"
#include "world.h"
#include "platform.h"
#include <QApplication>

void Enemy::load(QString config)
{
    QList<QString> params = config.split(",");
	Object::load(config);
	if (params.at(6) == "true") // true means dead
	{
		this->kill();
		this->setVisibility(false);
	}
	this->setDamage(10);
	this->setXSpeed(2);
    this->setRight(true);
}

QString Enemy::save()
{
	QString out = Object::save();
	out += "," + QString::fromStdString(this->isDead() ? "true" : "false");
	return out;
}

void Enemy::move()
{
    if (x + xSpeed >= currentPlatform->getRightPoint() || x - xSpeed <= currentPlatform->getX())
        right = !right;

    if (right)
    {
        x += xSpeed;
    }
    else
    {
        x -= xSpeed;
    }

    y += ySpeed;

    for (size_t i = 0; i < World::instance().getObjects().size(); i ++)
    {
        CollisionDetails* col = checkCollision(World::instance().getObjects().at(i));
        if (col != NULL)
        {
            collide(col);
            delete col;
        }
    }
}

void Enemy::collide(CollisionDetails *details)
{
    if (dynamic_cast<Platform*>(details->getCollided()) != NULL || dynamic_cast<Player*>(details->getCollided()) != NULL) {
        if (details->getXStopCollide() != 0) {
            x += details->getXStopCollide();
            if (details->getXStopCollide() > 0)
            {
                right = true;
                if (dynamic_cast<Player*>(details->getCollided()) != NULL)
                    x += 5;
            }
            if (details->getXStopCollide() < 0)
            {
                right = false;
                if (dynamic_cast<Player*>(details->getCollided()) != NULL)
                    x -= 5;
            }
        }
        if (details->getYStopCollide() != 0) {
            y += details->getYStopCollide();
            currentPlatform = dynamic_cast<Platform*>(details->getCollided());
        }
    }
}

void FlyingEnemy::move()
{
    if (isRight())
    {
        x += xSpeed;
    }
    else
    {
        x -= xSpeed;
    }

    if (up)
        y -= ySpeed;
    else
        y += ySpeed;

    count ++;
    xCount ++;
    if (count == 10)
    {
        up = !up;
        count = 0;
    }
    if (xCount == 40)
    {
        right = !right;
        xCount = 0;
    }

    for (size_t i = 0; i < World::instance().getObjects().size(); i ++)
    {
        CollisionDetails* col = checkCollision(World::instance().getObjects().at(i));
        if (col != NULL)
        {
            collide(col);
            delete col;
        }
    }
}

void FlyingEnemy::collide(CollisionDetails *details)
{
    if (dynamic_cast<Platform*>(details->getCollided()) != NULL || dynamic_cast<Player*>(details->getCollided()) != NULL) {
        if (details->getXStopCollide() != 0) {
            x += details->getXStopCollide();
            if (details->getXStopCollide() > 0)
            {
                setRight(true);
                if (dynamic_cast<Player*>(details->getCollided()) != NULL)
                    setX(getX() + 5);
            }
            if (details->getXStopCollide() < 0)
            {
                setRight(false);
                if (dynamic_cast<Player*>(details->getCollided()) != NULL)
                    setX(getX() - 5);
            }
        }
        if (details->getYStopCollide() != 0) {
            y += details->getYStopCollide();
            if (details->getYStopCollide() < 0)
            {
                setY(getY() + 5);
                up = true;
            }
            if (details->getYStopCollide() > 0)
            {
                setY(getY() + 5);
                up = false;
            }
        }
    }
}
