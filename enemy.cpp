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
    // TO DO: add checkCollision if statement.
        // IF this were about to collide with another object,
        // THEN switch directions.
        // ELSE move right.

}
bool Enemy::isAbovePlatform()
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
