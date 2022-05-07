#include "Map.h"
#include "Game.h"
#include<fstream>
#include<bits/stdc++.h>
using namespace std;
Map::Map(std::string file)
{
    loadMap(file);
}

Map::~Map()
{
}

void Map::loadMap(std::string file){
    //char tile;
    std::fstream mapFile;
    mapFile.open(file);

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            mapFile >> lvl[y][x];
            if (lvl[y][x] == 24){
                permitted.push_back(make_pair(x,y));
            }
            //this->lvl[y][x] = atoi(&tile);
        }
    }
    mapFile.close();
}
