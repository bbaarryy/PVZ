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

class zombie: public Move_Obj{
    public:
        int health;int score;
        float damage;
        zombie(){
            health=3;
            visiable=1;
            herotexture.loadFromFile("../images/zombie2.png");
            setup_pic();
        }
};

class PureZombie: public zombie{
    public:
        void Move(int speed) override{
            this->x -= speed*0.5;
        }
        PureZombie(){
            damage = 0.1;
            visiable=1;
            herotexture.loadFromFile("../images/zombie2.png");
            this->health = 3;
            this->score = 100;
        }
};


class FastZombie: public zombie{
    public:
        void Move(int speed) override{
            this->x -= speed;
        }
        FastZombie(){
            damage = 0.07;
            visiable=1;
            herotexture.loadFromFile("../images/zombie3.png");
            this->health = 1;
            this->score = 100;
        }
};

class ArmZombie: public zombie{
    public:
        void Move(int speed) override{
            this->x -= speed*0.2;
        }
        ArmZombie(){
            damage = 0.1;
            visiable=1;
            herotexture.loadFromFile("../images/zombie5.png");
            this->health = 5;
            this->score = 100;
        }
};

