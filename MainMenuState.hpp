#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace APlusPlus
{
    class MainMenuState : public State
    {
    public:
        MainMenuState(GameDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
        GameDataRef _data;
        
        sf::Sprite _background;
        sf::Sprite _title;
        sf::Sprite _playButton;
        sf::Sprite _jenny;
        sf:: Sprite _space;
        
        sf::SoundBuffer _backgroundSoundBuffer;
        sf::Sound _backgroundSound;
    };
}
