#include "Score.h"

Score::Score(const char * path, int x, int y)
{
	font = TTF_OpenFont(path, 28);
	if (font == nullptr)
	{
		std::cerr << "Failed to load the font for score!" << std::endl;
		std::cerr << "TTF_Error: " << TTF_GetError() << std::endl;
	}
	textColor = { 255, 255, 255 };
	destRect.x = x;
	destRect.y = y;
	destRect.h = 70;
	destRect.w = 40;
	score = 0;
	updateTexture();
}

Score::~Score()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}	
	if (font != nullptr)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}	
}

void Score::draw()
{
	TextureManager::DrawTexture(texture, destRect);
}

void Score::increment()
{
	score++;
	updateTexture();
}

int Score::getScore() const 
{
	return score;
}

void Score::resetScore()
{
	score = 0;
	updateTexture();
}

void Score::updateTexture()
{
	std::string scoreText = std::to_string(score);
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
	texture = TextureManager::LoadFontTexture(font, scoreText.c_str(), textColor);
}

bool Score::operator<(const Score & x)
{
	return (score < x.score);
}

bool Score::operator>(const Score & x)
{
	return (score > x.score);
}
