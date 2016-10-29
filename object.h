#ifndef OBJECT_H
#define OBJECT_H

#include<QString>
#include <QDebug>
#include "collisiondetails.h"

using namespace std;

class CollisionDetails;

class Object
{
protected:
    int x;
    int y;
    int id;
    int width;
    int height;
    QString image;
    static int nextID;
    bool onPlatform;
    bool  visibility;

    int count;// used to animate images. thought it'd be better to move it here from mainwindow.

public:
    Object();
    Object(int x_, int y_, int width_, int height_, QString image_): x(x_), y(y_), width(width_), height(height_), image(image_), onPlatform(false), count(0) {
		id = nextID++;
    }

	virtual ~Object();

	CollisionDetails* checkCollision(Object * that);
	static void resetNextId();

	// accessors & mutators
	virtual int getX() {return x;}
	virtual int getY() {return y;}
	virtual int getWidth() {return width;}
	virtual int getHeight() {return height;}
    virtual int getRightPoint() {return (x + width);}
    virtual int getBottomPoint() {return (y + height);}
	virtual QString getImage() {return image;}
	int getId() {return id;}
    bool getVisibility() { return visibility; }
    void setVisibility(bool newVisibility) { visibility = newVisibility; }

	virtual void setX(int x_) {x = x_;}
	virtual void setY(int y_) {y = y_;}
	virtual void setWidth(int w_) {width = w_;}
	virtual void setHeight(int h_) {height = h_;}
	virtual void setImage(QString image_) {image = image_;}
	void setId(int newId) { id = newId; }

    virtual void collide(CollisionDetails*) {}

    bool isOnObject(Object* that);

    static void unitTest();

    virtual void setAmount(int) { }


    int getCount() { return count; }
    void advanceCount() { count++; }
    void setCount(int num) { count = num; }
};

#endif // OBJECT_H
