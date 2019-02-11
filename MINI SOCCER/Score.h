#pragma once
#include "Game.h"

class Score
{
	SDL_Color textColor;
	TTF_Font* font;
	SDL_Texture* texture;
	SDL_Rect destRect;
	int score;

	void updateTexture();

public:
	Score(const Score&) = delete;
	Score(Score &&) = delete;
	Score& operator=(const Score&) = delete;
	Score& operator=(Score &&) = delete;

	Score(const char* path, int x, int y);
	~Score();

	void draw();
	void increment();
	int getScore() const;
	void resetScore();

	bool operator<(const Score& x);
	bool operator>(const Score& x);
};