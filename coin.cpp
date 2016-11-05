#include "coin.h"

//collectible constructor
Coin::Coin(int x_, int y_, int width_, int height_, QString image_, string type, bool visibility_,bool isCollectible_, int newAmount): Collectible(x_,y_,width_,height_,image_,type, visibility_, isCollectible_)
{
   amount = newAmount;
}

void Coin::load(QString config)
{
	QList<QString> params = config.split(",");
	Collectible::load(config);
	this->setAmount(params.at(6).toInt());
	this->setVisibility(params.at(7) == "true");
	this->setisCollectible(params.at(7) == "true");
}

QString Coin::save()
{
	QString out = Collectible::save();
	out += "," + QString::number(this->getAmount());
	out += "," + QString::fromStdString(this->getVisibility() ? "true" : "false");
	return out;
}
