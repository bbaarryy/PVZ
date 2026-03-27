#include "field.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#define ld float

void main_field::draw(sf::RenderWindow& Win){
    float curr_x = Win.getSize().x;
    float curr_y = Win.getSize().y;

    float stripe_w = (float)curr_x /(ld)(this->nx+1);

    sf::RectangleShape field_square;
    field_square.setSize({(ld)(curr_x)/(ld)(this->nx+1), (ld)curr_y/(ld)(this->ny)});
    field_square.setPosition(0,0);
    
    bool ch = 0;
    bool str_ch = 0;

    for(int j = 0 ; j < (this->ny);j++){
        ch = str_ch;
        str_ch = !str_ch;
        field_square.setPosition(stripe_w,field_square.getSize().y * (j));

        for(int i = 0 ; i < (this->nx) ; i ++){
            if(ch){field_square.setFillColor(this->major_c);}
            else{field_square.setFillColor(this->minor_c);}
            Win.draw(field_square);

            ch = !ch;
            field_square.move(field_square.getSize().x,0);
        }
    }

    sf::RectangleShape stripe_rect;
    stripe_rect.setSize({stripe_w, curr_y});
    stripe_rect.setPosition(0,0);
    stripe_rect.setFillColor(sf::Color(50,50,50));
    stripe_rect.setOutlineThickness(3.0);  
    Win.draw(stripe_rect);
}