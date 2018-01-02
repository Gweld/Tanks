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
extern ALLEGRO_DISPLAY *display;

extern ALLEGRO_CONFIG* iniFile;

extern ALLEGRO_BITMAP *surviveButton;
extern ALLEGRO_BITMAP *baseDefenceButton;
extern ALLEGRO_BITMAP *campaignButton;
extern ALLEGRO_BITMAP *highscoreButton;
extern ALLEGRO_BITMAP *exitButton;
extern ALLEGRO_BITMAP *backButton;
extern ALLEGRO_BITMAP *okButton;

extern unsigned short gameMode;

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
                    //HighscoreMenu();
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
