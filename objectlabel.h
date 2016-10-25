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

    Object* getObject() { return object; }

    void setObject(Object* initObject) { object = initObject; }

    // Updates the lable possistion to the position recoreded in the model
    void updateLabelPosition();
};

#endif // OBJECTLABEL_H
