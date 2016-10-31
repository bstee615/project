#include "coin.h"

//collectible constructor
Coin::Coin(int x_, int y_, int width_, int height_, QString image_, string type, bool visibility_,bool isCollectible_, int newAmount): Collectible(x_,y_,width_,height_,image_,type, visibility_, isCollectible_)
{
   amount = newAmount;
}

void Coin::load(QString config)
{
	Object::load(config);
	this->setAmount(10);
}

QString Coin::save() {return Object::save();}
