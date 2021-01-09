#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Land.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"
#include "Ball.hpp"
#include "Star.hpp"
#include "Tree.hpp"
#include "Turtle.hpp"

namespace APlusPlus
{
    class GameState : public State
    {
    public:
        GameState(GameDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;
        sf::Sprite _background;
        sf::Sprite _click;
        
        Tree* tree;
        Land* land;
        Turtle* turtle;
        Collision collision;
        Flash* flash;
        HUD* hud;
        Ball* ball;
        Star* star;
        
        sf::Clock clock;
        sf::Time tempclock;
        int _gameState;
        
        int _score;
        
        sf::SoundBuffer _hitSoundBuffer;
        sf::SoundBuffer _wingSoundBuffer;
        sf::SoundBuffer _pointSoundBuffer;
        sf::SoundBuffer _eatStarSoundBuffer;
        sf::SoundBuffer _dieSoundBuffer;
        sf::SoundBuffer _coinSoundBuffer;
        sf::SoundBuffer _backgroundSoundBuffer;
        
        sf::Sound _hitSound;
        sf::Sound _wingSound;
        sf::Sound _pointSound;
        sf::Sound _eatStar;
        sf::Sound _dieSound;
        sf:: Sound _coinSound;
        sf:: Sound _backgroundSound;
        
        float FREQUENCY;
        bool nowPause;
        float interval;
        bool addBall;
        bool addStar;
        float starTime;
        int random;
        int FlashControl;
        
    };
}
