#include "Land.hpp"
#include "CONST_VARIABLE.h"

namespace APlusPlus
{
    Land::Land(GameDataRef data) : _data(data)
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Land"));
        sf::Sprite sprite2(this->_data->assets.GetTexture("Land"));
        
        sprite.setPosition(0, this->_data->window.getSize().y - sprite.getLocalBounds().height);
        sprite2.setPosition(sprite.getLocalBounds().width, this->_data->window.getSize().y - sprite2.getLocalBounds().height);
        
        _landSprites.push_back(sprite);
        _landSprites.push_back(sprite2);
    }
        
    void Land::DrawLand()
    {
        for(unsigned short int i = 0; i < _landSprites.size(); i++)
        {
            this->_data->window.draw(_landSprites.at(i));
        }
    }
    
    const std::vector<sf::Sprite>& Land::GetSprites() const
    {
        return _landSprites;
    }
}
