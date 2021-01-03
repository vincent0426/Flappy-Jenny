#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024

#define SPLASH_STATE_SHOW_TIME 0  // 開啟畫面會出現多久

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/Back.psd"
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/res/Back.psd"
#define GAME_BACKGROUND_FILEPATH "Resources/res/Back.psd"
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/res/Back.psd"

#define GAME_TITLE_FILEPATH "Resources/res/Title.png"
#define PLAY_BUTTON_FILEPATH "Resources/res/PlayButton.png"
#define JENNY_FILEPATH "Resources/res/Jenny.png"

#define PIPE_UP_FILEPATH "Resources/res/PIPEUP.png"
#define PIPE_DOWN_FILEPATH "Resources/res/PIPEDOWN.png"

#define LAND_FILEPATH "Resources/res/land.png"

#define BIRD_FRAME_1_FILEPATH "Resources/res/turtle.png"
#define BIRD_FRAME_2_FILEPATH "Resources/res/turtle.png"
#define BIRD_FRAME_3_FILEPATH "Resources/res/turtle.png"
#define BIRD_FRAME_4_FILEPATH "Resources/res/turtle.png"

#define SCORING_PIPE_FILEPATH "Resources/res/InvisibleScoringPipe.png"

#define FLAPPY_FONT_FILEPATH "Resources/fonts/Marker Felt.ttf"

#define GAME_OVER_TITLE_FILEPATH "Resources/res/Game-Over-Title.png"
#define GAME_OVER_BODY_FILEPATH "Resources/res/Game-Over-Body.png"

#define BRONZE_MEDAL_FILEPATH "Resources/res/Bronze-Medal.png"
#define SILVER_MEDAL_FILEPATH "Resources/res/Silver-Medal.png"
#define GOLD_MEDAL_FILEPATH "Resources/res/Gold-Medal.png"
#define PLATINUM_MEDAL_FILEPATH "Resources/res/Platinum-Medal.png"

#define HIT_SOUND_FILEPATH "Resources/audio/Hit.wav"
#define POINT_SOUND_FILEPATH "Resources/audio/Point.wav"
#define WING_SOUND_FILEPATH "Resources/audio/Wing.wav"

#define PIPE_MOVEMENT_SPEED 200.0f
#define PIPE_SPAWN_FREQUENCY 1.5f

#define FIRST_THRESHOLD 5
#define SECOND_THRESHOLD 10
#define THIRD_THRESHOLD 20
#define FORTH_THRESHOLD 30
#define FIFTH_THRESHOLD 40
#define SIXTH_THRESHOLD 50

#define BIRD_ANIMATION_DURATION 0.4f

#define BIRD_STATE_STILL 1
#define BIRD_STATE_FALLING 2
#define BIRD_STATE_FLYING 3

#define GRAVITY 350.0f
#define FLYING_SPEED 350.0f

#define FLYING_DURATION 0.25f

#define ROTATION_SPEED 100.0f

enum GameStates
{
    eReady,
    ePlaying,
    eGameOver,
    ePause
};

#define DETECTION_SCALE 0.625f

#define FLASH_SPEED 1500.0f

#define TIME_BEFORE_GAME_OVER_APPEARS 1.5f

#define HIGH_SCORE_FILEPATH "Resources/Highscore.txt"

#define BRONZE_MEDAL_SCORE 0
#define SILVER_MEDAL_SCORE 5
#define GOLD_MEDAL_SCORE 10
#define PLATINUM_MEDAL_SCORE 15

#define BALL_FILEPATH "Resources/res/Pokeball.png"
#define STAR_FILEPATH "Resources/res/InvincibleStar.png"


#define AFTER_PIPE 0.2f
#define BALL_FREQUENCY 243
#define STAR_FREQUENCY 542
#define STAR_TIME 400
