#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <random>
#include <string>
#include <list>

#include "moving_obj.hpp"

class bullet: public Move_Obj{
    protected:
        int dir_diag;
    public:
        bullet(){
            visiable = 1;
            herotexture.loadFromFile("../images/sunflower-seed.png");
            setup_pic();
        }
        void setCoords(int X,int Y) override{
            this->y = Y;
            this->x = X;

            shsprite.setOrigin({float(X)/2,float(Y)/2});
            shsprite.setRotation(float(rnd2() % 360));
        }
};

class TomatoBullet: public bullet{
    public:
        void Move(int speed) override{
            this->x += speed;
        }
        TomatoBullet(){
            dir_diag = 0;
        }
};

class BananaBullet: public bullet{
    public:
        void Move(int speed) override{
            this->x += speed;
            this->y += dir_diag*speed;
        }
        BananaBullet(int dd){
            dir_diag = dd;
        }
};