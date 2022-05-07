#include "Game.h"

extern Game *game = nullptr;
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

	SDL_Texture* homescrn = TextureCreator::LoadTexture("store/welcomeScreen.png");

    SDL_RenderClear(Game::renderer);
    SDL_RenderCopy(Game::renderer,homescrn,NULL,NULL);
    SDL_RenderPresent(Game::renderer);
    
    SDL_Delay(1500);
    SDL_Event evt;
    
	homescrn = TextureCreator::LoadTexture("store/home.png");
	SDL_Rect srcR;
	srcR.h  = 680;
	srcR.w = 1472;
	srcR.y = 0;
	srcR.x = 0;
    	
	while (game->homescreen()){
	srcR.x = srcR.w * static_cast<int>((SDL_GetTicks()/ 100%5));
	SDL_RenderClear(Game::renderer);
    	SDL_RenderCopy(Game::renderer,homescrn,&srcR,NULL);
    	SDL_RenderPresent(Game::renderer);

        SDL_WaitEvent(&evt);
        if(evt.type == SDL_KEYDOWN){
            if(evt.key.keysym.sym == SDLK_p){
                game->home = false;
            }
            if(evt.key.keysym.sym == SDLK_h){
            	game->help = true;
                game->home = false;
            }
        }
	}
	
	homescrn = TextureCreator::LoadTexture("store/help.png");
    	
	while (game->helpstatus()){
	
	SDL_RenderClear(Game::renderer);
    	SDL_RenderCopy(Game::renderer,homescrn,NULL,NULL);
    	SDL_RenderPresent(Game::renderer);

        SDL_WaitEvent(&evt);
        if(evt.type == SDL_KEYDOWN){
            if(evt.key.keysym.sym == SDLK_p){
                game->help = false;
            } 
        }
        
	}
	

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
