#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include "CONST_VARIABLE.h"


namespace APlusPlus {
    class Ball{
    public:
        Ball(GameDataRef data);
        
        void SpawnBall();
        void MoveBall(float dt);
        void DrawBall();
        void RandomiseBallOffset();
        void ballErase(int i);
        int UpdateSpeed(int score) const;
        void UpdateScore(int score) ;
        const std::vector<sf::Sprite>& GetSprites() const;
        
    private:
        GameDataRef _data;
        std::vector<sf::Sprite> ballSprites;
        int _ballSpawnYOffset;
        float movement;
        int _landHeight;
        int MoveSpeed;
        int _nowScore;
    };
}
