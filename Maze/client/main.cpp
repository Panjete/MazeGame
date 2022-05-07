#include "Game.h"

Game *game = nullptr;
extern const int SCREEN_WIDTH = 1472;
extern const int SCREEN_HEIGHT = 680;

extern const int LEVEL_WIDTH = 5888;
extern const int LEVEL_HEIGHT = 2720;



int main(int argc, char *argv[])
{
	game = new Game();
	game->init("GameWindow", SCREEN_WIDTH, SCREEN_HEIGHT);

	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	Uint32 framestart;
	int frametime;

	while (game->running())
	{
	    framestart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frametime = SDL_GetTicks() - framestart;
		if(frametime < frameDelay){
            SDL_Delay(frameDelay - frametime);
		}
	}

	game->clean();
	return 0;
}
