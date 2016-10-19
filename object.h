#ifndef OBJECT_H
#define OBJECT_H

#include<QString>

class Object
{
protected:
    int x;
    int y;
    int width;
    int hieght;
    QString image;

public:
    Object();

    void CheckCollision(Object * that);
};

class Player : public Object
{
    int xSpeed;
    int YSpeed;
public:
    void jump();
    void moveRight();
    void moveLeft();
};

class Platform : public Object
{

};

class Enemy : public Object
{

};

class Collectible : public Object
{

};

class Coin : public Collectible
{

};

#endif // OBJECT_H
