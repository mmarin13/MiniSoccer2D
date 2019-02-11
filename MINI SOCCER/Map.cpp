#include "Map.h"

Map::Map(const char* path)
{
	texture = TextureManager::LoadTexture(path);
	dstRect.x = dstRect.y = 0;
	dstRect.h = SCREEN_HEIGHT;
	dstRect.w = SCREEN_WIDTH;
}

Map::~Map()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Map::draw()
{
	TextureManager::DrawTexture(texture, dstRect);
}

void Map::setTexture(const char* path)
{
	SDL_DestroyTexture(texture);
	texture = TextureManager::LoadTexture(path);
}
