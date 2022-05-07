#include "TextureCreator.h"



SDL_Texture* TextureCreator::LoadTexture(const char* file){
         SDL_Surface* tmp = IMG_Load(file);
         //SDL_SetColorKey( tmp, SDL_TRUE, SDL_MapRGB( tmp->format, 149, 165, 165 ) );
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

SDL_Texture* TextureCreator::LoadTextureFromText(std::string text, SDL_Color textColor, TTF_Font* gfont){
    SDL_Texture* tex;

    SDL_Surface* textSurface = TTF_RenderText_Solid( gfont, text.c_str(), textColor );
    tex = SDL_CreateTextureFromSurface(Game::renderer, textSurface );
    SDL_FreeSurface( textSurface );

    return tex;
}

