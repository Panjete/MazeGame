#pragma once
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <string>

class TextureCreator
{
    public:
        static SDL_Texture* LoadTexture(const char* file);
        static SDL_Texture* LoadTextureFromText(std::string text, SDL_Color textColor, TTF_Font* gfont);

    protected:

    private:

};

