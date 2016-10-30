/*
 * Class storing data for screen location relative to level
 */

#include "playingscreen.h"

int PlayingScreen::getCenterX(int objWidth)
{
	return (int) (0.5 * (width - objWidth));
}

int PlayingScreen::getCenterY(int objHeight)
{
	return (int) (0.5 * (height - objHeight));
}
