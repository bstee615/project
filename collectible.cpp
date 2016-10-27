#include "collectible.h"


Collectible::Collectible(int x_, int y_, int width_, int height_, QString image_, QString type): Object(x_,y_,width_,height_,image_)
{
   type_ = type;
}

