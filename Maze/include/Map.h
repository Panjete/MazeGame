#pragma once
#ifndef MAP_H
#define MAP_H
#include<bits/stdc++.h>
#include<string>
using namespace std;
class Map
{
    public:
        Map(std::string file);
        virtual ~Map();

        void loadMap(std::string file);
        const static int height = 85;
        const static int width = 184;
        int lvl[height][width];
        vector<pair<int, int>> permitted;

    protected:

    private:
};

#endif // MAP_H
