#pragma once

#include "SDL2/SDL.h"
#include <iostream>
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool CollRect(SDL_Rect obj1, SDL_Rect obj2);

    int minutes() {return (SDL_GetTicks()/250)%60;}
    int hours() {return ((SDL_GetTicks()/250)/60)%24;}
private:
	bool isRunning = false;
	SDL_Window *window;

};
