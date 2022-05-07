#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "Game.h"
#include "SDL2/SDL.h"
#include "Map.h"
#include "TextureCreator.h"

#include <string>

//#include "SDL_ttf.h"

class Object
{
    public:
        Object(float x_init, float y_init);

        void update();
        void handleEvents();
        void render();
        virtual ~Object();

        string DataToString(){
        	string f = (flip == SDL_FLIP_NONE)? "0" : "1";
            return std::to_string(xpos) + "#" +std::to_string(ypos) + "#" +std::to_string(direction) + "#" +std::to_string(yulu) + "#" +std::to_string(Score) + "#" + f;
        }
        //int right(){return xpos + destR.w;}
        //int left(){return xpos;}
        //int bottom(){return ypos + destR.h;}
        //int top(){return ypos;}

        bool CheckColl();
        bool yulu = false;
        bool stunned = false;
        SDL_Rect camera;

        float Energy;
        float Money;
        float Score;

        SDL_Texture* objtex;
        SDL_Texture* EnergyBar;
        SDL_Texture* MoneyBar;
        SDL_Texture* ScoreBar;
        SDL_Rect srcR, destR;

        float xpos;
        float ypos;
        int direction = 1;

        SDL_Rect* cam_addr;
        SDL_RendererFlip flip = SDL_FLIP_NONE;

    protected:

    private:
        float speed;
        
        int vx = 0;
        int vy = 0;

        int outdim;




};

#endif // OBJECT_H

