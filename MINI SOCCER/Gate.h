#pragma once
#include "Game.h"

class Gate
{
	SDL_Texture* texture;
	SDL_Rect dstRect;

public:
	Gate(const Gate&) = delete;
	Gate(Gate&&) = delete;
	Gate& operator=(const Gate&) = delete;
	Gate& operator=(Gate&&) = delete;

	Gate(const char* path);
	Gate(const char* path, int height, int width);
	~Gate();

	void init(float x, float y);
	void draw();

	SDL_Rect getBox() const;
};

