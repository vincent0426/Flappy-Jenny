#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace APlusPlus
{
    class Flash
    {
    public:
        Flash(GameDataRef data);
        ~Flash();
        
        void Show(float dt);
        void Draw();
        
    private:
        GameDataRef _data;
        sf::RectangleShape _shape;
        
        bool _flashOn;
    };
}
