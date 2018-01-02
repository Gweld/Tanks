#ifndef BONUSKI_H_INCLUDED
#define BONUSKI_H_INCLUDED

#include "explosion.hpp"

class Enemy;

class Bonus : public Wall
{
public:
    short getX();
    void setX( short _x);

    short getY();
    void setY( short _y);

    bool getVisible();
    void setVisible( bool _visible);
};

short GiveBonusID(Bonus ** bonus);
void Airstrike(Enemy ** enemy, Explosion ** explosion, Bonus ** bonus, Player *player);
void ClearBonus(Bonus ** bonus);

#endif
