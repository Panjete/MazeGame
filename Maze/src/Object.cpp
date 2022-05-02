#include "Object.h"
#include "TextureCreator.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern Map mp;

Object::Object(const char* file, int x_init, int y_init)
{

    objtex = TextureCreator::LoadTexture(file);
    xpos = x_init;
    ypos = y_init;
    scale = 0.1;
}

Object::~Object()
{}


bool Object::CheckColl(){
    //std::cout << "val: " << mp.lvl[8][10] << " ";
    //std::cout << xpos/10 << "," << ypos/10 << std::endl;

    if (mp.lvl[ypos/8][xpos/8]!= 24){
        return true;
    }
    if (mp.lvl[(ypos+destR.h)/8][xpos/8]!= 24){
        return true;
    }
    if (mp.lvl[ypos/8][(xpos+destR.w)/8] != 24){
        return true;
    }
    if (mp.lvl[(ypos+destR.h)/8][(xpos+destR.w)/8] != 24){
        return true;
    }
    return false;
}

void Object::position(){
    switch(Game::event.type){
        case SDL_KEYDOWN:
            switch(Game::event.key.keysym.sym){
            case SDLK_w:
                vy = -1;
                break;
            case SDLK_s:
                vy = 1;
                break;
            case SDLK_d:
                vx = 1;
                break;
            case SDLK_a:
                vx = -1;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch(Game::event.key.keysym.sym){
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
    xpos += speed * vx;
    ypos += speed * vy;

    if (xpos + (int)scale*srcR.w> SCREEN_WIDTH){
        xpos = SCREEN_WIDTH - (int)srcR.w*scale;
    }
    if(xpos < 0){
        xpos = 0;
    }
    if(ypos + (int)scale*srcR.h> SCREEN_HEIGHT){
        ypos = SCREEN_HEIGHT - (int)srcR.h*scale;
    }
    if(ypos < 0){
        ypos = 0;
    }
    if(this->CheckColl()){
        xpos -= speed * vx;
        ypos -= speed * vy;
    }
}
void Object::update(){
    position();

    srcR.x = 0;
    srcR.y = 0;
    srcR.h = 32;
    srcR.w = 32;


    destR.x = xpos;
    destR.y = ypos;
    destR.h = (int)srcR.h*scale;
    destR.w = (int)srcR.w*scale;

    srcR.x = srcR.w * static_cast<int>((SDL_GetTicks()/ 100%4));


}
void Object::render(){


    SDL_RenderCopy(Game::renderer, objtex, &srcR, &destR);
}

