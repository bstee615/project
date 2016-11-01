#ifndef ENDGAMEOBJECT_H
#define ENDGAMEOBJECT_H

#include "object.h"

class EndGameObject : public Object
{
public:
    EndGameObject() : Object() {}
    EndGameObject(int x_, int y_, int width_, int height_, QString image_):
        Object(x_, y_, width_, height_, image_) {}
};

#endif // ENDGAMEOBJECT_H
