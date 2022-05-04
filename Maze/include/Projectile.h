#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Game.h"
#include "SDL.h"
#include "Map.h"
#include "TextureCreator.h"
#include "Object.h"

class Projectile
{
    public:
        Projectile(float x_init, float y_init);

        void update();

        void render();
        virtual ~Projectile();

        bool CheckColl();

    protected:

    private:
        float speed;
        int direction = 0;
        int vx = 0;
        int vy = 0;
        SDL_RendererFlip flip = (vx < 0? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        float xpos;
        float ypos;
        int outdim;

        SDL_Texture* objtex;
        SDL_Rect srcR, destR;
};

#endif // PROJECTILE_H
