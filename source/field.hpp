#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using sf::Color;

class main_field{
    private:
        int nx,ny;//count of 
        Color major_c,minor_c;

    public:

        main_field(int NX, int NY, Color major, Color minor): nx(NX), ny(NY), major_c(major), minor_c(minor) {};
        void draw(sf::RenderWindow& window);
};