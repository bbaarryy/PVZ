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
#include <string>

std::mt19937 rnd2(std::chrono::steady_clock::now().time_since_epoch().count());

int chosen_index = -1;

int main(int args, char** argv){
    int speed;
    speed = std::stoi(argv[1]);
    int move_step = speed;


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
    myvector<plants*> field_plants;
    ///

    ///
    vector<vector<bool>> field_used(NX,vector<bool> (NY,0));
    int last_chosen = 0;
    ///

    int q=0;
    int expect=rnd2()%(200/speed) + (100/speed);

    sf::Mouse MyMouse;
    sf::CircleShape check_circle;
    check_circle.setRadius(15);
    check_circle.setOutlineColor(sf::Color::Red);
    check_circle.setOutlineThickness(5);
    check_circle.setPosition({10, 20});

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
        conv_plants.move(window,move_step);

        if (event.type == sf::Event::MouseButtonPressed){
            int MouseX = (int)MyMouse.getPosition(window).x;
            int MouseY = (int)MyMouse.getPosition(window).y;

            check_circle.setPosition({MouseX, MouseY});
            window.draw(check_circle);
            conv_plants[last_chosen]->UnSelect();
            if(MouseX <= SQ_X){
                for(int i = 0 ; i < conv_plants.size();i++){
                    if( ((conv_plants[i]->get_coords().y) < MouseY) && (MouseY < (conv_plants[i]->get_coords().y)+(conv_plants[i]->PlantGetSize().y))){
                        
                        conv_plants[i]->Select();
                        last_chosen = i;
                        chosen_index = i;
                    }
                }
            }
            else{
                if(chosen_index != -1){
                    plants* curr = conv_plants[chosen_index];
                    if(field_used[MouseX / SQ_X][MouseY / SQ_Y] == 0){
                        field_used[MouseX / SQ_X][MouseY / SQ_Y] = 1;
                        curr->setCoords((MouseX / SQ_X ) * SQ_X + 10, (MouseY / SQ_Y)  * SQ_Y);
                        field_plants.push_back(conv_plants[chosen_index]);
                        conv_plants.erase(conv_plants.begin() + chosen_index);
                    }
                    curr->UnSelect();
                    chosen_index = -1;
                }
            }
        }



        ///generate---spawn
        q++;
        if(q==expect){
            expect=rnd2()%(200/speed) + (100/speed);
            q=0;
            conv_plants.spawn(YYY,rnd2()%2+1);
        }

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pause for 50 milliseconds
    }

}