#include "moving_obj.hpp"

class burst: public Move_Obj{
    public:
        int lifetime;

        burst() {
            lifetime = 100;
            herotexture.loadFromFile("../images/explosion.png");
            setup_pic();
        }
        void setCoords(int X,int Y) override{
            this->y = Y;
            this->x = X;
        }
        void Move(int speed) override {
            shsprite.setTexture(herotexture);
            //shsprite.setScale({0.13 - 0.13 * lifetime / 100, 0.13 - 0.13 * lifetime / 100});
        }

};

