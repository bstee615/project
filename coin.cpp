#include "coin.h"

//collectible constructor
Coin::Coin(int x_, int y_, int width_, int height_, QString image_, QString type, bool visibility_,bool isCollectible_, int newAmount): Collectible(x_,y_,width_,height_,image_,type, visibility_, isCollectible_)
{
   amount = newAmount;
}

void Coin::load(QString config)
{
	try
	{
		QList<QString> params = config.split(",");
		Object::load(config);
		this->setAmount(Object::getQListElement(params, 6).toInt());
		this->setVisibility(Object::getQListElement(params, 7) == "true");
		this->setisCollectible(Object::getQListElement(params, 7) == "true");
	}
	catch (exception& ex)
	{
		throw invalid_argument(ex.what());
	}
}

QString Coin::save()
{
	QString out = Object::save();
	out += "," + QString::number(this->getAmount());
	out += "," + QString::fromStdString(this->getVisibility() ? "true" : "false");
	return out;
}

void Coin::move()
{
    count += 10;

    if (count == 10)
        image = ":/images/goldCoin/goldCoin1.png";
    if (count == 20)
        image = ":/images/goldCoin/goldCoin2.png";
    if (count == 30)
        image = ":/images/goldCoin/goldCoin3.png";
    if (count == 40)
        image = ":/images/goldCoin/goldCoin4.png";
    if (count == 50)
        image = ":/images/goldCoin/goldCoin5.png";
    if (count == 60)
        image = ":/images/goldCoin/goldCoin6.png";
    if (count == 70)
        image = ":/images/goldCoin/goldCoin7.png";
    if (count == 80)
        image = ":/images/goldCoin/goldCoin8.png";
    if (count == 90)
    {
        image = ":/images/goldCoin/goldCoin1.png";
        count = 0;
    }
}
