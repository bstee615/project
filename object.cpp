#include "object.h"
#include <QRect>

int Object::nextID = 0;

void Object::resetNextId() {nextID = 0;}

Object::Object()
{
	id = nextID++;
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

    QRect thatRec = QRect(that->x,that->y,that->width,that->height);
    QRect thisRec = QRect(this->x,this->y,this->width,this->height);

    if (thisRec.intersects(thatRec)) {
        QRect thatRec = QRect(that->x,that->y,that->width,that->height);
        bool topLeft = thatRec.contains(thisRec.topLeft());
        bool topRight = thatRec.contains(thisRec.topRight());
        bool bottomLeft = thatRec.contains(thisRec.bottomLeft());
        bool bottomRight = thatRec.contains(thisRec.bottomRight());

        // distances that would stop the collision
        int xStopCollide = 0;
        int yStopCollide = 0;

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
    return NULL;
}



