#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define DEBUG 0
#define VERSION "Tanks 1.0"

#define FRAMERATE 60

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

#define BATTLEFIELD_WIDTH 900
#define BATTLEFIELD_HEIGHT 650
#define REAL_BATTLEFIELD_WIDTH BATTLEFIELD_WIDTH + TANK_SIZE
#define REAL_BATTLEFIELD_HEIGHT BATTLEFIELD_HEIGHT + TANK_SIZE

#define XSIZE 19 //x possibilities
#define YSIZE 14 //y possibilities
#define DIRECTIONS 4 // number of possible directions to go at any position

#define MENU_BUTTON_WIDTH 500
#define MENU_BUTTON_HEIGHT 70
#define MENU_BUTTON_SPACE 200

#define AMMO_SPEED 4
#define TANK_SPEED 2
#define TANK_SIZE 50

#define PLAYER_TANK "playerTank.png"
#define ENEMY_NORMAL_TANK "enemyNormal.png"
#define ENEMY_FAST_TANK "enemyFast.png"
#define ENEMY_MID_TANK "enemyMid.png"
#define ENEMY_HEAVY_TANK "enemyHeavy.png"
#define AMMO_BITMAP "ammo.png"
#define WALL_BITMAP "immortallObstacle.png"
#define DESTROYABLE_WALL "wall.png"
#define BIG_EXPLOSION "explosion.bmp"
#define SMALL_EXPLOSION "smallExplosion.bmp"
#define BONUS_BITMAP "bonus.png"
#define BASE_BITMAP "base.png"
#define BASE_DESTROY "baseD.png"
#define SURVIVE_BUTTON "surviveButton.png"
#define BASE_DEFENCE_BUTTON "baseDefenceButton.png"
#define CAMPAIGN_BUTTON "campaignButton.png"
#define HIGHSCORE_BUTTON "highscoreButton.png"
#define EXIT_BUTTON "exitButton.png"
#define BACKGROUND_BITMAP "background.png"
#define BACK_BUTTON "backButton.png"
#define OK_BUTTON "okButton.png"

#define WALL_DESTROY_SOUND "wallDestroy.wav"
#define SHOT_SOUND "shot.wav"
#define EXPLOSION_SOUND "explosion.wav"
#define HIT_TANK_SOUND "hitTank.wav"
#define HIT_WALL_SOUND "hitWall.wav"

#define MAIN_FONT "calibri.ttf"
#define HUD_FONT "hudFont.ttf"
#define CAMPAIGN_FONT "campaign.otf"

#define HIGHSCORE "highscore.cfg"

#define SOUNDS 5

#define OBSTACLES 60
#define BONUSES 10
#define OBSTACLE_SIZE 50
#define FREE_SPACE 100
#define MARGIN_SIZE 5
#define VIEW_RANGE 25
#define BLIND_RANGE 100

#define ROCKET_X 20
#define ROCKET_Y 7
#define ROCKET_SIZE 20

#define ROCKETS 25
#define ENEMY_MAX_SHOOTS ROCKETS-15
#define ENEMIES 4
#define ENEMY_SIMULTANEOUSLY 3
#define EXPLOSIONS 20

#define SMALL_EXPLOSION_TIME 31
#define BIG_EXPLOSION_TIME 63
#define POINTS_FOR_KILL 10

#define BONUS_CHANCE 15
#define HUD_COLOR al_map_rgb(0,0,0)
#define HIGHSCORE_COLOR al_map_rgb(0,255,0)

#define BIG_ANIMATION_SIZE 50
#define SMALL_ANIMATION_SIZE 25

#define RESPAWN_TIMER FRAMERATE*4

#pragma GCC diagnostic ignored "-Wwrite-strings" //to ignore showError warning which is correct
#endif
