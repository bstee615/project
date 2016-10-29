/*
 * Class storing data for screen location relative to level
 */

#ifndef PLAYINGSCREEN_H
#define PLAYINGSCREEN_H

class PlayingScreen
{
	int x;
	int y;
	int width;
	int height;

public:
	PlayingScreen() {}
	PlayingScreen(int x_, int y_) : x(x_), y(y_) {};

	// getters and setters
	int getX() {return x;}
	int getY() {return y;}
	int getWidth() {return width;}
	int getHeight() {return height;}

	void setX(int x_) {x = x_;}
	void setY(int y_) {y = y_;}
	void setWidth(int w_) {width = w_;}
	void setHeight(int h_) {height = h_;}
};

#endif // PLAYINGSCREEN_H
