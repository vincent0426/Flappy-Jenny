#include "Turtle.hpp"
#include "GameState.hpp"

namespace APlusPlus
{
    Turtle::Turtle(GameDataRef data) : _data(data)
    {
        _animationIterator = 0;
        
        _animationFrames.push_back(this->_data->assets.GetTexture("Turtle Frame 1"));
        _animationFrames.push_back(this->_data->assets.GetTexture("Turtle Frame 1"));
        _animationFrames.push_back(this->_data->assets.GetTexture("Turtle Frame 1"));
        _animationFrames.push_back(this->_data->assets.GetTexture("Turtle Frame 1"));
        
        _turtleSprite.setTexture(_animationFrames.at(_animationIterator));
        
        _turtleSprite.setPosition((_data->window.getSize().x / 4) - (_turtleSprite.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_turtleSprite.getGlobalBounds().height / 2));
        
        _turtleState = BIRD_STATE_STILL;
        
        sf::Vector2f origin = sf::Vector2f(_turtleSprite.getGlobalBounds().width / 2, _turtleSprite.getGlobalBounds().height / 2);
        _turtleSprite.setOrigin(origin);
        _rotation = 0;
    }
    
    Turtle::~Turtle() {}
    
    void Turtle::Draw()
    {
        _data->window.draw(_turtleSprite);
    }
    
    void Turtle::Animate(float dt)
    {
        if(_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size())
        {
            if(_animationIterator < _animationFrames.size() - 1)
            {
                _animationIterator++;
            }
            else
            {
                _animationIterator = 0;
            }
            
            _turtleSprite.setTexture(_animationFrames.at(_animationIterator));
            
            this->_clock.restart();
        }
    }
    
    void Turtle::Update(float dt)
    {
        if(_turtleState == BIRD_STATE_FALLING)
        {
            _turtleSprite.move(0, GRAVITY * dt);
            
            
            if(_rotation > 25.0f) _rotation = 25.0f;
            _rotation = 0;
        }
        else if(_turtleState == BIRD_STATE_FLYING)
        {
            _turtleSprite.move(0, -FLYING_SPEED * dt);
            
            _rotation = -25.0f;
            _rotation = 0;
        }
        
        if(_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
        {
            _turtleState = BIRD_STATE_FALLING;
            _movementClock.restart();
        }
        _turtleSprite.setRotation(_rotation);
    }
    
    void Turtle::Tap()
    {
        _turtleState = BIRD_STATE_FLYING;

        _movementClock.restart();
    }
    
    const sf::Sprite& Turtle::GetSprite() const
    {
        return _turtleSprite;
    }
}
