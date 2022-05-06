#include "Object.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;

SDL_Texture* objright;
SDL_Texture* objstand;
SDL_Texture* objcycle;

SDL_Texture* EnergyBar;
SDL_Texture* MoneyBar;
SDL_Texture* ScoreBar;

Mix_Chunk *eat = nullptr;

extern SDL_Color textColor;
extern TTF_Font* gfont;

int levelratio = 4;
bool largeview = false;
extern SDL_Rect* cam_addr;
extern Map mp;

SDL_RendererFlip flip = SDL_FLIP_NONE;

Object::Object(float x_init, float y_init)
{

    objright = TextureCreator::LoadTexture("store/boy-right.png");
    objstand = TextureCreator::LoadTexture("store/boy-stand.png");
    objcycle = TextureCreator::LoadTexture("store/boy-cycleright.png");
    objtex = objstand;

    xpos = x_init;
    ypos = y_init;
    speed = 0.5;
    outdim = 6;

    Energy = 100;
    Money = 50;
    Score = 0;

    eat = Mix_LoadWAV( "store/eating.wav");

}

Object::~Object()
{}

SDL_Rect cam_init(SDL_Rect camera, SDL_Rect destR, float xpos, float ypos){
    camera = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
    camera.x = (int)levelratio*( xpos + destR.w / 2 ) - SCREEN_WIDTH / 2;
    camera.y = (int)levelratio*( ypos +  destR.h / 2 ) - SCREEN_HEIGHT / 2;

    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
    return camera;

}

bool Object::CheckColl(){
    //std::cout << "val: " << mp.lvl[8][10] << " ";
    //std::cout << xpos << "," << ypos << std::endl;
    int a = (int)xpos;
    int b = (int)ypos;
    if (mp.lvl[b/8][a/8] > 24){
        return true;
    }
    if (mp.lvl[(b+outdim)/8][a/8] > 24){
        return true;
    }
    if (mp.lvl[b/8][(a+outdim)/8] > 24){
        return true;
    }
    if (mp.lvl[(b+outdim)/8][(a+outdim)/8] >24){
        return true;
    }
    return false;
}

void Object::handleEvents(){
    int a = (int)xpos;
    int b = (int)ypos;
    switch(Game::event.type){
        case SDL_KEYDOWN:
            switch(Game::event.key.keysym.sym){
            case SDLK_SPACE:
                if(mp.lvl[b/8][a/8] == 22 || mp.lvl[(b+outdim)/8][a/8] == 22 || mp.lvl[b/8][(a+outdim)/8] == 22 || mp.lvl[(b+outdim)/8][(a+outdim)/8] == 22){
                    yulu = !yulu;
                }
                if(mp.lvl[b/8][a/8] < 13 || mp.lvl[(b+outdim)/8][a/8] < 13 || mp.lvl[b/8][(a+outdim)/8] < 13 || mp.lvl[(b+outdim)/8][(a+outdim)/8] < 13){
                    Energy += 0.05;
                    Money -= 0.03;
                    Mix_PlayChannel(-1, eat, 0);
                }
                if(mp.lvl[b/8][a/8] == 13 || mp.lvl[(b+outdim)/8][a/8] == 13 || mp.lvl[b/8][(a+outdim)/8] == 13 || mp.lvl[(b+outdim)/8][(a+outdim)/8] == 13){
                    Energy += 0.08;
                    Money -= 0.06;
                    Mix_PlayChannel(-1, eat, 0);
                }
                break;
            case SDLK_l:
                largeview = true;
                break;
            case SDLK_w:
                vy = -1;
                break;
            case SDLK_s:
                vy = 1;
                break;
            case SDLK_d:
                vx = 1;
                direction = 1;
                break;
            case SDLK_a:
                vx = -1;
                direction = -1;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch(Game::event.key.keysym.sym){
            case SDLK_l:
                largeview = false;
                break;
            case SDLK_w:
                vy = 0;
                break;
            case SDLK_s:
                vy = 0;
                break;
            case SDLK_d:
                vx = 0;
                break;
            case SDLK_a:
                vx = 0;
                break;
            default:
                break;
            }
        break;
            default:
                break;
    }
    if(yulu){
        speed = 2;
    }
    else{
        speed = 0.7;
    }
    xpos += speed * vx;
    if (xpos + outdim> SCREEN_WIDTH){
        xpos = SCREEN_WIDTH - outdim;
    }
    if(xpos < 0){
        xpos = 0;
    }
    if(this->CheckColl()){
        xpos -= speed * vx;
    }

    ypos += speed * vy;
    if(ypos + outdim> SCREEN_HEIGHT){
        ypos = SCREEN_HEIGHT - outdim;
    }
    if(ypos < 0){
        ypos = 0;
    }
    if(this->CheckColl()){
        ypos -= speed * vy;
    }
}
void Object::update(){

    //if(! (EnergyBar = TextureCreator::LoadTextureFromText("Energy: "+ std::to_string((int)Energy), textColor, gfont))){
      //  std::cout << "fail" ;
    //}
    EnergyBar = TextureCreator::LoadTextureFromText("Energy: "+ std::to_string((int)Energy), textColor, gfont);
    MoneyBar = TextureCreator::LoadTextureFromText("Money: "+ std::to_string((int)Money), textColor, gfont);
    ScoreBar = TextureCreator::LoadTextureFromText("Score: "+ std::to_string((int)Score), textColor, gfont);
    Money += 0.005;

    destR.h = outdim;
    destR.w = outdim;
    if(largeview){
        destR.x = (int)xpos;
        destR.y = (int)ypos;
        cam_addr = NULL;
    }
    else{
        camera = cam_init(camera, destR, xpos, ypos);
        destR.x = (int)(levelratio*xpos - camera.x);
        destR.y = (int)(levelratio*ypos - camera.y);
        destR.h = outdim*levelratio;
        destR.w = outdim*levelratio;
        cam_addr = &camera;
    }

    if(Money < 0){
        yulu = false;
        Money = 0;
        Energy -= 5;
    }
    if(!stunned && Energy > 0){
        handleEvents();
        Energy -= (abs(vx) + abs(vy))*0.005;
        if(yulu){
            Money -= 0.02;
            objtex = objcycle;
            srcR.x = 0;
            srcR.y = 0;
            srcR.h = 92;
            srcR.w = 106;
            srcR.x = srcR.w * static_cast<int>((SDL_GetTicks()/ 100%8));
            if(static_cast<int>((SDL_GetTicks()/ 100%16)) >= 8){
                srcR.y = srcR.h;
            }
        }
        else if(vx == 0 && vy  == 0){
            objtex = objstand;
            srcR.x = 0;
            srcR.y = 0;
            srcR.h = 426;
            srcR.w = 316;
        }
        else if (direction){
            objtex = objright;
            srcR.x = 0;
            srcR.y = 0;
            srcR.h = 76;
            srcR.w = 76;
            srcR.x = srcR.w * static_cast<int>((SDL_GetTicks()/ 100%8));
        }

        flip = SDL_FLIP_NONE;
        if (direction == -1){
            flip = SDL_FLIP_HORIZONTAL;
        }
    }
    //std::cout << camera.x << " " << camera.y << " " << camera.w << " " << camera.h << std::endl;

}
void Object::render(){


    SDL_RenderCopyEx(Game::renderer, objtex, &srcR, &destR, 0, NULL, flip);

    SDL_Rect rectE = {0,0,300,50};
    if(SDL_RenderCopy(Game::renderer, EnergyBar, NULL, &rectE)<0){
       printf(SDL_GetError());
    }

    SDL_Rect rectM = {0,50,300,50};
    if(SDL_RenderCopy(Game::renderer, MoneyBar, NULL, &rectM)<0){
       printf(SDL_GetError());
    }

    SDL_Rect rectS = {0,100,300,50};
    if(SDL_RenderCopy(Game::renderer, ScoreBar, NULL, &rectS)<0){
       printf(SDL_GetError());
    }
}

