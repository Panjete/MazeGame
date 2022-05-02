#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "Game.h"
#include "SDL.h"
#include "Map.h"

class Object
{
    public:
        Object(const char* file, int x_init, int y_init);

        void update();
        void position();
        void render();
        virtual ~Object();

        int right(){return xpos + destR.w;}
        int left(){return xpos;}
        int bottom(){return ypos + destR.h;}
        int top(){return ypos;}

        bool CheckColl();

    protected:

    private:
        int speed = 1 ;
        int vx = 0;
        int vy = 0;

        int xpos;
        int ypos;
        float scale;

        SDL_Texture* objtex;
        SDL_Rect srcR, destR;


};

#endif // OBJECT_H

