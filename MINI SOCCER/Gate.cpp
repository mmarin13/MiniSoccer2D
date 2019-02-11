#include "Gate.h"

Gate::Gate(const char* path)
{
	texture = TextureManager::LoadTexture(path);
	dstRect.h = 180;
	dstRect.w = 100;
}

Gate::Gate(const char * path, int height, int width)
{
	texture = TextureManager::LoadTexture(path);
	dstRect.h = height;
	dstRect.w = width;
}

Gate::~Gate()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Gate::init(float x, float y)
{
	dstRect.x = (int)x;
	dstRect.y = (int)y;
}

void Gate::draw()
{
	TextureManager::DrawTexture(texture, dstRect);
}

SDL_Rect Gate::getBox() const
{
	return dstRect;
}
