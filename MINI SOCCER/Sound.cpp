#include "Sound.h"

Sound::Sound()
{	
	/*load files*/
	music = Mix_LoadMUS("music/crowd.wav");
	if (music == nullptr)
	{
		std::cerr << "Unable to load background music!" << std::endl;
		std::cerr << "MIXER_Error: " << Mix_GetError() << std::endl;
	}
	goal = Mix_LoadWAV("music/goal.wav");
	if (goal == nullptr)
	{
		std::cerr << "Unable to load goal sound effect!" << std::endl;
		std::cerr << "MIXER_Error: " << Mix_GetError() << std::endl;
	}
	shoot = Mix_LoadWAV("music/shoot.wav");
	if (shoot == nullptr)
	{
		std::cerr << "Unable to load shoot sound effect!" << std::endl;
		std::cerr << "MIXER_Error: " << Mix_GetError() << std::endl;
	}
	win = Mix_LoadWAV("music/goal_1.wav");
	if (win == nullptr)
	{
		std::cerr << "Unable to load win sound effect!" << std::endl;
		std::cerr << "MIXER_Error: " << Mix_GetError() << std::endl;
	}
	click = Mix_LoadWAV("music/effect_3.wav");
	if (click == nullptr)
	{
		std::cerr << "Unable to load click sound effect!" << std::endl;
		std::cerr << "MIXER_Error: " << Mix_GetError() << std::endl;
	}
}

Sound::~Sound()
{
	if (goal != nullptr)
	{
		Mix_FreeChunk(goal);
		goal = nullptr;
	}	
	if (shoot != nullptr)
	{
		Mix_FreeChunk(shoot);
		shoot = nullptr;
	}
	if (win != nullptr)
	{
		Mix_FreeChunk(win);
		win = nullptr;
	}
	if (click != nullptr)
	{
		Mix_FreeChunk(click);
		click = nullptr;
	}
	if (music != nullptr)
	{
		Mix_FreeMusic(music);
		music = nullptr;
	}
}

void Sound::changeState()
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
	Game::volumeOn = !Game::volumeOn;
}
