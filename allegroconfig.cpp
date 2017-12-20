#include "allegroconfig.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_windows.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "config.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "bonus.hpp"
#include "explosion.hpp"
#include "wall.hpp"
#include "rocket.hpp"

ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *playerTank;
ALLEGRO_BITMAP *enemyNormalTank;
ALLEGRO_BITMAP *enemyFastTank;
ALLEGRO_BITMAP *enemyMidTank;
ALLEGRO_BITMAP *enemyHeavyTank;
ALLEGRO_BITMAP *ammoBitmap;
ALLEGRO_BITMAP *wallBitmap;
ALLEGRO_BITMAP *immortalWallBitmap;
ALLEGRO_BITMAP *surviveButton;
ALLEGRO_BITMAP *baseDefenceButton;
ALLEGRO_BITMAP *campaignButton;
ALLEGRO_BITMAP *highscoreButton;
ALLEGRO_BITMAP *exitButton;
ALLEGRO_BITMAP *backButton;
ALLEGRO_BITMAP *okButton;
ALLEGRO_KEYBOARD_STATE keyboard;
ALLEGRO_CONFIG* iniFile;

extern Player * player;
extern Enemy ** enemy;
extern Wall ** wall;
extern Rocket ** rocket;

void AllegroInitialize()
{
    if(!al_init())
        ShowError("Allegro 5 engine", 1);

    if(!al_install_keyboard())
        ShowError("Keyboard", 1);

    if(!al_init_image_addon())
        ShowError("Image addon", 1);

    al_init_font_addon(); //never return false ->> info from allegro 5 DOCS
    if(!al_init_primitives_addon())
        ShowError("Primitives addon", 1);

    if(!al_init_ttf_addon())
        ShowError("TTF font addon", 1);

    al_set_new_display_option(ALLEGRO_DEPTH_SIZE,32,ALLEGRO_REQUIRE);
    al_set_new_display_option(ALLEGRO_RENDER_METHOD,1,ALLEGRO_REQUIRE);
    al_set_new_display_option(ALLEGRO_VSYNC,1,ALLEGRO_REQUIRE);
    al_inhibit_screensaver(1);

    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_NOFRAME );
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if(!display)
        ShowError("Display", 1);

    if(!al_install_mouse())
        ShowError("Mouse", 1);

    al_set_window_title(display, VERSION);

    srand(time(NULL));
};

void DataInitialize()
{
    playerTank = al_load_bitmap(PLAYER_TANK);
    if(!playerTank)
        ShowError(PLAYER_TANK, 0);

    enemyNormalTank = al_load_bitmap(ENEMY_NORMAL_TANK);
    if(!enemyNormalTank)
        ShowError(ENEMY_NORMAL_TANK, 0);

    enemyFastTank = al_load_bitmap(ENEMY_FAST_TANK);
    if(!enemyFastTank)
        ShowError(ENEMY_FAST_TANK, 0);

    enemyMidTank = al_load_bitmap(ENEMY_MID_TANK);
    if(!enemyMidTank)
        ShowError(ENEMY_MID_TANK, 0);

    enemyHeavyTank = al_load_bitmap(ENEMY_HEAVY_TANK);
    if(!enemyHeavyTank)
        ShowError(ENEMY_HEAVY_TANK, 0);

    ammoBitmap = al_load_bitmap(AMMO_BITMAP);
    if(!ammoBitmap)
        ShowError(AMMO_BITMAP, 0);

    wallBitmap = al_load_bitmap(WALL_BITMAP);
    if(!wallBitmap)
        ShowError(WALL_BITMAP, 0);

    immortalWallBitmap = al_load_bitmap(DESTROYABLE_WALL);
    if(!immortalWallBitmap)
        ShowError(DESTROYABLE_WALL, 0);

    surviveButton = al_load_bitmap(SURVIVE_BUTTON);
    if(!surviveButton)
        ShowError(SURVIVE_BUTTON, 0);

    baseDefenceButton = al_load_bitmap(BASE_DEFENCE_BUTTON);
    if(!baseDefenceButton)
        ShowError(BASE_DEFENCE_BUTTON, 0);

    campaignButton = al_load_bitmap(CAMPAIGN_BUTTON);
    if(!campaignButton)
        ShowError(CAMPAIGN_BUTTON, 0);

    highscoreButton = al_load_bitmap(HIGHSCORE_BUTTON);
    if(!highscoreButton)
        ShowError(HIGHSCORE_BUTTON, 0);

    exitButton = al_load_bitmap(EXIT_BUTTON);
    if(!exitButton)
        ShowError(EXIT_BUTTON, 0);

    backButton = al_load_bitmap(BACK_BUTTON);
    if(!backButton)
        ShowError(BACK_BUTTON, 0);

    okButton = al_load_bitmap(OK_BUTTON);
    if(!okButton)
        ShowError(OK_BUTTON, 0);

    al_convert_mask_to_alpha(playerTank, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(enemyNormalTank, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(enemyMidTank, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(enemyFastTank, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(enemyHeavyTank, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(ammoBitmap, al_map_rgb(0, 0, 0));
};

void ShowError(char *name, short option)
{
    char message[64];
    switch(option)
    {
    case 0:
    {
        sprintf(message, "%s has not been loaded", name);
        break;
    }
    case 1:
    {
        sprintf(message, "%s has not been initialized", name);
        break;
    }
    case 2:
    {
        sprintf(message, "%s have not been initialized", name);
        break;
    }

    }

    al_show_native_message_box(display, "Error", "Error occurred", message, NULL, ALLEGRO_MESSAGEBOX_ERROR);
    ClearMemory();
}

void ClearMemory()
{
    for (short i = 0; i < OBSTACLES; i++)
    {
        delete wall[i];
    }

    for (short i = 0; i < ROCKETS; i++)
    {
        delete rocket[i];
    }

    for (short i = 0; i < ENEMIES; i++)
    {
        delete enemy[i];
    }

    delete[] rocket;
    delete[] enemy;
    delete[] player;
    delete[] wall;

    if(playerTank)
        al_destroy_bitmap(playerTank);

    if(ammoBitmap)
        al_destroy_bitmap(ammoBitmap);

    if(wallBitmap)
        al_destroy_bitmap(wallBitmap);

    if(immortalWallBitmap)
        al_destroy_bitmap(immortalWallBitmap);

    if(enemyNormalTank)
        al_destroy_bitmap(enemyNormalTank);

    if(enemyFastTank)
        al_destroy_bitmap(enemyFastTank);

    if(enemyMidTank)
        al_destroy_bitmap(enemyMidTank);

    if(enemyHeavyTank)
        al_destroy_bitmap(enemyHeavyTank);

    if(surviveButton)
        al_destroy_bitmap(surviveButton);

    if(baseDefenceButton)
        al_destroy_bitmap(baseDefenceButton);

    if(campaignButton)
        al_destroy_bitmap(campaignButton);

    if(highscoreButton)
        al_destroy_bitmap(highscoreButton);

    if(exitButton)
        al_destroy_bitmap(exitButton);

    if(okButton)
        al_destroy_bitmap(okButton);

    if(display)
        al_destroy_display(display);

    exit(0);
};

