#include "field.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#define ld float

void main_field::draw(sf::RenderWindow& Win){
    float curr_x = Win.getSize().x;
    float curr_y = Win.getSize().y;

    float stripe_w = (float)curr_x /(ld)(this->nx+1);
    float score_h = (float)curr_y /(ld)(this->ny);

    sf::RectangleShape field_square;
    field_square.setSize({(ld)(curr_x)/(ld)(this->nx+1), (ld)curr_y/(ld)(this->ny)});
    field_square.setPosition(0,0);
    
    bool ch = 0;
    bool str_ch = 0;

    for(int j = 0 ; j < (this->ny);j++){
        ch = str_ch;
        str_ch = !str_ch;
        field_square.setPosition(stripe_w,field_square.getSize().y * (j) + score_h);

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

    sf::RectangleShape score_rect;
    score_rect.setSize({curr_x, score_h });
    score_rect.setPosition(stripe_w,0);
    score_rect.setFillColor(sf::Color(50,50,50));
    score_rect.setOutlineThickness(3.0);

    Win.draw(score_rect);
    Win.draw(stripe_rect);
}

void main_field::display_score(sf::RenderWindow& Win, int score){

    float curr_x = Win.getSize().x;
    float curr_y = Win.getSize().y;

    float stripe_w = (float)curr_x /(ld)(this->nx+1);

    sf::Font font;
    font.loadFromFile("../eufm10.ttf");
    std::string string_score = "Score: ";

    sf::Text text(string_score + std::to_string(score), font, 50); 
    
    text.setPosition((curr_x - text.getGlobalBounds().width)/2,0);


    Win.draw(text);
}

void main_field::draw_def(sf::RenderWindow& Win, int def){

    float curr_x = Win.getSize().x;
    float curr_y = Win.getSize().y;

    float stripe_w = (float)curr_x /(ld)(this->nx+1);

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/lyx/eufm10.ttf");

    sf::Text text("Game Over", font, 100); 
    
    text.setPosition((curr_x-text.getGlobalBounds().width)/2,curr_y/3);

    sf::Text text2("You've killed " + std::to_string(def) + " zombies", font, 60); 
    text2.setPosition((curr_x-text2.getGlobalBounds().width)/2,curr_y/3 + text.getGlobalBounds().height +5 );

    sf::Text text3("Predd enter", font, 30); 
    text3.setPosition((curr_x-text3.getGlobalBounds().width)/2,curr_y/3 + text.getGlobalBounds().height + text2.getGlobalBounds().height +5);
    Win.draw(text);
    Win.draw(text2);
    Win.draw(text3);
}