#include "explosion.hpp"
#include "config.hpp"

short Explosion::getX()
{
    return x;
};

void Explosion::setX( short _x)
{
    x = _x;
};

short Explosion::getY()
{
    return y;
};
void Explosion::setY( short _y)
{
    y = _y;
};

short Explosion::getAnimationHeight()
{
    return animationHeight;
};
void Explosion::setAnimationHeight( short _animationHeight)
{
    animationHeight = _animationHeight;
};

short Explosion::getAnimationWidth()
{
    return animationWidth;
};
void Explosion::setAnimationWidth( short _animationWidth)
{
    animationWidth = _animationWidth;
};

bool Explosion::getVisible()
{
    return visible;
};

void Explosion::setVisible( bool _visible)
{
    visible = _visible;
};

short Explosion::getLife()
{
    return life;
};

void Explosion::setLife( short _life)
{
    life = _life;
};

bool Explosion::getSmall()
{
    return smallExplosion;
};

void Explosion::setSmall( bool _smallExplosion)
{
    smallExplosion = _smallExplosion;
};

void Explosion::createExplosion()
{
    if(visible)
    {
        life --;

        if(life == 0)
            visible = false;
    }
};

short GiveExplosionID(Explosion **explosion)
{
    short countExplosions=0;
    for(short i=0; i<EXPLOSIONS; i++)
    {
        if(!explosion[i] -> getVisible())
        {
            countExplosions=i;
            break;
        }
    }
    return countExplosions;
};

void ClearExplosion(Explosion **explosion)
{
    for(short i=0; i<EXPLOSIONS; i++)
    {
        explosion[i] -> setX(0);
        explosion[i] -> setY(0);
        explosion[i] -> setVisible(false);
        explosion[i] -> setAnimationHeight(0);
        explosion[i] -> setAnimationWidth(0);
        explosion[i] -> setLife(0);
        explosion[i] -> setSmall(false);
    }
}
