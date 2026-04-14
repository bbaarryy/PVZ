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

int chosen_index = -1;

int main(){
    unsigned int XXX,YYY,NX,NY;
    XXX=700;YYY=600;NX=8;NY=8;
    int SQ_X = XXX/(NX+1);
    int SQ_Y = YYY/NY;
    
    sf::RenderWindow window(sf::VideoMode({XXX, YYY}), "PVZ");
    main_field FIELD(8,8,sf::Color(250,250,250),sf::Color(0,0,0));

    tomato* tom_p = new tomato(0.13,5,YYY);
    window.display();

    ///
    myvector<plants*> conv_plants;
    conv_plants.push_back(tom_p);
    ///
    myvector<plants*> field_plants;
    ///

    int q=0;
    int expect=rnd2()%200 + 100;

    sf::Mouse MyMouse;

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        FIELD.draw(window);
        conv_plants.show(window);
        field_plants.show(window);
        conv_plants.move(window);




        ///////
        sf::CircleShape circle;
        circle.setRadius(15);
        circle.setOutlineColor(sf::Color::Red);
        circle.setOutlineThickness(5);
        circle.setPosition({10, 20});
        ///touch technics



        if (event.type == sf::Event::MouseButtonPressed){
            std::cout << MyMouse.getPosition().x << ' ' << MyMouse.getPosition().y << '\n';

            int MouseX = MyMouse.getPosition().x;
            int MouseY = MyMouse.getPosition().y;

            circle.setPosition({MouseX, MouseY});
            window.draw(circle);

            if(MouseX <= 120){
                for(int i = 0 ; i < conv_plants.size();i++){
                    if( ((conv_plants[i]->get_coords().y) < MouseY) && (MouseY < (conv_plants[i]->get_coords().y)+(conv_plants[i]->PlantGetSize().y))){
                        std::cout << (conv_plants[i]->get_coords().y)-(conv_plants[i]->PlantGetSize().y/2) << " : " << (conv_plants[i]->get_coords().y)+(conv_plants[i]->PlantGetSize().y/2) << '\n';
                        conv_plants[i]->Select();
                        chosen_index = i;
                    }
                }
            }
            else{
                if(chosen_index != -1){
                    plants* curr = conv_plants[chosen_index];
                    curr->setCoords((MouseX / SQ_X ) * SQ_X, (MouseY / SQ_Y)  * SQ_Y);
                    field_plants.push_back(conv_plants[chosen_index]);
                    conv_plants.erase(conv_plants.begin() + chosen_index);
                    chosen_index = -1;
                }
            }
        }

        ///

        q++;
        if(q==expect){
            expect=rnd2()%200 + 100;
            q=0;
            conv_plants.spawn(YYY,rnd2()%2+1);
        }

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pause for 50 milliseconds
    }

}