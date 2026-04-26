#include <vector>
#include "plants.hpp"

using std::vector;

template <typename T>
class myvector : public vector<T> {
public:
    void show(sf::RenderWindow& win){
        for(int j = 0 ; j < (*this).size();j++){
            (*(*this)[j]).Draw(win);
        }
    }

    void move(sf::RenderWindow& win,int d){
        for(int j = 0 ; j < (*this).size();j++){
            float curr_y = (*(*this)[j]).get_coords().y;
            if (j!=0 && curr_y >= (*(*this)[j-1]).get_coords().y + (*(*this)[j]).PlantGetSize().y ) (*(*this)[j]).Move(0,-d);
            if (j==0 && curr_y >= 0) (*(*this)[j]).Move(0,-d);
        }
    }

    void spawn(int YYY,int type){
        plants* tom_p;
        if(type == 1){
            tom_p = new tomato(0.13,5,YYY);
        }
        if(type == 2){
            tom_p = new banana(0.13,5,YYY);
        }
        (*this).push_back(tom_p);
    }
};