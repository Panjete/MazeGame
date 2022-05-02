#include "TextureCreator.h"
#include "SDL_image.h"

SDL_Texture* TextureCreator::LoadTexture(const char* file){
         SDL_Surface* tmp = IMG_Load(file);
         if(!tmp) {
            printf("IMG_Load: %s\n", IMG_GetError());
            // handle error
         }
         SDL_Texture* tex;
         if(SDL_CreateTextureFromSurface(Game::renderer, tmp) == NULL){
            printf("failed: %s\n", SDL_GetError());
         }
         else{
            tex = SDL_CreateTextureFromSurface(Game::renderer, tmp);
         }

         SDL_FreeSurface(tmp);

         return tex;
     }

