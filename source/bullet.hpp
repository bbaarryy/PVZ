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

std::mt19937 rnd2(std::chrono::steady_clock::now().time_since_epoch().count());

class bullet{
    protected:
        sf::Texture herotexture;
        sf::Sprite shsprite;
        sf::RectangleShape rectangle;
        float x,y;
        float szx, szy;
        int dir_diag;
        bool visiable;
    public:
        bullet(){
            visiable = 1;
            herotexture.loadFromFile("../images/sunflower-seed.png");
            shsprite.setTexture(herotexture);
            shsprite.setScale({0.13,0.13});
            shsprite.setRotation(float(rnd2() % 360));
            this->szx = shsprite.getScale().x * herotexture.getSize().x;
            this->szy = shsprite.getScale().y * herotexture.getSize().y;
        }
        void Draw(sf::RenderWindow& window) {
            //DEBUG
            //rectangle.setPosition(this->x,this->y);
            //rectangle.setSize({this->szx, this->szy});
            //rectangle.setFillColor(sf::Color(250, 0, 50));
            //window.draw(rectangle);
            //
            if(visiable){
            shsprite.setPosition({this->x, this->y });
            window.draw(shsprite);}
        }
        sf::Vector2f get_coords(){
            return( sf::Vector2f(this->x,this->y) );
        }

        virtual void Move(int speed) = 0;

        sf::Vector2f BulletGetSize(){
            return( sf::Vector2f(this->szx,this->szy) );
        }
        
        void setCoords(int X,int Y){
            this->y = Y;
            this->x = X;
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