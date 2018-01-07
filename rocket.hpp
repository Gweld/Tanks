#ifndef ROCKET_H_INCLUDED
#define ROCKET_H_INCLUDED

#include "wall.hpp"
#include "player.hpp"
#include "config.hpp"

class Rocket
{
private:
    short x;
    short y;
    short direction;
    bool team;
    bool visible;
    short speed;

public:
    Rocket():
        visible(0),
        speed(0)		{}

    static short rocketsCounter[2];

    short getX();
    void setX( short _x);

    short getY();
    void setY( short _y);

    short getDirection();
    void setDirection( short _direction);

    bool getTeam();
    void setTeam( bool _team);

    bool getVisible();
    void setVisible( bool _visible);

    short getSpeed();
    void setSpeed( short _speed);

    void rocketOff();
    void checkColision(Rocket ** rocket, Wall ** sciany, Player *player, Enemy ** enemy, Explosion ** explosion, Bonus ** bonus);
    void move(Rocket ** rocket, Wall ** sciany, Player *player, Enemy ** enemy, Explosion ** explosion, Bonus ** bonus);
    void shoot(Player * player);
    void createSmallExplosion(Explosion ** explosion);
    void createBigExplosion(Explosion ** explosion, short _x, short _y);
    void hitWall(Wall ** sciany, short choice);
    void hitPlayer(Player * player);
    void hitEnemy(Enemy ** enemy, Player * player, short choice);
    void hitRocket(Rocket ** rocket, short choice);
};

short GiveRocketID(Rocket **rocket);
void ClearRocket(Rocket ** rocket);

#endif
