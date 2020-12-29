#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"
#include "GameState.hpp"

#include <iostream>

namespace Sonar
{
    GameOverState::GameOverState(GameDataRef data, int score) : _data(data), _score(score)
    {
        
    }
    
    void GameOverState::Init()
    {
        // reading historic high scores
        std::ifstream readFile;
        readFile.open(HIGH_SCORE_FILEPATH);
        
        if(readFile.is_open())
        {
            while(!readFile.eof())
            {
                readFile >> _highScore;
            }
        }
        readFile.close();
        
        // over writing high score if it's broken
        std::ofstream writeFile;
        writeFile.open(HIGH_SCORE_FILEPATH);
        
        if(writeFile.is_open())
        {
            if(_score > _highScore)
            {
                _highScore = _score;
            }
            
            writeFile << _highScore;
        }
        
        writeFile.close();
        
        // load textures
        this->_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
        this->_data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
        this->_data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
        this->_data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
        this->_data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
        this->_data->assets.LoadTexture("Platinum Medal", PLAY_BUTTON_FILEPATH);
        
        // applying textures
        this->_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
        this->_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));
        this->_gameOverContainer.setTexture(this->_data->assets.GetTexture("Game Over Body"));
        this->_retryButton.setTexture(this->_data->assets.GetTexture("Play Button"));
        
        // setting positions
        this->_gameOverContainer.setPosition(sf::Vector2f((_data->window.getSize().x / 2) - (_gameOverContainer.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_gameOverContainer.getGlobalBounds().height / 2)));
        this->_gameOverTitle.setPosition(sf::Vector2f((_data->window.getSize().x / 2) - (_gameOverTitle.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y - _gameOverTitle.getGlobalBounds().height * 1.2));
        this->_retryButton.setPosition(sf::Vector2f((_data->window.getSize().x / 2) - (_retryButton.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height + _retryButton.getGlobalBounds().height * 0.2));
        
        // current score appearance
        this->_scoreText.setFont(this->_data->assets.GetFont("Flappy Font"));
        this->_scoreText.setString(std::to_string(_score));
        this->_scoreText.setCharacterSize(56);
        this->_scoreText.setFillColor(sf::Color::White);
        this->_scoreText.setOrigin(sf::Vector2f(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2));
        this->_scoreText.setPosition(sf::Vector2f(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 2.15));
        
        // high score appearance
        this->_highScoreText.setFont(this->_data->assets.GetFont("Flappy Font"));
        this->_highScoreText.setString(std::to_string(_highScore));
        this->_highScoreText.setCharacterSize(56);
        this->_highScoreText.setFillColor(sf::Color::White);
        this->_highScoreText.setOrigin(sf::Vector2f(_highScoreText.getGlobalBounds().width / 2, _highScoreText.getGlobalBounds().height / 2));
        this->_highScoreText.setPosition(sf::Vector2f(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 1.78));
        
        // assigning medal
        if(_score >= PLATINUM_MEDAL_SCORE)
        {
            _medal.setTexture(_data->assets.GetTexture("Platinum Medal"));
        }
        else if(_score >= GOLD_MEDAL_SCORE)
        {
            _medal.setTexture(_data->assets.GetTexture("Gold Medal"));
        }
        else if(_score >= SILVER_MEDAL_SCORE)
        {
            _medal.setTexture(_data->assets.GetTexture("Silver Medal"));
        }
        else
        {
            _medal.setTexture(_data->assets.GetTexture("Bronze Medal"));
        }
        
        _medal.setPosition(175, 465);
    }
    
    void GameOverState::HandleInput()
    {
        sf::Event event;
        
        while(this->_data->window.pollEvent(event))
        {
            if(sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }
            //added for experiment
            if(this->_data->input.IsSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window))
            {
                // make a new game state
                this->_data->machine.AddState(StateRef(new GameState(_data)), true);
            }
        }
    }
    
    void GameOverState::Update(float dt)
    {
        
    }
    
    void GameOverState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);
        
        this->_data->window.draw(this->_background);
        
        this->_data->window.draw(_gameOverTitle);
        this->_data->window.draw(_gameOverContainer);
        this->_data->window.draw(_retryButton);
        this->_data->window.draw(_highScoreText);
        this->_data->window.draw(_scoreText);
        this->_data->window.draw(_medal);
        
        this->_data->window.display();
    }
}
