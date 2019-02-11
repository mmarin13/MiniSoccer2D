#pragma once
#include "Game.h"

#define GROUND_LINE 76

class Map
{
	SDL_Rect dstRect;
	SDL_Texture* texture;

public:
	Map(const Map&) = delete;
	Map(Map &&) = delete;
	Map& operator=(const Map&) = delete;
	Map& operator=(Map &&) = delete;

	Map(const char* path);
	~Map();

	void draw();
	void setTexture(const char* path);
};

