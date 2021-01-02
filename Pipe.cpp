#include "Pipe.hpp"
#include <iostream>

namespace APlusPlus
{
    Pipe::Pipe(GameDataRef data) : _data(data)
    {
        _landHeight = this->_data->assets.GetTexture("Land").getSize().y;
        _pipeSpawnYOffset = 0;
    }
    
    void Pipe::SpawnBottomPipe()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Up"));
        sprite.setPosition(this->_data->window.getSize().x, this->_data->window.getSize().y - sprite.getLocalBounds().height - _pipeSpawnYOffset);
        pipeSprites.push_back(sprite);
    }
    
    void Pipe::SpawnTopPipe()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Down"));
        sprite.setPosition(this->_data->window.getSize().x, -_pipeSpawnYOffset);
        pipeSprites.push_back(sprite);
    }
    
    void Pipe::SpawnInvisiblePipe()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Down"));
        sprite.setPosition(this->_data->window.getSize().x, -_pipeSpawnYOffset);
        sprite.setColor(sf::Color(0, 0, 0, 0));
        
        pipeSprites.push_back(sprite);
    }
    
    void Pipe::SpawnScoringPipe()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Scoring Pipe"));
        sprite.setPosition(this->_data->window.getSize().x, 0);
        scoringPipes.push_back(sprite);
    }

    void Pipe::MovePipes(float dt)
    {
        for(int i = 0; i < pipeSprites.size(); i++)
        {
            if(pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getLocalBounds().width)
            {
                pipeSprites.erase(pipeSprites.begin() + i);
            }
            else
            {
                movement = Pipe::UpdateSpeed(_nowScore) * dt;
                if(_nowScore >= 20)
                {
                    if(i%2==0)
                    {
                        pipeSprites.at(i).move(-movement, 2);
                    }
                    else
                    {
                        pipeSprites.at(i).move(-movement, -2);
                    }
                }
                else
                {
                    pipeSprites.at(i).move(-movement, 0);
                }
            }

        }
//         moving the scoring pipes
        for(int i = 0; i < scoringPipes.size(); i++)
        {
            if(scoringPipes.at(i).getPosition().x < 0 - scoringPipes.at(i).getLocalBounds().width)
            {
                scoringPipes.erase(scoringPipes.begin() + i);
            }
            else
            {
                movement = Pipe::UpdateSpeed(_nowScore) * dt;
                if(_nowScore >= 20)
                {
                    if(i%2==0)
                    {
                        scoringPipes.at(i).move(-movement, 2);
                    }
                    else
                    {
                        scoringPipes.at(i).move(-movement, -2);
                    }
                }
                else
                {
                    scoringPipes.at(i).move(-movement, 0);
                }
            }
        }
    }
    
    void Pipe::DrawPipes()
    {
        for(unsigned short int i = 0; i < pipeSprites.size(); i++)
        {
            this->_data->window.draw(pipeSprites.at(i));
        }
    }
    
    void Pipe::RandomisePipeOffset()
    {
        _pipeSpawnYOffset = rand() % _landHeight;
    }
    
    const std::vector<sf::Sprite>& Pipe::GetSprites() const
    {
        return pipeSprites;
    }
    
    std::vector<sf::Sprite>& Pipe::GetScoringSprites()
    {
        return scoringPipes;
    }
    void Pipe::UpdateScore(int score)
    {
        _nowScore = score;
    }

    int Pipe::UpdateSpeed(int _nowScore) const
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
}
