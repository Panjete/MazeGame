#include "Treasure.h"
#include <bits/stdc++.h>
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;

extern Object* player1;
extern bool largeview;

extern int levelratio;
extern Map mp;

Treasure::Treasure()
{

    DisplayTime = 0;
    found = false;

    TreasureList[0] = TextureCreator::LoadTexture("store/shoe.png");
    TreasureList[1] = TextureCreator::LoadTexture("store/pen.png");
    TreasureList[2] = TextureCreator::LoadTexture("store/cassette.png");
    TreasureList[3] = TextureCreator::LoadTexture("store/specs.png");
    TreasureList[4] = TextureCreator::LoadTexture("store/daaru.png");
    TreasureList[5] = TextureCreator::LoadTexture("store/diary.png");
    TreasureList[6] = TextureCreator::LoadTexture("store/floppy.png");
    TreasureList[7] = TextureCreator::LoadTexture("store/cd-rom.png");
    TreasureList[8] = TextureCreator::LoadTexture("store/computer-bot.png");
    TreasureList[9] = TextureCreator::LoadTexture("store/videogame.png");
    TreasureList[10] = TextureCreator::LoadTexture("store/mouse.png");
    TreasureList[11] = TextureCreator::LoadTexture("store/cooler.png");
    TreasureList[12] = TextureCreator::LoadTexture("store/cycle.png");
    TreasureList[13] = TextureCreator::LoadTexture("store/envelope.png");

    PointList[0] = 6;
    PointList[1] = 5;
    PointList[2] = 7;
    PointList[3] = 7;
    PointList[4] = 8;
    PointList[5] = 10;
    PointList[6] = 5;
    PointList[7] = 5;
    PointList[8] = 10;
    PointList[9] = 8;
    PointList[10] = 6;
    PointList[11] = 9;
    PointList[12] = 9;
    PointList[13] = 5;

    destR = {0,0,outdim,outdim};
}

Treasure::~Treasure()
{

}

void Treasure::update(){
    DisplayTime -= 1;
    if(DisplayTime < 0 || found == true){
        found = false;
        DisplayTime = 1000;
        ID = rand()%14;


        std::pair loc = mp.permitted[rand()%mp.permitted.size()];

        xpos = 8*loc.first;
        ypos = 8*loc.second;
    }
    destR.h = outdim*levelratio;
    destR.w = outdim*levelratio;
    destR.x = (levelratio*xpos - player1->camera.x);
    destR.y = (levelratio*ypos - player1->camera.y);


    //std::cout << xpos << " " << ypos << " " << ID <<  "\n";
}

void Treasure::render(){
    if(!largeview){
        if(SDL_RenderCopy(Game::renderer, TreasureList[ID], NULL, &destR)){
                printf(SDL_GetError());
        }
    }
}
