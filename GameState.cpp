#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include "GameOverState.hpp"

#include <iostream>

namespace APlusPlus
{
    GameState::GameState(GameDataRef data) : _data(data) {}
    
    void GameState::Init()
    {
        if(!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
        {
            std::cout << "Error Loading Hit Sound Effect" << std::endl;
        }
        
        if(!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
        {
            std::cout << "Error Loading Wing Sound Effect" << std::endl;
        }
        
        if(!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
        {
            std::cout << "Error Loading Point Sound Effect" << std::endl;
        }
        
        _hitSound.setBuffer(_hitSoundBuffer);
        _wingSound.setBuffer(_wingSoundBuffer);
        _pointSound.setBuffer(_pointSoundBuffer);
        
        this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        this->_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        this->_data->assets.LoadTexture("Land", LAND_FILEPATH);
        this->_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
        this->_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
        this->_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
        this->_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
        this->_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
        this->_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
        this -> _data-> assets.LoadTexture("Ball", BALL_FILEPATH);
        this-> _data -> assets.LoadTexture("Star", STAR_FILEPATH);
        
        pipe = new Pipe(_data);
        land = new Land(_data);
        bird = new Bird(_data);
        flash = new Flash(_data);
        hud = new HUD(_data);
        ball = new Ball(_data);
        star = new Star(_data);
        
        _background.setTexture(this->_data->assets.GetTexture("Game Background"));
        
        _score = 0;
        starTime = -0.3;
        random = 1;
        FlashControl = 1;
        addBall = false;
        addStar = false;
        hud->UpdateScore(_score);
        pipe -> UpdateScore(_score);
        ball -> UpdateScore(_score);
        star -> UpdateScore(_score);
        
        _gameState = GameStates::eReady;
    }
    
    void GameState::HandleInput()
    {
        sf::Event event;
        
        while(this->_data->window.pollEvent(event))
        {
            if(sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }
            // testing for moving pipe implementation
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                if(_gameState == GameStates::ePlaying)
                {
                    _gameState = GameStates::ePause;
                    tempclock = sf::seconds(clock.getElapsedTime().asSeconds());
                    //std::cout << tempclock.asSeconds() << std::endl;
                    nowPause = true;
                    //std::cout << "SPACE" << std::endl;
                }
            }
            else if(this->_data->input.IsSpriteClicked(this->_background
                                                  , sf::Mouse::Left, this->_data->window))
            {
                if(_gameState == GameStates::ePause)
                {
                    clock.restart();
                }
                if(_gameState != GameStates::eGameOver)
                {
                    _gameState = GameStates::ePlaying;
                    bird->Tap();
                    
                    _wingSound.play();
                }
            }
        }
    }
    
    void GameState::Update(float dt)
    {
        if(_gameState != GameStates::ePause)
        {
            if(_gameState != GameStates::eGameOver)
            {
                bird->Animate(dt);
                //land->MoveLand(dt);
            }
            if(_gameState == GameStates::ePlaying)
            {
                FREQUENCY = PIPE_SPAWN_FREQUENCY;
                FlashControl++;
                starTime -= dt;
                star -> UpdateScore(_score);
                ball -> UpdateScore(_score);
                pipe->MovePipes(dt);
                ball->MoveBall(dt);
                star -> MoveStar(dt);
                
                if( FIRST_THRESHOLD <= _score && _score < SECOND_THRESHOLD )
                {
                    FREQUENCY = 1.0f;
                }
                else if( SECOND_THRESHOLD <= _score && _score < THIRD_THRESHOLD )
                {
                    FREQUENCY = 0.8f;
                }
                else if( THIRD_THRESHOLD <= _score )
                {
                    FREQUENCY = 0.6f;
                }
                if(nowPause)
                {
                    interval = FREQUENCY - tempclock.asSeconds();
                }
                if(nowPause && clock.getElapsedTime().asSeconds() > interval)
                {
                    //std::cout << "nowPause" << std::endl;
                    //std::cout << tempclock.asSeconds() << std::endl;
                    pipe->RandomisePipeOffset();
                    pipe->SpawnInvisiblePipe();
                    pipe->SpawnBottomPipe();
                    pipe->SpawnTopPipe();
                    pipe->SpawnScoringPipe();
                    
                    clock.restart();
                    nowPause = false;
                }
                else if(!nowPause && clock.getElapsedTime().asSeconds() > FREQUENCY)
                {
                    pipe->RandomisePipeOffset();
                    pipe->SpawnInvisiblePipe();
                    pipe->SpawnBottomPipe();
                    pipe->SpawnTopPipe();
                    pipe->SpawnScoringPipe();
                    addBall = true;
                    addStar = true;
                    clock.restart();
                }
                else if(!nowPause && clock.getElapsedTime().asSeconds() + AFTER_PIPE > FREQUENCY)
                {
                    if(addBall && FlashControl % BALL_FREQUENCY == 0){
                        ball->RandomiseBallOffset();
                        ball->SpawnBall();
                        addBall = false;
                    }
                    
                    if(addStar && FlashControl % STAR_FREQUENCY == 0){
                        FlashControl = 1;
                        star -> RandomiseStarOffset();
                        star -> SpawnStar();
                        addStar = false;
                    }
                    
                }
                bird->Update(dt);
                
                // for land collision detection
                std::vector<sf::Sprite> landSprite = land->GetSprites();
                
                for(int i = 0; i < landSprite.size(); i++)
                {
                    if(collision.CheckSpriteCollision(landSprite.at(i), 1.0f, bird->GetSprite(), DETECTION_SCALE))
                    {
                        _gameState = GameStates::eGameOver;
                        
                        _hitSound.play();
                    }
                }
                if(starTime <= 0)
                {
                    // for pipe collision detection
                    std::vector<sf::Sprite> pipeSprite = pipe->GetSprites();
                    
                    for(int i = 0; i < pipeSprite.size(); i++)
                    {
                        if(collision.CheckSpriteCollision(pipeSprite.at(i), 1.0f, bird->GetSprite(), DETECTION_SCALE))
                        {
                            _gameState = GameStates::eGameOver;
                            
                            _hitSound.play();
                        }
                    }
                }
                
                // for ball collison detection
                std::vector<sf::Sprite> ballSprite = ball-> GetSprites();
                for(int i = 0; i < ballSprite.size(); i++)
                {
                    if(collision.CheckSpriteCollision(ballSprite.at(i), 1.0f, bird->GetSprite(), DETECTION_SCALE))
                    {
                        _score++;
                        ball -> ballErase(i);
                        hud -> UpdateScore(_score);
                        pipe-> UpdateScore(_score);
                        ball-> UpdateScore(_score);
                        _pointSound.play();
                        break;
                    }
                    
                }
                
                // for star collison detection
                std::vector<sf::Sprite> starSprite = star -> GetSprites();
                for(int i = 0; i < starSprite.size(); i++)
                {
                    if(collision.CheckSpriteCollision(starSprite.at(i), 1.0f, bird ->GetSprite(), DETECTION_SCALE))
                    {
                        starTime = dt * STAR_FREQUENCY;
                        star -> starErase(i);
                        break;
                    }
                    
                }
                
                if(_gameState == GameStates::ePlaying)
                {
                    std::vector<sf::Sprite>& scoringSprites = pipe->GetScoringSprites();

                    for(int i = 0; i < scoringSprites.size(); i++)
                    {
                        if(collision.CheckSpriteCollision(bird->GetSprite(), DETECTION_SCALE, scoringSprites.at(i), 1.0f))
                        {
                            _score++;
                            
                            hud -> UpdateScore(_score);
                            pipe-> UpdateScore(_score);
                            ball-> UpdateScore(_score);
                            _pointSound.play();

                            scoringSprites.erase(scoringSprites.begin() + i);
                        }
                    }
                }
            }
            
            if(_gameState == GameStates::eGameOver)
            {
                flash->Show(dt);
                if(clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
                {
                    this->_data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
                }
            }
        }
    }
    
    void GameState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);
        this->_data->window.draw(this->_background);
        
        this->pipe->DrawPipes();
        this -> star-> DrawStar();
        if(starTime <= 0){
            this -> bird -> Draw();
        }
        else{
            if(FlashControl % 5 == 0) this -> bird -> Draw();
        }
        this -> ball -> DrawBall();
        
        this->flash->Draw();
        
        this->hud->Draw();
        
        this->land->DrawLand();
        
        this->_data->window.display();
        
    }
}
