#ifndef COLLISIONDETAILS_H
#define COLLISIONDETAILS_H

#include "object.h"

class collisionDetails
{
    int overlapX1;
    int overlapX2;
    int overlapY1;
    int overlapY2;
public:
    collisionDetails(int initX1, int initX2, int initY1, int initY2) :
        overlapX1(initX1), overlapX2(initX2), overlapY1(initY1), overlapY2(initY2) {}

    int getOverlapX1() { return overlapX1; }
    int getOverlapX2() { return overlapX2; }
    int getOverlapY1() { return overlapY1; }
    int getOverlapY2() { return overlapY2; }
};

#endif // COLLISIONDETAILS_H
