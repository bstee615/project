#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include"object.h"

#include <QString>

#include <string>

class Collectible : public Object {
    protected:
    string type;
    bool isCollectible;
    public:
    Collectible () : Object() {}
    Collectible(int x_, int y_, int width_, int height_, QString image_, string type_, bool visibility_, bool isCollectible_);
    string getType() { return type; }
    void setType(string newType) { type = newType; }
    bool getisCollectible() { return isCollectible; }
    void setisCollectible(bool newCollectibility) { isCollectible = newCollectibility; }

    void load(QString);
};

#endif // COLLECTIBLE_H
