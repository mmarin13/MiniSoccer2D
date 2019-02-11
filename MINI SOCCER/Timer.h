#pragma once
#include "Game.h"

class Timer
{
	SDL_Color textColor;
	SDL_Rect destRect;
	TTF_Font* font;
	SDL_Texture* texture;
	
	std::string timeText;
	Uint32 startTicks;
	Uint32 pausedTicks;
	
	bool started;
	bool paused;

public:
	Timer(const char *fontPath);
	~Timer();

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	void start();
	void pause();
	void resume();
	void stop();

	bool isStarted() const;
	bool isPaused() const;

	void draw();
	bool update();
};