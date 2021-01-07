#include "Turtle.hpp"
#include "GameState.hpp"

namespace APlusPlus
{
    Turtle::Turtle(GameDataRef data) : _data(data)
    {
        _animationIterator = 0;
        
        _animationFrames.push_back(this->_data->assets.GetTexture("Turtle Frame 1"));

        _turtleSprite.setTexture(_animationFrames.at(_animationIterator));
        
        _turtleSprite.setPosition((_data->window.getSize().x / 4) - (_turtleSprite.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_turtleSprite.getGlobalBounds().height / 2));
        
        _turtleState = TURTLE_STATE_STILL;
        
        sf::Vector2f origin = sf::Vector2f(_turtleSprite.getGlobalBounds().width / 2, _turtleSprite.getGlobalBounds().height / 2);
        _turtleSprite.setOrigin(origin);
        _rotation = 0;
    }
    
    Turtle::~Turtle() {}
    
    void Turtle::Draw()
    {
        _data->window.draw(_turtleSprite);
    }
    
    void Turtle::Update(float dt)
    {
        if(_turtleState == TURTLE_STATE_FALLING)
        {
            _turtleSprite.move(0, GRAVITY * dt);

            _rotation = 0;
        }
        else if(_turtleState == TURTLE_STATE_FLYING)
        {
            _turtleSprite.move(0, -FLYING_SPEED * dt);
            
            _rotation = 0;
        }
        
        if(_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
        {
            _turtleState = TURTLE_STATE_FALLING;
            _movementClock.restart();
        }
        _turtleSprite.setRotation(_rotation);
    }
    
    void Turtle::Tap()
    {
        _turtleState = TURTLE_STATE_FLYING;

        _movementClock.restart();
    }
    
    const sf::Sprite& Turtle::GetSprite() const
    {
        return _turtleSprite;
    }
}
