#ifndef OBJECTLABEL_H
#define OBJECTLABEL_H
#include<QLabel>
#include"object.h"

class ObjectLabel : QLabel
{
private:
    Object* object;
public:
    ObjectLabel();
};

#endif // OBJECTLABEL_H
