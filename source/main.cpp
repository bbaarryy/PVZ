#include <iostream>
#include "field.hpp"
#include "plants.hpp"
#include "bullet.hpp"
#include "plant_vector.hpp"
#include "zombie.hpp"
#include "burst.hpp"

#include <chrono>
#include <ctime>
#include <thread>
#include <random>
#include <string>
#include <list>

int chosen_index = -1;

template <typename T>
void clean_containers(T& a){
    for(auto it : a){
        delete it;
    }
    a.clear();
}

int main(int args, char** argv){
    int speed;
    speed = std::stoi(argv[1]);
    int move_step = speed;

    unsigned int XXX, YYY;
    int NX,NY;
    XXX=700;YYY=600;NX=8;NY=8;
    int SQ_X = XXX/(NX+1);
    int SQ_Y = YYY/NY;
    
    sf::RenderWindow window(sf::VideoMode({XXX, YYY}), "PVZ");
    main_field FIELD(8,8,sf::Color(250,250,250),sf::Color(0,0,0));
    sf::RectangleShape red_velvet;
    red_velvet.setPosition({0,0});
    red_velvet.setSize({float(XXX), float(YYY)});
    sf::Color velvet_color = {255,0,0,100};
    red_velvet.setFillColor(velvet_color);
    sf::Uint8 velvet_transparent = 100;
    bool is_velvet = 0;

    tomato* tom_p = new tomato(0.13,5,YYY);
    window.display();

    ///
    plant_vector<plants*> conv_plants;
    conv_plants.push_back(tom_p);
    plant_vector<plants*> field_plants;
    ///
    
    ///
    std::list<bullet*> bullets;
    ///

    ///
    std::list<zombie*> zombies_l;
    int invaded_zombies = 0;
    int score = 1000;
    ///

    ///
    std::vector<vector<bool>> field_used(NX+1,vector<bool> (NY,0));
    int last_chosen = 0;
    ///
    
    ///
    std::list<burst*> burst_l;
    ///

    int q=0;
    int expect=rnd2()%(200/speed) + (100/speed);

    int q_bull=0;
    int expect_bull=rnd2()%(50/speed) + (30/speed);

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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)){
            std::cout << "NOO" << '\n';
            break;
        }

        window.clear();
        FIELD.draw(window);
        conv_plants.show(window);
        field_plants.show(window);
        conv_plants.move(window,move_step);
        
        //update animations for field plants
        for(int i = 0; i < field_plants.size(); i++){
            field_plants[i]->updateAnimation();
        }

        //seed plants on field
        if (event.type == sf::Event::MouseButtonPressed){
            auto MouseX = MyMouse.getPosition(window).x;
            auto MouseY = MyMouse.getPosition(window).y;

            check_circle.setPosition({float(MouseX),float(MouseY)});

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
                    if(field_used.at(MouseX / SQ_X).at(MouseY / SQ_Y) == 0){
                        field_used[MouseX / SQ_X][MouseY / SQ_Y] = 1;
                        curr->setCoordsAnimated((MouseX / SQ_X ) * SQ_X + 10, (MouseY / SQ_Y)  * SQ_Y);
                        
                        //curr->setCoords((MouseX / SQ_X ) * SQ_X + 10, (MouseY / SQ_Y)  * SQ_Y);
                        curr->UnSelect();

                        field_plants.push_back(conv_plants[chosen_index]);
                        conv_plants.erase(conv_plants.begin() + chosen_index);
                    }
                    chosen_index = -1;
                }
            }
        }

        ///generate---spawn
        q++;
        if(q==expect){
            expect=rnd2()%(200/speed) + (100/speed);
            q=0;
            
            conv_plants.spawn(YYY,rnd2()%3+1);
            
            PureZombie* z_p = new PureZombie;
            (*z_p).setCoords(XXX, rnd2()%NY * SQ_Y);
            zombies_l.push_back(z_p);
        }

        //generate---bullets
        q_bull++;
        if(q_bull == expect_bull){
            q_bull=0;
            expect_bull=rnd2()%(50/speed) + (30/speed);
            for(int i = 0 ; i < field_plants.size();i++){
                if(rnd2()%5 == 0){
                    field_plants[i]->shoot(bullets);
                }
            }        
        }
    
        //bullets move
        auto it = bullets.begin();
        while(it != bullets.end()){
            (*it)->Move(speed);
            (*it)->Draw(window);

            if( (*it)->get_coords().x > 2*XXX+SQ_X || (*it)->get_coords().x > 2*YYY+SQ_Y || !(*it)->visiable){
                delete (*it);
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }

        auto itb = burst_l.begin();
        while(itb != burst_l.end()){
            (*itb)->Draw(window);
            (*itb)->lifetime -=10;
            //(*itb)->Move(speed);

            if( (*itb)->lifetime <= 0){
                delete (*itb);
                itb = burst_l.erase(itb);
            } else {
                ++itb;
            }
        }

        //zombies move
        auto it_z = zombies_l.begin();

        while(it_z != zombies_l.end()){
            bool is_move = 1;
            (*it_z)->Draw(window);
            

            //if kill
            for(auto it : bullets){
                if(((*it_z)->boundingBox).intersects(it->boundingBox)){
                    it->visiable = 0;
                    (*it_z)->health--;
                    burst* bb = new burst();
                    auto curr_x = (it->boundingBox).left;
                    auto curr_y = (it->boundingBox).top;
                    score += (*it_z)->score;
                    bb->setCoords(curr_x,curr_y);
                    burst_l.push_back(bb);
                }
            }

            //if eat
            auto it_p = field_plants.begin();
            while(it_p!=field_plants.end()){
                if(((*it_z)->boundingBox).intersects((*it_p)->boundingBox)){
                    is_move = 0;

                    //killing this plant
                    bool is_killed = (*it_p)->harm((*(*it_z)));
                    if(is_killed){
                        //std::cout << "KILLED!" << '\n';
                        //std::cout << int((*it_p)->get_coords().x / SQ_X) << ' ' << int((*it_p)->get_coords().y / SQ_Y) << '\n';
                        field_used[(*it_p)->get_coords().x / SQ_X][(*it_p)->get_coords().y / SQ_Y] = 0;
                        delete *it_p;it_p = field_plants.erase(it_p);
                    }
                    else{it_p++;}
                    //
                }
                else{it_p++;}
            }
            
            if(is_move)(*it_z)->Move(speed);
             
            if((*it_z)->get_coords().x < SQ_X){
                delete *it_z;it_z = zombies_l.erase(it_z);
                invaded_zombies++;
                score-=1000;
                is_velvet=1;
            } 

            if((*it_z)->health == 0){delete *it_z;it_z = zombies_l.erase(it_z);}
            else{it_z++;}
        }

        if(is_velvet)
        {
            window.draw(red_velvet);
            red_velvet.setFillColor(velvet_color);
            velvet_transparent -= 5;
            if(velvet_transparent == 0){velvet_transparent=100;is_velvet= 0;}
            velvet_color = {255,0,0,velvet_transparent};
        }

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pause for 50 milliseconds
    }
    window.close();

    clean_containers(conv_plants);
    clean_containers(field_plants);
    clean_containers(zombies_l);
    clean_containers(bullets);
    clean_containers(burst_l);

}