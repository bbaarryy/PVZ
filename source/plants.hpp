#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "bullet.hpp"
#include <list>

typedef std::list<bullet*> shoot_massive_T;

class plants{
    protected:
        sf::Texture herotexture;
        sf::Sprite shsprite;
        sf::RectangleShape rectangle;
        float x,y;
        float dx,dy;
        float szx, szy;
        bool chosen;

        // Effect variables
        float shootEffectTimer; // 0 = no effect, >0 = effect active
        float baseScaleX, baseScaleY;
        // Animation variables for placement
        float targetX, targetY;
        bool isAnimating;
        float animSpeed;

    public:
        plants(){
            herotexture.loadFromFile("../images/sesame.png");
            shsprite.setTexture(herotexture);
            shsprite.setScale({0.13,0.13});
            this->szx = shsprite.getScale().x * herotexture.getSize().x;
            this->szy = shsprite.getScale().y * herotexture.getSize().y;
            chosen=0;
            shootEffectTimer = 0;
            baseScaleX = 0.13f;
            baseScaleY = 0.13f;
            isAnimating = false;
            dx=0;dy=0;
            targetX = 0;
            targetY = 0;
            animSpeed = 50.0f; // pixels per frame
        }
        void Draw(sf::RenderWindow& window) {
            rectangle.setPosition(this->x+dx,this->y+dy);
            rectangle.setSize({this->szx, this->szy});
            rectangle.setFillColor(sf::Color(250, 0, 50));
            //DEBUG
            //window.draw(rectangle);
            //
            
            // Apply shoot compression effect
            float currentScaleX = baseScaleX;
            float currentScaleY = baseScaleY;
            
            if (shootEffectTimer > 0) {
                // Compression effect: squeeze horizontally, stretch vertically
                float progress = shootEffectTimer / 10.0f; // 10 frames duration
                float compression = sin(progress * 3.14159f); // smooth sine wave
                
                currentScaleY = baseScaleY * (1.0f - 0.3f * compression);  //shrink to 70%
                this->dy = (0.3f*compression)*(this->szy);

                shootEffectTimer -= 1.0f; // decrease timer
            }
            else{dy=0;}
            
            shsprite.setScale({0.13f, currentScaleY});
            
            if(this->chosen){
                shsprite.setColor(sf::Color(255, 255, 255, 128));
            }
            else{
                shsprite.setColor(sf::Color(255, 255, 255, 255));
            }
            shsprite.setPosition({this->x + dx, this->y + dy});
            window.draw(shsprite);
        }
        
        // Update animation - call this every frame
        void updateAnimation() {
            if (isAnimating) {
                float dx = targetX - this->x;
                float dy = targetY - this->y;
                float dist = sqrt(dx*dx + dy*dy);
                
                if (dist < animSpeed) {
                    // Arrived
                    this->x = targetX;
                    this->y = targetY;
                    isAnimating = false;
                } else {
                    // Move towards target
                    this->x += (dx / dist) * animSpeed;
                    this->y += (dy / dist) * animSpeed;
                }
            }
        }

        bool isMoving() const {
            return isAnimating;
        }
        void setCoordsAnimated(int X, int Y) {
            targetX = X;
            targetY = Y;
            isAnimating = true;
        }
        void triggerShootEffect() {
            shootEffectTimer = 10.0f; // Start 10-frame animation
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
            triggerShootEffect();
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
            triggerShootEffect();
            bullet* curr1 = new BananaBullet(1);
            curr1->setCoords(this->get_coords().x, this->get_coords().y);
            bullet* curr2 = new BananaBullet(-1);
            curr2->setCoords(this->get_coords().x, this->get_coords().y);
            arr.push_back(curr1);arr.push_back(curr2);
        }
};

