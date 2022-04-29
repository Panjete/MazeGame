#ifndef OBJECT_H
#define OBJECT_H
#include "Game.h"
#include "SDL.h"

class Object
{
    public:
        Object(const char* file, int x_init, int y_init);

        void update();
        void render();
        virtual ~Object();

    protected:

    private:
        int speed = 100;
        int vx = 0;
        int vy = 0;

        int xpos;
        int ypos;

        SDL_Texture* objtex;
        SDL_Rect srcR, destR;

};

#endif // OBJECT_H

