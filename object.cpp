#include "object.h"

int Object::nextID = 0;

void Object::resetNextId() {nextID = 0;}

Object::Object()
{

}

collisionDetails* Object::CheckCollision(Object *that)
{
    int thisX2 = this->x + this->width;
    int thisY2 = this->y + this->height;
    int thatX2 = that->x + that->width;
    int thatY2 = that->y + that->height;
    collisionDetails* collision = NULL;

    if ((this->x <= that->x && thatX2 >= thisX2) &&
            (this->y <= that->y && thisY2 <= thatY2)) {
        //collision = new collisionDetails();
    }
    return NULL;
}



