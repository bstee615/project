#include "endgameobject.h"

void EndGameObject::load(QString config)
{
	Object::load(config);
}

QString EndGameObject::save()
{
	return Object::save();
}
