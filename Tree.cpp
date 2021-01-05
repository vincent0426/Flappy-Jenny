
#include "Tree.hpp"

namespace APlusPlus
{
    Tree::Tree(GameDataRef data) : _data(data)
    {
        _landHeight = this->_data->assets.GetTexture("Land").getSize().y;
        _treeSpawnYOffset = 0;
    }
    
    void Tree::SpawnBottomTree()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Tree Up"));
        sprite.setPosition(this->_data->window.getSize().x, this->_data->window.getSize().y - sprite.getLocalBounds().height - _treeSpawnYOffset);
        treeSprites.push_back(sprite);
    }
    
    void Tree::SpawnTopTree()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Tree Down"));
        sprite.setPosition(this->_data->window.getSize().x, -_treeSpawnYOffset);
        treeSprites.push_back(sprite);
    }
    
    void Tree::SpawnInvisibleTree()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Tree Down"));
        sprite.setPosition(this->_data->window.getSize().x, -_treeSpawnYOffset);
        sprite.setColor(sf::Color(0, 0, 0, 0));
        
        treeSprites.push_back(sprite);
    }
    
    void Tree::SpawnScoringTree()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Scoring Tree"));
        sprite.setPosition(this->_data->window.getSize().x, 0);
        scoringTrees.push_back(sprite);
    }

    void Tree::MoveTrees(float dt)
    {
        for(int i = 0; i < treeSprites.size(); i++)
        {
            if(treeSprites.at(i).getPosition().x < 0 - treeSprites.at(i).getLocalBounds().width)
            {
                treeSprites.erase(treeSprites.begin() + i);
            }
            else
            {
                movement = Tree::UpdateSpeed(_nowScore) * dt;
                if(_nowScore >= 20)
                {
                    if(i%2==0)
                    {
                        treeSprites.at(i).move(-movement, 2);
                    }
                    else
                    {
                        treeSprites.at(i).move(-movement, -2);
                    }
                }
                else
                {
                    treeSprites.at(i).move(-movement, 0);
                }
            }

        }
//         moving the scoring pipes
        for(int i = 0; i < scoringTrees.size(); i++)
        {
            if(scoringTrees.at(i).getPosition().x < 0 - scoringTrees.at(i).getLocalBounds().width)
            {
                scoringTrees.erase(scoringTrees.begin() + i);
            }
            else
            {
                movement = Tree::UpdateSpeed(_nowScore) * dt;
                if(_nowScore >= 20)
                {
                    if(i%2==0)
                    {
                        scoringTrees.at(i).move(-movement, 2);
                    }
                    else
                    {
                        scoringTrees.at(i).move(-movement, -2);
                    }
                }
                else
                {
                    scoringTrees.at(i).move(-movement, 0);
                }
            }
        }
    }
    
    void Tree::DrawTrees()
    {
        for(unsigned short int i = 0; i < treeSprites.size(); i++)
        {
            this->_data->window.draw(treeSprites.at(i));
        }
    }
    
    void Tree::RandomiseTreeOffset()
    {
        _treeSpawnYOffset = rand() % _landHeight;
    }
    
    const std::vector<sf::Sprite>& Tree::GetSprites() const
    {
        return treeSprites;
    }
    
    std::vector<sf::Sprite>& Tree::GetScoringSprites()
    {
        return scoringTrees;
    }
    void Tree::UpdateScore(int score)
    {
        _nowScore = score;
    }

    int Tree::UpdateSpeed(int _nowScore) const
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
        else if(THIRD_THRESHOLD <= _nowScore && _nowScore < FORTH_THRESHOLD )
        {
            PIPEMOVEMENT += 300;
        }
        else if(FORTH_THRESHOLD <= _nowScore && _nowScore < FIFTH_THRESHOLD )
        {
            PIPEMOVEMENT += 500;
        }
        else if(FIFTH_THRESHOLD <= _nowScore && _nowScore < SIXTH_THRESHOLD )
        {
            PIPEMOVEMENT += 700;
        }
        else if(SIXTH_THRESHOLD <= _nowScore )
        {
            PIPEMOVEMENT += 900;
        }
        return PIPEMOVEMENT;
    }
}
