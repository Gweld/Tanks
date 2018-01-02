#include "enemy.hpp"
#include "config.hpp"
#include "allegroconfig.hpp"
#include "main.hpp"
#include "aStar.hpp"
#include <cstdlib>
#include <cstdio>
#include <string>

short Enemy::getX()
{
    return x;
};

void Enemy::setX(short _x)
{
    x = _x;
};

short Enemy::getTempX()
{
    return tempX;
};

void Enemy::setTempX( short _tempX)
{
    tempX = _tempX;
};

short Enemy::getY()
{
    return y;
};

void Enemy::setY( short _Y)
{
    y = _Y;
};

short Enemy::getTempY()
{
    return tempY;
};

void Enemy::setTempY( short _tempY)
{
    tempY = _tempY;
};

bool Enemy::getColision()
{
    return colision;
};

void Enemy::setColision( bool _colision)
{
    colision = _colision;
};

short Enemy::getDirection()
{
    return direction;
};

void Enemy::setDirection( short _direction)
{
    direction = _direction;
};

short Enemy::getLife()
{
    return life;
};

void Enemy::setLife(short _life)
{
    life = _life;
};

bool Enemy::getDead()
{
    return dead;
};

void Enemy::setDead( bool _dead)
{
    dead = _dead;
};

bool Enemy::getCanShoot()
{
    return canShoot;
};

void Enemy::setCanShoot( bool _canShoot)
{
    canShoot = _canShoot;
};

short Enemy::getAmmoSpeed()
{
    return ammoSpeed;
};

void Enemy::setAmmoSpeed( short _ammoSpeed)
{
    ammoSpeed = _ammoSpeed;
};

short Enemy::getTempDirection()
{
    return tempDirection;
};

void Enemy::setTempDirection( short _tempDirection)
{
    tempDirection = _tempDirection;
};

short Enemy::getDirectionCounter()
{
    return directionCounter;
};

void Enemy::setDirectionCounter( short _directionCounter)
{
    directionCounter = _directionCounter;
};

short Enemy::getDestinationX()
{
    return destinationX;
};

void Enemy::setDestinationX(short _destinationX)
{
    destinationX = _destinationX;
};

short Enemy::getDestinationY()
{
    return destinationY;
};

void Enemy::setDestinationY(short _destinationY)
{
    destinationY = _destinationY;
};

bool Enemy::getTargetAhead()
{
    return targetAhead;
};

void Enemy::setTargetAhead(bool _targetAhead)
{
    targetAhead = _targetAhead;
};

short Enemy::getAmmoTimer()
{
    return ammoTimer;
};

void Enemy::setAmmoTimer( short _ammoTimer)
{
    ammoTimer = _ammoTimer;
};

short Enemy::getAmmoDelay()
{
    return ammoDelay;
};

void Enemy::setAmmoDelay( short _ammoDelay)
{
    ammoDelay = _ammoDelay;
};

short Enemy::getRespawnDelayTimer()
{
    return respawnDelayTimer;
};

void Enemy::setRespawnDelayTimer( short _respawnDelayTimer)
{
    respawnDelayTimer = _respawnDelayTimer;
};

short Enemy::getDifficulty()
{
    return difficulty;
};

void Enemy::setDifficulty( short _difficulty)
{
    difficulty = _difficulty;
};

bool Enemy::getStop()
{
    return stop;
}

void Enemy::setStop( bool _stop)
{
    stop = _stop;
}

short Enemy::getTempDestinationX()
{
    return tempDestinationX;
}

void Enemy::setTempDestinationX(short _tempDestinationX)
{
    tempDestinationX = _tempDestinationX;
}

short Enemy::getTempDestinationY()
{
    return tempDestinationY;
}

void Enemy::setTempDestinationY( short _tempDestinationY)
{
    tempDestinationY = _tempDestinationY;
}

short Enemy::getWallID()
{
    return wallID;
}

void Enemy::setWallID( short _wallID)
{
    wallID = _wallID;
}

bool Enemy::getWallAtPath()
{
    return wallAtPath;
}

void Enemy::setWallAtPath( bool _wallAtPath)
{
    wallAtPath = _wallAtPath;
}

bool Enemy::getFirstmovement()
{
    return firstmovement;
}

void Enemy::setFirstmovement( bool _firstmovement)
{
    firstmovement = _firstmovement;
}

bool Enemy::getAttack()
{
    return attack;
}

void Enemy::setAttack( bool _attack)
{
    attack = _attack;
}

short GiveEnemyID(Enemy **enemy)
{
    short temp = 0;
    for(short i=0; i<  ENEMIES; i++)
    {
        if(enemy[i] -> getDead())
        {
            temp = i;
            break;
        }
    }
    return temp;
};