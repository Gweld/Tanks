#include "enemy.hpp"
#include "config.hpp"
#include "allegroconfig.hpp"
#include "main.hpp"
#include "aStar.hpp"
#include <cstdlib>
#include <cstdio>
#include <string>

extern ALLEGRO_CONFIG* iniFile;
extern ALLEGRO_SAMPLE *sound[SOUNDS];
extern short enemiesAtOnce;
extern short enemies;
extern short enemiesKilled;
extern bool start;
extern bool gameover;
extern unsigned short gameMode;

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

void Enemy::setPlayerCoord(Enemy **enemy, Player * player)
{
    short playerX = player -> getX();
    short playerY = player -> getY();

    Enemy::playerDirection = player -> getDirection();

    for(short g = 0; g < ENEMIES; g++)
    {
        if(!enemy[g] -> getDead())
        {
            if(!enemy[g] -> getAttack() || (Enemy::attackBase[g] == 0 && Wall::baseExist == true))
            {
                enemy[g] -> setDestinationX(playerX);
                enemy[g] -> setDestinationY(playerY);
            }
        }
    }
}

void SetBaseCoord(Enemy ** enemy, Wall **wall, short choice)
{
    short baseX = wall[Wall::baseID] -> getX();
    short baseY = wall[Wall::baseID] -> getY();

    Enemy::baseCoord[0] = baseX;
    Enemy::baseCoord[1] = baseY;

    for(short g = 0; g < ENEMIES; g++)
    {
        if(!enemy[g] -> getDead())
        {
            if(!enemy[g] -> getAttack() && Enemy::attackBase[g] == 1 && Wall::baseExist == true)
            {
                enemy[choice] -> setDestinationX(baseX);
                enemy[choice] -> setDestinationY(baseY);
            }
        }
    }
}

void ClearEnemy(Enemy **enemy)
{
    for(short g = 0; g < ENEMIES; g++)
    {
        enemy[g] -> setTempX(0);
        enemy[g] -> setTempY(0);
        enemy[g] -> setDirection(0);
        enemy[g] -> setLife(0);
        enemy[g] -> setColision(false);
        enemy[g] -> setX(0);
        enemy[g] -> setY(0);
        enemy[g] -> setAmmoSpeed(0);
        enemy[g] -> setDead(true);
        enemy[g] -> setAmmoTimer(0);
        enemy[g] -> setAmmoDelay(0);
        enemy[g] -> setRespawnDelayTimer(0);
        enemy[g] -> setDifficulty(0);
        enemy[g] -> setTempDirection(0);
        enemy[g] -> setDirectionCounter(0);
        enemy[g] -> setCanShoot(true);
        enemy[g] -> setTargetAhead(false);
        enemy[g] -> setStop(false);
        enemy[g] -> setTempDestinationY(0);
        enemy[g] -> setTempDestinationX(0);
        enemy[g] -> setWallAtPath(false);
        enemy[g] -> setFirstmovement(false);
        enemy[g] -> setAttack(false);
        enemy[g] -> setDestinationX(0);
        enemy[g] -> setDestinationY(0);
        enemy[g] -> setWallID(0);
    }

    Enemy::playerTimer = 0;
    Enemy::hasPlayer = false;
    Enemy::hasBase = false;
    Enemy::baseCoord[0] = 0;
    Enemy::baseCoord[1] = 0;
}

void ClearPlayerArray(Wall ** wall)
{
    for(short i=0; i< REAL_BATTLEFIELD_WIDTH; i++)
        for(short j=0; j< REAL_BATTLEFIELD_HEIGHT; j++)
        {
            Enemy::isPlayer[i][j] = 0;
        }

    SetImmortallWallsVisible(wall);
}

void EnemycampaingInitialize(Enemy ** enemy, short currentLevel, Wall **wall, Player *player)
{
    char message[16];
    char levelName[15];
    short choice;

    sprintf(levelName, "level%i.tank", currentLevel);

    iniFile = al_load_config_file(levelName);
    if(!iniFile)
        ShowError(levelName, 0);

    enemies = atoi(al_get_config_value(iniFile, "options", "enemies"));
    if(enemies == 0)
        ShowError("error", 3);

    enemiesAtOnce = atoi(al_get_config_value(iniFile, "options", "enemiesAtOnce"));
    if(enemiesAtOnce == 0)
        ShowError("error", 3);

    for(short g = 1; g <= enemiesAtOnce; g++)
    {
        sprintf(message, "enemyNR%i", g);
        choice = GiveEnemyID(enemy);
        enemy[choice] -> setDirection(atoi(al_get_config_value(iniFile, message, "direction")));
        enemy[choice] -> setLife(atoi(al_get_config_value(iniFile, message, "life")));
        enemy[choice] -> setColision(true);
        enemy[choice] -> setStop(false);
        enemy[choice] -> setX(atoi(al_get_config_value(iniFile, message, "x"))/TANK_SIZE * TANK_SIZE);
        enemy[choice] -> setY(atoi(al_get_config_value(iniFile, message, "y"))/TANK_SIZE * TANK_SIZE);
        enemy[choice] -> setAmmoSpeed(atoi(al_get_config_value(iniFile, message, "ammoSpeed")));
        enemy[choice] -> setAmmoDelay(atoi(al_get_config_value(iniFile, message, "ammoDelay")));
        enemy[choice] -> setDifficulty(atoi(al_get_config_value(iniFile, message, "difficulty")));
        enemy[choice] -> setTempDestinationY(0);
        enemy[choice] -> setTempDestinationX(0);
        enemy[choice] -> setWallAtPath(false);
        enemy[choice] -> setFirstmovement(false);
        enemy[choice] -> setAmmoTimer(0);
        enemy[choice] -> setTempDirection(0);
        enemy[choice] -> setDirectionCounter(0);
        enemy[choice] -> setCanShoot(true);
        enemy[choice] -> setTargetAhead(false);
        enemy[choice] -> setAttack(false);
        enemy[choice] -> setDestinationX(0);
        enemy[choice] -> setDestinationY(0);
        enemy[choice] -> setWallID(0);
        enemy[choice] -> setRespawnDelayTimer(0);

        while(enemy[choice] -> getColision())
        {
            enemy[choice] -> checkPlace(wall, player, enemy);

            if(!enemy[choice] -> getColision())
                break;

            enemy[choice] -> setX(rand()%(BATTLEFIELD_WIDTH)/TANK_SIZE * TANK_SIZE);
            enemy[choice] -> setY(rand()%(BATTLEFIELD_HEIGHT)/TANK_SIZE * TANK_SIZE);
        }

        enemy[choice] -> setTempX(enemy[choice] -> getX());
        enemy[choice] -> setTempY(enemy[choice] -> getY());
        enemy[choice] -> setDead(false);
    }
    SetTarget(enemy, player);
    al_destroy_config(iniFile);
}

void EnemyCampaignDrop(Enemy ** enemy, short currentLevel, Wall **wall, Player *player)
{
    char message[16];
    char levelName[15];
    short choice;

    sprintf(levelName, "level%i.tank", currentLevel);

    iniFile = al_load_config_file(levelName);
    if(!iniFile)
        ShowError(levelName, 0);

    for(short g = enemiesKilled + CheckEnemyAlive(enemy) ; g < enemiesAtOnce + enemiesKilled; g++)
    {
        if( enemiesKilled + CheckEnemyAlive(enemy) < enemies )
        {
            sprintf(message, "enemyNR%i", g + 1);
            choice = GiveEnemyID(enemy);
            enemy[choice] -> setDirection(atoi(al_get_config_value(iniFile, message, "direction")));
            enemy[choice] -> setLife(atoi(al_get_config_value(iniFile, message, "life")));
            enemy[choice] -> setColision(true);
            enemy[choice] -> setStop(false);
            enemy[choice] -> setX(atoi(al_get_config_value(iniFile, message, "x"))/TANK_SIZE * TANK_SIZE);
            enemy[choice] -> setY(atoi(al_get_config_value(iniFile, message, "y"))/TANK_SIZE * TANK_SIZE);
            enemy[choice] -> setAmmoSpeed(atoi(al_get_config_value(iniFile, message, "ammoSpeed")));
            enemy[choice] -> setAmmoDelay(atoi(al_get_config_value(iniFile, message, "ammoDelay")));
            enemy[choice] -> setDifficulty(atoi(al_get_config_value(iniFile, message, "difficulty")));
            enemy[choice] -> setTempDestinationY(0);
            enemy[choice] -> setTempDestinationX(0);
            enemy[choice] -> setWallAtPath(false);
            enemy[choice] -> setFirstmovement(false);
            enemy[choice] -> setAmmoTimer(0);
            enemy[choice] -> setTempDirection(0);
            enemy[choice] -> setDirectionCounter(0);
            enemy[choice] -> setCanShoot(true);
            enemy[choice] -> setTargetAhead(false);
            enemy[choice] -> setAttack(false);
            enemy[choice] -> setDestinationX(0);
            enemy[choice] -> setDestinationY(0);
            enemy[choice] -> setWallID(0);
            enemy[choice] -> setRespawnDelayTimer(0);

            while(enemy[choice] -> getColision())
            {
                enemy[choice] -> checkPlace(wall, player, enemy);

                if(!enemy[choice] -> getColision())
                    break;

                enemy[choice] -> setX(rand()%(BATTLEFIELD_WIDTH)/TANK_SIZE * TANK_SIZE);
                enemy[choice] -> setY(rand()%(BATTLEFIELD_HEIGHT)/TANK_SIZE * TANK_SIZE);
            }

            enemy[choice] -> setTempX(enemy[choice] -> getX());
            enemy[choice] -> setTempY(enemy[choice] -> getY());
            enemy[choice] -> setDead(false);
        }
    }
    SetTarget(enemy, player);

    al_destroy_config(iniFile);
}

void Enemy::spawn(short _x, short _y, short _life, short _ammoSpeed, short _direction, short _ammoDelay, short _difficulty, Wall **wall, Player * player, Enemy **enemy)
{
    direction = _direction;
    life = _life;
    x = (_x/TANK_SIZE) *TANK_SIZE;
    y = (_y/TANK_SIZE) *TANK_SIZE;
    ammoSpeed = _ammoSpeed;
    colision = true;
    ammoDelay = _ammoDelay;
    difficulty = _difficulty;
    stop = false;
    canShoot = true;
    tempDirection = 0;
    directionCounter = 0;
    destinationX = 0;
    destinationY = 0;
    targetAhead = false;
    wallAtPath = false;
    firstmovement = false;
    ammoTimer = 0;
    tempDestinationX = 0;
    tempDestinationY = 0;
    respawnDelayTimer = 0;
    attack = false;
    wallID = 0;

    while(colision == true)
    {
        this -> checkPlace(wall, player, enemy);

        if(!colision)
            break;

        x = ((rand()%(BATTLEFIELD_WIDTH))/TANK_SIZE) *TANK_SIZE;
        x = ((rand()%(BATTLEFIELD_HEIGHT))/TANK_SIZE) *TANK_SIZE;
    }

    tempX = x;
    tempY = y;
    dead = false;
    SetTarget(enemy, player);
};

void Enemy::checkPlace(Wall **wall, Player * player, Enemy **enemy)
{
    bool kolizja=false;
    for (short i=0; i<OBSTACLES ; i++)
    {
        if(wall[i] -> getVisible())
        {
            if(wall[i] -> getBase())//more space when it is base
            {
                if(x > wall[i] -> getX() - (3*FREE_SPACE) && x < wall[i] -> getX() + OBSTACLE_SIZE + (3*FREE_SPACE))
                    if(y + OBSTACLE_SIZE > wall[i] -> getY() - (3*FREE_SPACE) && y < wall[i] -> getY() + OBSTACLE_SIZE + (3*FREE_SPACE))
                    {
                        kolizja = true;
                        break;
                    }
            }
            else
            {
                if(x > wall[i] -> getX() - OBSTACLE_SIZE && x < wall[i] -> getX() + OBSTACLE_SIZE )
                    if(y + OBSTACLE_SIZE > wall[i] -> getY() && y < wall[i] -> getY() + OBSTACLE_SIZE )
                    {
                        kolizja = true;
                        break;
                    }
            }
        }
    }

    if(player->getActive() && !kolizja)
    {
        if(x > player -> getX() - FREE_SPACE && x < player -> getX() + TANK_SIZE + FREE_SPACE)
            if(y + TANK_SIZE > player -> getY() - FREE_SPACE && y < player -> getY() + TANK_SIZE + FREE_SPACE)
                kolizja = true;
    }

    for(short j=0; j < ENEMIES && !kolizja; j++)
    {
        if(!enemy[j] -> getDead() && this != enemy[j])
        {
            if(x > enemy[j] -> getX() - FREE_SPACE && x < enemy[j] -> getX() + TANK_SIZE + FREE_SPACE)
                if(y + TANK_SIZE > enemy[j] -> getY() - FREE_SPACE && y < enemy[j] -> getY() + TANK_SIZE + FREE_SPACE)
                {
                    kolizja = true;
                    break;
                }
        }
    }

    if (kolizja)
        colision = true;
    else
        colision = false;
};

short Enemy::checkCollision(Wall **wall, Player * player, Enemy **enemy, Bonus **bonus)
{
    if(!dead)
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->getVisible())
            {
                if(x >= wall[i]->getX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=wall[i]->getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= wall[i]->getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= wall[i]->getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    x = tempX;
                    y = tempY;

                    if(wall[i]->getDestroyable())
                    {
                        if(wall[i]->getBase())
                        {
                            stop = true;
                            return 5; //base
                        }
                        else
                            return 3; //destroyable
                    }
                    else
                        return 1;  //immortal wall
                }
            }
        }

        if(player->getActive())
        {
            if(x >= player -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=player -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                x = tempX;
                y = tempY;
                stop = true;
                return 4;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> getDead() && this!=enemy[j])
            {
                if(x >= enemy[j] -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=enemy[j] -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= enemy[j] -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= enemy[j] -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    x = tempX;
                    y = tempY;
                    return 2;
                }
            }
        }

        for (short i=0; i<BONUSES ; i++)
        {
            if(bonus[i]->getVisible())
            {
                if(x >= bonus[i]->getX()-OBSTACLE_SIZE+MARGIN_SIZE && x<=bonus[i]->getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= bonus[i]->getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= bonus[i]->getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                    bonus[i]->setVisible(false);
            }
        }
    }

    return 0;
};

short CheckEnemyAlive(Enemy **enemy)
{
    short temp=0;
    for(short i=0; i<ENEMIES; i++)
    {
        if(!enemy[i]->getDead())
        {
            temp++;
        }
    }
    return temp;
}

bool Enemy::checkAimWall(Wall **wall, Enemy ** enemy)
{
    if(!dead)
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->getVisible() && wall[i] -> getDestroyable() && !wall[i] -> getBase())
            {
                switch(direction)
                {
                case 0:
                {
                    if(x <= wall[i] -> getX() && y + 21 >= wall[i] -> getY() - ROCKET_Y  && y + 21 <= wall[i] -> getY() + OBSTACLE_SIZE)
                    {
                        bool value = this -> checkAimImmortallWall(wall, wall[i] -> getX(), wall[i] -> getY());
                        bool valueF = this -> checkAimEnemy(enemy, wall[i] -> getX(), wall[i] -> getY());

                        if(value == true && valueF == true)
                        {
                            wallID = i;
                            return true;
                        }
                    }
                    break;
                }
                case 1:
                {
                    if(x >= wall[i] -> getX() && y + 21 >= wall[i] -> getY() - ROCKET_Y  && y + 21 <= wall[i] -> getY() + OBSTACLE_SIZE)
                    {
                        bool value = this -> checkAimImmortallWall(wall, wall[i] -> getX(), wall[i] -> getY());
                        bool valueF = this -> checkAimEnemy(enemy, wall[i] -> getX(), wall[i] -> getY());

                        if(value == true && valueF == true)
                        {
                            wallID = i;
                            return true;
                        }
                    }
                    break;
                }
                case 2://dol
                {
                    if(x + 21 >= wall[i] -> getX() - ROCKET_Y && x + 21 <= wall[i] -> getX() + OBSTACLE_SIZE && y <= wall[i] -> getY())
                    {
                        bool value = this -> checkAimImmortallWall(wall, wall[i] -> getX(), wall[i] -> getY());
                        bool valueF = this -> checkAimEnemy(enemy, wall[i] -> getX(), wall[i] -> getY());

                        if(value == true && valueF == true)
                        {
                            wallID = i;
                            return true;
                        }
                    }
                    break;
                }
                case 3:
                {
                    if(x + 29 >= wall[i] -> getX() - ROCKET_Y && x + 29 <= wall[i] -> getX() + OBSTACLE_SIZE && y >= wall[i] -> getY())
                    {
                        bool value = this -> checkAimImmortallWall(wall, wall[i] -> getX(), wall[i] -> getY());
                        bool valueF = this -> checkAimEnemy(enemy, wall[i] -> getX(), wall[i] -> getY());

                        if(value == true && valueF == true)
                        {
                            wallID = i;
                            return true;
                        }
                    }
                    break;
                }
                }
            }
        }
    }
    return false;
}

bool Enemy::checkAimImmortallWall(Wall **wall, short _x, short _y)
{
    bool clearWay = true; //can shoot?
    if(!dead)
    {
        for (short i=0; i<OBSTACLES && clearWay == true; i++)
        {
            if(wall[i]->getVisible() && !wall[i] -> getDestroyable() && !wall[i] -> getBase())
            {
                switch(direction)
                {
                case 0:
                {
                    if(x <= wall[i] -> getX() && y + 21 >= wall[i] -> getY() - ROCKET_Y  && y + 21 <= wall[i] -> getY() + OBSTACLE_SIZE)
                    {
                        if(wall[i] -> getX() < _x)
                            clearWay = false;
                    }

                    break;
                }
                case 1:
                {
                    if(x >= wall[i] -> getX() && y + 21 >= wall[i] -> getY() - ROCKET_Y  && y + 21 <= wall[i] -> getY() + OBSTACLE_SIZE)
                    {
                        if(wall[i] -> getX() > _x)
                            clearWay = false;
                    }

                    break;
                }
                case 2://down
                {
                    if(x + 21 >= wall[i] -> getX() - ROCKET_Y && x + 21 <= wall[i] -> getX() + OBSTACLE_SIZE && y <= wall[i] -> getY())
                    {
                        if(wall[i] -> getY() < _y)
                            clearWay = false;
                    }

                    break;
                }
                case 3:
                {
                    if(x + 29 >= wall[i] -> getX() - ROCKET_Y && x + 29 <= wall[i] -> getX() + OBSTACLE_SIZE && y >= wall[i] -> getY())
                    {
                        if(wall[i] -> getY() > _y)
                            clearWay = false;
                    }

                    break;
                }
                }
            }
        }
    }
    return clearWay;
}

bool Enemy::checkAimPlayer(Player *player, Enemy ** enemy, Wall ** wall)
{
    if(!dead)
    {
        if(player -> getActive())
        {
            switch(direction)
            {
            case 0:
            {
                if(x <= player -> getX() && y + 21 >= player -> getY() - ROCKET_Y  && y + 21 <= player -> getY() + TANK_SIZE)
                {
                    bool value = this -> checkAimImmortallWall(wall, player -> getX(), player -> getY());
                    bool valueF = this -> checkAimEnemy(enemy, player -> getX(), player -> getY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 1:
            {
                if(x >= player -> getX() && y + 21 >= player -> getY() - ROCKET_Y  && y + 21 <= player -> getY() + TANK_SIZE)
                {
                    bool value = this -> checkAimImmortallWall(wall, player -> getX(), player -> getY());
                    bool valueF = this -> checkAimEnemy(enemy, player -> getX(), player -> getY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 2://dol
            {
                if(x + 21 >= player -> getX() - ROCKET_Y && x + 21 <= player -> getX() + TANK_SIZE && y <= player -> getY())
                {
                    bool value = this -> checkAimImmortallWall(wall, player -> getX(), player -> getY());
                    bool valueF = this -> checkAimEnemy(enemy, player -> getX(), player -> getY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 3:
            {
                if(x + 29 >= player -> getX() - ROCKET_Y && x + 29 <= player -> getX() + TANK_SIZE && y >= player -> getY())
                {
                    bool value = this -> checkAimImmortallWall(wall, player -> getX(), player -> getY());
                    bool valueF = this -> checkAimEnemy(enemy, player -> getX(), player -> getY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            }
        }
    }
    return false;
}

bool Enemy::checkAimBase(Wall **wall, short id, Enemy ** enemy)
{
    if(!dead)
    {
        if(wall[id] -> getBase() && wall[id] -> getVisible())
        {
            switch(direction)
            {
            case 0:
            {
                if(x <= wall[id] -> getX() && y + 21 >= wall[id] -> getY() - ROCKET_Y  && y + 21 <= wall[id] -> getY() + OBSTACLE_SIZE)
                {
                    bool value = this -> checkAimImmortallWall(wall, wall[id] -> getX(), wall[id] -> getY());
                    bool valueF = this -> checkAimEnemy(enemy, wall[id] -> getX(), wall[id] -> getY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 1:
            {
                if(x >= wall[id] -> getX() && y + 21 >= wall[id] -> getY() - ROCKET_Y  && y + 21 <= wall[id] -> getY() + OBSTACLE_SIZE)
                {
                    bool value = this -> checkAimImmortallWall(wall, wall[id] -> getX(), wall[id] -> getY());
                    bool valueF = this -> checkAimEnemy(enemy, wall[id] -> getX(), wall[id] -> getY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 2://dol
            {
                if(x + 21 >= wall[id] -> getX() - ROCKET_Y && x + 21 <= wall[id] -> getX() + OBSTACLE_SIZE && y <= wall[id] -> getY())
                {
                    bool value = this -> checkAimImmortallWall(wall, wall[id] -> getX(), wall[id] -> getY());
                    bool valueF = this -> checkAimEnemy(enemy, wall[id] -> getX(), wall[id] -> getY());

                    if(value == true && valueF == true)
                        return true;
                }

                break;
            }
            case 3:
            {
                if(x + 29 >= wall[id] -> getX() - ROCKET_Y && x + 29 <= wall[id] -> getX() + OBSTACLE_SIZE && y >= wall[id] -> getY())
                {
                    bool value = this -> checkAimImmortallWall(wall, wall[id] -> getX(), wall[id] -> getY());
                    bool valueF = this -> checkAimEnemy(enemy, wall[id] -> getX(), wall[id] -> getY());

                    if(value == true && valueF == true)
                        return true;
                }
                break;
            }
            }
        }
    }
    return false;
}

bool Enemy::checkAimEnemy(Enemy **enemy, short _x, short _y)
{
    bool clearWay = true; //czy mozna strzelac czy nie
    if(!dead)
    {
        for (short i=0; i<ENEMIES ; i++)
        {
            if(!enemy[i]->getDead() && enemy[i] != this)
            {
                switch(direction)
                {
                case 0:
                {
                    if(x <= enemy[i] -> getX() && y + 21 >= enemy[i] -> getY() - ROCKET_Y  && y + 21 <= enemy[i] -> getY() + TANK_SIZE)
                    {
                        if(enemy[i] -> getX() < _x)
                            clearWay = false;
                    }

                    break;
                }
                case 1:
                {
                    if(x >= enemy[i] -> getX() && y + 21 >= enemy[i] -> getY() - ROCKET_Y  && y + 21 <= enemy[i] -> getY() + TANK_SIZE)
                    {
                        if(enemy[i] -> getX() > _x)
                            clearWay = false;
                    }

                    break;
                }
                case 2://dol
                {
                    if(x + 21 >= enemy[i] -> getX() - ROCKET_Y && x + 21 <= enemy[i] -> getX() + TANK_SIZE && y <= enemy[i] -> getY())
                    {
                        if(enemy[i] -> getY() < _y)
                            clearWay = false;
                    }
                    break;
                }
                case 3:
                {
                    if(x + 29 >= enemy[i] -> getX() - ROCKET_Y && x + 29 <= enemy[i] -> getX() + TANK_SIZE && y >= enemy[i] -> getY())
                    {
                        if(enemy[i] -> getY() > _y)
                            clearWay = false;
                    }

                    break;
                }
                }
            }
        }
    }
    return clearWay;
}

bool Enemy::searchForDirection()
{
    switch(id % 4)
    {
    case 0:
    {
        for(short i=0; i< BATTLEFIELD_WIDTH; i++) //x
            for(short j=0; j< BATTLEFIELD_HEIGHT; j++)
            {
                if(Enemy::isPlayer[i][j] < 2)
                {
                    destinationX = i;
                    destinationY = j;
                    return true;
                }
            }
        break;
    }
    case 1:
    {
        for(short i=BATTLEFIELD_WIDTH-1; i >= 0; i--)
            for(short j=BATTLEFIELD_HEIGHT-1; j >= 0; j--)
            {
                if(Enemy::isPlayer[i][j] < 2)
                {
                    destinationX = i;
                    destinationY = j;
                    return true;
                }
            }
        break;
    }

    case 2:
    {
        for(short i=BATTLEFIELD_WIDTH-1; i >= 0; i--)
            for(short j=1; j< BATTLEFIELD_HEIGHT; j++)
            {
                if(Enemy::isPlayer[i][j] < 2)
                {
                    destinationX = i;
                    destinationY = j;
                    return true;
                }
            }
        break;
    }

    case 3:
    {
        for(short i=0; i< BATTLEFIELD_WIDTH; i++)
            for(short j=BATTLEFIELD_HEIGHT-1; j>= 0; j--)
            {
                if(Enemy::isPlayer[i][j] < 2)
                {
                    destinationX = i;
                    destinationY = j;
                    return true;
                }
            }
        break;
    }

    }

    return false;
}

void Enemy::checkForBase(Wall ** wall, Enemy ** enemy)
{
    if(Enemy::hasBase == false)
    {
        for(short i=0; i < OBSTACLES && Enemy::hasBase == false; i++)
        {
            if(wall[i] -> getBase() && wall[i] -> getVisible())
            {
                for (short k = 0 ; k < 4 && Enemy::hasBase == false; k++)
                {
                    if(k == 0)
                    {
                        short j= wall[i] -> getY();
                        for (short k = wall[i] -> getX() ; k <= wall[i] -> getX() + OBSTACLE_SIZE && Enemy::hasBase == false; k++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if( Enemy::isPlayer[k][j] == 4)
                            {
                                Enemy::hasBase = true;
                                Wall::baseID = i;
                                SetBaseCoord(enemy, wall, 0);
                            }
                        }
                    }
                    else if(k == 1)
                    {
                        short j= wall[i] -> getY() + OBSTACLE_SIZE;
                        for (short k = wall[i] -> getX() ; k <= wall[i] -> getX() + OBSTACLE_SIZE && Enemy::hasBase == false; k++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if( Enemy::isPlayer[k][j] == 4)
                            {
                                Enemy::hasBase = true;
                                Wall::baseID = i;
                                SetBaseCoord(enemy, wall,0);
                            }
                        }
                    }
                    else if(k == 2)
                    {
                        short k= wall[i] -> getX();
                        for (short j = wall[i] -> getY(); j <= wall[i] -> getY() + OBSTACLE_SIZE && Enemy::hasBase == false ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if( Enemy::isPlayer[k][j] == 4)
                            {
                                Enemy::hasBase = true;
                                Wall::baseID = i;
                                SetBaseCoord(enemy, wall,0);
                            }
                        }
                    }
                    else if(k == 3)
                    {
                        short k= wall[i] -> getX() + OBSTACLE_SIZE;
                        for (short j = wall[i] -> getY(); j <= wall[i] -> getY() + OBSTACLE_SIZE && Enemy::hasBase == false ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if( Enemy::isPlayer[k][j] == 4)
                            {
                                Enemy::hasBase = true;
                                Wall::baseID = i;
                                SetBaseCoord(enemy, wall,0);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Enemy::checkForPlayer(Player *player, Enemy **enemy)
{
    bool detected = false;
    for (short k = 0 ; k < 4 && !detected && player -> getActive(); k++)
    {
        if(k == 0)
        {
            short j = player -> getY();
            for(short i = player -> getX() ; i <= player -> getX() + TANK_SIZE && !detected; i++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[i][j] == 3)
                {
                    Enemy::hasPlayer = true;
                    Enemy::playerTimer = 0;
                    detected = true;
                    this -> setPlayerCoord(enemy, player);
                    break;
                }
            }
        }
        else if(k == 1)
        {
            short j= player -> getY() + TANK_SIZE;
            for(short i = player -> getX() ; i <= player -> getX() + TANK_SIZE && !detected; i++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[i][j] == 3)
                {
                    Enemy::hasPlayer = true;
                    Enemy::playerTimer = 0;
                    detected = true;
                    this -> setPlayerCoord(enemy, player);
                    break;
                }
            }
        }
        else if(k == 2)
        {
            short i= player -> getX();
            for(short j = player -> getY() ; j <= player -> getY() + TANK_SIZE && !detected; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[i][j] == 3)
                {
                    Enemy::hasPlayer = true;
                    Enemy::playerTimer = 0;
                    detected = true;
                    this -> setPlayerCoord(enemy, player);
                    break;
                }
            }
        }
        else if(k == 3)
        {
            short i= player -> getX() + TANK_SIZE;
            for(short j = player -> getY() ; j <= player -> getY() + TANK_SIZE && !detected; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[i][j] == 3)
                {
                    Enemy::hasPlayer = true;
                    Enemy::playerTimer = 0;
                    detected = true;
                    this -> setPlayerCoord(enemy, player);
                    break;
                }
            }
        }
    }
}

bool Enemy::checkDirection(short direction, Wall ** wall, Enemy ** enemy, Player *player, short moves)
{
    switch(direction)
    {
    case 0:
    {
        if(x + TANK_SPEED > BATTLEFIELD_WIDTH)
            return false;

        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->getVisible())
            {
                if(x + (moves*TANK_SPEED) >= wall[i]->getX()-OBSTACLE_SIZE+MARGIN_SIZE && x + (moves*TANK_SPEED) <=wall[i]->getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= wall[i]->getY()-OBSTACLE_SIZE+MARGIN_SIZE && y <= wall[i]->getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    if(wall[i]->getDestroyable())
                    {
                        if(wall[i]->getBase())
                        {
                            targetAhead = true;
                            stop = true;
                            return true; //baza
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
        }

        if(player->getActive())
        {
            if(x + (moves*TANK_SPEED) >= player -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x + (moves*TANK_SPEED) <=player -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                targetAhead = true;
                stop = true;
                return true;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> getDead() && this!=enemy[j])
            {
                if(x + (moves*TANK_SPEED) >= enemy[j] -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x + (moves*TANK_SPEED) <=enemy[j] -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= enemy[j] -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= enemy[j] -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    return false;
                }
            }
        }

        break;
    }
    case 1:
    {
        if(x - TANK_SPEED < 0)
            return false;

        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->getVisible())
            {
                if(x - (moves*TANK_SPEED) >= wall[i]->getX()-OBSTACLE_SIZE+MARGIN_SIZE && x - (moves*TANK_SPEED) <=wall[i]->getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= wall[i]->getY()-OBSTACLE_SIZE+MARGIN_SIZE && y <= wall[i]->getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    if(wall[i]->getDestroyable())
                    {
                        if(wall[i]->getBase())
                        {
                            targetAhead = true;
                            stop = true;
                            return true; //baza
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
        }

        if(player->getActive())
        {
            if(x - (moves*TANK_SPEED) >= player -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x - (moves*TANK_SPEED)<=player -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                targetAhead = true;
                stop = true;
                return true;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> getDead() && this!=enemy[j])
            {
                if(x - (moves*TANK_SPEED) >= enemy[j] -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x - (moves*TANK_SPEED)<=enemy[j] -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= enemy[j] -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= enemy[j] -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    return false;
                }
            }
        }

        break;
    }
    case 2:
    {
        if(y + (moves*TANK_SPEED) > BATTLEFIELD_HEIGHT)
            return false;

        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->getVisible())
            {
                if(x >= wall[i]->getX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=wall[i]->getX()+OBSTACLE_SIZE-MARGIN_SIZE && y + (moves*TANK_SPEED) >= wall[i]->getY()-OBSTACLE_SIZE+MARGIN_SIZE && y + (moves*TANK_SPEED) <= wall[i]->getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    if(wall[i]->getDestroyable())
                    {
                        if(wall[i]->getBase())
                        {
                            targetAhead = true;
                            stop = true;
                            return true; //baza
                        }
                        else
                            return false; //destroyable
                    }
                    else
                        return false;  //immortal
                }
            }
        }

        if(player->getActive())
        {
            if(x >= player -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=player -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y + (moves*TANK_SPEED) >= player -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y + (moves*TANK_SPEED)<= player -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                targetAhead = true;
                stop = true;
                return true;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> getDead() && this!=enemy[j])
            {
                if(x >= enemy[j] -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=enemy[j] -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y + (moves*TANK_SPEED) >= enemy[j] -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y + (moves*TANK_SPEED)<= enemy[j] -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    return false;
                }
            }
        }

        break;
    }
    case 3:
    {
        if(y - (moves*TANK_SPEED) < 0)
            return false;

        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i]->getVisible())
            {
                if(x >= wall[i]->getX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=wall[i]->getX()+OBSTACLE_SIZE-MARGIN_SIZE && y - (moves*TANK_SPEED) >= wall[i]->getY()-OBSTACLE_SIZE+MARGIN_SIZE && y - (moves*TANK_SPEED) <= wall[i]->getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    if(wall[i]->getDestroyable())
                    {
                        if(wall[i]->getBase())
                        {
                            targetAhead = true;
                            stop = true;
                            return true; //baza
                        }
                        else
                            return false; //zniszczalna
                    }
                    else
                        return false;  //niezniszczalna
                }
            }
        }

        if(player->getActive())
        {
            if(x >= player -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=player -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y - (moves*TANK_SPEED) >= player -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y - (moves*TANK_SPEED)<= player -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
            {
                targetAhead = true;
                stop = true;
                return true;
            }
        }

        for(short j=0; j<ENEMIES; j++)
        {
            if(!enemy[j] -> getDead() && this!=enemy[j])
            {
                if(x >= enemy[j] -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=enemy[j] -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y - (moves*TANK_SPEED) >= enemy[j] -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y - (moves*TANK_SPEED)<= enemy[j] -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                {
                    return false;
                }
            }
        }

        break;
    }
    }

    return true;
}

void Enemy::shoot(Rocket ** rocket)
{
    canShoot = false;
    ammoTimer = 1;

    if(Rocket::rocketsCounter[1] < ENEMY_MAX_SHOOTS)
    {
        short choice=GiveRocketID(rocket);

        switch(direction)
        {
        case 0:
        {
            rocket[choice] -> setDirection(0);
            rocket[choice] -> setX(x + 51);
            rocket[choice] -> setY(y + 21);

            break; //right
        }
        case 1:
        {
            rocket[choice] -> setDirection(1);
            rocket[choice] -> setX(x - 16);
            rocket[choice] -> setY(y + 21);

            break; //left
        }
        case 2:
        {
            rocket[choice] -> setDirection(2);
            rocket[choice] -> setX(x + 21);
            rocket[choice] -> setY(y + 60);

            break; //down
        }
        case 3:
        {
            rocket[choice] -> setDirection(3);
            rocket[choice] -> setX(x + 29);
            rocket[choice] -> setY(y - 14);

            break; //up
        }
        }
        Rocket::rocketsCounter[1]++;
        rocket[choice] -> setSpeed(ammoSpeed);
        rocket[choice] -> setVisible(true);
        rocket[choice] -> setTeam(false);

        al_play_sample(sound[0], 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }
}

void Enemy::checkNearbyArea(Wall ** wall, Enemy ** enemy, Player * player)
{
    switch(direction)
    {
    case 0:
    {
        for (short i=0; i < OBSTACLES ; i++)
        {
            if(wall[i] -> getVisible())
            {
                if( (wall[i] -> getX() + OBSTACLE_SIZE) < x - VIEW_RANGE ) //1 wall is too far behind
                    continue;

                if(wall[i] -> getY() + OBSTACLE_SIZE <  y - VIEW_RANGE) //2 enemy is under wall
                    continue;

                if(wall[i] -> getY() >  y + VIEW_RANGE + TANK_SIZE)                 //3 enemy is up the wall
                    continue;

                //1 condition wall at left
                //2 condition complete wall in sight
                //3 wall at right

                if((wall[i] -> getY() < y - VIEW_RANGE) && (wall[i] -> getY() + OBSTACLE_SIZE > y - VIEW_RANGE) && (wall[i] -> getX() + MARGIN_SIZE >= x + TANK_SIZE)) // 1. z gory wystaje ale widac przed czolgiem
                {
                    //behind wall we set 1
                    for(int k = wall[i] -> getX() + OBSTACLE_SIZE - MARGIN_SIZE ; k < REAL_BATTLEFIELD_WIDTH ; k++ )
                        for(int j = y - VIEW_RANGE ; j <= wall[i] -> getY() + OBSTACLE_SIZE + MARGIN_SIZE ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }

                else if((wall[i] -> getY() > y - VIEW_RANGE) && (wall[i] -> getY() + OBSTACLE_SIZE < y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> getX() + MARGIN_SIZE >= x + OBSTACLE_SIZE)) //2. cala widac
                {
                    if(wall[i] -> getX() < x + TANK_SIZE + BLIND_RANGE)
                    {
                        for(int k = wall[i] -> getX() + OBSTACLE_SIZE - MARGIN_SIZE ; k < REAL_BATTLEFIELD_WIDTH ; k++ )
                            for(int j = wall[i] -> getY() - VIEW_RANGE ; j <= wall[i] -> getY() + OBSTACLE_SIZE + VIEW_RANGE ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                    else
                    {
                        for(int k = wall[i] -> getX() + OBSTACLE_SIZE - MARGIN_SIZE ; k < REAL_BATTLEFIELD_WIDTH ; k++ )
                            for(int j = wall[i] -> getY() - MARGIN_SIZE ; j <= wall[i] -> getY() + OBSTACLE_SIZE + MARGIN_SIZE ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                }
                else if((wall[i] -> getY() < y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> getY() + OBSTACLE_SIZE > y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> getX() + MARGIN_SIZE >= x + OBSTACLE_SIZE))
                {
                    for(int k = wall[i] -> getX() + OBSTACLE_SIZE - MARGIN_SIZE ; k < REAL_BATTLEFIELD_WIDTH ; k++ )
                        for(int j = wall[i] -> getY() - MARGIN_SIZE ; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
            }
        }

        for (short k = x - VIEW_RANGE ; k < REAL_BATTLEFIELD_WIDTH ; k++)
        {
            for (short j = y - VIEW_RANGE; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || k < 0)
                    continue;

                if(Enemy::isPlayer[k][j] == 0 || Enemy::isPlayer[k][j] == 4)
                    Enemy::isPlayer[k][j] = 3;
            }
        }

        this -> checkForPlayer(player, enemy);

        for (short i= x - VIEW_RANGE ; i < REAL_BATTLEFIELD_WIDTH ; i++)
            for (short j = y - VIEW_RANGE; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[j][i] == 2 || Enemy::isPlayer[j][i] == 3)
                    Enemy::isPlayer[j][i] = 4;
                else if(Enemy::isPlayer[j][i] == 1)
                    Enemy::isPlayer[j][i] = 0;
            }
        break;
    }
    case 1:
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i] -> getVisible())
            {
                if( wall[i] -> getX() > x + VIEW_RANGE + TANK_SIZE)
                    continue;

                if(wall[i] -> getY() + OBSTACLE_SIZE <  y - VIEW_RANGE)
                    continue;

                if(wall[i] -> getY() >  y + VIEW_RANGE + TANK_SIZE)
                    continue;

                if((wall[i] -> getY() < y - VIEW_RANGE) && (wall[i] -> getY() + OBSTACLE_SIZE > y - VIEW_RANGE) && (wall[i] -> getX() + OBSTACLE_SIZE <= x + MARGIN_SIZE)) // 1. z gory ale widac przed czolgiem
                {
                    for(int k = wall[i] -> getX() + MARGIN_SIZE ; k > 0 ; k-- )
                        for(int j = y - VIEW_RANGE ; j <= wall[i] -> getY() + OBSTACLE_SIZE + MARGIN_SIZE ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }

                else if((wall[i] -> getY() > y - VIEW_RANGE) && (wall[i] -> getY() + OBSTACLE_SIZE < y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> getX() + OBSTACLE_SIZE <= x + MARGIN_SIZE))
                {
                    if(wall[i] -> getX() + OBSTACLE_SIZE > x - BLIND_RANGE)
                    {
                        for(int k = wall[i] -> getX() + MARGIN_SIZE ; k > 0 ; k-- )
                            for(int j = wall[i] -> getY() - VIEW_RANGE ; j <= wall[i] -> getY() + OBSTACLE_SIZE + VIEW_RANGE ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                    else
                    {
                        for(int k = wall[i] -> getX() + MARGIN_SIZE ; k > 0 ; k-- )
                            for(int j = wall[i] -> getY() - MARGIN_SIZE ; j <= wall[i] -> getY() + OBSTACLE_SIZE + MARGIN_SIZE ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                }
                else if((wall[i] -> getY() < y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> getY() + OBSTACLE_SIZE > y + VIEW_RANGE + TANK_SIZE) && (wall[i] -> getX() + OBSTACLE_SIZE <= x + MARGIN_SIZE))
                {
                    for(int k = wall[i] -> getX() + MARGIN_SIZE ; k >= 0 ; k-- )
                        for(int j = wall[i] -> getY() - MARGIN_SIZE ; j <= y + VIEW_RANGE + TANK_SIZE; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
            }
        }

        for (short k = x + TANK_SIZE + VIEW_RANGE ; k >= 0 ; k--)
        {
            for (short j = y - VIEW_RANGE; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || k < 0)
                    continue;

                if(Enemy::isPlayer[k][j] == 0 || Enemy::isPlayer[k][j] == 4)
                    Enemy::isPlayer[k][j] = 3;
            }
        }

        this -> checkForPlayer(player, enemy);

        for (short i = x + TANK_SIZE +VIEW_RANGE ; i >= 0 ; i--)
            for (short j = y - VIEW_RANGE; j <= y + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[j][i] == 2 || Enemy::isPlayer[j][i] == 3)
                    Enemy::isPlayer[j][i] = 4;
                else if(Enemy::isPlayer[j][i] == 1)
                    Enemy::isPlayer[j][i] = 0;
            }
        break;
    }
    case 2:
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i] -> getVisible())
            {
                if( wall[i] -> getY() + OBSTACLE_SIZE < y - VIEW_RANGE )
                    continue;

                if(wall[i] -> getX() + OBSTACLE_SIZE <  x - VIEW_RANGE)
                    continue;

                if(wall[i] -> getX() >  x + VIEW_RANGE + TANK_SIZE)
                    continue;

                if(wall[i] -> getX() < x - VIEW_RANGE && wall[i] -> getX() + OBSTACLE_SIZE > x - VIEW_RANGE && wall[i] -> getY() + MARGIN_SIZE >= y + TANK_SIZE)
                {
                    for(int k = x - VIEW_RANGE ; k <= wall[i] -> getX() + OBSTACLE_SIZE + MARGIN_SIZE ; k++ )
                        for(int j = wall[i] -> getY() + OBSTACLE_SIZE - MARGIN_SIZE ; j < REAL_BATTLEFIELD_HEIGHT ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
                else if(wall[i] -> getX() > x - VIEW_RANGE && wall[i] -> getX() + OBSTACLE_SIZE < x + TANK_SIZE + VIEW_RANGE && wall[i] -> getY() + MARGIN_SIZE >= y + TANK_SIZE)
                {
                    if(wall[i] -> getY() < y + TANK_SIZE + BLIND_RANGE )
                    {
                        for(int k = wall[i] -> getX() - VIEW_RANGE ; k <= wall[i] -> getX() + OBSTACLE_SIZE + VIEW_RANGE; k++ )
                            for(int j = wall[i] -> getY() + OBSTACLE_SIZE - MARGIN_SIZE ; j < REAL_BATTLEFIELD_HEIGHT ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                    else
                    {
                        for(int k = wall[i] -> getX() - MARGIN_SIZE ; k <= wall[i] -> getX() + OBSTACLE_SIZE + MARGIN_SIZE; k++ )
                            for(int j = wall[i] -> getY() + OBSTACLE_SIZE - MARGIN_SIZE ; j < REAL_BATTLEFIELD_HEIGHT ; j++)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                }
                else if(wall[i] -> getX() < x + TANK_SIZE + VIEW_RANGE && wall[i] -> getX() + OBSTACLE_SIZE > x + TANK_SIZE + VIEW_RANGE && wall[i] -> getY() + MARGIN_SIZE >= y + TANK_SIZE)
                {
                    for(int k = wall[i] -> getX() - MARGIN_SIZE ; k <= x + TANK_SIZE + VIEW_RANGE; k++ )
                        for(int j = wall[i] -> getY() + OBSTACLE_SIZE - MARGIN_SIZE ; j < REAL_BATTLEFIELD_HEIGHT ; j++)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
            }
        }

        for (short k = x - VIEW_RANGE ; k <= x + VIEW_RANGE + TANK_SIZE; k++)
        {
            for (short j = y - VIEW_RANGE; j < REAL_BATTLEFIELD_HEIGHT ; j++)
            {
                if(k < 0 || j < 0)
                    continue;

                if(Enemy::isPlayer[k][j] == 0 || Enemy::isPlayer[k][j] == 4)
                    Enemy::isPlayer[k][j] = 3;
            }
        }

        this -> checkForPlayer(player, enemy);

        for (short i= y - VIEW_RANGE ; i < REAL_BATTLEFIELD_HEIGHT ; i++)
            for (short j = x - VIEW_RANGE; j <= x + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(i < 0 || j < 0)
                    continue;

                if(Enemy::isPlayer[j][i] == 2 || Enemy::isPlayer[j][i] == 3)
                    Enemy::isPlayer[j][i] = 4;
                else if(Enemy::isPlayer[j][i] == 1)
                    Enemy::isPlayer[j][i] = 0;
            }
        break;
    }
    case 3:
    {
        for (short i=0; i<OBSTACLES ; i++)
        {
            if(wall[i] -> getVisible())
            {
                if( wall[i] -> getY() > y + VIEW_RANGE + TANK_SIZE)
                    continue;

                if(wall[i] -> getX() + OBSTACLE_SIZE <  x - VIEW_RANGE)
                    continue;

                if(wall[i] -> getX() >  x + VIEW_RANGE + TANK_SIZE)
                    continue;

                if(wall[i] -> getX() < x - VIEW_RANGE && wall[i] -> getX() + OBSTACLE_SIZE > x - VIEW_RANGE && wall[i] -> getY() + OBSTACLE_SIZE <= y + MARGIN_SIZE )
                {
                    for(int k = x - VIEW_RANGE ; k <= wall[i] -> getX() + OBSTACLE_SIZE + MARGIN_SIZE ; k++ )
                        for(int j = wall[i] -> getY() + MARGIN_SIZE ; j >= 0 ; j--)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
                else if(wall[i] -> getX() > x - VIEW_RANGE && wall[i] -> getX() + OBSTACLE_SIZE < x + TANK_SIZE + VIEW_RANGE && wall[i] -> getY() + OBSTACLE_SIZE <= y + MARGIN_SIZE )
                {
                    if(wall[i] -> getY() + OBSTACLE_SIZE > y - BLIND_RANGE )
                    {
                        for(int k = wall[i] -> getX() - VIEW_RANGE ; k <= wall[i] -> getX() + OBSTACLE_SIZE + VIEW_RANGE; k++ )
                            for(int j = wall[i] -> getY() + MARGIN_SIZE ; j >= 0 ; j--)
                            {
                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                    else
                    {
                        for(int k = wall[i] -> getX() - MARGIN_SIZE ; k <= wall[i] -> getX() + OBSTACLE_SIZE + MARGIN_SIZE; k++ )
                            for(int j = wall[i] -> getY() + MARGIN_SIZE ; j >= 0 ; j--)
                            {

                                if(j < 0 || k < 0)
                                    continue;

                                if(Enemy::isPlayer[k][j] == 0)
                                    Enemy::isPlayer[k][j] = 1;
                                else if(Enemy::isPlayer[k][j] == 4)
                                    Enemy::isPlayer[k][j] = 2;
                            }
                    }
                }
                else if(wall[i] -> getX() < x + TANK_SIZE + VIEW_RANGE && wall[i] -> getX() + OBSTACLE_SIZE > x + TANK_SIZE + VIEW_RANGE && wall[i] -> getY() + OBSTACLE_SIZE <= y + MARGIN_SIZE )
                {
                    for(int k = wall[i] -> getX() - MARGIN_SIZE ; k <= x + TANK_SIZE + VIEW_RANGE; k++ )
                        for(int j = wall[i] -> getY() + MARGIN_SIZE ; j >= 0 ; j--)
                        {
                            if(j < 0 || k < 0)
                                continue;

                            if(Enemy::isPlayer[k][j] == 0)
                                Enemy::isPlayer[k][j] = 1;
                            else if(Enemy::isPlayer[k][j] == 4)
                                Enemy::isPlayer[k][j] = 2;
                        }
                }
            }
        }

        for (short k = x - VIEW_RANGE ; k <= x + VIEW_RANGE + TANK_SIZE; k++)
        {
            for (short j = y + VIEW_RANGE; j >= 0 ; j--)
            {
                if(j < 0 || k < 0)
                    continue;

                if(Enemy::isPlayer[k][j] == 0 || Enemy::isPlayer[k][j] == 4)
                    Enemy::isPlayer[k][j] = 3;
            }
        }

        this -> checkForPlayer(player, enemy);

        for (short i= y + VIEW_RANGE ; i >= 0 ; i--)
            for (short j = x - VIEW_RANGE; j <= x + VIEW_RANGE + TANK_SIZE ; j++)
            {
                if(j < 0 || i < 0)
                    continue;

                if(Enemy::isPlayer[j][i] == 2 || Enemy::isPlayer[j][i] == 3)
                    Enemy::isPlayer[j][i] = 4;
                else if(Enemy::isPlayer[j][i] == 1)
                    Enemy::isPlayer[j][i] = 0;
            }

        break;
    }
    }
    this -> checkForBase(wall,enemy);
}

bool Enemy::checkPlayerFuture(short direction, Player *player, short moves)
{
    switch(direction)
    {
    case 0:
    {
        if(x + 2 > BATTLEFIELD_WIDTH)
            return false;

        if(player -> getActive())
        {
            if(x + (moves*2) >= player -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x + (moves*2) <=player -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                return true;
            else
                return false;
        }

        break;
    }
    case 1:
    {
        if(x - TANK_SPEED < 0)
            return false;

        if(player->getActive())
        {
            if(x - (moves*2) >= player -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x - (moves*2)<=player -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y >= player -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y<= player -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                return true;
            else
                return false;
        }


        break;
    }
    case 2:
    {
        if(y + (moves*2) > BATTLEFIELD_HEIGHT)
            return false;

        if(player->getActive())
        {
            if(x >= player -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=player -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y + (moves*2) >= player -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y + (moves*2)<= player -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                return true;
            else
                return false;
        }


        break;
    }
    case 3:
    {
        if(y - (moves*2) < 0)
            return false;

        if(player->getActive())
        {
            if(x >= player -> getX()-OBSTACLE_SIZE+MARGIN_SIZE && x <=player -> getX()+OBSTACLE_SIZE-MARGIN_SIZE && y - (moves*2) >= player -> getY()-OBSTACLE_SIZE+MARGIN_SIZE && y - (moves*2)<= player -> getY()+OBSTACLE_SIZE-MARGIN_SIZE)
                return true;
            else
                return false;
        }

        break;
    }
    }

    return true;
}

void Enemy::checkDestination(Wall ** wall)
{
    if (Enemy::isPlayer[destinationX][destinationY] > 1)
    {
        if(!this -> searchForDirection())
            ClearPlayerArray(wall);
    }
}

void Enemy::fightCoord(Player *player, Wall ** wall, Enemy **enemy)
{
    switch(direction)
    {
    case 0 ... 1:
    {
        if(player -> getY() > y)
        {
            attack = true;
            bool mozna = true;
            std::string route;
            if(player -> getY() + TANK_SIZE > BATTLEFIELD_HEIGHT)
                mozna = false;

            if(mozna)
            {
                destinationY = player -> getY() + TANK_SIZE;
                destinationX = player -> getX();
                route = FindPath(enemy, wall, player, id, false, true);
            }

            if(mozna == true && route.at(0) != '5')
            {
                directionCounter = 0;
                tempDirection = this-> enemyPilot(enemy, wall, player, true);
            }
            else
            {
                mozna = true;
                if(player -> getY() - TANK_SIZE < 0)
                    mozna = false;

                if(mozna)
                {
                    destinationX = player -> getX();
                    destinationY = player -> getY() - TANK_SIZE;
                    route = FindPath(enemy, wall, player, id, false, true);
                }
                if(mozna && route.at(0) != '5')
                {
                    directionCounter = 0;
                    tempDirection = this-> enemyPilot(enemy, wall, player, true);
                }
                else
                {
                    mozna = true;
                    if(player -> getX() + TANK_SIZE > BATTLEFIELD_WIDTH)
                        mozna = false;

                    if(mozna)
                    {
                        destinationX = player -> getX() + TANK_SIZE;
                        destinationY = player -> getY();
                        route = FindPath(enemy, wall, player, id, false, true);
                    }
                    if(mozna && route.at(0) != '5')
                    {
                        directionCounter = 0;
                        tempDirection = this-> enemyPilot(enemy, wall, player, true);
                    }
                    else
                    {
                        mozna = true;
                        if(player -> getX() - TANK_SIZE > 0)
                            mozna = false;

                        if(mozna)
                        {
                            destinationX = player -> getX() - TANK_SIZE;
                            destinationY = player -> getY();
                            route = FindPath(enemy, wall, player, id, false, true);
                        }
                        if(mozna && route.at(0) != '5')
                        {
                            directionCounter = 0;
                            tempDirection = this-> enemyPilot(enemy, wall, player, true);
                        }
                        else
                        {
                            enemy[id] -> setStop(true);
                            tempDirection = 5;
                        }
                    }
                }
            }
        }
        else if (player -> getY() < y)
        {
            attack = true;
            bool mozna = true;
            std::string route;
            if(player -> getY() - TANK_SIZE < 0)
                mozna = false;

            if(mozna)
            {
                destinationY = player -> getY() - TANK_SIZE;
                destinationX = player -> getX();
                route = FindPath(enemy, wall, player, id, false, true);
            }
            if(mozna && route.at(0) != '5')
            {
                directionCounter = 0;
                tempDirection = this-> enemyPilot(enemy, wall, player, true);
            }
            else
            {
                mozna = true;
                if(player -> getY() + TANK_SIZE > BATTLEFIELD_HEIGHT)
                    mozna = false;

                if(mozna)
                {
                    destinationX = player -> getX();
                    destinationY = player -> getY() + TANK_SIZE;
                    route = FindPath(enemy, wall, player, id, false, true);
                }
                if(mozna && route.at(0) != '5')
                {
                    directionCounter = 0;
                    tempDirection = this-> enemyPilot(enemy, wall, player, true);
                }
                else
                {
                    mozna = true;
                    if(player -> getX() + TANK_SIZE > BATTLEFIELD_WIDTH)
                        mozna = false;

                    if(mozna)
                    {
                        destinationX = player -> getX() + TANK_SIZE;
                        destinationY = player -> getY();
                        route = FindPath(enemy, wall, player, id, false, true);
                    }
                    if(mozna && route.at(0) != '5')
                    {
                        directionCounter = 0;
                        tempDirection = this-> enemyPilot(enemy, wall, player, true);
                    }
                    else
                    {
                        mozna = true;
                        if(player -> getX() - TANK_SIZE < 0)
                            mozna = false;

                        if(mozna)
                        {
                            destinationX = player -> getX() - TANK_SIZE;
                            destinationY = player -> getY();
                            route = FindPath(enemy, wall, player, id, false, true);
                        }
                        if(mozna && route.at(0) != '5')
                        {
                            directionCounter = 0;
                            tempDirection = this-> enemyPilot(enemy, wall, player, true);
                        }
                        else
                        {
                            enemy[id] -> setStop(true);
                            tempDirection = 5;
                        }
                    }
                }
            }
        }
        break;
    }
    case 2 ... 3:
    {
        if(player -> getX() > x)
        {
            attack = true;
            bool mozna = true;
            std::string route;
            if(player -> getX() + TANK_SIZE > BATTLEFIELD_WIDTH)
                mozna = false;

            if(mozna)
            {
                destinationX = player -> getX() + TANK_SIZE;
                destinationY = player -> getY();
                route = FindPath(enemy, wall, player, id, false, true);
            }

            if(mozna && route.at(0) != '5')
            {
                directionCounter = 0;
                tempDirection = this-> enemyPilot(enemy, wall, player, true);
            }
            else
            {
                mozna = true;
                if(player -> getX() - TANK_SIZE < 0)
                    mozna = false;

                if(mozna)
                {
                    destinationX = player -> getX() - TANK_SIZE;
                    destinationY = player -> getY();
                    route = FindPath(enemy, wall, player, id, false, true);
                }
                if(route.at(0) != '5' && mozna)
                {
                    directionCounter = 0;
                    tempDirection = this-> enemyPilot(enemy, wall, player, true);
                }
                else
                {
                    mozna = true;
                    if(player -> getY() + TANK_SIZE > BATTLEFIELD_HEIGHT)
                        mozna = false;

                    if(mozna)
                    {
                        destinationX = player -> getX();
                        destinationY = player -> getY() + TANK_SIZE;
                        route = FindPath(enemy, wall, player, id, false, true);
                    }
                    if(mozna && route.at(0) != '5')
                    {
                        directionCounter = 0;
                        tempDirection = this-> enemyPilot(enemy, wall, player, true);
                    }
                    else
                    {
                        mozna = true;
                        if(player -> getY() - TANK_SIZE < 0)
                            mozna = false;

                        if(mozna)
                        {
                            destinationX = player -> getX();
                            destinationY = player -> getY() - TANK_SIZE;
                            route = FindPath(enemy, wall, player, id, false, true);
                        }
                        if(mozna && route.at(0) != '5')
                        {
                            directionCounter = 0;
                            tempDirection = this-> enemyPilot(enemy, wall, player, true);
                        }
                        else
                        {
                            enemy[id] -> setStop(true);
                            tempDirection = 5;
                        }
                    }
                }
            }
        }
        else if (player -> getX() < x)
        {

            attack = true;
            bool mozna = true;
            std::string route;
            if(player -> getX() - TANK_SIZE < 0)
                mozna = false;

            if(mozna)
            {
                destinationX = player -> getX() - TANK_SIZE;
                destinationY = player -> getY();
                route = FindPath(enemy, wall, player, id, false, true);
            }
            if(mozna && route.at(0) != '5')
            {
                directionCounter = 0;
                tempDirection = this-> enemyPilot(enemy, wall, player, true);
            }
            else
            {
                mozna = true;
                if(player -> getX() + TANK_SIZE > BATTLEFIELD_WIDTH)
                    mozna = false;

                if(mozna)
                {
                    destinationX = player -> getX() + TANK_SIZE;
                    destinationY = player -> getY();
                    route = FindPath(enemy, wall, player, id, false, true);
                }
                if(mozna && route.at(0) != '5')
                {
                    directionCounter = 0;
                    tempDirection = this-> enemyPilot(enemy, wall, player, true);
                }
                else
                {
                    mozna = true;
                    if(player -> getY() + TANK_SIZE > BATTLEFIELD_HEIGHT)
                        mozna = false;

                    if(mozna)
                    {
                        destinationX = player -> getX();
                        destinationY = player -> getY() + TANK_SIZE;
                        route = FindPath(enemy, wall, player, id, false, true);
                    }
                    if(mozna && route.at(0) != '5')
                    {
                        directionCounter = 0;
                        tempDirection = this-> enemyPilot(enemy, wall, player, true);
                    }
                    else
                    {
                        mozna = true;
                        if(player -> getY() - TANK_SIZE < 0)
                            mozna = false;

                        if(mozna)
                        {
                            destinationX = player -> getX();
                            destinationY = player -> getY() - TANK_SIZE;
                            route = FindPath(enemy, wall, player, id, false, true);
                        }
                        if(mozna && route.at(0) != '5')
                        {
                            directionCounter = 0;
                            tempDirection = this-> enemyPilot(enemy, wall, player, true);
                        }
                        else
                        {
                            enemy[id] -> setStop(true);
                            tempDirection = 5;
                        }
                    }
                }
            }
        }
        break;
    }
    }
}

void SetTarget(Enemy **enemy, Player *player)
{
    short enemyAlive = CheckEnemyAlive(enemy);

    if(Wall::baseExist)
    {
        if(Enemy::hasPlayer == false && Enemy::hasBase == false)
        {
            Enemy::attackBase[0] = true;
            Enemy::attackBase[1] = false;
            Enemy::attackBase[2] = false;
        }
        else
        {
            switch(enemyAlive)
            {
            case 1:
            {
                if(Enemy::hasPlayer == true && (Enemy::hasBase == false && Wall::baseExist == true))
                {
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> getDead())
                        {
                            Enemy::attackBase[j] = false;
                            break;
                        }
                    }
                }
                else if(Enemy::hasPlayer == false && Enemy::hasBase == true)
                {
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> getDead())
                        {
                            Enemy::attackBase[j] = true;
                            break;
                        }
                    }
                }
                else if(Enemy::hasPlayer == true && Enemy::hasBase == true)
                {
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> getDead() && !enemy[j] -> getAttack())
                        {
                            if(player -> getLife() < 2)
                                Enemy::attackBase[j] = false;
                            else
                                Enemy::attackBase[j] = true;

                            break;
                        }
                    }
                }
                break;
            }
            case 2 ... 3:
            {
                if(Enemy::hasPlayer == true && (Enemy::hasBase == false && Wall::baseExist == true))
                {
                    bool tempSet = false;
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> getDead())
                        {
                            if(!tempSet)
                            {
                                Enemy::attackBase[j] = true;
                                tempSet = true;
                            }
                            else
                                Enemy::attackBase[j] = false;
                        }
                    }
                }
                else if(Enemy::hasPlayer == false && Enemy::hasBase == true)
                {
                    bool tempSet = false;
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> getDead())
                        {
                            if(!tempSet)
                            {
                                Enemy::attackBase[j] = true;
                                tempSet = true;
                            }
                            else
                                Enemy::attackBase[j] = false;

                        }
                    }
                }
                else if(Enemy::hasPlayer == true && Enemy::hasBase == true)
                {
                    bool tempSet = false;
                    for(short j=0 ; j < ENEMIES ; j++)
                    {
                        if(!enemy[j] -> getDead())
                        {
                            if(!tempSet)
                            {
                                Enemy::attackBase[j] = true;
                                tempSet = true;
                            }
                            else
                                Enemy::attackBase[j] = false;
                        }
                    }
                }
                break;
            }
            }

        }
    }
}

short Enemy::enemyPilot(Enemy **enemy, Wall **wall, Player *player, bool fight)
{
    std::string route;
    if(!fight)
        route = FindPath(enemy, wall, player, id, false, false);
    else
        route = FindPath(enemy, wall, player, id, false, true);

    wallAtPath = false;
    if(route.at(0) == '0')
    {
        tempDestinationY = (enemy[id] -> getY()/TANK_SIZE) * TANK_SIZE;
        tempDestinationX = (enemy[id] -> getX()/TANK_SIZE + 1) * TANK_SIZE;
        return 0;
    }
    else if(route.at(0) == '1')
    {
        tempDestinationY = (enemy[id] -> getY()/TANK_SIZE + 1) * TANK_SIZE;
        tempDestinationX = (enemy[id] -> getX()/TANK_SIZE) * TANK_SIZE;
        return 2;
    }
    else if(route.at(0) == '2')
    {
        tempDestinationY = (enemy[id] -> getY()/TANK_SIZE) * TANK_SIZE;
        tempDestinationX = (enemy[id] -> getX()/TANK_SIZE - 1)*TANK_SIZE;
        return 1;
    }
    else if(route.at(0) == '3')
    {
        tempDestinationY = (enemy[id] -> getY()/TANK_SIZE - 1)*TANK_SIZE;
        tempDestinationX = (enemy[id] -> getX() /TANK_SIZE) * TANK_SIZE;
        return 3;
    }
    else
    {
        std::string route;
        if(!fight)
            route = FindPath(enemy, wall, player, id, true, false);
        else
            route = FindPath(enemy, wall, player, id, true, true);

        wallAtPath = true;
        if(route.at(0) == '0')
        {
            tempDestinationY = (enemy[id] -> getY()/TANK_SIZE) * TANK_SIZE;
            tempDestinationX = (enemy[id] -> getX()/TANK_SIZE + 1) * TANK_SIZE;
            return 0;
        }

        else if(route.at(0) == '1')
        {
            tempDestinationY = (enemy[id] -> getY()/TANK_SIZE + 1) * TANK_SIZE;
            tempDestinationX = (enemy[id] -> getX()/TANK_SIZE) * TANK_SIZE;
            return 2;
        }
        else if(route.at(0) == '2')
        {
            tempDestinationY = (enemy[id] -> getY()/TANK_SIZE) * TANK_SIZE;
            tempDestinationX = (enemy[id] -> getX()/TANK_SIZE - 1)*TANK_SIZE;
            return 1;
        }
        else if(route.at(0) == '3')
        {
            tempDestinationY = (enemy[id] -> getY()/TANK_SIZE - 1)*TANK_SIZE;
            tempDestinationX = (enemy[id] -> getX() /TANK_SIZE) * TANK_SIZE;
            return 3;
        }
    }

    return 5;
};
/*
0 - right
1 - down
2 - left
3 - up
*/

void  Enemy::moveCorrection(Wall **wall, Player *player, Enemy **enemy, Bonus **bonus)
{
    short howMuch=0;
    if(x % TANK_SIZE != 0 && tempDirection > 1)
    {
        howMuch = x % TANK_SIZE ;
        if(howMuch <= 25 && this -> checkDirection(1, wall, enemy, player, 1))
        {
            x -= 1;
        }
        else if (howMuch > 25 && this -> checkDirection(0, wall, enemy, player, 1))
        {
            x += 1;
        }
        this -> checkCollision(wall, player, enemy, bonus);
    }
    else if(y % TANK_SIZE != 0 && tempDirection < 2)
    {
        howMuch = y % TANK_SIZE ;
        if(howMuch <= 25 && this -> checkDirection(3, wall, enemy, player, 1))
        {
            y -= 1;
        }
        else if (howMuch > 25 && this -> checkDirection(2, wall, enemy, player, 1))
        {
            y += 1;
        }
        this -> checkCollision(wall, player, enemy, bonus);
    }
}

void Enemy::moveAI(Wall **wall, Player *player, Enemy **enemy, Bonus **bonus)
{
    short collisionWith=0;
    switch(tempDirection)
    {
    case 0: //right
    {
        direction = 0;

        tempX = x;
        x += TANK_SPEED;

        if(x > BATTLEFIELD_WIDTH)
            x = tempX;

        collisionWith = this -> checkCollision(wall, player, enemy, bonus);

        if(collisionWith > 0)
            colision = true;
        else
            colision = false;

        if(collisionWith == 3 || collisionWith == 1)
        {
            short howMuch=0;
            if(y % TANK_SIZE != 0 )
            {
                howMuch = y % TANK_SIZE ;
                if(howMuch <= 25 && this -> checkDirection(3, wall, enemy, player, 1))
                    y -= 2;
                else if (howMuch > 25 && this -> checkDirection(2, wall, enemy, player, 1))
                    y += 2;

                this -> checkCollision(wall, player, enemy, bonus);
            }

            if (collisionWith == 3) //destroyable wall
            {
                if(this -> checkAimWall(wall, enemy))
                {
                    targetAhead = true;
                    stop = true;
                }
            }
        }
        else if (collisionWith == 4) //player
        {
            if(this -> checkAimPlayer(player, enemy, wall))
            {
                attack = false;
                targetAhead = true;
            }
            else
                attack = true;
        }
        else
        {
            if(this -> checkAimPlayer(player, enemy, wall))
                targetAhead = true;
            else if(this -> checkAimWall(wall, enemy))
                targetAhead = true;
        }

        break;
    }
    case 1://left
    {
        direction = 1;

        tempX = x;
        x -= TANK_SPEED;
        if(x < 0)
            x = tempX;

        collisionWith = this -> checkCollision(wall, player, enemy, bonus);

        if(collisionWith > 0)
            colision = true;
        else
            colision = false;

        if(collisionWith == 3 || collisionWith == 1)
        {
            short howMuch=0;

            if(y % TANK_SIZE != 0 )
            {
                howMuch = y % TANK_SIZE ;
                if(howMuch <= 25 && this -> checkDirection(3, wall, enemy, player, 1))
                    y -= 2;
                else if (howMuch > 25 && this -> checkDirection(2, wall, enemy, player, 1))
                    y += 2;

                this -> checkCollision(wall, player, enemy, bonus);
            }
            if (collisionWith == 3) //destroyable wall
            {
                if(this -> checkAimWall(wall, enemy))
                {
                    targetAhead = true;
                }
            }
        }
        else if (collisionWith == 4) //player
        {
            if(this -> checkAimPlayer(player, enemy, wall))
            {
                attack =false;
                targetAhead = true;
            }
            else
                attack = true;
        }
        else
        {
            if(this -> checkAimPlayer(player, enemy, wall))
                targetAhead = true;

            else if(this -> checkAimWall(wall, enemy))
                targetAhead = true;

        }
        break;
    }
    case 2: //dol
    {
        direction = 2;

        tempY = y;
        y += TANK_SPEED;
        if(y > BATTLEFIELD_HEIGHT)
            y = tempY;

        collisionWith = this -> checkCollision(wall, player, enemy, bonus);

        if(collisionWith > 0)
            colision = true;
        else
            colision = false;

        if(collisionWith == 3 || collisionWith == 1)
        {
            short howMuch=0;
            if(x % TANK_SIZE != 0)
            {
                howMuch = x % TANK_SIZE ;
                if(howMuch <= 25 && this -> checkDirection(1, wall, enemy, player, 1))
                    x -= 2;
                else if (howMuch > 25 && this -> checkDirection(0, wall, enemy, player, 1))
                    x += 2;

                this -> checkCollision(wall, player, enemy, bonus);
            }
            if (collisionWith == 3) //destroyable wall
            {
                if(this -> checkAimWall(wall, enemy))
                {
                    targetAhead = true;
                }
            }
        }
        else if (collisionWith == 4) //player
        {

            if(this -> checkAimPlayer(player, enemy, wall))
            {
                attack =false;
                targetAhead = true;
            }
            else
                attack = true;
        }
        else
        {
            if(this -> checkAimPlayer(player, enemy, wall))
                targetAhead = true;

            else if(this -> checkAimWall(wall, enemy))
                targetAhead = true;
        }
        break;
    }
    case 3: //gora
    {
        direction = 3;

        tempY = y;
        y -= TANK_SPEED;
        if(y < 0)
            y = tempY;


        collisionWith = this -> checkCollision(wall, player, enemy, bonus);

        if(collisionWith > 0)
            colision = true;
        else
            colision = false;

        if(collisionWith == 3 || collisionWith == 1)
        {
            short howMuch=0;
            if(x % TANK_SIZE != 0)
            {
                howMuch = x % TANK_SIZE ;
                if(howMuch <= 25 && this -> checkDirection(1, wall, enemy, player, 1))
                    x -= 2;
                else if (howMuch > 25 && this -> checkDirection(0, wall, enemy, player, 1))
                    x += 2;

                this -> checkCollision(wall, player, enemy, bonus);
            }
            if (collisionWith == 3) //destroyable wall
            {
                if(this -> checkAimWall(wall, enemy))
                {
                    targetAhead = true;
                }
            }
        }
        else if (collisionWith == 4) //player
        {
            if(this -> checkAimPlayer(player, enemy, wall))
            {
                attack =false;
                targetAhead = true;
            }
            else
                attack = true;
        }
        else
        {
            if(this -> checkAimPlayer(player, enemy, wall))
                targetAhead = true;

            else if(this -> checkAimWall(wall, enemy))
                targetAhead = true;
        }
        break;
    }
    }
}

void Enemy::enemyAI(Wall **wall, Enemy **enemy, Player *player, Bonus **bonus, Rocket **rocket)
{
    if(!dead && !gameover)
    {
        stop = false;
        targetAhead = false;

        short enemyAlive = CheckEnemyAlive(enemy);
        if(enemyAlive == 1 && ((player -> getLife() > 1 && gameMode != 2) || (enemies - enemiesKilled - enemyAlive > 0 && player -> getLife() > 1 && enemiesAtOnce > 1) || (Enemy::hasBase && Wall::baseExist && wall[Wall::baseID] -> getLife() > 1 )) && !attack)
        {
            stop = true;
            if(this -> checkAimPlayer(player, enemy, wall))
                targetAhead = true;
            else if(Enemy::hasBase && this -> checkAimBase(wall, Wall::baseID, enemy))
                targetAhead = true;

            short tempDirectionAI = direction;

            direction = 0;
            if(this -> checkAimPlayer(player, enemy, wall))
                targetAhead = true;
            else
            {
                direction = 1;
                if(this -> checkAimPlayer(player, enemy, wall))
                    targetAhead = true;
                else
                {
                    direction = 2;
                    if(this -> checkAimPlayer(player, enemy, wall))
                        targetAhead = true;
                    else
                    {
                        direction = 3;
                        if(this -> checkAimPlayer(player, enemy, wall))
                            targetAhead = true;
                        else
                            direction = tempDirectionAI;
                    }
                }
            }

            tempDirection = direction;
            firstmovement = false;
        }
        else if((Enemy::hasPlayer == false && Enemy::hasBase == false) || (Enemy::hasPlayer == false && Enemy::attackBase[id] == false))
        {
            if(attack == true)
                attack = false;

            this -> checkNearbyArea(wall, enemy, player);

            if(Enemy::hasPlayer == true && this -> checkAimPlayer(player, enemy, wall))
            {
                targetAhead = true;
                if(direction > 1 && abs(player -> getY() - y) < 76)
                    stop = true;
                else if(direction < 2 && abs(player -> getX() - x) < 76)
                    stop = true;
                else if(canShoot)
                    stop = true;
            }
            else if(this -> checkAimWall(wall, enemy))
            {
                targetAhead = true;
                if(wallAtPath)
                {
                    if(direction > 1 && abs(wall[wallID] -> getY() - y) < 76)
                        stop = true;
                    else if(direction < 2 && abs(wall[wallID] -> getX() - x) < 76)
                        stop = true;
                    else if(colision || canShoot)
                        stop = true;
                }
            }

            if(!stop)
            {
                if(!firstmovement)
                {
                    if(this -> searchForDirection())
                    {
                        tempDirection = this -> enemyPilot(enemy, wall, player, false);
                        if(tempDirection == 5)
                        {
                            Enemy::isPlayer[destinationX][destinationY] = 4;
                            stop = true;
                        }
                    }
                    else
                        ClearPlayerArray(wall);

                    firstmovement = true;
                }

                if(x == tempDestinationX && tempDestinationY == y)
                {
                    directionCounter = 0;
                    this -> checkDestination(wall);
                    tempDirection = this -> enemyPilot(enemy, wall, player, false);
                    if(tempDirection == 5)
                    {
                        stop = true;
                        Enemy::isPlayer[destinationX][destinationY] = 4;
                    }
                }
                else
                {
                    directionCounter ++;

                    this -> moveCorrection(wall, player, enemy, bonus);

                    if (directionCounter >= 26)
                    {
                        directionCounter = 0;
                        this -> checkDestination(wall);
                        tempDirection = this -> enemyPilot(enemy, wall, player, false);
                        if(tempDirection == 5)
                        {
                            stop = true;
                            Enemy::isPlayer[destinationX][destinationY] = 4;
                        }
                    }
                }
            }
        }
        else if(Enemy::hasBase == true && Enemy::attackBase[id] == true)
        {
            this -> checkNearbyArea(wall, enemy, player);
            SetBaseCoord(enemy,wall, id);

            if(Enemy::hasPlayer == true && this-> checkAimPlayer(player, enemy, wall))
            {
                targetAhead = true;
                if(direction > 1 && abs(player -> getY() - y) < 76)
                    stop = true;
                else if(direction < 2 && abs(player -> getX() - x) < 76)
                    stop = true;
                else if(canShoot)
                    stop = true;

                if(attack == true)
                    attack = false;
            }
            else if(this -> checkAimWall(wall, enemy) && wallAtPath)
            {
                targetAhead = true;
                if(wallAtPath)
                {
                    if(direction > 1 && abs(wall[wallID] -> getY() - y) < 76)
                        stop = true;
                    else if(direction < 2 && abs(wall[wallID] -> getX() - x) < 76)
                        stop = true;
                    else if(colision || canShoot)
                        stop = true;
                }
            }
            else if(this -> checkAimBase(wall, Wall::baseID, enemy))
            {
                targetAhead = true;

                if(direction > 1 && abs(wall[Wall::baseID] -> getY() - y) < 76)
                    stop = true;
                else if(direction < 2 && abs(wall[Wall::baseID] -> getX() - x) < 76)
                    stop = true;
                else if(colision || canShoot)
                    stop = true;
            }

            if(!stop)
            {
                if(!firstmovement)
                {
                    tempDirection = this -> enemyPilot(enemy, wall, player, false);
                    if(tempDirection == 5)
                        stop = true;

                    firstmovement = true;
                }

                if(x == tempDestinationX && tempDestinationY == y)
                {
                    attack = false;
                    directionCounter = 0;
                    tempDirection = this -> enemyPilot(enemy, wall, player, false);

                    if(tempDirection == 5)
                        stop = true;
                }
                else
                {
                    directionCounter ++;

                    this -> moveCorrection(wall, player, enemy, bonus);

                    if (directionCounter >= 26)
                    {
                        directionCounter = 0;

                        tempDirection = this -> enemyPilot(enemy, wall, player, false);
                        if(tempDirection == 5)
                            stop = true;
                    }
                }
            }
        }
        else if(Enemy::hasPlayer == true)
        {
            this -> checkNearbyArea(wall, enemy, player);

            if(this -> checkAimPlayer(player, enemy, wall))
            {
                targetAhead = true;
                if(direction > 1 && abs(player -> getY() - y) < 76)
                    stop = true;
                else if(direction < 2 && abs(player -> getX() - x) < 76)
                    stop = true;
                else if(canShoot)
                    stop = true;

                if(attack == true)
                    attack = false;
            }
            else if(this -> checkAimWall(wall, enemy) && wallAtPath)
            {
                targetAhead = true;
                if(wallAtPath)
                {
                    if(direction > 1 && abs(wall[wallID] -> getY() - y) < 76)
                        stop = true;
                    else if(direction < 2 && abs(wall[wallID] -> getX() - x) < 76)
                        stop = true;
                    else if(colision || canShoot)
                        stop = true;
                }
            }

            if(!stop)
            {
                if(!firstmovement)
                {
                    tempDirection = this -> enemyPilot(enemy, wall, player, false);
                    if(tempDirection == 5)
                        stop = true;

                    firstmovement = true;
                }

                if(x == tempDestinationX && tempDestinationY == y)
                {
                    attack = false;
                    directionCounter = 0;
                    tempDirection = this -> enemyPilot(enemy, wall, player, false);

                    short kierunek = direction;

                    direction = 0;
                    if(this -> checkAimPlayer(player, enemy, wall))
                        stop = true;
                    else
                    {
                        direction = 1;
                        if(this -> checkAimPlayer(player, enemy, wall))
                            stop = true;
                        else
                        {
                            direction = 2;
                            if(this -> checkAimPlayer(player, enemy, wall))
                                stop = true;
                            else
                            {
                                direction = 3;
                                if(this -> checkAimPlayer(player, enemy, wall))
                                    stop = true;
                                else
                                    direction = kierunek;
                            }
                        }
                    }

                    tempDirection = direction;

                    if(abs(x - player -> getX()) < 112 || abs(y - player -> getY()) < 112)
                        attack = true;

                    if(tempDirection == 5)
                    {
                        //No stop if enemy can't see player but he try to follow player
                        if(abs(x - player -> getX()) > 112 || abs(y - player -> getY()) > 112)
                        {
                            switch(Enemy::playerDirection)
                            {
                            case 0:
                            {
                                destinationX += TANK_SIZE;
                                if( destinationX > BATTLEFIELD_WIDTH)
                                    destinationX = BATTLEFIELD_WIDTH;

                                break;
                            }
                            case 1:
                            {
                                destinationX -= TANK_SIZE;
                                if(destinationX < 0)
                                    destinationX = 0;

                                break;
                            }
                            case 2:
                            {
                                destinationY += TANK_SIZE;
                                if( destinationY > BATTLEFIELD_HEIGHT)
                                    destinationY = BATTLEFIELD_HEIGHT;
                                break;
                            }
                            case 3:
                            {
                                destinationY -= TANK_SIZE;
                                if( destinationY < 0)
                                    destinationY = 0;
                                break;
                            }
                            }

                            if(Enemy::lostPlayerTimer >= 2)
                            {
                                Enemy::lostPlayerTimer = 0;
                                Enemy::hasPlayer = false;
                            }
                            else
                                Enemy::lostPlayerTimer++;
                        }
                        else
                            this -> fightCoord(player, wall, enemy);
                    }
                }
                else
                {
                    directionCounter++;

                    bool canMove = this -> checkPlayerFuture(tempDirection, player, 2);
                    if(canMove == true)
                        this -> fightCoord(player, wall, enemy);

                    short howNeed=0;
                    if(x % TANK_SIZE != 0 && tempDirection > 1 && !canMove && this -> checkPlayerFuture(tempDirection, player, 1))
                    {
                        howNeed = x % TANK_SIZE ;
                        if(howNeed <= 25)
                            x -= 1;
                        else
                            x += 1;

                        this -> checkCollision(wall, player, enemy, bonus);
                    }
                    else if(y % TANK_SIZE != 0 && tempDirection <2 && !canMove && this -> checkPlayerFuture(tempDirection, player, 1))
                    {
                        howNeed = y % TANK_SIZE ;
                        if(howNeed <= 25)
                            y -= 1;
                        else
                            y += 1;

                        this -> checkCollision(wall, player, enemy, bonus);
                    }

                    if(canMove == false)
                    {
                        if(x % TANK_SIZE != 0 && tempDirection >1)
                        {
                            howNeed = x % TANK_SIZE ;
                            if(howNeed <= 25)
                                x -= 1;
                            else
                                x += 1;

                            this -> checkCollision(wall, player, enemy, bonus);
                        }
                        else if(y % TANK_SIZE != 0 && tempDirection <2)
                        {
                            howNeed = y % TANK_SIZE ;
                            if(howNeed <= 25)
                                y -= 1;
                            else
                                y += 1;

                            this -> checkCollision(wall, player, enemy, bonus);
                        }
                    }

                    if (directionCounter >= 27)
                    {
                        directionCounter = 0;

                        tempDirection = this -> enemyPilot(enemy, wall, player, false);
                        if(tempDirection == 5)
                            stop = true;
                    }
                }
            }
        }
        else if(!player -> getActive())
        {
            if(directionCounter == 0)
                tempDirection = this -> enemyPilot(enemy, wall, player, false);

            this -> moveCorrection(wall, player, enemy, bonus);

            directionCounter ++;

            if (directionCounter >= 35)
                directionCounter = 0;

            if(this -> checkAimWall(wall, enemy))
                targetAhead = true;
        }

        if(!stop)
            this -> moveAI(wall, player, enemy, bonus);

        if(canShoot && targetAhead)
            this -> shoot(rocket);
    }
}
