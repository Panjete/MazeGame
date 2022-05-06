#pragma once
#ifndef TREASURE_H
#define TREASURE_H

#include "Game.h"
#include "SDL.h"
#include "Map.h"
#include "TextureCreator.h"
#include "Object.h"

const int total = 14;

class Treasure
{
    public:
        Treasure();
        virtual ~Treasure();

        int ID;
        SDL_Texture* TreasureList[total];
        int PointList[total];

        float xpos;
        float ypos;
        SDL_Rect destR;

        int DisplayTime;
        bool found;

        void update();
        void render();

        int outdim = 8;

    protected:

    private:
};

#endif // TREASURE_H
