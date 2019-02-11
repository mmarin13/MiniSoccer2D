/***************************************************************************
Application name: MINI SOCCER
Author: Moisii Marin
Afiliation: Faculty of Automatic Control and Computer Engineering
2018-2019
***************************************************************************/

#include "Game.h"

int main(int argc, char *argv[])
{
	Game *game = new Game(); 
	game->init("MINI SOCCER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	game->showMenu();

	/*game loop*/
	while (game->running())
	{
		Uint32 frameStart = SDL_GetTicks(); /*get current time relative of SDL initialization*/
		
		game->handleEvents(); 
		game->update();
		game->render();

		if (game->goReset())
		{
			SDL_Delay(2000);	/*wait 2 seconds*/
			game->reset();
		}

		if (game->isGameOver())
		{ 
			SDL_Delay(2000);	/*wait 2 seconds*/
			game->showWinner();
		}

		if (game->isGoingBack())
		{
			game->showMenu();
		}

		const int frameTime = SDL_GetTicks() - frameStart; /*get the duration of current frame*/
		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}
	game->clean();
	delete game;
	return 0;
}