#include "Game.h"
#include "SDL_image.h"
#include "TextureCreator.h"
#include "Object.h"
#include "Map.h"
#include "Projectile.h"

Object* player1 = nullptr;
Projectile* dog = nullptr;
Projectile* dog2 = nullptr;

Mix_Music *MyMusic = NULL;
SDL_Texture* bgtex;
SDL_Rect* cam_addr = NULL;
SDL_Renderer* Game::renderer = nullptr;
Map mp("store/lvl.txt");
SDL_Event Game::event;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow("MAZE GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	TTF_Init();
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    MyMusic = Mix_LoadMUS( "store/Ghostrifter-Official-Deflector.mp3");
    //Mix_PlayMusic( MyMusic, -1 );
	player1 = new Object(100, 0);
	dog = new Projectile(100,500);
	dog2 = new Projectile(100,100);
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
    case SDL_KEYDOWN :
        switch( event.key.keysym.sym ){

            case SDLK_m:
                if( Mix_PlayingMusic() == 0 ){
                        Mix_PlayMusic( MyMusic, -1 );
                    }
                    else{
                        if( Mix_PausedMusic() == 1 ){
                            Mix_ResumeMusic();
                        }
                        else{
                            Mix_PauseMusic();
                        }
                    }
                    break;

            default:
                break;
        }
        break;

	default:
		break;
	}
}

void Game::update()
{
    player1->update();
    dog->update();
    dog2->update();
}
void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(Game::renderer, bgtex, cam_addr, NULL);
	player1->render();
	dog->render();
	dog2->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
bool Game::CollRect(SDL_Rect obj1, SDL_Rect obj2){
    if(obj1.x + obj1.w <= obj2.x){
        return false;
    }
    if(obj2.x + obj2.w <= obj1.x){
        return false;
    }
    if(obj1.y + obj1.h <= obj2.y){
        return false;
    }
    if(obj2.y + obj2.h <= obj1.y){
        return false;
    }
    return true;
}
