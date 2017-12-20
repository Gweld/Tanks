#ifndef TESTASTAR_H_INCLUDED
#define TESTASTAR_H_INCLUDED

#include <string>

std::string FindPath(Enemy **enemy, Wall **wall, Player * player, short choice, bool onlyImmortal, bool isPlayer);

#endif
