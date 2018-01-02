#ifndef EXPLODE_H_INCLUDED
#define EXPLODE_H_INCLUDED

#include "wall.hpp"

class Explosion : public Wall
{
private:
    bool smallExplosion;
    short animationHeight;
    short animationWidth;

public:
    Explosion():
        smallExplosion(false),
        animationHeight(0),
        animationWidth(0)		{}

    short getX();
    void setX( short _x);

    short getY();
    void setY( short _y);

    short getLife();
    void setLife( short _life);

    short getAnimationHeight();
    void setAnimationHeight( short _animationHeight);

    short getAnimationWidth();
    void setAnimationWidth( short _animationWidth);

    bool getVisible();
    void setVisible( bool _visible);

    bool getSmall();
    void setSmall( bool _smallExplosion);

    void createExplosion();

};

short GiveExplosionID(Explosion **explosion);
void ClearExplosion(Explosion **explosion);

#endif
