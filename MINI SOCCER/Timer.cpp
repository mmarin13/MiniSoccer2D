#include "Timer.h"

Timer::Timer(const char * fontPath)
{
	font = TTF_OpenFont(fontPath, 28);
	if (font == nullptr)
	{
		std::cerr << "Failed to load the font for timer!" << std::endl;
		std::cerr << "TTF_Error: " << TTF_GetError() << std::endl;
	}
	textColor = { 255, 255, 255 };
	destRect.x = 375;
	destRect.y = 530;
	destRect.h = 80;
	destRect.w = 50;
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

Timer::~Timer()
{
	if (font != nullptr)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}	
}

void Timer::start()
{
	started = true;
	startTicks = SDL_GetTicks();
	timeText = std::to_string(60);
	textColor = { 255, 255, 255 };
	texture = TextureManager::LoadFontTexture(font, timeText.c_str(), textColor);
}

void Timer::pause()
{
	if (started && !paused)
	{
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::resume()
{
	if (started && paused)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

void Timer::stop()
{
	if (started)
	{
		started = false;
		paused = false;
		startTicks = 0;
		pausedTicks = 0;
	}
}

bool Timer::isStarted() const
{
	return started;
}

bool Timer::isPaused() const
{
	return paused;
}

void Timer::draw()
{
	TextureManager::DrawTexture(texture, destRect);
	//std::cout << timeText << std::endl;
}

/*if time is over return true, else false*/
bool Timer::update()
{
	if (started && !paused)
	{
		Uint32 currentTime = (SDL_GetTicks() - startTicks) / 1000;
		if (currentTime > 60)
		{
			return true;
		}
		timeText = std::to_string(60 - currentTime);
		if (currentTime > 50)
		{
			textColor = { 184, 0, 0 }; /*last 10 seconds are displayed with red color*/
		}
		SDL_DestroyTexture(texture);
		texture = TextureManager::LoadFontTexture(font, timeText.c_str(), textColor);
	}
	return false;
}

