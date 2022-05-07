#include "Object2.h"

SDL_Texture* ScoreBar;

SDL_Texture* objright2;
SDL_Texture* objstand2;
SDL_Texture* objcycle2;
extern string message ;
extern SDL_Color textColor;
extern TTF_Font* gfont;
extern Object* player1;
extern bool largeview;
extern Game *game;
extern int levelratio;

Object2::Object2(float x_init, float y_init)
{

    objright2 = TextureCreator::LoadTexture("store/boy-right.png");
    objstand2 = TextureCreator::LoadTexture("store/boy-stand.png");
    objcycle2 = TextureCreator::LoadTexture("store/boy-cycleright.png");
    objtex = objstand2;

    xpos = x_init;
    ypos = y_init;

    outdim = 6;

}

Object2::~Object2()
{
    //dtor
}

void Object2::update(){
    vector<string> words = DataToStrings(message);

    xpos = stof(words[0]);
    ypos = stof(words[1]);
    direction = stoi(words[2]);
    yulu = (words[3] == "1");
    Score = stof(words[4]);
    flip = stoi(words[5]) == 1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    winlose = stoi(words[6]);
    /*
    xpos = 100;
    ypos = 200;
    direction = 0;
    
    yulu = false;
    Score = 10;
    flip = SDL_FLIP_NONE;
*/
    srcR.x = 0;
    srcR.y = 0;
    srcR.w = 316;
    srcR.h = 426;

    if(yulu){
        objtex = objcycle2;
        srcR.x = 0;
            srcR.y = 0;
            srcR.h = 92;
            srcR.w = 106;
            srcR.x = srcR.w * static_cast<int>((SDL_GetTicks()/ 100%8));
            if(static_cast<int>((SDL_GetTicks()/ 100%16)) >= 8){
                srcR.y = srcR.h;
            }
        
    }
    else if(direction == 0){
        objtex = objstand2;
        srcR.x = 0;
            srcR.y = 0;
            srcR.h = 426;
            srcR.w = 316;
    }
    else{
        objtex = objright2;
        srcR.x = 0;
            srcR.y = 0;
            srcR.h = 76;
            srcR.w = 76;
            srcR.x = srcR.w * static_cast<int>((SDL_GetTicks()/ 100%8));
    }

    ScoreBar = TextureCreator::LoadTextureFromText("Enemy Score: "+ std::to_string((int)Score), textColor, gfont);

    if(largeview){
        destR.x = xpos;
        destR.y = ypos;
        destR.h = outdim;
        destR.w = outdim;
    }
    else{

        destR.x = (levelratio*xpos - player1->camera.x);
        destR.y = (levelratio*ypos - player1->camera.y);
        destR.h = outdim*levelratio;
        destR.w = outdim*levelratio;
    }
}
void Object2::render(){

    if(SDL_RenderCopyEx(Game::renderer, objtex, &srcR, &destR, 0, NULL, flip)<0){
    	printf(SDL_GetError());
    }

    SDL_Rect rectS = {1200,50,272,50};
    if(SDL_RenderCopy(Game::renderer, ScoreBar, NULL, &rectS)<0){
       printf(SDL_GetError());
    }
    if(winlose != 0){
    	game->isRunning = false;
    	SDL_Texture* endscrn;
    	if(winlose == 1){
    		endscrn = TextureCreator::LoadTexture("store/loseScreen.png");;
    	}
    	if(winlose == -1){
    		endscrn = TextureCreator::LoadTexture("store/winScreen.png");;
    	}
    	SDL_RenderClear(Game::renderer);
    	SDL_RenderCopy(Game::renderer,endscrn,NULL,NULL);
    	SDL_RenderPresent(Game::renderer);
    
    	SDL_Delay(5000);
    }
}
