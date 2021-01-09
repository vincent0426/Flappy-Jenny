#include <sstream>
#include "CONST_VARIABLE.h"
#include "MainMenuState.hpp"
#include "GameState.hpp"

#include <iostream>

namespace APlusPlus
{
    MainMenuState::MainMenuState(GameDataRef data) : _data(data) {}
    
    void MainMenuState::Init()
    {
        this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
        this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
        this->_data->assets.LoadTexture("Jenny", JENNY_FILEPATH);
        this -> _data -> assets.LoadTexture("space", SPACE_FILEPATH);
        
        //_backgroundSoundBuffer.loadFromFile(BACKGROUND_SOUND_FILEPATH);
        //_backgroundSound.setBuffer(_backgroundSoundBuffer);
        
        _background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
        _title.setTexture(this->_data->assets.GetTexture("Game Title"));
        _playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
        _jenny.setTexture(this->_data->assets.GetTexture("Jenny"));
        _space.setTexture(this-> _data  -> assets.GetTexture("space"));
        // 修改_title.getlocalBounds -> _title.getGlobalBounds
        _title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2);
        _playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - _playButton.getGlobalBounds().height / 2 -30);
        _jenny.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2) - 250, (SCREEN_HEIGHT / 2) - _playButton.getGlobalBounds().height / 2 + 75);
        _space.setPosition((SCREEN_WIDTH / 2)-325, (SCREEN_HEIGHT / 2) +100);
        //_backgroundSound.play();
        
    }
    
    void MainMenuState::HandleInput()
    {
        sf::Event event;
        
        while(this->_data->window.pollEvent(event))
        {
            if(sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }
            
            if(this->_data->input.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
            {
                // Switch To Game State
                this->_data->machine.AddState(StateRef(new GameState(_data)), true);
                //_backgroundSound.stop();
            }
        }
    }
    
    void MainMenuState::Update(float dt)
    {
        
    }
    
    void MainMenuState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);
        
        this->_data->window.draw(this->_background);
        this->_data->window.draw(this->_title);
        this->_data->window.draw(this->_playButton);
        this->_data->window.draw(this->_jenny);
        this -> _data -> window.draw(this->_space);
        
        this->_data->window.display();
    }
}
