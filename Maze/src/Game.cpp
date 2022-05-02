#include "Game.h"
#include "SDL_image.h"
#include "TextureCreator.h"
#include "Object.h"
#include "Map.h"

Object* player1;
SDL_Renderer* Game::renderer = nullptr;
SDL_Texture* bgtex;
Map mp("store/lvl.txt");
SDL_Event Game::event;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	player1 = new Object("store/animated_player.png", 100, 0);
	bgtex = TextureCreator::LoadTexture("store/map.png");

}

void Game::handleEvents()
{


	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	cnt++;

    player1->update();
	//std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgtex, NULL, NULL);
    //if (SDL_RenderCopy(renderer, bgtex, NULL, NULL)< 0) {
    //printf("failed: %s\n", SDL_GetError());
    //}
	player1->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
