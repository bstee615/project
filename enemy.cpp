#include "enemy.h"
#include "world.h"
#include "platform.h"

Enemy::Enemy(int x_, int y_, int width_, int height_, QString image_, int damage_, int speed_): Object(x_,y_,width_,height_,image_)
{
    damage = damage_;
    speed = speed_;
    right = true;
    onPlatform = true;
}
void Enemy::move()
{
    if (right)
    {
        x += speed;
    }
    else
    {
        x -= speed;
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
    if (dynamic_cast<Platform*>(details->getCollided()) != NULL) {
        if (details->getXStopCollide() != 0) {
            x += details->getXStopCollide();
            right = !right;
        }
        if (details->getYStopCollide() != 0) {
            y += details->getYStopCollide();
            if (details->getYStopCollide() < 0) {
                onPlatform = true;
            }
        }
    }
}
