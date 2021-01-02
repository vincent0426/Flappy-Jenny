#include "Star.hpp"


namespace APlusPlus{
    Star::Star(GameDataRef data): _data(data){
        _landHeight = this->_data->assets.GetTexture("Land").getSize().y;
        _starSpawnYOffset = 10;
    }
    
    void Star::SpawnStar()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Star"));
        sprite.setPosition(this->_data->window.getSize().x, _starSpawnYOffset);
        starSprites.push_back(sprite);
    }

    void Star::MoveStar(float dt)
    {
        for(int i = 0; i < starSprites.size(); i++)
        {
            if(starSprites.at(i).getPosition().x < 0 - starSprites.at(i).getLocalBounds().width)
            {
                starSprites.erase(starSprites.begin() + i);
            }
            else{
                movement = Star::UpdateSpeed(_nowScore) * dt;
                starSprites.at(i).move(-movement,0);
            }
        }
    }

    void Star::DrawStar(){
        for(unsigned short int i = 0; i < starSprites.size(); i++)
        {
            this->_data->window.draw(starSprites.at(i));
        }
        
    }

    void Star::RandomiseStarOffset(){
        _starSpawnYOffset = rand() % _data->window.Window::getSize().y;
    }

    const std::vector<sf::Sprite>& Star::GetSprites() const
    {
        return starSprites;
    }

    void Star::starErase(int i){
        starSprites.erase(starSprites.begin()+i);
    }


    int Star::UpdateSpeed(int _nowScore) const
    {
        float PIPEMOVEMENT = PIPE_MOVEMENT_SPEED;
        if( FIRST_THRESHOLD <= _nowScore && _nowScore < SECOND_THRESHOLD )
        {
            PIPEMOVEMENT += 100;
        }
        else if(SECOND_THRESHOLD <= _nowScore && _nowScore < THIRD_THRESHOLD )
        {
            PIPEMOVEMENT += 200;
        }
        else if(THIRD_THRESHOLD <= _nowScore )
        {
            PIPEMOVEMENT += 300;
        }
        return PIPEMOVEMENT;
    }
    
    void Star::UpdateScore(int score) {
        _nowScore = score;
    }
        
}
