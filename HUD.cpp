#include "HUD.hpp"
#include <string>

namespace APlusPlus
{
    HUD::HUD(GameDataRef data) : _data(data)
    {
        _scoreText.setFont(this->_data->assets.GetFont("Flappy Font"));
        _scoreText.setString("0");
        _scoreText.setCharacterSize(128);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setOrigin(sf::Vector2f(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2));
        _scoreText.setPosition(sf::Vector2f(_data->window.getSize().x / 2, _data->window.getSize().y / 5));
    }
    
    HUD::~HUD() {}

    void HUD::Draw()
    {
        _data->window.draw(_scoreText);
    }
    
    void HUD::UpdateScore(int score)
    {
        _scoreText.setString(std::to_string(score));
        if(score == FIRST_THRESHOLD ){
            _scoreText.setFillColor(sf::Color(250,235,215));
        }
        else if(score == SECOND_THRESHOLD){
            _scoreText.setFillColor(sf::Color(255,127,80));
        }
        else if(score ==  THIRD_THRESHOLD){
            _scoreText.setFillColor(sf::Color(8,46,84));
        }
        else if(score == FORTH_THRESHOLD){
            _scoreText.setFillColor(sf::Color(189,252,201));
        }
        else if(score ==  FIFTH_THRESHOLD){
            _scoreText.setFillColor(sf::Color(255,215,0));
        }
    }
}
