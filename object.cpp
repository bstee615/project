#include <QRect>
#include <cassert>
#include <iostream>
#include "object.h"
#include "world.h"

int Object::nextID = 0;

void Object::resetNextId() {nextID = 0;}

void Object::unitTest()
{
    Object* one = new Object(10,10,10,10,"one");
    Object* two = new Object(5,15,20,20,"two");
    CollisionDetails* collision = one->checkCollision(two);

    assert(collision->getXStopCollide() == 0);
    assert(collision->getYStopCollide() == -5);

    delete two;
    delete collision;

    two = new Object(5,5,20,10,"two");
    collision = one->checkCollision(two);

    assert(collision->getXStopCollide() == 0);
    assert(collision->getYStopCollide() == 5);

    delete two;
    delete collision;

    two = new Object(15,5,20,20,"two");
    collision = one->checkCollision(two);

    assert(collision->getXStopCollide() == -5);
    assert(collision->getYStopCollide() == 0);

    delete two;
    delete collision;

    two = new Object(5,5,10,20,"two");
    collision = one->checkCollision(two);

    assert(collision->getXStopCollide() == 5);
    assert(collision->getYStopCollide() == 0);

    delete one;
    delete two;
    delete collision;
}

Object::Object()
{
	id = nextID++;
}

Object::Object(QString config) : Object()
{
	this->load(config);
}

void Object::load(QString config)
{
	QList<QString> params = config.split(",");
	// get and set object properties
	this->setX(params.at(1).toInt());
	this->setY(params.at(2).toInt());
	this->setWidth(params.at(3).toInt());
	this->setHeight(params.at(4).toInt());
	this->setImage(params.at(5));
}

QString Object::save()
{
	QString out = "";
	QString type;
	// check and print object type
	if (dynamic_cast<Item*>(this))
		type = "item";
	else if (dynamic_cast<Collectible*>(this))
		type = "collectible";
	else if (dynamic_cast<Coin*>(this))
		type = "coin";
	else if (dynamic_cast<Player*>(this))
		type = "player";
	else if (dynamic_cast<Platform*>(this))
		type = "platform";
	else if (dynamic_cast<Enemy*>(this))
		type = "enemy";
	else if (dynamic_cast<FlyingEnemy*>(this))
		type = "flyingenemy";
	else
		type = "object";

	out += type;
	out += "," + QString::number(this->getX());
	out += "," + QString::number(this->getY());
	out += "," + QString::number(this->getWidth());
	out += "," + QString::number(this->getHeight());
	out += "," + this->getImage();
	return out;
}

Object::~Object()
{

}

bool Object::isOnObject(Object* that)
{
    if (this->getRightPoint() >= that->getX() && this->getX() <= that->getRightPoint())
    {
        if (this->getBottomPoint() >= that->getY() - 5)
        {
            return true;
        }
    }
    return false;
}

CollisionDetails* Object::checkCollision(Object *that)
{
    int thisX2 = this->x + this->width;
    int thisY2 = this->y + this->height;
    int thatX2 = that->x + that->width;
    int thatY2 = that->y + that->height;

    // The geometry of both this and that objects to be used for collision testing
    QRect thatRec = QRect(that->x,that->y,that->width,that->height);
    QRect thisRec = QRect(this->x,this->y,this->width,this->height);

    // Checks to see if Objects intersect
    if (thisRec.intersects(thatRec)) {
        // Checks to see which corners of <this> are within the boundaries of <that>
        bool topLeft = thatRec.contains(thisRec.topLeft());
        bool topRight = thatRec.contains(thisRec.topRight());
        bool bottomLeft = thatRec.contains(thisRec.bottomLeft());
        bool bottomRight = thatRec.contains(thisRec.bottomRight());

        // distances that would stop the collision
        int xStopCollide = 0;
        int yStopCollide = 0;

        // Different cases of corner comonations of corners that collide with <that> object
        // and what to set the xStopCollide and yStopCollide depending on the exact details of the collision
        if ((topLeft && topRight && bottomLeft && bottomRight) || (!topLeft && !topRight && bottomLeft && bottomRight)) {
            yStopCollide = that->y - thisY2;
        } else if (!topLeft && topRight && bottomLeft && bottomRight) {
            xStopCollide = that->x - thisX2;
            yStopCollide = that->y - thisY2;
        } else if (topLeft && !topRight && bottomLeft && bottomRight) {
            xStopCollide = thatX2 - this->x;
            yStopCollide = that->y - thisY2;
        } else if (topLeft && topRight && !bottomLeft && !bottomRight) {
            yStopCollide = thatY2 - this->y;
        } else if (!topLeft && topRight && !bottomLeft && bottomRight) {
            xStopCollide = that->x - thisX2;
        } else if (topLeft && !topRight && bottomLeft && !bottomRight) {
            xStopCollide = thatX2 - this->x;
        } else if (!topLeft && topRight && !bottomLeft && !bottomRight) {
            if (size_t(that->x - thisX2) > size_t(thatY2 - this->y)) {
                xStopCollide = that->x - thisX2;
            } else {
                yStopCollide = thatY2 - this->y;
            }
        } else if (topLeft && !topRight && !bottomLeft && !bottomRight) {
            if (size_t(thatX2 - this->x) > size_t(thatY2 - this->y)) {
                xStopCollide = thatX2 - this->x;
            } else {
                yStopCollide = thatY2 - this->y;
            }
        } else if (!topLeft && !topRight && bottomLeft && !bottomRight) {
            if (size_t(thatX2 - this->x) > size_t(that->y - thisY2)) {
                xStopCollide = thatX2 - this->x;
            } else {
                yStopCollide = that->y - thisY2;
            }
        } else if (!topLeft && !topRight && !bottomLeft && bottomRight) {
            if (size_t(that->x - thisX2) > size_t(that->y - thisY2)) {
                xStopCollide = that->x - thisX2;
            } else {
                yStopCollide = that->y - thisY2;
            }
        } else {
            yStopCollide = that->y - thisY2;
        }

        return new CollisionDetails(xStopCollide, yStopCollide, that);

    }
    // returns nulll if there is no collision
    return NULL;
}



