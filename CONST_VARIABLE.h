#pragma once
#include <string>
using namespace std;



const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 1024;

const int SPLASH_STATE_SHOW_TIME = 0;  // 開啟畫面會出現多久

const string  SPLASH_SCENE_BACKGROUND_FILEPATH = "Resources/res/Back.psd";
const string MAIN_MENU_BACKGROUND_FILEPATH = "Resources/res/Back.psd";
const string GAME_BACKGROUND_FILEPATH = "Resources/res/Back.psd";
const string GAME_OVER_BACKGROUND_FILEPATH = "Resources/res/Back.psd";

const string GAME_TITLE_FILEPATH = "Resources/res/tittle2.png";
const string PLAY_BUTTON_FILEPATH = "Resources/res/PlayButton3.png";
const string JENNY_FILEPATH = "Resources/res/Jenny.png";
const string SPACE_FILEPATH = "Resources/res/space.png";
const string CLICK_FILEPATH = "Resources/res/click.png";

const string TREE_UP_FILEPATH = "Resources/res/PIPEUP.png";
const string TREE_DOWN_FILEPATH = "Resources/res/PIPEDOWN.png";

const string LAND_FILEPATH = "Resources/res/land.jpg";

const string TURTLE_FRAME_1_FILEPATH = "Resources/res/turtle.png";


const string SCORING_TURTLE_FILEPATH = "Resources/res/InvisibleScoringPipe.png";

const string FLAPPY_FONT_FILEPATH = "Resources/fonts/Marker Felt.ttf";

const string GAME_OVER_TITLE_FILEPATH = "Resources/res/Game-Over-Title.png";
const string GAME_OVER_BODY_FILEPATH = "Resources/res/Game-Over-Body.png";

const string BRONZE_MEDAL_FILEPATH = "Resources/res/Bronze-Medal.png";
const string SILVER_MEDAL_FILEPATH = "Resources/res/Silver-Medal.png";
const string GOLD_MEDAL_FILEPATH = "Resources/res/Gold-Medal.png";
const string PLATINUM_MEDAL_FILEPATH = "Resources/res/Platinum-Medal.png";

const string HIT_SOUND_FILEPATH = "Resources/audio/Hit.wav";
const string POINT_SOUND_FILEPATH = "Resources/audio/Point.wav";
const string WING_SOUND_FILEPATH = "Resources/audio/jump1.wav";
const string EAT_STAR_SOUND_FILEPATH = "Resources/audio/eatStar.wav";
const string DIE_SOUND_FILEPATH = "Resources/audio/die.wav";
const string COIN_SOUND_FILEPATH = "Resources/audio/coin.wav";
const string BACKGROUND_SOUND_FILEPATH = "Resources/audio/background3.wav";
const string GAME_SOUND_FILEPATH  = "";

const double PIPE_MOVEMENT_SPEED = 200.0;
const double PIPE_SPAWN_FREQUENCY = 1.5;

const int FIRST_THRESHOLD = 5;
const int SECOND_THRESHOLD = 10;
const int THIRD_THRESHOLD = 20;
const int FORTH_THRESHOLD = 30;
const int FIFTH_THRESHOLD = 40;
const int SIXTH_THRESHOLD = 50;

const double TURTLE_ANIMATION_DURATION = 0.4;

const int TURTLE_STATE_STILL = 1;
const int TURTLE_STATE_FALLING = 2;
const int TURTLE_STATE_FLYING = 3;

const double GRAVITY = 350.0;
const double FLYING_SPEED = 350.0;

const double FLYING_DURATION = 0.25;

const double ROTATION_SPEED = 100.0;

enum GameStates
{
    eReady,
    ePlaying,
    eGameOver,
    ePause
};

const double DETECTION_SCALE = 0.7;

const double FLASH_SPEED = 1500.0;

const double TIME_BEFORE_GAME_OVER_APPEARS = 1.5;

const string  HIGH_SCORE_FILEPATH = "Resources/Highscore.txt";

const int BRONZE_MEDAL_SCORE = 0;
const int SILVER_MEDAL_SCORE = 5;
const int GOLD_MEDAL_SCORE = 10;
const int PLATINUM_MEDAL_SCORE = 15;

const string BALL_FILEPATH = "Resources/res/Pokeball.png";
const string STAR_FILEPATH = "Resources/res/InvincibleStar.png";


const double AFTER_PIPE = 0.2f;
const int BALL_FREQUENCY = 243;
const int STAR_FREQUENCY = 542;
const double STAR_TIME = 200;

