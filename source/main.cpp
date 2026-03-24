#include <iostream>
#include "field.hpp"
#include <chrono>
#include <ctime>
#include <thread>

int main(){
    unsigned int XXX,YYY;
    XXX=600;YYY=600;
    
    sf::RenderWindow window(sf::VideoMode({600, 600}), "PVZ");
    main_field FIELD(8,8,sf::Color(250,250,250),sf::Color(0,0,0));

    window.display();
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        FIELD.draw(window);

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Pause for 50 milliseconds
    }

}