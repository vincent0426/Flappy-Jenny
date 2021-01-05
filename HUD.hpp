#pragma once

#include <SFML/Graphics.hpp>

#include "CONST_VARIABLE.h"
#include "Game.hpp"

namespace APlusPlus
{
    class HUD
    {
    public:
        HUD(GameDataRef data);
        ~HUD();
        
        void Draw();
        void UpdateScore(int score);
        
    private:
        GameDataRef _data;
        sf::Text _scoreText;
    };
}
