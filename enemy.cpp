#include "enemy.h"

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
