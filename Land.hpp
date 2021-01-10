#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace APlusPlus
{
    class Land
    {
    public:
        Land(GameDataRef data);
        
        void DrawLand();
        const std::vector<sf::Sprite>& GetSprites() const;
        
    private:
        GameDataRef _data;
        std::vector<sf::Sprite> _landSprites;
    };
}
