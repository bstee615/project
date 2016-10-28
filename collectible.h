#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include"object.h"

class Collectible : public Object {
    protected:
    string type;
    public:
    Collectible () : Object() {}
    Collectible(int x_, int y_, int width_, int height_, QString image_, string type_, bool visibility_);
    string getType() { return type; }
    void setType(string newType) { type = newType; }
    bool getVisibility() { return visibility; }

};

#endif // COLLECTIBLE_H
