#include "coin.h"

//collectible constructor
Coin::Coin(int x_, int y_, int width_, int height_, QString image_, string type, bool visibility_, int newAmount): Collectible(x_,y_,width_,height_,image_,type, visibility_)
{
   amount = newAmount;
}
