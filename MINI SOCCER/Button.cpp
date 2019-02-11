#include "Button.h"

Button::Button(const char* path, int x, int y)
{
	texture = TextureManager::LoadTexture(path);
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = x;
	destRect.y = y;
	/* button's dimensions*/
	srcRect.h = 87;
	srcRect.w = 279;
	destRect.h = 86;
	destRect.w = 200;
}

Button::Button(const char* path,  int x, int y, int h, int w)
{
	texture = TextureManager::LoadTexture(path);
	destRect.x = x;
	destRect.y = y;
	srcRect.x = 0;
	srcRect.y = 0;
	/* button's dimensions*/
	srcRect.h = 87;
	srcRect.w = 279;
	destRect.h = h;
	destRect.w = w;
}

Button::~Button()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Button::draw()
{
	TextureManager::DrawTexture(texture, srcRect, destRect);
}

void Button::mouseOver()
{
	srcRect.y = srcRect.h;
}

void Button::mouseOut()
{
	srcRect.y = 0;
}

SDL_Rect Button::getBox() const
{
	return destRect;
}

