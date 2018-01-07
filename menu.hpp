#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "player.hpp"

void MenuDisplay();
void Menu();
void HighscoreMenu();
void InputNick();
void HighscoreLoad();
void HighscoreSave(short mode, Player * player);
void HighscoreDisplay(short mode);

#endif 
