#include "player.hpp"
#include "main.hpp"
#include "config.hpp"
#include "enemy.hpp"
#include "allegroconfig.hpp"
#include <stdio.h>


extern ALLEGRO_CONFIG* iniFile;
extern Player * playerCampaign;

short Player::getX()
{
    return x;
};

void Player::setX(short _x)
{
    x = _x;
};

short Player::getTempX()
{
    return tempX;
};

void Player::setTempX( short _tempX)
{
    tempX = _tempX;
};

short Player::getY()
{
    return y;
};

void Player::setY( short _y)
{
    y = _y;
};

short Player::getTempY()
{
    return tempY;
};

void Player::setTempY( short _tempY)
{
    tempY = _tempY;
};

short Player::getDirection()
{
    return direction;
};

void Player::setDirection( short _direction)
{
    direction = _direction;
};

short Player::getLife()
{
    return life;
};

void Player::setLife(short _life)
{
    life = _life;
};

int Player::getPoints()
{
    return points;
};

void Player::setPoints(int _points)
{
    points = _points;
};

short Player::getKills()
{
    return kills;
};

void Player::setKills(short _kills)
{
    kills = _kills;
};

bool Player::getActive()
{
    return active;
};

void Player::setActive( bool _active)
{
    active = _active;
};

short Player::getShoots()
{
    return shoots;
};

void Player::setShoots( short _shoots)
{
    shoots = _shoots;
};

short Player::getAmmoSpeed()
{
    return ammoSpeed;
};

void Player::setAmmoSpeed( short _ammoSpeed)
{
    ammoSpeed = _ammoSpeed;
};

short Player::getAmmoTimer()
{
    return ammoTimerDelay;
};

void Player::setAmmoTimer( short _ammoTimerDelay)
{
    ammoTimerDelay = _ammoTimerDelay;
};

void Player::initialize(short _x, short _y, short _life, short _shoots, short _direction, short _ammoSpeed, int _points, short _kills, short _ammoTimerDelay)
{
    x = _x/50 * 50;
    tempX = x;
    y = _y/50 * 50;
    tempY = y;
    life = _life;
    shoots = _shoots;
    direction = _direction;
    ammoSpeed = _ammoSpeed;
    points = _points;
    kills = _kills;
    active = true;
    ammoTimerDelay = _ammoTimerDelay;
};

void Player::campaingInitialize(short _currentLevel)
{
    char levelName[15];
    sprintf(levelName, "level%i.tank", _currentLevel);

    iniFile = al_load_config_file(levelName);
    if(!iniFile)
        ShowError(levelName, 0);

    if(_currentLevel == 1)
    {
        x = atoi(al_get_config_value(iniFile, "player", "x"))/50 * 50;
        y = atoi(al_get_config_value(iniFile, "player", "y"))/50 * 50;
        life = atoi(al_get_config_value(iniFile, "player", "life"));
        shoots = atoi(al_get_config_value(iniFile, "player", "shoots"));
        direction = atoi(al_get_config_value(iniFile, "player", "direction"));
        ammoSpeed = atoi(al_get_config_value(iniFile, "player", "ammoSpeed"));
        ammoTimerDelay = atoi(al_get_config_value(iniFile, "player", "ammoTimerDelay"));
        points = 0;
        kills = 0;
    }
    else
    {
        * this = * playerCampaign;
        x = atoi(al_get_config_value(iniFile, "player", "x"))/50 * 50;
        y = atoi(al_get_config_value(iniFile, "player", "y"))/50 * 50;
        direction = atoi(al_get_config_value(iniFile, "player", "direction"));
    }
    tempX = x;
    tempY = y;
    active = true;

    al_destroy_config(iniFile);
}

void Player::clear()
{
    x = 0;
    tempX = 0;
    y = 0;
    tempY = 0;
    life = 0;
    shoots = 1;
    direction = 0;
    ammoSpeed = 0;
    points = 0;
    kills = 0;
    active = false;
    ammoTimerDelay = 0;
    Player::ammoTimer = 0;
};

void Player::move(short _where)
{
    switch(_where)
    {
    case 0: //prawo
    {
        direction = 0;
        tempX = x;
        x += TANK_SPEED;

        if(x > BATTLEFIELD_WIDTH)
            x = tempX;

        break;
    }
    case 1://lewo
    {
        direction = 1;
        tempX = x;
        x -= TANK_SPEED;

        if(x < 0)
            x = tempX;

        break;
    }
    case 2: //dol
    {
        direction = 2;
        tempY = y;
        y += TANK_SPEED;

        if(y > BATTLEFIELD_HEIGHT)
            y = tempY;

        break;
    }
    case 3: //gora
    {
        direction = 3;
        tempY = y;
        y -= TANK_SPEED;

        if(y < 0)
            y = tempY;

        break;
    }
    }
};

void Player::checkColision(Wall **wall, Enemy **enemy, Bonus **bonus)
{
    bool collision = false;//only can collide with one thing, so if player has collision we can leave function

    for (short i=0; i < OBSTACLES ; i++)
    {
        if(wall[i] -> getVisible())
        {
            if(x >= wall[i] -> getX() - OBSTACLE_SIZE + MARGIN_SIZE && x <= wall[i] -> getX() + OBSTACLE_SIZE - MARGIN_SIZE && y >= wall[i]->getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= wall[i]->getY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                x = tempX;
                y = tempY;
                collision = true;
                break;
            }
        }
    }

    for(short g=0; g < ENEMIES && !collision; g++)
    {
        if(!enemy[g] -> getDead())
        {
            if(x >= enemy[g] -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=enemy[g] -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= enemy[g] -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= enemy[g] -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                x = tempX;
                y = tempY;
                collision = true;
                break;
            }
        }
    }
    for (short i=0; i < BONUSES && !collision ; i++)
    {
        if(bonus[i]->getVisible())
        {
            if(x >= bonus[i]->getX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=bonus[i]->getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= bonus[i]->getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= bonus[i]->getY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                RandomBonus();
                bonus[i] -> setVisible(false);
                break;
            }
        }
    }
};
