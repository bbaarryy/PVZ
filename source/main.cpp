#include <iostream>
#include "field.hpp"
#include "plants.hpp"
#include <chrono>
#include <ctime>
#include <thread>

void show(std::vector<plants*>& v, sf::RenderWindow& win){
    for(int j = 0 ; j < v.size();j++){
        (*v[j]).Draw(win);
    }
}
void move(std::vector<plants*>& v, sf::RenderWindow& win){
    for(int j = 0 ; j < v.size();j++){
        float curr_y = (*v[j]).get_coords().y;
        if (curr_y !=0) (*v[j]).Move(0,-1);
    }
}

int main(){
    unsigned int XXX,YYY;
    XXX=700;YYY=600;
    
    sf::RenderWindow window(sf::VideoMode({XXX, YYY}), "PVZ");
    main_field FIELD(8,8,sf::Color(250,250,250),sf::Color(0,0,0));

    tomato* tom_p = new tomato(0.13,5,YYY);
    
    window.display();

    ///
    std::vector<plants*> my_plants;
    my_plants.push_back(tom_p);
    ///

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        FIELD.draw(window);
        show(my_plants, window);
        move(my_plants,window);

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pause for 50 milliseconds
    }

}