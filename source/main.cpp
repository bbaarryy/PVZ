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
int killed_normal_zombies = 0;

template <typename T>
void clean_containers(T& a){
    for(auto it : a){
        delete it;
    }
    a.clear();
}

void upd_except(int& curr,int speed){
    curr = rnd2()%(200/speed) + (300/speed);
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

    sf::RectangleShape scoreBoard;
    scoreBoard.setSize({180, 40});
    scoreBoard.setFillColor(sf::Color(255, 0, 0, 255));  // ЯРКО-КРАСНЫЙ, НЕПРОЗРАЧНЫЙ
    scoreBoard.setPosition(10, 10);
    scoreBoard.setOutlineThickness(2);
    scoreBoard.setOutlineColor(sf::Color::White);

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: 1000");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(15, 12);
        
    main_field FIELD(8,8,sf::Color(250,250,250),sf::Color(0,0,0));
    //это мигание экрана красным 
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
    int expect=rnd2()%(200/speed) + (300/speed); // plant generation
    upd_except(expect,speed);

    int q_bull=0;
    int expect_bull=rnd2()%(50/speed) + (30/speed);// bullet generation

    sf::Mouse MyMouse;

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
        FIELD.display_score(window,score);
        conv_plants.show(window);
        field_plants.show(window);

        if(score < 0){
            break;
        }

        conv_plants.move(window,move_step);
        
        //window.draw(scoreBoard);
        scoreText.setString("Score: " + std::to_string(score));
        //window.draw(scoreText);
        //update animations for field plants
        for(int i = 0; i < field_plants.size(); i++){
            field_plants[i]->updateAnimation(); // speed of the жмыхи
        }

        //seed plants on field
        if (event.type == sf::Event::MouseButtonPressed){
            auto MouseX = MyMouse.getPosition(window).x;
            auto MouseY = MyMouse.getPosition(window).y;

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
                    if(field_used.at(MouseX / SQ_X).at(MouseY / SQ_Y) == 0 && (MouseY / SQ_Y != 0)){
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
            upd_except(expect,speed);
            q=0;
            
            conv_plants.spawn(YYY,rnd2()%4+1);
            
            // PureZombie* z_p = new PureZombie;
            // (*z_p).setCoords(XXX, rnd2()%NY * SQ_Y);
            // zombies_l.push_back(z_p);
            // Логика спавна: сначала 4 обычных зомби, потом рандом
            zombie* new_zombie;

            
            // После 2 убитых - рандом сильных
            if(killed_normal_zombies == 2){
                killed_normal_zombies = 0;
                auto rr = rnd2() % 3;
                if(rr == 0) {
                    new_zombie = new StrongZombie;
                } else if(rr == 1){
                    new_zombie = new ArmZombie;
                }
                else{
                    new_zombie = new FastZombie;
                }
            }
            else{
                new_zombie = new PureZombie;
            }
            

            new_zombie->setCoords(XXX, (rnd2() % (NY-1) + 1) * SQ_Y );
            zombies_l.push_back(new_zombie);
        }

        //generate---bullets
        q_bull++;
        if(q_bull == expect_bull){
            q_bull=0;
            expect_bull=rnd2()%(50/speed) + (30/speed);
            for(int i = 0 ; i < field_plants.size();i++){
                if(rnd2()%7 == 0){
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

        //burstes
        auto itb = burst_l.begin();
        while(itb!=burst_l.end()){
        (*itb)->Draw(window);
            (*itb)->lifetime-=10;

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
                if(((*it_z)->boundingBox).intersects(it->boundingBox) && (*it_z)->get_coords().x < XXX - SQ_X){
                    it->visiable = 0;
                    (*it_z)->takeDamage(1);

                    burst* bb = new burst();
                    auto curr_x = (it->boundingBox).left;
                    auto curr_y = (it->boundingBox).top;
                    
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
                    //std::cout << (*it_z)->damage << '\n';
                    //std::cout << (*it_p)->get_health() << '\n';
                    if(is_killed){
                        std::cout << "KILLED!" << '\n';
                        std::cout << (*(*it_z)).damage << '\n';
                        //std::cout << int((*it_p)->get_coords().x / SQ_X) << ' ' << int((*it_p)->get_coords().y / SQ_Y) << '\n';
                        field_used[(*it_p)->get_coords().x / SQ_X][(*it_p)->get_coords().y / SQ_Y] = 0;
                        delete *it_p;it_p = field_plants.erase(it_p);
                    }
                    else{it_p++;}
                    break;
                    //
                }
                else{it_p++;}
            }
            
            if(is_move)(*it_z)->Move(speed);
             
            if((*it_z)->get_coords().x < SQ_X){
                delete *it_z;it_z = zombies_l.erase(it_z);
                
                score-=1000;
                is_velvet=1;
                continue;
            } 

            // Проверка, умер ли зомби
            if((*it_z)->isDead()){
                invaded_zombies++;

                if((*it_z)->isNormal()) {
                    killed_normal_zombies++;
                }
                score += (*it_z)->getScore();
                delete *it_z;
                it_z = zombies_l.erase(it_z);
            } 
            else {
                ++it_z;
            }
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

    red_velvet.setFillColor({255,0,0,127});

    while(window.isOpen()){
        window.clear();
        FIELD.draw(window);
        FIELD.display_score(window,score);
        conv_plants.show(window);
        field_plants.show(window);

        window.draw(red_velvet);

        FIELD.draw_def(window,invaded_zombies);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter)){
            std::cout << "NOO" << '\n';
            break;
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