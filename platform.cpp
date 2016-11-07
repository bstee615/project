#include "platform.h"

QString Platform::save()
{
	QString out = Object::save();
	out += "," + QString::number(this->getXSpeed());
	out += "," + QString::number(this->getYSpeed());
	out += "," + QString::number(this->getXRange());
	out += "," + QString::number(this->getYRange());
	out += "," + QString::number(this->getStartX());
	out += "," + QString::number(this->getStartY());
	return out;
}

void Platform::load(QString config)
{
	Object::load(config);
	QList<QString> params = config.split(",");
	// set object properties specific to Platform
	this->setXSpeed(params.at(6).toInt());
	this->setYSpeed(params.at(7).toInt());
	this->setXRange(params.at(8).toInt());
	this->setYRange(params.at(9).toInt());
	this->setStartX(params.at(10).toInt());
	this->setStartY(params.at(11).toInt());
}

void Platform::move()
{
	this->setX(this->getX() + this->getXSpeed());
	if (this->getX() > (this->getStartX() + this->getXRange()) || this->getX() < (this->getStartX() - this->getXRange()))
		this->setXSpeed(-1 * this->getXSpeed());

	this->setY(this->getY() + this->getYSpeed());
	if (this->getY() > (this->getStartY() + this->getYRange()) || this->getY() < (this->getStartY() - this->getYRange()))
		this->setYSpeed(-1 * this->getYSpeed());
}
