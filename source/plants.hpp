#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class plants{
    protected:
        sf::Texture herotexture;
        sf::Sprite shsprite;
        float x,y;
        float szx, szy;
    public:
        plants(){
            herotexture.loadFromFile("../images/sesame.png");
            shsprite.setTexture(herotexture);
            shsprite.setScale({0.13,0.13});
            this->szx = shsprite.getScale().x * herotexture.getSize().x;
            this->szy = shsprite.getScale().y * herotexture.getSize().y;
        }
        void Draw(sf::RenderWindow& window) {
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
};

