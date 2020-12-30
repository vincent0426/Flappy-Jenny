#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include "DEFINITIONS.hpp"

namespace APlusPlus
{
    class Pipe
    {
    public:
        Pipe(GameDataRef data);
        
        void SpawnBottomPipe();
        void SpawnTopPipe();
        void SpawnInvisiblePipe();
        void SpawnScoringPipe();
        void MovePipes(float dt);
        void DrawPipes();
        void RandomisePipeOffset();
        void UpdateScore(int score);
        const std::vector<sf::Sprite>& GetSprites() const;
        std::vector<sf::Sprite>& GetScoringSprites();
        
        int UpdateSpeed(int score) const;
        
    private:
        GameDataRef _data;
        std::vector<sf::Sprite> pipeSprites;
        std::vector<sf::Sprite> scoringPipes;
        sf::Clock totalclock;
        int _landHeight;
        int _pipeSpawnYOffset;
        int _nowScore;
        float movement;
        bool add = false;
    };
}
