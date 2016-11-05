#include "collectible.h"

//collectible constructor
Collectible::Collectible(int x_, int y_, int width_, int height_, QString image_, string type_, bool visibility_, bool isCollectible_): Object(x_,y_,width_,height_,image_)
{
   type = type_;
   visibility = visibility_;
   isCollectible = isCollectible_;
}

void Collectible::load(QString config)
{
	Object::load(config);
}

QString Collectible::save()
{
	return Object::save();
}

