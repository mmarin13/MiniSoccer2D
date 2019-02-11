#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
size_t Game::speed = 3;
Sound* Game::sound = nullptr;
bool Game::volumeOn = true;

/*game's components*/
Timer* timer;
Player* playerA;
Player* playerB;
Ball* ball;
Map* map;
Gate* gateR;
Gate* gateL;

Game::Game() : isRunning(false), window(nullptr)
{ }

Game::~Game()
{ }

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) /*SDL initialization*/
	{
		std::cout << "SDL subsystems initialized!..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags); /*create the window*/
		if (window != nullptr)
		{
			std::cout << "Window created!..." << std::endl;
		}
		else
		{
			std::cerr << "Unable to create window!" << std::endl;
			clean();
			exit(0);
		}
		renderer = SDL_CreateRenderer(window, -1, 0); /*create 2D render component*/
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); /*white color*/
			std::cout << "Renderer created!..." << std::endl;
		}
		else
		{
			std::cerr << "Unable to create render component!" << std::endl;
			clean();
			exit(0);
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	resetGame = false;
	GameOver = false;

	/*set window's icon*/
	SDL_Surface* icon = IMG_Load("assets/icon.png");
	if(icon == nullptr)
	{ 
		std::cerr << "Unable to load the icon!" << std::endl;
		std::cerr << "IMG_Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}

	/*SDL_TTF library initialization*/
	if (TTF_Init() == -1)
	{
		std::cerr << "Unable to initialize SDL_TTF!" << std::endl;
		std::cerr << "TTF_Error: " << TTF_GetError() << std::endl;
	}

	/*SDL_IMG library initialization*/
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) /*initialize the library for .PNG images*/
	{
		std::cerr << "Unable to initialize SDL_IMG for PNG format!" << std::endl;
		std::cerr << "IMG_Error: " << IMG_GetError() << std::endl;
	}
	
	/*SDL_Mixer library initialization*/
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 204800) == -1) /*frequency = 44.1[kHz], number of channels = 2*/
	{
		std::cerr << "Unable to initialize SDL_Mixer!" << std::endl;
		std::cerr << "IMG_Error: " << Mix_GetError() << std::endl;
	}
	
	/*init game's components*/
	try {
		timer = new Timer("fonts/visitor.ttf");

		playerA = new Player("assets/playerA_s.png", new Score("fonts/visitor.ttf", 40, SCREEN_HEIGHT - 70));
		playerA->init(70.0f, SCREEN_HEIGHT - GROUND_LINE - (float)playerA->getBox().h);

		playerB = new Player("assets/playerB_s.png", new Score("fonts/visitor.ttf", SCREEN_WIDTH - 90, SCREEN_HEIGHT - 70));
		playerB->init(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - GROUND_LINE - (float)playerB->getBox().h);

		ball = new Ball("assets/ball.png");
		ball->init((SCREEN_WIDTH - ball->getBox().w) / 2.0f, (SCREEN_HEIGHT - ball->getBox().h) / 2.0f);

		map = new Map("assets/map.png");

		gateR = new Gate("assets/gate_right.png");
		gateR->init(SCREEN_WIDTH - (float)gateR->getBox().w + 30.f, SCREEN_HEIGHT - GROUND_LINE - (float)gateR->getBox().h);

		gateL = new Gate("assets/gate_left.png");
		gateL->init(-30.0f, SCREEN_HEIGHT - GROUND_LINE - (float)gateL->getBox().h);

		sound = new Sound();
		Mix_PlayMusic(sound->music, -1);	/*play background music*/
	}
	catch (std::bad_alloc &e)
	{
		std::cerr << e.what() << std::endl;
		exit(0);
	}
	
}

/*handle inputs*/
void Game::handleEvents()
{
	SDL_Event event; /*an event is a union*/
	SDL_PollEvent(&event); /*extracts an event from the queue of events*/
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	/*a key was pressed*/
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
			/*keys control for player A*/
		case SDLK_w:
			if (!playerA->isJumping && !playerA->isFalling)
			{
				playerA->isJumping = true;
				playerA->isFalling = false;
			}
			break;
		case SDLK_a:
			playerA->velocity.x = -1;
			playerA->setTexture("assets/playerA_l.png");
			playerA->isRunning = true;
			break;
		case SDLK_d:
			playerA->velocity.x = 1;
			playerA->setTexture("assets/playerA_r.png");
			playerA->isRunning = true;
			break;
		case SDLK_SPACE:
			playerA->isShooting = true;			
			break;
			/*keys control for player B*/
		case SDLK_UP:
			if (!playerB->isJumping && !playerB->isFalling)
			{
				playerB->isJumping = true;
				playerB->isFalling = false;
			}
			break;
		case SDLK_LEFT:
			playerB->velocity.x = -1;
			playerB->setTexture("assets/playerB_l.png");
			playerB->isRunning = true;
			break;
		case SDLK_RIGHT:
			playerB->velocity.x = 1;
			playerB->setTexture("assets/playerB_r.png");
			playerB->isRunning = true;
			break;
		case SDLK_KP_0:
			playerB->isShooting = true;
			break;
		case SDLK_p: /*pause/resume sounds*/
			sound->changeState();
			break;
		}
		break;
	/*a key was released*/
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
			/*keys control for player A*/
		case SDLK_w:
			playerA->velocity.y = 0;
			break;
		case SDLK_s:
			playerA->velocity.y = 0;
			break;
		case SDLK_a:
			playerA->velocity.x = 0;
			playerA->setTexture("assets/playerA_s.png");
			playerA->isRunning = false;
			break;
		case SDLK_d:
			playerA->velocity.x = 0;
			playerA->setTexture("assets/playerA_s.png");
			playerA->isRunning = false;
			break;
		case SDLK_SPACE:
			playerA->isShooting = false;
			break;
			/*keys control for player B*/
		case SDLK_UP:
			playerB->velocity.y = 0;
			break;
		case SDLK_DOWN:
			playerB->velocity.y = 0;
			break;
		case SDLK_LEFT:
			playerB->velocity.x = 0;
			playerB->setTexture("assets/playerB_s.png");
			playerB->isRunning = false;
			break;
		case SDLK_RIGHT:
			playerB->velocity.x = 0;
			playerB->setTexture("assets/playerB_s.png");
			playerB->isRunning = false;
			break;
		case SDLK_KP_0:
			playerB->isShooting = false;
			break;
		}
		break;
	}
}

/*update game's components*/
void Game::update()
{
	if (timer->update()) /*time is over*/
	{
		timer->stop();
		if (playerA->scoreBoard->getScore() < playerB->scoreBoard->getScore()) /*playerB is the winner, Game is over*/
		{
			winner = playerB;
			GameOver = true;
		}			
		else if (playerA->scoreBoard->getScore() > playerB->scoreBoard->getScore())	/*playerB is the winner, Game is over*/
		{
			winner = playerA;
			GameOver = true;
		}
		else /*draw*/
		{
			goldenGoal = true; /*start golden goal mode*/
			map->setTexture("assets/map_golden.png");
		}
	}
	if (Collision::AABB(playerA->getBox(), ball->getBox()))
	{ 
		std::cout << "PlayerA hits the ball!" << std::endl;
		playerA->hitsTheBall(ball);
	}
	if (Collision::AABB(playerB->getBox(), ball->getBox()))
	{
		std::cout << "PlayerB hits the ball!" << std::endl;
		playerB->hitsTheBall(ball);
	}
	if (Collision::AABB_GoalR(ball->getBox(), gateR->getBox()))
	{
		std::cout << "GOAL!!!!!" << std::endl;
		timer->pause();
		if (volumeOn == true)
		{
			Mix_PlayChannel(-1, Game::sound->goal, 0);	/*play sound effect for goals*/
		}
		map->setTexture("assets/map_goal.png"); /*update map*/
		playerA->scoreBoard->increment();	/*update scoreboard*/
		if (goldenGoal) /*golden goal mode is active*/
		{
			winner = playerA;
			GameOver = true;
		}
		else
		{
			resetGame = true;
		}
	}
	if (Collision::AABB_GoalL(ball->getBox(), gateL->getBox()))
	{
		std::cout << "GOAL!!!!!" << std::endl;
		timer->pause();
		if (volumeOn == true)
		{
			Mix_PlayChannel(-1, Game::sound->goal, 0);	/*play sound effect for goals*/
		}
		map->setTexture("assets/map_goal.png");	/*update map*/
		playerB->scoreBoard->increment(); /*update scoreboard*/
		if (goldenGoal) /*golden goal mode is active*/
		{
			winner = playerB;
			GameOver = true;
		}
		else
		{
			resetGame = true;
		}
	}
	if (Collision::AABB_GateL(ball->getBox(), gateL->getBox())) /*the ball hits the crossbar of left gate*/
	{
		ball->velocity.y = -ball->velocity.y - 0.7f;		/*the ball is rebounded*/
		ball->velocity.x += 1.0f;						/*the ball is forced to return on the field*/
	}
	if (Collision::AABB_GateR(ball->getBox(), gateR->getBox())) /*the ball hits the crossbar of right gate*/
	{
		ball->velocity.y = -ball->velocity.y - 0.7f;		/*the ball is rebounded*/
		ball->velocity.x += -1.0f;						/*the ball is forced to return on the field*/
	}

	ball->update();
	playerA->update();
	playerB->update();

	/*display information in console*/
	std::cout << "Ball: " << (*ball);
	std::cout << "Red Player: " << (*playerA);
	std::cout << "Blue Player: " << (*playerB) << std::endl;;

}

/*display game's components*/
void Game::render()
{
	SDL_RenderClear(renderer); /*clear window to the setted color*/
	
	map->draw();
	timer->draw();
	ball->draw();
	playerA->draw();
	playerA->scoreBoard->draw();
	playerB->draw();
	playerB->scoreBoard->draw();
	gateR->draw();
	gateL->draw();

	SDL_RenderPresent(renderer); /*update window*/
}

/*delete game's components*/
void Game::clean()
{
	if (timer != nullptr)
	{
		delete timer;
		timer = nullptr;
	}
	if (playerA != nullptr)
	{
		delete playerA;
		playerA = nullptr;
	}
	if (playerB != nullptr)
	{
		delete playerB;
		playerB = nullptr;
	}
	if (ball != nullptr)
	{
		delete ball;
		ball = nullptr;
	}
	if (gateL != nullptr)
	{
		delete gateL;
		gateL = nullptr;
	}
	if (gateR != nullptr)
	{
		delete gateR;
		gateR = nullptr;
	}
	if (map != nullptr)
	{
		delete map;
		map = nullptr;
	}
	if (winner != nullptr)
	{
		delete winner;
		winner = nullptr;
	}
	if (sound != nullptr)
	{
		delete sound;
		sound = nullptr;
	}

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();

	std::cout << "Game cleaned!..." << std::endl;
}

/*reinit the game after a player scored*/
void Game::reset()
{
	resetGame = false;
	GameOver = false;

	playerA->setTexture("assets/playerA_s.png");
	playerA->init(70.0f, SCREEN_HEIGHT - GROUND_LINE - (float)playerA->getBox().h);

	playerB->setTexture("assets/playerB_s.png");
	playerB->init(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - GROUND_LINE - (float)playerB->getBox().h);

	ball->init((SCREEN_WIDTH - ball->getBox().w) / 2.0f, (SCREEN_HEIGHT - ball->getBox().h) / 2.0f);
	map->setTexture("assets/map.png");
	timer->resume();
}

/*display the menu and handle input*/
void Game::showMenu()
{
	backToMenu = false;
	bool flag = true;
	struct {
		int x;
		int y;
	} mouse; /*mouse position*/
	SDL_Event event;
	Button* startBtn = new Button("assets/start_button.png", 300, 360);
	Button* exitBtn = new Button("assets/exit_button.png", 300, 450);
	SDL_Texture* background = TextureManager::LoadTexture("assets/background.png");
	
	while (flag)
	{
		/*display background and buttons*/
		SDL_RenderClear(renderer); 
		TextureManager::DrawTexture(background);
		startBtn->draw();
		exitBtn->draw();
		SDL_RenderPresent(renderer);

		/*handle user input*/
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			flag = false;
			break;
		case SDL_MOUSEMOTION:
			mouse.x = event.motion.x;
			mouse.y = event.motion.y;
			if (Collision::AABB(startBtn, mouse.x, mouse.y))
			{
				startBtn->mouseOver();
			}
			else
			{
				startBtn->mouseOut();
			}
			if (Collision::AABB(exitBtn, mouse.x, mouse.y))
			{
				exitBtn->mouseOver();
			}
			else
			{
				exitBtn->mouseOut();
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse.x = event.motion.x;
			mouse.y = event.motion.y;
			if (volumeOn)
			{
				Mix_PlayChannel(-1, sound->click, 0); /*sound effect on click*/
			}
			if (Collision::AABB(exitBtn, mouse.x, mouse.y))
			{
				isRunning = false;
				flag = false;
			}
			if (Collision::AABB(startBtn, mouse.x, mouse.y))
			{
				isRunning = true;
				goldenGoal = false;
				flag = false;
			}
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_p) /*pause/resume sounds*/
			{
				sound->changeState();
			}
		}
	}
	
	/*show instructions before game start*/
	if (isRunning)
	{
		SDL_RenderClear(renderer);
		SDL_Texture *infoPage = TextureManager::LoadTexture("assets/instructions.png");
		TextureManager::DrawTexture(infoPage);
		SDL_RenderPresent(renderer);

		while (!flag)
		{
			SDL_PollEvent(&event);
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				flag = true;
				break;
			case SDL_KEYDOWN: /*press any key to continue*/
				flag = true;
				if (volumeOn)
				{
					Mix_PlayChannel(-1, sound->click, 0); /*sound effect*/
				}
				timer->start();	/*start timer*/
				break;
			}
		}
		if (infoPage != nullptr)
		{
			SDL_DestroyTexture(infoPage);
			infoPage = nullptr;
		}
	}

	/*delete menu's components*/
	if (startBtn != nullptr)
	{
		delete startBtn;
		startBtn = nullptr;
	}
	if (exitBtn != nullptr)
	{
		delete exitBtn;
		exitBtn = nullptr;
	}
	if (background != nullptr)
	{
		SDL_DestroyTexture(background);
		background = nullptr;
	}
}

/*show the winner when game is over*/
void Game::showWinner()
{
	bool flag = true;
	struct {
		int x;
		int y;
	} mouse; /*mouse position*/
	SDL_Event event;
	Button* backBtn = new Button("assets/back_button.png", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 86);
	
	if (winner == playerA)
	{
		winner->setTexture("assets/playerA_s.png");
	}		
	else
	{
		winner->setTexture("assets/playerB_s.png");
	}		
	winner->init((SCREEN_WIDTH - winner->getBox().w) / 2.0f, SCREEN_HEIGHT - GROUND_LINE - winner->getBox().h - 82.0f); /*82 - podium height*/
	map->setTexture("assets/map_winner.png");
	if (volumeOn)
	{
		Mix_PlayChannel(-1, sound->win, 0); /*sound effect for winner*/
	}

	while (flag)
	{
		SDL_RenderClear(renderer);
		map->draw();
		winner->draw();
		playerA->scoreBoard->draw();
		playerB->scoreBoard->draw();
		backBtn->draw();
		SDL_RenderPresent(Game::renderer);

		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			flag = false;
			break;
		case SDL_MOUSEMOTION:
			mouse.x = event.motion.x;
			mouse.y = event.motion.y;
			if (Collision::AABB(backBtn, mouse.x, mouse.y))
			{
				backBtn->mouseOver();
			}
			else
			{
				backBtn->mouseOut();
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse.x = event.motion.x;
			mouse.y = event.motion.y;
			if (volumeOn)
			{
				Mix_PlayChannel(-1, sound->click, 0); /*sound effect on click*/
			}			
			if (Collision::AABB(backBtn, mouse.x, mouse.y))
			{
				isRunning = false;
				backToMenu = true;
				flag = false;
			}
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_p)  /*pause/resume sounds*/
			{
				sound->changeState();
			}
		}
	}

	/*reset the game*/
	winner = nullptr;
	playerA->scoreBoard->resetScore();
	playerB->scoreBoard->resetScore();
	reset();

	/*delete back button*/
	if (backBtn != nullptr)
	{
		delete backBtn;
		backBtn = nullptr;
	}
}

/*return game states*/
bool Game::running() const
{
	return isRunning;
}

bool Game::goReset() const
{
	return resetGame;
}

bool Game::isGameOver() const
{
	return GameOver;
}

bool Game::isGoingBack() const
{
	return backToMenu;
}
