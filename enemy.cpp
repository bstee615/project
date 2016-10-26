#include "enemy.h"
#include "world.h"
#include "platform.h"

Enemy::Enemy(int x_, int y_, int width_, int height_, QString image_, int damage_, int speed_): Object(x_,y_,width_,height_,image_)
{
    damage = damage_;
    speed = speed_;
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
    for (int i = 0; i < world.getObjects().size(); i ++)
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
        }
        if (details->getYStopCollide() != 0) {
            y += details->getYStopCollide();
        }
    }
}
bool Enemy::isOnPlatform()
{
    vector<Object*> objects = World::instance().getObjects();

    for (auto i: objects)
    {
        Platform* plat = dynamic_cast<Platform*>(i);

        if (this->getRightPoint() >= plat->getX() && this->getX() <= plat->getRightPoint())
        {

        }
    }
}
