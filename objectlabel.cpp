#include "objectlabel.h"

ObjectLabel::ObjectLabel()
{
}

void ObjectLabel::updateLabelPosition()
{
    setGeometry(object->getX(),object->getY(),object->getWidth(),object->getHeight());
}
