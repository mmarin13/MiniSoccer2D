#pragma once
#include "Game.h"
#include "Point2D.h"

class Ball
{
	Point2D position;
	SDL_Texture *texture;
	SDL_Rect dstRect;
	float maxHeight;

public:
	Point2D velocity;

	Ball() = delete;
	Ball(const Ball&) = delete;
	Ball(Ball&&) = delete;
	Ball& operator=(const Ball&) = delete;
	Ball& operator=(Ball&&) = delete;
	Ball(const char *path);
	~Ball();

	void init(float x, float y);
	void update();
	void draw();

	float x() const;
	float y() const;
	float getMaxHeight() const;
	SDL_Rect getBox() const;
	Point2D getPosition() const;

	friend std::ostream & operator<<(std::ostream & os, const Ball & ball);
};