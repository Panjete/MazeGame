#pragma once

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Game.h"
#include "SDL2/SDL.h"
#include "Map.h"
#include "TextureCreator.h"
#include "Object.h"

class Projectile
{
    public:
        Projectile(int category);

        void update();

        void render();
        virtual ~Projectile();

        bool CheckColl();
        bool pro = false;

        SDL_Rect srcR, destR;
        SDL_Texture* objtex;
        SDL_Texture* objusual;
        SDL_Texture* objpro;
        int typeinfo;
        float xpos;
        float ypos;

    protected:

    private:

        float speed;
        int direction = 0;
        int vx = 0;
        int vy = 0;
        SDL_RendererFlip flip = (vx < 0? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

        int outdim;



};

#endif // PROJECTILE_H
