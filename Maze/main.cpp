#include "Game.h"

Game *game = nullptr;
extern const int SCREEN_WIDTH = 1472;
extern const int SCREEN_HEIGHT = 680;

bool fullscreen = false;
int main(int argc, char *argv[])
{
	game = new Game();
	game->init("GameWindow", SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen);

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	return 0;
}
