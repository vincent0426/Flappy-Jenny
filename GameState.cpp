#include "CONST_VARIABLE.h"
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
        
        if(!_eatStarSoundBuffer.loadFromFile(EAT_STAR_SOUND_FILEPATH))
        {
            std::cout << "Error Loading Hit Sound Effect" << std::endl;
        }
        if(!_dieSoundBuffer.loadFromFile(DIE_SOUND_FILEPATH)){
            
        }
        if(!_coinSoundBuffer.loadFromFile(COIN_SOUND_FILEPATH)){
            
        }
        /*if(!_backgroundSoundBuffer.loadFromFile(BACKGROUND_SOUND_FILEPATH)){
            
        }*/
        
        _coinSound.setBuffer(_coinSoundBuffer);
        _dieSound.setBuffer(_dieSoundBuffer);
        _eatStar.setBuffer(_eatStarSoundBuffer);
        _hitSound.setBuffer(_hitSoundBuffer);
        _wingSound.setBuffer(_wingSoundBuffer);
        _pointSound.setBuffer(_pointSoundBuffer);
        //_backgroundSound.setBuffer(_backgroundSoundBuffer);
        
        this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Tree Up", TREE_UP_FILEPATH);
        this->_data->assets.LoadTexture("Tree Down", TREE_DOWN_FILEPATH);
        this->_data->assets.LoadTexture("Land", LAND_FILEPATH);
        this->_data->assets.LoadTexture("Turtle Frame 1", TURTLE_FRAME_1_FILEPATH);
        this->_data->assets.LoadTexture("Scoring Tree", SCORING_TURTLE_FILEPATH);
        this->_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
        this -> _data-> assets.LoadTexture("Ball", BALL_FILEPATH);
        this-> _data -> assets.LoadTexture("Star", STAR_FILEPATH);
        this -> _data -> assets.LoadTexture("click", CLICK_FILEPATH);
        
        tree = new Tree(_data);
        land = new Land(_data);
        turtle = new Turtle(_data);
        flash = new Flash(_data);
        hud = new HUD(_data);
        ball = new Ball(_data);
        star = new Star(_data);
        
        _background.setTexture(this->_data->assets.GetTexture("Game Background"));
        _click.setTexture(this ->  _data -> assets.GetTexture("click"));
        _click.setPosition(SCREEN_WIDTH/2 - 350, SCREEN_HEIGHT/2);
        
        _score = 0;
        starTime = -0.3;
        random = 1;
        FlashControl = 1;
        addBall = false;
        addStar = false;
        hud->UpdateScore(_score);
        tree -> UpdateScore(_score);
        ball -> UpdateScore(_score);
        star -> UpdateScore(_score);
        
        _gameState = GameStates::eReady;
        //_backgroundSound.play();
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
                    nowPause = true;
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
                    turtle->Tap();
                    
                    _wingSound.play();
                }
            }
        }
    }
    
    void GameState::Update(float dt)
    {
        if(_gameState != GameStates::ePause)
        {
            if(_gameState == GameStates::ePlaying)
            {
                std::vector<sf::Sprite> treeSprite = tree->GetSprites();
                FREQUENCY = PIPE_SPAWN_FREQUENCY;
                FlashControl++;
                starTime -= dt;
                star -> UpdateScore(_score);
                ball -> UpdateScore(_score);
                tree->MoveTrees(dt);
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
                else if( THIRD_THRESHOLD <= _score && _score < FORTH_THRESHOLD )
                {
                    FREQUENCY = 0.6f;
                }
                else if( FORTH_THRESHOLD <= _score && _score < FIFTH_THRESHOLD )
                {
                    FREQUENCY = 0.4f;
                }
                else if( FIFTH_THRESHOLD <= _score && _score < SIXTH_THRESHOLD )
                {
                    FREQUENCY = 0.35f;
                }
                else if( SIXTH_THRESHOLD <= _score)
                {
                    FREQUENCY = 0.25f;
                }
                if(nowPause)
                {
                    interval = FREQUENCY - tempclock.asSeconds();
                }
                if(nowPause && clock.getElapsedTime().asSeconds() > interval)
                {
                    tree->RandomiseTreeOffset();
                    tree->SpawnInvisibleTree();
                    tree->SpawnBottomTree();
                    tree->SpawnTopTree();
                    tree->SpawnScoringTree();
                    
                    clock.restart();
                    nowPause = false;
                }
                else if(!nowPause && clock.getElapsedTime().asSeconds() > FREQUENCY)
                {
                    tree->RandomiseTreeOffset();
                    tree->SpawnInvisibleTree();
                    tree->SpawnBottomTree();
                    tree->SpawnTopTree();
                    tree->SpawnScoringTree();
                    addBall = true;
                    addStar = true;
                    clock.restart();
                }
                else if(!nowPause)
                {
                    if(addBall && FlashControl % BALL_FREQUENCY == 0){
                        ball->RandomiseBallOffset();
                        ball->SpawnBall();
                        addBall = false;
                        for(int i = 0;  i < treeSprite.size(); i++){
                            if(collision.CheckSpriteCollision(treeSprite.at(i), ball->GetSprites().back())){
                                int j = ball->GetSprites().size();
                                ball->ballErase(j-1);
                                addBall = true;
                            }
                        }
                    }
                    
                    if(addStar && FlashControl % STAR_FREQUENCY == 0){
                        FlashControl = 1;
                        star -> RandomiseStarOffset();
                        star -> SpawnStar();
                        addStar = false;
                        for(int i = 0; i < treeSprite.size(); i++){
                            if(collision.CheckSpriteCollision(treeSprite.at(i), star-> GetSprites().back())){
                                int j = star->GetSprites().size();
                                star -> starErase(j-1);
                                addStar = true;
                            }
                        }

                    }
                    
                }
                turtle->Update(dt);
                
                // for land collision detection
                std::vector<sf::Sprite> landSprite = land->GetSprites();
                std::vector<sf::Sprite> ballSprite = ball-> GetSprites();
                std::vector<sf::Sprite> starSprite = star -> GetSprites();
                
                
                for(int i = 0; i < landSprite.size(); i++)
                {
                    if(collision.CheckSpriteCollision(landSprite.at(i), 1.0f, turtle->GetSprite(), DETECTION_SCALE))
                    {
                        _gameState = GameStates::eGameOver;
                        //_backgroundSound.stop();
                        _hitSound.play();
                        _dieSound.play();
                    }
                }
                if(starTime <= 0)
                {
                    // for pipe collision detection
                    
                    for(int i = 0; i < treeSprite.size(); i++)
                    {
                        if(collision.CheckSpriteCollision(treeSprite.at(i), 0.85f, turtle->GetSprite(), DETECTION_SCALE))
                        {
                            _gameState = GameStates::eGameOver;
                            //_backgroundSound.stop();
                            _hitSound.play();
                            _dieSound.play();
                        }
                        for(int j = 0; j < starSprite.size();j++){
                            if(collision.CheckSpriteCollision(treeSprite.at(i), 0.5f, starSprite.at(j) ,DETECTION_SCALE )){
                                star -> starErase(j);
                                break;
                            }
                        }
                        
                        for(int j = 0; j < ballSprite.size();j++){
                            if(collision.CheckSpriteCollision(treeSprite.at(i), 0.5f, ballSprite.at(j) ,DETECTION_SCALE )){
                                ball -> ballErase(j);
                                break;
                            }
                        }
                        
                    }
                }
                
                // for ball collison detection
                ballSprite = ball-> GetSprites();
                for(int i = 0; i < ballSprite.size(); i++)
                {
                    if(collision.CheckSpriteCollision(ballSprite.at(i), 1.0f, turtle->GetSprite(), DETECTION_SCALE))
                    {
                        _score++;
                        ball -> ballErase(i);
                        hud -> UpdateScore(_score);
                        tree -> UpdateScore(_score);
                        ball-> UpdateScore(_score);
                        _coinSound.play();
                        break;
                    }
                    
                }
                
                // for star collison detection
                starSprite = star -> GetSprites();
                for(int i = 0; i < starSprite.size(); i++)
                {
                    if(collision.CheckSpriteCollision(starSprite.at(i), 1.0f, turtle ->GetSprite(), DETECTION_SCALE))
                    {
                        starTime = dt * STAR_TIME;
                        star -> starErase(i);
                        _eatStar.play();
                        break;
                    }
                    
                }
                
                
                if(_gameState == GameStates::ePlaying)
                {
                    std::vector<sf::Sprite>& scoringSprites = tree ->GetScoringSprites();

                    for(int i = 0; i < scoringSprites.size(); i++)
                    {
                        if(collision.CheckSpriteCollision(turtle->GetSprite(), DETECTION_SCALE, scoringSprites.at(i), 1.0f))
                        {
                            _score++;
                            
                            hud -> UpdateScore(_score);
                            tree-> UpdateScore(_score);
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
        
        this->tree->DrawTrees();
        this -> star-> DrawStar();
        if(starTime <= 0){
            this -> turtle -> Draw();
        }
        else{
            if(FlashControl % 5 == 0) this -> turtle -> Draw();
            if(_gameState == GameStates::ePause) this -> turtle -> Draw();
        }
        this -> ball -> DrawBall();
        
        this->flash->Draw();
        
        this->hud->Draw();
        
        this->land->DrawLand();
        
        if(_gameState == GameStates::ePause) this -> _data -> window.draw(this->_click);
        
        this->_data->window.display();
        
    }
}

