#include "enemy.h"
#include "world.h"
#include "platform.h"

void Enemy::load(QString config)
{
    QList<QString> params = config.split(",");
	Object::load(config);
	this->setDamage(10);
	this->setXSpeed(2);
    this->setRight(true);
}

QString Enemy::save() {return Object::save();}

void Enemy::move()
{
    if (right)
    {
        x += xSpeed;
    }
    else
    {
        x -= xSpeed;
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

void Enemy::collide(CollisionDetails *details)
{
    if (dynamic_cast<Platform*>(details->getCollided()) != NULL || dynamic_cast<Player*>(details->getCollided()) != NULL) {
        if (details->getXStopCollide() != 0) {
            x += details->getXStopCollide();
            if (details->getXStopCollide() > 0)
                right = true;
            if (details->getXStopCollide() < 0)
                right = false;
        }
        if (details->getYStopCollide() != 0) {
            y += details->getYStopCollide();
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
    if (count == 10)
    {
        up = !up;
        count = 0;
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
                setRight(true);
            if (details->getXStopCollide() < 0)
                setRight(false);
        }
        if (details->getYStopCollide() != 0) {
            y += details->getYStopCollide();
            if (details->getYStopCollide() < 0)
                up = true;
            if (details->getYStopCollide() > 0)
                up = false;
        }
    }
}
