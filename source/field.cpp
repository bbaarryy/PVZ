#include "field.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#define ld float

void main_field::draw(sf::RenderWindow& Win){
    int curr_x = Win.getSize().x;
    int curr_y = Win.getSize().y;

    sf::RectangleShape field_square;
    field_square.setSize({(ld)curr_x/(ld)(this->nx), (ld)curr_y/(ld)(this->ny)});
    field_square.setPosition(0,0);
    
    bool ch = 0;
    for(int j = 0 ; j < (this->ny);j++){
        for(int i = 0 ; i < (this->nx) ; i ++){
            Win.draw(field_square);
            if(ch){field_square.setFillColor(this->major_c);}
            else{field_square.setFillColor(this->minor_c);}
            ch = !ch;
            field_square.move(field_square.getSize().x,0);
        }
        field_square.setPosition(0,field_square.getSize().y * (j+1));
    }
}