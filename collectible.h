#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include"object.h"

class Collectible : public Object {
    protected:
    QString type_;

    public:
    Collectible () : Object() {}
    Collectible(int x_, int y_, int width_, int height_, QString image_, QString type_);


};

#endif // COLLECTIBLE_H
