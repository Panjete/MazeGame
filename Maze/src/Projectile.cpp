#include "Projectile.h"
using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;

extern Object* player1;
extern bool largeview;

extern int levelratio;
extern Map mp;

int sgn(int val){
    return (0 < val) - (val < 0);
}

Projectile::Projectile(float x_init, float y_init)
{
    xpos = x_init;
    ypos = y_init;
    objtex = TextureCreator::LoadTexture("store/dog-right.png");
    srcR.x = 0;
    srcR.y = 0;
    srcR.w = 95;
    srcR.h = 63;
    speed = 1;
    outdim = 6;

}

Projectile::~Projectile()
{
}

bool Projectile::CheckColl(){
    //std::cout << "val: " << mp.lvl[8][10] << " ";
    //std::cout << xpos << "," << ypos << std::endl;
    int a = (int)xpos;
    int b = (int)ypos;
    if (mp.lvl[b/8][a/8]!= 24 && mp.lvl[b/8][a/8]!= 22){
        return true;
    }
    if (mp.lvl[(b+outdim)/8][a/8]!= 24 && mp.lvl[(b+outdim)/8][a/8]!= 22){
        return true;
    }
    if (mp.lvl[b/8][(a+outdim)/8] != 24 && mp.lvl[b/8][(a+outdim)/8] != 22){
        return true;
    }
    if (mp.lvl[(b+outdim)/8][(a+outdim)/8] != 24 && mp.lvl[(b+outdim)/8][(a+outdim)/8] != 22){
        return true;
    }
    return false;
}

void Projectile::update(){
    //std::cout << xpos << "," << ypos << std::endl;
    srcR.x = srcR.w * static_cast<int>((SDL_GetTicks()/ 100%10));

    vx += (rand()%3 - 1);
    vy += (rand()%3 - 1);

    xpos += sgn(vx) * speed;

    if (xpos + outdim> SCREEN_WIDTH){
        xpos = SCREEN_WIDTH - outdim;
        vx -= sgn(vx);
    }
    if(xpos < 0){
        xpos = 0;
        vx -= sgn(vx);
    }
    if(this->CheckColl()){
        xpos -= speed * sgn(vx);
        vx = 0;
    }

    ypos += sgn(vy) * speed;
    if(ypos + outdim> SCREEN_HEIGHT){
        ypos = SCREEN_HEIGHT - outdim;
        ypos -= sgn(vy);
    }
    if(ypos < 0){
        ypos = 0;
        ypos -= sgn(vy);
    }
    if(this->CheckColl()){
        ypos -= speed * sgn(vy);
        vy = 0;
    }

    destR.h = outdim;
    destR.w = outdim;
    if(largeview){
        destR.x = (int)xpos;
        destR.y = ypos;
    }
    else{

        destR.x = (levelratio*xpos - player1->camera.x);
        destR.y = (levelratio*ypos - player1->camera.y);
        destR.h = outdim*levelratio;
        destR.w = outdim*levelratio;
    }
    flip = SDL_FLIP_NONE;
    if (vx < 0){
        flip = SDL_FLIP_HORIZONTAL;
    }


}
void Projectile::render(){
    if(SDL_RenderCopyEx(Game::renderer, objtex, &srcR, &destR, 0 , NULL, flip) < 0){
        printf("failed");
    };
}
