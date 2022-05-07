#include "Game.h"
#include "SDL2/SDL_image.h"
#include "TextureCreator.h"
#include "Object.h"
#include "Map.h"
#include "Projectile.h"
#include "Treasure.h"
#include "client.h"
#include "Object2.h"

Object* player1 = nullptr;
Object2* player2 = nullptr;

Projectile* dog = nullptr;
Projectile* dog2 = nullptr;
Projectile* bee = nullptr;
Projectile* bee2 = nullptr;
Treasure* obj1 = nullptr;
Treasure* obj2 = nullptr;

Mix_Music *MyMusic = nullptr;
Mix_Chunk *bark = nullptr;
Mix_Chunk *buzz = nullptr;
Mix_Chunk *gain = nullptr;

SDL_Texture* bgtex;
SDL_Texture* bgday;
SDL_Texture* bgnight;
SDL_Texture* clok;

Uint32 t_start = 0;
SDL_Renderer* Game::renderer = nullptr;
Map mp("store/lvl.txt");
SDL_Event Game::event;

SDL_Color textColor = { 0, 255, 255 };
TTF_Font* gfont;
client FP1;

string message;

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

    gfont = TTF_OpenFont("store/CaviarDreams_BoldItalic.ttf",28);
    if(gfont == NULL){printf(TTF_GetError());}

    MyMusic = Mix_LoadMUS( "store/LALA.mp3");
    bark = Mix_LoadWAV( "store/dog-barking");
    buzz = Mix_LoadWAV( "store/wasp-fly.mp3");
    gain = Mix_LoadWAV( "store/gain.wav");
   //if   (!gain) {
    //printf("Mix_LoadWAV: %s\n", Mix_GetError());
//     handle error
//}

    //Mix_PlayMusic( MyMusic, -1 );
	player1 = new Object(1086, 0);
	player2 = new Object2(100,0);
	dog = new Projectile(0);
	dog2 = new Projectile(0);
	bee= new Projectile(1);
	bee2 = new Projectile(1);
	bgday = TextureCreator::LoadTexture("store/map.png");
	bgnight = TextureCreator::LoadTexture("store/map-dark.png");
	bgtex = bgday;
    obj1 = new Treasure();
    obj2 = new Treasure();
  
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
    message = FP1.sendrecieve(player1-> DataToString());; 
    //FP1.sendrecieve(player1-> DataToString());

    clok = TextureCreator::LoadTextureFromText("Time "+ std::to_string(hours())+":"+std::to_string(minutes()), textColor, gfont);
    //std::cout << hours() << ":"<< minutes() << "\n";
    if(hours() < 6 || hours() >= 20){
        bgtex = bgnight;
        //std::cout << "raat";
    }
    else{
        bgtex = bgday;
    }
    dog->update();
    dog2->update();
    bee->update();
    bee2->update();

    player1->update();
    player2->update();

    obj1->update();
    obj2->update();

    if(!player1->stunned && CollRect(player1->destR, dog->destR)){
        t_start = SDL_GetTicks();
        player1->stunned = true;
        player1->xpos = 497;
        player1->ypos = 266;
        player1->Energy -= 20;
        dog->pro = true;
    }
    if(!player1->stunned && CollRect(player1->destR, dog2->destR)){
        t_start = SDL_GetTicks();
        player1->stunned = true;
        player1->xpos = 497;
        player1->ypos = 266;
        player1->Energy -= 20;
        dog2->pro = true;
    }
    if(!player1->stunned && CollRect(player1->destR, bee->destR)){
        t_start = SDL_GetTicks();
        player1->stunned = true;
        player1->Energy -= 10;
        bee->pro = true;
    }
    if(!player1->stunned && CollRect(player1->destR, bee2->destR)){
        t_start = SDL_GetTicks();
        player1->stunned = true;
        player1->Energy -= 10;
        bee2->pro = true;
    }
    if(player1->stunned && (SDL_GetTicks()  - t_start > 5000)){
        player1->stunned = false;
        dog->pro = false;
        dog2->pro = false;
        bee->pro = false;
        bee2->pro = false;
    }

    if(CollRect(player1->destR, obj1->destR)){
        player1->Score += obj1->PointList[obj1->ID];
        Mix_PlayChannel(-1, gain, 0);
        obj1->found = true;
    }
    if(CollRect(player1->destR, obj2->destR)){
        player1->Score += obj2->PointList[obj2->ID];
        Mix_PlayChannel(-1, gain, 0);
        obj2->found = true;
    }

    if(((abs(dog2->xpos - player1->xpos) < 50) && (abs(dog2->ypos - player1->ypos) < 50)) || ((abs(dog->xpos - player1->xpos) < 50) && (abs(dog->ypos - player1->ypos) < 50))){
        Mix_PlayChannel(-1, bark, 0);
        //std::cout << "bhau " ;
        //if(Mix_PlayChannel(-1, bark, 0)==-1) {
        //printf("Mix_PlayChannel: %s\n",Mix_GetError());
        //}
    }
    if(((abs(bee2->xpos - player1->xpos) < 50) && (abs(bee2->ypos - player1->ypos) < 50)) || ((abs(bee->xpos - player1->xpos) < 50) && (abs(bee->ypos - player1->ypos) < 50))){

        Mix_PlayChannel(-1, buzz, 0);
        //std::cout << "bhau " ;
        //if(Mix_PlayChannel(-1, bark, 0)==-1) {
        //printf("Mix_PlayChannel: %s\n",Mix_GetError());
        //}
    }


}
void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(Game::renderer, bgtex, player1->cam_addr, NULL);
	player1->render();
	player2->render();
	dog->render();
	dog2->render();
	bee->render();
	bee2->render();
	obj1->render();
	obj2->render();
	SDL_Rect clockR = {1200,0,272,50};
	if(SDL_RenderCopy(renderer, clok, NULL, &clockR)<0){
       printf(SDL_GetError());
    }


	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_FreeChunk(gain);
    Mix_FreeChunk(bark);
    Mix_FreeChunk(buzz);
    Mix_FreeMusic(MyMusic);
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
