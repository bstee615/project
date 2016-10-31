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
    if (params.at(6) == "flying")
        flying = true;
}

QString Enemy::save() {return Object::save();}

void Enemy::move()
{
    vector<Object*> objects = World::instance().getObjects();

    if (!flying)
    {
    for (size_t i = 0; i < objects.size(); i ++)
    {
        if (dynamic_cast<Platform*>(objects.at(i)) != NULL)
            {
                if (x == objects.at(i)->getX() || x + width == objects.at(i)->getRightPoint())
                {
                    right = !right;
                }
            }
        }
    }

    if (right)
    {
        x += xSpeed;
    }
    else
    {
        x -= xSpeed;
    }

    if (flying)
    {
        if (up)
            y -= ySpeed;
        else
            y += ySpeed;
        if (y == initY + 40 || y == initY)
            up = !up;
    }

    if (count < 80)
    {
        count++;
    }
    if (count  == 80)
    {
        up = !up;
    }



    World& world = World::instance();
    for (size_t i = 0; i < world.getObjects().size(); i ++)
    {
        CollisionDetails* col = this->checkCollision(world.getObjects().at(i));
        if (col != NULL)
        {
            this->collide(col);
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
            if (details->getYStopCollide() < 0)
                up = true;
            if (details->getYStopCollide() > 0)
                up = false;
        }
    }
}
