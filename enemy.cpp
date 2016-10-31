#include "enemy.h"
#include "world.h"
#include "platform.h"

Enemy::Enemy(int x_, int y_, int width_, int height_, QString image_, int damage_, int speed_): Object(x_,y_,width_,height_,image_)
{
    damage = damage_;
    xSpeed = speed_;
    right = true;
}

void Enemy::load(QString config)
{
	Object::load(config);
	this->setDamage(10);
	this->setXSpeed(2);
	this->setRight(true);
}

QString Enemy::save() {return Object::save();}

void Enemy::move()
{
    vector<Object*> objects = World::instance().getObjects();
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

    if (right)
    {
        x += xSpeed;
    }
    else
    {
        x -= xSpeed;
    }

    if (ySpeed < 5)
    {
        if (count < 10)
            count ++;
        if (count == 10)
        {
            count = 0;
            ySpeed ++;
        }
    }

    y += ySpeed;



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
        }
    }
}


void FlyingEnemy::move()
{
    if (this->isRight())
    {
        x += xSpeed;
    }
    else
    {
        x -= xSpeed;
    }
    if (movingUp)
    {
        y += xSpeed;
    }
    else
    {
        y -= xSpeed;
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
void FlyingEnemy::collide(CollisionDetails *details)
{
    if (dynamic_cast<Platform*>(details->getCollided()) != NULL) {
        if (details->getXStopCollide() != 0) {
            x += details->getXStopCollide();
        }
        if (details->getYStopCollide() != 0) {
            y += details->getYStopCollide();
            if (details->getYStopCollide() < 0) {
                movingUp = true;
            }
            else
            {
                movingUp = false;
            }
        }
    }
}
