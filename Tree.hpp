#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include "CONST_VARIABLE.h"

namespace APlusPlus
{
    class Tree
    {
    public:
        Tree(GameDataRef data);
        
        void SpawnBottomTree();
        void SpawnTopTree();
        void SpawnInvisibleTree();
        void SpawnScoringTree();
        void MoveTrees(float dt);
        void DrawTrees();
        void RandomiseTreeOffset();
        void UpdateScore(int score);
        const std::vector<sf::Sprite>& GetSprites() const;
        std::vector<sf::Sprite>& GetScoringSprites();
        
        int UpdateSpeed(int score) const;
        
    private:
        GameDataRef _data;
        std::vector<sf::Sprite> treeSprites;
        std::vector<sf::Sprite> scoringTrees;
        sf::Clock totalclock;
        int _landHeight;
        int _treeSpawnYOffset;
        int _nowScore;
        float movement;
        bool add = false;
    };
}
