#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include "CONST_VARIABLE.h"

namespace APlusPlus
{
    class Star{
    public:
        Star(GameDataRef data);
        
        void SpawnStar();
        void MoveStar(float dt);
        void DrawStar();
        void RandomiseStarOffset();
        void starErase(int i);
        int UpdateSpeed(int score) const;
        void UpdateScore(int score) ;
        const std::vector<sf::Sprite>& GetSprites() const;
        
    private:
        GameDataRef _data;
        std::vector<sf::Sprite> starSprites;
        int _starSpawnYOffset;
        float movement;
        int _landHeight;
        int MoveSpeed;
        int _nowScore;
    };
}
