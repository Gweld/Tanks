#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_windows.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void Play();
void RandomBonus();
void InitializeVariables();
void InitializeGame();
void GameMenu();
void ClearVariables();
void ModeGuardian();
void CampaignMapCreate();

#endif
