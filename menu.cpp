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
#include <string>
#include "config.hpp"
#include "menu.hpp"
#include "main.hpp"
#include "allegroconfig.hpp"

extern ALLEGRO_KEYBOARD_STATE keyboard;
extern ALLEGRO_FONT * font30;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT * font60;
extern ALLEGRO_FONT * hudFont;

extern ALLEGRO_BITMAP *surviveButton;
extern ALLEGRO_BITMAP *baseDefenceButton;
extern ALLEGRO_BITMAP *campaignButton;
extern ALLEGRO_BITMAP *highscoreButton;
extern ALLEGRO_BITMAP *exitButton;
extern ALLEGRO_BITMAP *backButton;
extern ALLEGRO_BITMAP *okButton;

extern ALLEGRO_CONFIG* iniFile;

extern unsigned short gameMode;

int highscore[3][10] = {0};
char highscoreNick[3][10][7];
char nick[7];

void MenuDisplay()
{
    al_clear_to_color( al_map_rgb(0,0,153) );
    al_draw_bitmap (surviveButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 100, 0);
    al_draw_bitmap (baseDefenceButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 190, 0);
    al_draw_bitmap (campaignButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 280, 0);
    al_draw_bitmap (highscoreButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 370, 0);
    al_draw_bitmap (exitButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 460, 0);
    al_flip_display();
};

void Menu()
{
    al_show_mouse_cursor( display );
    MenuDisplay();
    ALLEGRO_EVENT_QUEUE *EventQueue = NULL;
    ALLEGRO_EVENT Event;
    EventQueue = al_create_event_queue();
    al_register_event_source(EventQueue, al_get_mouse_event_source());
    al_register_event_source(EventQueue, al_get_keyboard_event_source());

    while(1)
    {
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);
        bool get_event = al_wait_for_event_until(EventQueue, &Event, &timeout);

        if(get_event)
        {
            if(Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 100) && (Event.mouse.y <= 100 + MENU_BUTTON_HEIGHT))
                {
                    al_hide_mouse_cursor( display );
                    gameMode = 0;
                    al_destroy_event_queue(EventQueue);
                    break;
                }
                else if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 190) && (Event.mouse.y <= 190 + MENU_BUTTON_HEIGHT))
                {
                    al_hide_mouse_cursor( display );
                    gameMode = 1;
                    al_destroy_event_queue(EventQueue);
                    break;
                }
                else if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 280) && (Event.mouse.y <= 280 + MENU_BUTTON_HEIGHT))
                {
                    al_hide_mouse_cursor( display );
                    gameMode = 2;
                    al_destroy_event_queue(EventQueue);
                    break;
                }
                else if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 370) && (Event.mouse.y <= 370 + MENU_BUTTON_HEIGHT))
                {
                    al_destroy_event_queue(EventQueue);
                    HighscoreMenu();
                    break;
                }

                else if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 460) && (Event.mouse.y <= 460 + MENU_BUTTON_HEIGHT))
                {
                    al_destroy_event_queue(EventQueue);
                    ClearMemory();
                    break;
                }
            }

            else if(Event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                al_destroy_event_queue(EventQueue);
                ClearMemory();
                break;
            }
        }
    }
};

void HighscoreMenu()
{
    al_clear_to_color( al_map_rgb(0,0,153) );
    al_draw_bitmap (surviveButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 100, 0);
    al_draw_bitmap (baseDefenceButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 190, 0);
    al_draw_bitmap (campaignButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 280, 0);
    al_draw_bitmap (backButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 450, 0);
    al_draw_textf( font30, HIGHSCORE_COLOR, SCREEN_WIDTH - 75, SCREEN_HEIGHT - 30, ALLEGRO_ALIGN_CENTRE, VERSION);
    al_flip_display();

    ALLEGRO_EVENT_QUEUE *EventQueue = NULL;
    ALLEGRO_EVENT Event;
    EventQueue = al_create_event_queue();
    al_register_event_source(EventQueue, al_get_mouse_event_source());

    while(1)
    {
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);

        bool get_event = al_wait_for_event_until(EventQueue, &Event, &timeout);

        if(get_event)
        {
            if(Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 100) && (Event.mouse.y <= 100 + MENU_BUTTON_HEIGHT))
                {
                    al_destroy_event_queue(EventQueue);
                    HighscoreDisplay(0);
                    break;
                }
                else if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 190) && (Event.mouse.y <= 190 + MENU_BUTTON_HEIGHT))
                {
                    al_destroy_event_queue(EventQueue);
                    HighscoreDisplay(1);
                    break;
                }
                else if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 280) && (Event.mouse.y <= 280 + MENU_BUTTON_HEIGHT))
                {
                    al_destroy_event_queue(EventQueue);
                    HighscoreDisplay(2);
                    break;
                }
                else if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 450) && (Event.mouse.y <= 450 + MENU_BUTTON_HEIGHT))
                {
                    al_destroy_event_queue(EventQueue);
                    Menu();
                    break;
                }
            }
        }
    }
};

void InputNick()
{
    std::string edittext;
    std::string::iterator iter = edittext.begin();
    bool insert = true;
    bool ready=false;
    short i=0; //max 5 sign

    ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
    al_register_event_source( event_queue, al_get_keyboard_event_source() );
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_show_mouse_cursor( display );
    al_clear_to_color( al_map_rgb(0,0,153) );
    al_draw_text( font60, HIGHSCORE_COLOR, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 100, ALLEGRO_ALIGN_CENTRE, "Your nickname:");
    al_draw_text(font60, al_map_rgb(255,255,255), SCREEN_WIDTH/2,SCREEN_HEIGHT/2,ALLEGRO_ALIGN_CENTRE,edittext.c_str());
    al_draw_bitmap (okButton, SCREEN_WIDTH/2 - 240, 600, 0);
    al_flip_display();

    ALLEGRO_EVENT ev;
    do
    {
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            int  newkey   = ev.keyboard.unichar;
            char ASCII    = newkey & 0xff;
            char scancode = ev.keyboard.keycode;

            if(ASCII > 32 && ASCII < 126)
            {
                if(insert || iter == edittext.end())
                {
                    if(i < 5)
                    {
                        iter = edittext.insert(iter, ASCII);
                        i++;
                        iter++;
                    }
                }
            }
            else
                switch(scancode)
                {
                case ALLEGRO_KEY_ENTER:
                {
                    ready=true;
                    break;
                }
                case ALLEGRO_KEY_BACKSPACE:
                    if(iter != edittext.begin())
                    {
                        iter--;
                        i--;
                        iter = edittext.erase(iter);
                        al_clear_to_color( al_map_rgb(0,0,153) );
                        al_flip_display();
                    }
                    break;

                default:
                    break;
                }
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if((ev.mouse.x >= SCREEN_WIDTH/2 - 240) && (ev.mouse.x <= SCREEN_WIDTH/2 + MENU_BUTTON_WIDTH - 240) &&
                    (ev.mouse.y >= 600) && (ev.mouse.y <= 600 + MENU_BUTTON_HEIGHT))
            {
                ready=true;
            }
        }
        al_clear_to_color( al_map_rgb(0,0,153) );
        al_draw_text( font60, HIGHSCORE_COLOR, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 100, ALLEGRO_ALIGN_CENTRE, "Your nickname:");
        al_draw_text(font60, al_map_rgb(255,255,255), SCREEN_WIDTH/2,SCREEN_HEIGHT/2,ALLEGRO_ALIGN_CENTRE,edittext.c_str());
        al_draw_bitmap (okButton, SCREEN_WIDTH/2 - 240, 600, 0);
        al_flip_display();
    }
    while(!ready);

    al_destroy_event_queue(event_queue);
    sprintf(nick, "%s", edittext.c_str());
}

void HighscoreLoad()
{
    char message[16];
    const char *value;
    char* type;

    iniFile = al_load_config_file(HIGHSCORE);
    if(!iniFile)
        ShowError(HIGHSCORE, 0);

    for(short j = 0; j < 3 ; j++)
    {
        if(j == 0)
            type = "survive";
        else if (j == 1)
            type = "baseDefense";
        else if(j == 2)
            type = "campaign";

        for(short i = 0; i < 10; i++)
        {
            sprintf(message, "number%i", i+ 1);
            value=al_get_config_value(iniFile, type, message);
            highscore[j][i] = atoi(value);
            sprintf(message, "nick%i", i+ 1);
            value=al_get_config_value(iniFile, type, message);
            sprintf(highscoreNick[j][i], "%s", value);
        }
    }
    al_destroy_config(iniFile);
};

void HighscoreSave(short mode, Player * player)
{
    char numberX[16], points[16], nick[16];
    bool isHighscore = false;
    char* type;

    iniFile = al_load_config_file(HIGHSCORE);
    if(!iniFile)
        ShowError(HIGHSCORE, 0);

    if(mode == 0)
        type = "survive";
    else if (mode == 1)
        type = "baseDefense";
    else if(mode == 2)
        type = "campaign";

    for(short i=0; i < 10; i++)
    {
        sprintf(numberX, "number%i", i+ 1);
        sprintf(nick, "nick%i", i+ 1);
        if(player -> getPoints() > highscore[mode][i])
        {
            InputNick();
            sprintf(points, "%i",player -> getPoints());
            al_set_config_value(iniFile, type, numberX, points);
            al_set_config_value(iniFile, type, nick, nick);
            for(short y=i; y < 9; y++)
            {
                sprintf(numberX, "number%i", y+2);
                sprintf(points, "%i",highscore[mode][y]);
                al_set_config_value(iniFile, type, numberX, points);
                sprintf(nick, "nick%i", y+2);
                al_set_config_value(iniFile, type, nick, highscoreNick[mode][y]);
            }
            isHighscore=true;
            break;
        }
        if(!isHighscore)
        {
            sprintf(points, "%i",highscore[mode][i]);
            al_set_config_value(iniFile, type, numberX, points);
            al_set_config_value(iniFile, type, nick, highscoreNick[mode][i]);
        }

    }
    al_save_config_file(HIGHSCORE,iniFile);
    al_destroy_config(iniFile);
    HighscoreLoad();
};

void HighscoreDisplay(short mode)
{
    al_clear_to_color( al_map_rgb(0,0,153) );
    al_draw_textf( hudFont, HIGHSCORE_COLOR, 100, 20, ALLEGRO_ALIGN_CENTRE, "RANK: ");
    al_draw_textf( hudFont, HIGHSCORE_COLOR, 400, 20, ALLEGRO_ALIGN_CENTRE, "NAME: ");
    al_draw_textf( hudFont, HIGHSCORE_COLOR, 800, 20, ALLEGRO_ALIGN_CENTRE, "POINTS: ");

    for(short i=0; i < 10; i++)
    {
        al_draw_textf( hudFont, HIGHSCORE_COLOR, 100, 70+(i*55), ALLEGRO_ALIGN_CENTRE, "%i", i + 1);
        al_draw_textf( hudFont, HIGHSCORE_COLOR, 400, 70+(i*55), ALLEGRO_ALIGN_CENTRE, "%s", highscoreNick[mode][i]);
        al_draw_textf( hudFont, HIGHSCORE_COLOR, 800, 70+(i*55), ALLEGRO_ALIGN_CENTRE, "%i", highscore[mode][i]);
    }
    al_draw_bitmap (backButton, SCREEN_WIDTH/2 - MENU_BUTTON_SPACE, 620, 0);
    al_flip_display();

    ALLEGRO_EVENT_QUEUE *EventQueue = NULL;
    ALLEGRO_EVENT Event;
    EventQueue = al_create_event_queue();
    al_register_event_source(EventQueue, al_get_mouse_event_source());

    while(1)
    {
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.03);

        bool get_event = al_wait_for_event_until(EventQueue, &Event, &timeout);

        if(get_event)
        {
            if(Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                if((Event.mouse.x >= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE) && (Event.mouse.x <= SCREEN_WIDTH/2 - MENU_BUTTON_SPACE + MENU_BUTTON_WIDTH) &&
                        (Event.mouse.y >= 640) && (Event.mouse.y <= 640 + MENU_BUTTON_HEIGHT))
                {
                    al_destroy_event_queue(EventQueue);
                    HighscoreMenu();
                    break;
                }
            }
        }
    }
};
