#pragma once

#include <SFML/Graphics.hpp>

#include "CONST_VARIABLE.h"
#include "Game.hpp"

#include <vector>

namespace APlusPlus
{
    class Turtle
    {
    public:
        Turtle(GameDataRef data);
        ~Turtle();
        
        void Draw();
        
        void Animate(float dt);
        void Update(float dt);
        void Tap();
        
        const sf::Sprite& GetSprite() const;
        
    private:
        GameDataRef _data;
        
        sf::Sprite _turtleSprite;
        std::vector<sf::Texture> _animationFrames;
        
        unsigned int _animationIterator;
        
        sf::Clock _clock;
        sf::Clock _movementClock;
        
        int _turtleState;
        float _rotation;
        
    };
}
