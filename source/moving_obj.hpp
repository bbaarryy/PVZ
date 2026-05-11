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

class Move_Obj{
    protected:
        sf::Texture herotexture;
        sf::Sprite shsprite;
        sf::RectangleShape rectangle;
        float x,y;
        float szx, szy;
    public:
        sf::FloatRect boundingBox;
        bool visiable;
        Move_Obj(){
            visiable = 1;
            
            herotexture.loadFromFile("../images/sunflower-seed.png");
        }
        virtual ~Move_Obj(){
            
        }

        void setup_pic(){
            shsprite.setTexture(herotexture);
            shsprite.setScale({0.13,0.13});
            
            this->szx = shsprite.getScale().x * herotexture.getSize().x;
            this->szy = shsprite.getScale().y * herotexture.getSize().y;
        }
        void Draw(sf::RenderWindow& window) {
            
            boundingBox = shsprite.getGlobalBounds();
            //DEBUG
            // rectangle.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
            // rectangle.setSize(sf::Vector2f(boundingBox.width, boundingBox.height));
            // rectangle.setFillColor(sf::Color(250, 0, 50));
            // window.draw(rectangle);
            //
            shsprite.setPosition({this->x, this->y });
            window.draw(shsprite);
        }

        sf::Vector2f get_coords(){
            return( sf::Vector2f(this->x,this->y) );
        }

        virtual void Move(int speed) = 0;

        sf::Vector2f GetSize(){
            return( sf::Vector2f(this->szx,this->szy) );
        }
        
        virtual void setCoords(int X,int Y){
            this->y = Y;
            this->x = X;
        }
};