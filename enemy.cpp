#include "enemy.h"
#include "world.h"
#include "platform.h"

Enemy::Enemy(int x_, int y_, int width_, int height_, QString image_, int damage_, int speed_): Object(x_,y_,width_,height_,image_)
{
    damage = damage_;
    xSpeed = speed_;
    facingRight = true;
}
void Enemy::move()
{
    if (facingRight)
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
    if (dynamic_cast<Platform*>(details->getCollided()) != NULL) {
        if (details->getXStopCollide() != 0) {
            x += details->getXStopCollide();
            facingRight = !facingRight;
        }
        if (details->getYStopCollide() != 0) {
            y += details->getYStopCollide();
        }
    }
}
/*
void FlyingEnemy::move()
{
    if (this->isRight())
    {
        x += speed;
    }
    else
    {
        x -= speed;
    }
    if (movingUp)
    {
        y += speed;
    }
    else
    {
        y -= speed;
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
            facingRight = !facingRight;
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
*/
