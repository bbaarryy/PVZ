#include <iostream>
#include "field.hpp"
#include <chrono>
#include <ctime>
#include <thread>

int main(){
    unsigned int XXX,YYY;
    XXX=600;YYY=600;

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode({XXX, YYY}), "PVZ");

    main_field FIELD(5,5,sf::Color(250,250,250),sf::Color(0,0,0));

    while (window.isOpen()){ 
        FIELD.draw(window);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pause for 50 milliseconds
    }
}