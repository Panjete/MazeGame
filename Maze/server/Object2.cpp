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
	//for(int i = 0; i< 5; i++){
	//	std::cout << words[i] <<  "lol" << "\n";
	//}	

    
    xpos = stof(words[0]);
    ypos = stof(words[1]);
    direction = stoi(words[2]);
    yulu = (words[3] == "1");
    Score = stof(words[4]);
    flip = stoi(words[5]) == 1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
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
    /*if(yulu){
        objtex =
        srcR.x =
        srcR.y =
        srcR.w =
        srcR.h =
    }
    else if(direction == 0){
        objtex =
        srcR.x =
        srcR.y =
        srcR.w =
        srcR.h =
    }
    else{
        objtex =
        srcR.x =
        srcR.y =
        srcR.w =
        srcR.h =
    }*/

    ScoreBar = TextureCreator::LoadTextureFromText("Score: "+ std::to_string((int)Score), textColor, gfont);

    if(largeview){
        destR.x = xpos;
        destR.y = ypos;
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
}
