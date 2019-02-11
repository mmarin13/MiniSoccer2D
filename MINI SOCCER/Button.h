#pragma once
#include "Game.h"

class Button
{
	SDL_Rect destRect;
	SDL_Rect srcRect;
	SDL_Texture* texture;

public:
	Button(const Button&) = delete;
	Button(Button &&) = delete;
	Button& operator=(const Button&) = delete;
	Button& operator=(Button &&) = delete;

	Button(const char* path, int x, int y);
	Button(const char* path, int x, int y, int h, int w);
	~Button();

	void draw();
	void mouseOver();
	void mouseOut();
	SDL_Rect getBox() const;
};

