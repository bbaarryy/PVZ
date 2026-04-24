#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "bullet.hpp"
#include <list>

typedef std::list<bullet*> shoot_massive_T;

class plants{
    protected:
        sf::Texture herotexture;
        sf::Sprite shsprite;
        sf::RectangleShape rectangle;
        float x,y;
        float szx, szy;
        bool chosen;

    public:
        plants(){
            herotexture.loadFromFile("../images/sesame.png");
            shsprite.setTexture(herotexture);
            shsprite.setScale({0.13,0.13});
            this->szx = shsprite.getScale().x * herotexture.getSize().x;
            this->szy = shsprite.getScale().y * herotexture.getSize().y;
            chosen=0;
        }
        void Draw(sf::RenderWindow& window) {
            rectangle.setPosition(this->x,this->y);
            rectangle.setSize({this->szx, this->szy});
            rectangle.setFillColor(sf::Color(250, 0, 50));
            //DEBUG
            //window.draw(rectangle);
            //
            if(this->chosen){
                shsprite.setColor(sf::Color(255, 255, 255, 128));
            }
            else{
                shsprite.setColor(sf::Color(255, 255, 255, 255));
            }
            shsprite.setPosition({this->x, this->y });
            window.draw(shsprite);
        }
        sf::Vector2f get_coords(){
            return( sf::Vector2f(this->x,this->y) );
        }
        void Move(int dx,int dy){
            this->y += dy;
            this->x += dx;
        }
        sf::Vector2f PlantGetSize(){
            return( sf::Vector2f(this->szx,this->szy) );
        }
        void Select(){
            this->chosen = 1;
        }
        void UnSelect(){
            this->chosen = 0;
        }
        void setCoords(int X,int Y){
            this->y = Y;
            this->x = X;
        }
        virtual void shoot(shoot_massive_T& arr)=0;
};


class tomato: public plants{ 
    public:
        tomato(float sc){
            herotexture.loadFromFile("../images/tomato.png");//загружаем картинку
        }
        tomato(float sc,float x,float y){
            herotexture.loadFromFile("../images/tomato.png");//загружаем картинку
            this->x = x;
            this->y = y;
        }
        void shoot(shoot_massive_T& arr ){
            bullet* curr = new TomatoBullet;
            curr->setCoords(this->get_coords().x, this->get_coords().y);
            arr.push_back(curr);
        }
};

class banana: public plants{ 
    public:
        banana(float sc){
            herotexture.loadFromFile("../images/banana.png");//загружаем картинку
        }
        banana(float sc,float x,float y){
            herotexture.loadFromFile("../images/banana.png");//загружаем картинку
            this->x = x;
            this->y = y;
        }
        void shoot(shoot_massive_T& arr ){
            bullet* curr1 = new BananaBullet(1);
            curr1->setCoords(this->get_coords().x, this->get_coords().y);
            bullet* curr2 = new BananaBullet(-1);
            curr2->setCoords(this->get_coords().x, this->get_coords().y);
            arr.push_back(curr1);arr.push_back(curr2);
        }
};

