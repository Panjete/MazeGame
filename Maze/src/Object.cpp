#include "Object.h"
#include "TextureCreator.h"
#include <iostream>
Object::Object(const char* file, int x_init, int y_init)
{

    objtex = TextureCreator::LoadTexture(file);
    xpos = x_init;
    ypos = y_init;
}

Object::~Object()
{
}

void Object::update(){
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

    srcR.x = 0;
    srcR.y = 0;
    srcR.h = 50;
    srcR.w = 50;


    destR.x = xpos/100;
    destR.y = ypos/100;
    destR.h = srcR.h*4;
    destR.w = srcR.w*4;

    srcR.x = srcR.w * static_cast<int>((SDL_GetTicks()/ 100%4));

    std::cout << vx << " " << vy << "#/n";
}
void Object::render(){
    SDL_RenderCopy(Game::renderer, objtex, &srcR, &destR);
}
