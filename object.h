#ifndef OBJECT_H
#define OBJECT_H

#include<QString>
#include"collisiondetails.h"

class Object
{
protected:
    int x;
    int y;
    int width;
    int height;
    QString image;

public:
    Object();
    Object(int x_, int y_, int width_, int height_, QString image_): x(x_), y(y_), width(width_), height(height_), image(image_) { }

    void CheckCollision(Object * that);
};

#endif // OBJECT_H
