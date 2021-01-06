#pragma once

#include "SFML/Graphics.hpp"

namespace APlusPlus
{
    class InputManager
    {
    public:
        InputManager() {}
        ~InputManager() {}
        
        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
        bool IsSpacepressed();
        sf::Vector2i GetMousePosition(sf::RenderWindow& window);
    };
    
}
