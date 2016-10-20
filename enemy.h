#ifndef ENEMY_H
#define ENEMY_H

#include <QString>

#include "object.h"

class Enemy : public Object
{
public:
    Enemy(): Object() { }
    Enemy(int x_, int y_, int width_, int height_, QString image_): Object(x_,y_,width_,height_,image_) { }
};

#endif // ENEMY_H
