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

ALLEGRO_SAMPLE *sound[SOUNDS]= {NULL};
ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *playerTank;
ALLEGRO_BITMAP *enemyNormalTank;
ALLEGRO_BITMAP *enemyFastTank;
ALLEGRO_BITMAP *enemyMidTank;
ALLEGRO_BITMAP *enemyHeavyTank;
ALLEGRO_BITMAP *ammoBitmap;
ALLEGRO_BITMAP *wallBitmap;
ALLEGRO_BITMAP *immortalWallBitmap;
ALLEGRO_BITMAP *explosionBitmap;
ALLEGRO_BITMAP *smallExplosionBitmap;
ALLEGRO_BITMAP *baseBitmap;
ALLEGRO_BITMAP *baseDamageBitmap;
ALLEGRO_BITMAP *bonusBitmap;
ALLEGRO_BITMAP *surviveButton;
ALLEGRO_BITMAP *baseDefenceButton;
ALLEGRO_BITMAP *campaignButton;
ALLEGRO_BITMAP *highscoreButton;
ALLEGRO_BITMAP *exitButton;
ALLEGRO_BITMAP *background;
ALLEGRO_BITMAP *backButton;
ALLEGRO_BITMAP *okButton;
ALLEGRO_KEYBOARD_STATE keyboard;
ALLEGRO_FONT * font30;
ALLEGRO_FONT * font60;
ALLEGRO_FONT * hudFont;
ALLEGRO_FONT * pauseFont;
ALLEGRO_FONT * campaignFont;
ALLEGRO_CONFIG* iniFile;

extern Player * player;
extern Enemy ** enemy;
extern Bonus ** bonus;
extern Explosion ** explosion;
extern Wall ** wall;
extern Rocket ** rocket;
extern Player * playerCampaign;

void SoundInitialize()
{
    if( !al_install_audio() )
        ShowError("Sound", 1);

    if( !al_init_acodec_addon() )
        ShowError("Codecs", 2);

    if( !al_reserve_samples(32) )
        ShowError("Samples", 2);

    sound[0]=al_load_sample(SHOT_SOUND);
    if(!sound[0])
        ShowError(SHOT_SOUND, 0);

    sound[1]=al_load_sample(EXPLOSION_SOUND);
    if(!sound[1])
        ShowError(EXPLOSION_SOUND, 0);

    sound[2]=al_load_sample(WALL_DESTROY_SOUND);
    if(!sound[2])
        ShowError(WALL_DESTROY_SOUND, 0);

    sound[3]=al_load_sample(HIT_TANK_SOUND);
    if(!sound[3])
        ShowError(HIT_TANK_SOUND, 0);

    sound[4]=al_load_sample(HIT_WALL_SOUND);
    if(!sound[4])
        ShowError(HIT_WALL_SOUND, 0);
};

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

    explosionBitmap = al_load_bitmap(BIG_EXPLOSION);
    if(!explosionBitmap)
        ShowError(BIG_EXPLOSION, 0);

    smallExplosionBitmap = al_load_bitmap(SMALL_EXPLOSION);
    if(!smallExplosionBitmap)
        ShowError(SMALL_EXPLOSION, 0);

    baseBitmap = al_load_bitmap(BASE_BITMAP);
    if(!baseBitmap)
        ShowError(BASE_BITMAP, 0);

    baseDamageBitmap = al_load_bitmap(BASE_DESTROY);
    if(!baseDamageBitmap)
        ShowError(BASE_DESTROY, 0);

    bonusBitmap = al_load_bitmap(BONUS_BITMAP);
    if(!bonusBitmap)
        ShowError(BONUS_BITMAP, 0);

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

    background = al_load_bitmap(BACKGROUND_BITMAP);
    if(!background)
        ShowError(BACKGROUND_BITMAP, 0);

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
    al_convert_mask_to_alpha(bonusBitmap, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(baseBitmap, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(explosionBitmap, al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(smallExplosionBitmap, al_map_rgb(0, 0, 0));
};

void FontsInitialize()
{
    font30 = al_load_ttf_font(MAIN_FONT, 20, 4);
    if(!font30)
        ShowError(MAIN_FONT, 0);

    font60 = al_load_ttf_font(MAIN_FONT, 60, 4);
    if(!font60)
        ShowError(MAIN_FONT, 0);

    campaignFont = al_load_ttf_font(CAMPAIGN_FONT, 72, 4);
    if(!campaignFont)
        ShowError(CAMPAIGN_FONT, 0);

    hudFont = al_load_ttf_font(HUD_FONT, 30, 4);
    if(!hudFont)
        ShowError(HUD_FONT, 0);

    pauseFont = al_load_ttf_font(HUD_FONT, 72, 4);
    if(!pauseFont)
        ShowError(HUD_FONT, 0);
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
    case 3:
    {
        sprintf(message, "Campaign file is corrupted");
        break;
    }
    }

    al_show_native_message_box(display, "Error", "Error occurred", message, NULL, ALLEGRO_MESSAGEBOX_ERROR);
    ClearMemory();
}

void ClearMemory()
{
    for (short i = 0; i < BONUSES; i++)
    {
        delete bonus[i];
    }

    for (short i = 0; i < EXPLOSIONS; i++)
    {
        delete explosion[i];
    }

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
    delete[] bonus;
    delete[] explosion;
    delete[] wall;
    delete[] playerCampaign;

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

    if(explosionBitmap)
        al_destroy_bitmap(explosionBitmap);

    if(smallExplosionBitmap)
        al_destroy_bitmap(smallExplosionBitmap);

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

    if(background)
        al_destroy_bitmap(background);

    if(baseBitmap)
        al_destroy_bitmap(baseBitmap);

    if(baseDamageBitmap)
        al_destroy_bitmap(baseDamageBitmap);

    if(bonusBitmap)
        al_destroy_bitmap(bonusBitmap);

    if(font30)
        al_destroy_font(font30);

    if(font60)
        al_destroy_font(font60);

    if(hudFont)
        al_destroy_font(hudFont);

    if(pauseFont)
        al_destroy_font(pauseFont);

    if(campaignFont)
        al_destroy_font(campaignFont);

    for (short t = 0; t < SOUNDS; t++)
    {
        if(sound[t])
            al_destroy_sample(sound[t]);
    }

    if(display)
        al_destroy_display(display);

    exit(0);
}
