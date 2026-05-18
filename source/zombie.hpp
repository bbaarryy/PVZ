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
        int health;
        int score;
        float damage;

        zombie(){
            health=3;
            score=100;
            visiable=1;
            herotexture.loadFromFile("../images/zombie2.png");
            setup_pic();
        }
        
        virtual ~zombie() {}
        
        virtual void takeDamage(int damage) {
            health -= damage;
        }
        
        virtual bool isDead() const {
            return health <= 0;
        }
        
        virtual bool isNormal() const {
            return true;
        }
        
        virtual int getScore() const {
            return score;
        }
        
        virtual void Move(int speed) override = 0;
};

class PureZombie: public zombie{
    public:
        void Move(int speed) override{
            this->x -= speed*0.5;
        }
        
        PureZombie(){
            visiable=1;
            herotexture.loadFromFile("../images/zombie2.png");
            this->health = 3;
            this->score = 100;
            this->damage = 0.1;
        }
        bool isNormal() const override {
            return true;
        }
};

class StrongZombie: public zombie{
    public:
        void Move(int speed) override{
            this->x -= speed*0.7;
        }
        
        StrongZombie(){
            visiable=1;
            herotexture.loadFromFile("../images/chasing.png");
            this->health = 6;
            this->score = 200;
            this->damage = 0.1;
        }
        
        bool isNormal() const override {
            return false;
        }
};

class FastZombie: public zombie{
    public:
        void Move(int speed) override{
            this->x -= speed;
        }
        FastZombie(){
            this->damage = 0.07;
            visiable=1;
            herotexture.loadFromFile("../images/zombie3.png");
            this->health = 1;
            this->score = 100;
        }
        bool isNormal() const override {
            return false;
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
        bool isNormal() const override {
            return false;
        }
};

