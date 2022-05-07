#pragma once
#include "Game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <string>

class TextureCreator
{
    public:
        static SDL_Texture* LoadTexture(const char* file);
        static SDL_Texture* LoadTextureFromText(std::string text, SDL_Color textColor, TTF_Font* gfont);

    protected:

    private:

};

