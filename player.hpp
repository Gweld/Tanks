#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "wall.hpp"
#include "bonus.hpp"

class Enemy;
class Wall;
class Bonus;

class Player
{
private:
    short kills;
    int points;
    bool active;

protected:
    short shoots;
    short ammoSpeed;
    short direction;
    short x;
    short y;
    short tempX;
    short tempY;
    short life;
    short ammoTimerDelay;

public:
    Player():
        kills(0),
        points(0),
        shoots(1),
        ammoSpeed(0),
        direction(0),
        ammoTimerDelay(0)		{}

    void operator =( const Player &_playerCampaign ) //to store info for campaign
    {
        kills = _playerCampaign.kills;
        points = _playerCampaign.points;
        shoots = _playerCampaign.shoots;
        ammoSpeed = _playerCampaign.ammoSpeed;
        life = _playerCampaign.life;
        ammoTimerDelay = _playerCampaign.ammoTimerDelay;
    }

    static unsigned short ammoTimer;

    short getX();
    void setX(short _x);

    short getY();
    void setY( short _y);

    short getTempX();
    void setTempX( short _tempX);

    short getTempY();
    void setTempY( short _tempY);

    short getDirection();
    void setDirection( short _direction);

    short getLife();
    void setLife( short _life);

    short getKills();
    void setKills( short _kills);

    int getPoints();
    void setPoints(int _points);

    bool getActive();
    void setActive( bool _active);

    short getShoots();
    void setShoots( short _shoots);

    short getAmmoSpeed();
    void setAmmoSpeed( short _ammoSpeed);

    short getAmmoTimer();
    void setAmmoTimer( short _ammoTimerDelay);

    void initialize(short _x, short _y, short _life, short _shoots, short _direction, short _ammoSpeed, int _points, short _kills, short _ammoTimerDelay);
    void campaingInitialize(short _currentLevel);
    void move(short _where);

    void clear();

    void checkColision(Wall **wall, Enemy **enemy, Bonus **bonus);
};

#endif
