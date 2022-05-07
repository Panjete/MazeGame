#pragma once
#ifndef OBJECT2_H
#define OBJECT2_H

#include "Game.h"
#include "SDL2/SDL.h"
#include "Map.h"
#include "TextureCreator.h"

#include<bits/stdc++.h>
#include <string>
#include "Object.h"
using namespace std;

//#include "SDL_ttf.h"

class Object2
{
    public:
        Object2(float x_init, float y_init);

        void update();

        void render();
        virtual ~Object2();

        bool yulu = false;

        float Score;

        SDL_Texture* objtex;

        SDL_Rect srcR, destR;

        float xpos;
        float ypos; 
        SDL_RendererFlip flip;

        vector<string> DataToStrings(string s){
        //cout << s << "\n";
            vector<string> words;

            stringstream sstream(s);
            string txt;
            while (getline(sstream, txt, '#')){
                words.push_back(txt);
                //cout << txt << "no";
            }
            return words;
        }
	int direction = 0 ;
	int winlose = 0;
    protected:

    private:

        int outdim;

};

#endif // OBJECT_H

