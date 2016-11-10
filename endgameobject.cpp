#include "endgameobject.h"

void EndGameObject::load(QString config)
{
	try
	{
		Object::load(config);
	}
	catch (exception& ex)
	{
		throw invalid_argument(ex.what());
	}
}

QString EndGameObject::save()
{
	return Object::save();
}
