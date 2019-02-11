#pragma once
#include "Game.h"

class TextureManager
{
public:
	TextureManager() = delete;
	TextureManager(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;
	~TextureManager() = delete;

	static SDL_Texture* LoadTexture(const char* filename);
	static SDL_Texture* LoadFontTexture(TTF_Font* font, const char* text, SDL_Color textColor);
	static void DrawTexture(SDL_Texture* texture);
	static void DrawTexture(SDL_Texture* texture, SDL_Rect dst);
	static void DrawTexture(SDL_Texture * texture, SDL_Rect src, SDL_Rect dst);
};

