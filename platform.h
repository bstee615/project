#ifndef PLATFORM_H
#define PLATFORM_H

#include"object.h"

class Platform : public Object
{
public:
    Platform() : Object() {}
	Platform(int x_, int y_, int width_, int height_, QString image_):
		Object(x_, y_, width_, height_, image_) {}
};

#endif // PLATFORM_H
