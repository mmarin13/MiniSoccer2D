#pragma once
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>
/*SDL2 headers*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
/*own headers*/
#include "TextureManager.h"
#include "Player.h"
#include "Map.h"
#include "Ball.h"
#include "Collision.h"
#include "Gate.h"
#include "Score.h"
#include "Sound.h"
#include "Button.h"
#include "Timer.h"

/*window's dimensions*/
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

/*frames per second*/
#define FPS 60	
/*FrameDelay = (int) 1000/60 -> the time between 2 frames*/
#define FRAME_DELAY 16	

/*Forward declarations*/
class Player;
class Sound;

class Game
{
	bool isRunning;
	bool resetGame;
	bool GameOver;
	bool backToMenu;
	bool goldenGoal;
	SDL_Window* window;
	Player* winner;
	
public:
	static SDL_Renderer *renderer;
	static size_t speed;
	static Sound* sound;
	static bool volumeOn;

	Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
	~Game();

	void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();
	void reset();

	void showMenu();
	void showWinner();

	bool running() const;
	bool goReset() const;
	bool isGameOver() const;
	bool isGoingBack() const;
};

