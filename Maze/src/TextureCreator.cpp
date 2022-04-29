#include "TextureCreator.h"
#include "SDL_image.h"

SDL_Texture* TextureCreator::LoadTexture(const char* file){
         SDL_Surface* tmp = IMG_Load(file);
         SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmp);
         SDL_FreeSurface(tmp);

         return tex;
     }

