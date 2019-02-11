#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* tempSurface = IMG_Load(filename);
	if (tempSurface == nullptr)
	{
		std::cerr << "Unable to load a image!" << std::endl;
		std::cerr << "IMG_Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
		if (texture == nullptr)
		{
			std::cerr << "Unable to create texture from loaded image!" << std::endl;
		}
		SDL_FreeSurface(tempSurface);
	}	
	return texture;
}

SDL_Texture* TextureManager::LoadFontTexture(TTF_Font* font, const char* text, SDL_Color textColor)
{
	SDL_Texture* texture = nullptr;
	if (font != nullptr)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
		if (surface == nullptr)
		{
			std::cerr << "Unable to render text surface!" << std::endl;
			std::cerr << "TFF_Error: " << TTF_GetError() << std::endl;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
			if (texture == nullptr)
			{
				std::cout << "Unable to create texture from rendered text!" << std::endl;
			}
			SDL_FreeSurface(surface);
		}
	}
	return texture;
}

void TextureManager::DrawTexture(SDL_Texture * texture)
{
	if (texture != nullptr)
	{
		SDL_RenderCopy(Game::renderer, texture, nullptr, nullptr); /*nullptr, nullptr to render whole texture on whole area of window*/
	}
	else
	{
		std::cerr << "Unable to draw a null texture!" << std::endl;
	}
	
}

void TextureManager::DrawTexture(SDL_Texture * texture, SDL_Rect dst)
{
	if (texture != nullptr)
	{
		SDL_RenderCopy(Game::renderer, texture, nullptr, &dst); /*nullptr to render whole texture*/
	}
	else
	{
		std::cerr << "Unable to draw a null texture!" << std::endl;
	}
}

void TextureManager::DrawTexture(SDL_Texture * texture, SDL_Rect src, SDL_Rect dst)
{
	if (texture != nullptr)
	{
		SDL_RenderCopy(Game::renderer, texture, &src, &dst);
	}
	else
	{
		std::cerr << "Unable to draw a null texture!" << std::endl;
	}
}
