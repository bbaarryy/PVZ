#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class plants{
    protected:
        sf::Texture herotexture;
        sf::Sprite shsprite;
        float x,y;
    public:
        virtual void Draw(sf::RenderWindow& window)=0;
        virtual void Move(int dx,int dy)=0;
        virtual sf::Vector2f get_coords()=0;
        
};

class tomato: public plants{ 
    public:
        tomato(float sc){
            herotexture.loadFromFile("../images/tomato.png");//загружаем картинку
            shsprite.setTexture(herotexture);
            shsprite.setScale({sc, sc});
        }
        tomato(float sc,float x,float y){
            herotexture.loadFromFile("../images/tomato.png");//загружаем картинку
            shsprite.setTexture(herotexture);
            shsprite.setScale({sc, sc});
            this->x = x;
            this->y = y;
        }
        void Draw(sf::RenderWindow& window) override{
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
};

