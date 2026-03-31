#include <iostream>
#include "field.hpp"
#include "plants.hpp"
#include <chrono>
#include <ctime>
#include <thread>
#include "my_vector.hpp"
#include <random>
#include <chrono>
#include <ctime>
#include <thread>

std::mt19937 rnd2(std::chrono::steady_clock::now().time_since_epoch().count());

int main(){
    unsigned int XXX,YYY;
    XXX=700;YYY=600;
    
    sf::RenderWindow window(sf::VideoMode({XXX, YYY}), "PVZ");
    main_field FIELD(8,8,sf::Color(250,250,250),sf::Color(0,0,0));

    tomato* tom_p = new tomato(0.13,5,YYY);
    
    window.display();


    ///
    myvector<plants*> my_plants;
    my_plants.push_back(tom_p);
    ///

    int q=0;
    int expect=rnd2()%200 + 100;

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        FIELD.draw(window);
        my_plants.show(window);
        my_plants.move(window);

        ///touch technics
        
        


        ///

        q++;
        if(q==expect){
            expect=rnd2()%200 + 100;
            q=0;
            my_plants.spawn(YYY,rnd2()%2+1);
        }

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pause for 50 milliseconds
    }

}