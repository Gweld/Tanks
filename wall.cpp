#include "wall.hpp"
#include "main.hpp"
#include "config.hpp"
#include "allegroconfig.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <cstdlib>
#include <cstdio>


extern ALLEGRO_CONFIG* iniFile;

short Wall::getX()
{
    return x;
};

void Wall::setX( short _x)
{
    x = _x;
};

short Wall::getY()
{
    return y;
};

void Wall::setY( short _y)
{
    y = _y;
};

bool Wall::getDestroyable()
{
    return destroyable;
};

void Wall::setDestroyable( bool _destroyable)
{
    destroyable = _destroyable;
};

bool Wall::getVisible()
{
    return visible;
};

void Wall::setVisible( bool _visible)
{
    visible = _visible;
};

bool Wall::getBase()
{
    return base;
};

void Wall::setBase( bool _base)
{
    base = _base;
};

short Wall::getLife()
{
    return life;
};

void Wall::setLife( short _life)
{
    life = _life;
};

void SetBaseID(Wall ** wall)
{
    if(Wall::baseExist == true)
    {
        for(short i=0; i < OBSTACLES; i++)
        {
            if(wall[i]->getBase())
            {
                Wall::baseID = i;
                break;
            }
        }
    }
}

void ClearWall(Wall ** wall)
{
    for(short i=0; i < OBSTACLES; i++)
    {
        wall[i] -> setX(0);
        wall[i] -> setY(0);
        wall[i] -> setDestroyable(true);
        wall[i] -> setLife(0);
        wall[i] -> setBase(false);
        wall[i] -> setVisible(false);
    }
    Wall::baseExist = false;
    Wall::baseID = 0;
    Wall::respawnTimer = 0;
}

void WallCampaingInitialize(Wall **wall, Player * player, Enemy ** enemy, short currentLevel, bool respawn)
{
    char message[16];
    char levelName[15];
    short choice;

    sprintf(levelName, "level%i.tank", currentLevel);

    iniFile = al_load_config_file(levelName);
    if(!iniFile)
        ShowError(levelName, 0);

    short walls = atoi(al_get_config_value(iniFile, "options", "walls"));
    if(walls == 0)
        ShowError("error", 3);

    bool isBase = atoi(al_get_config_value(iniFile, "options", "isBase"));
    if(isBase == true)
        Wall::baseExist = true;

    for(short g = 0; g < walls; g++)
    {
        sprintf(message, "wallNR%i", g + 1);
        choice = GiveWallID(wall);
        wall[choice] -> setDestroyable(atoi(al_get_config_value(iniFile, message, "destroyable")));
        wall[choice] -> setLife(atoi(al_get_config_value(iniFile, message, "life")));
        wall[choice] -> setX(atoi(al_get_config_value(iniFile, message, "x")));
        wall[choice] -> setY(atoi(al_get_config_value(iniFile, message, "y")));
        wall[choice] -> setBase(atoi(al_get_config_value(iniFile, message, "base")));
        if(!respawn)
            wall[choice] -> setVisible(true);
        else
        {
            bool collision = wall[choice] -> checkPlace(wall, player, enemy);
            if(collision)
                wall[choice] -> setVisible(true);
        }
    }
    al_destroy_config(iniFile);
}

void Wall::create(Wall ** wall, Player * player, Enemy ** enemy, short _x, short _y, bool _destroyable, short _life, bool _base)
{
    x = (_x/50)* 50;
    y = (_y/50)* 50;
    destroyable = _destroyable;
    life = _life;

    if(_base)
    {
        if(Wall::baseExist == false)
        {
            base = true;
            Wall::baseExist = true;
        }
    }
    else
        base = false;

    while(1)
    {
        if(this -> checkPlace(wall,player,enemy))
            break;

        x = ((rand()%(BATTLEFIELD_WIDTH - 50))/50)* 50;
        y = ((rand()%(BATTLEFIELD_HEIGHT - 50))/50)* 50;
    }

    visible = true;
};

bool Wall::checkPlace(Wall **wall, Player * player, Enemy **enemy)
{
    bool collision=false; //if wall has collision with another object we can return false
    for (short i=0; i<OBSTACLES ; i++)
    {
        if(wall[i]->getVisible() && this != wall[i])
        {
            if(x > wall[i] -> getX() - OBSTACLE_SIZE && x < wall[i] -> getX() + OBSTACLE_SIZE )
                if(y + OBSTACLE_SIZE > wall[i] -> getY() && y < wall[i] -> getY() + OBSTACLE_SIZE )
                {
                    collision = true;
                    break;
                }
        }
    }
    if(player->getActive() && !collision)
    {
        if(x > player -> getX() - OBSTACLE_SIZE && x < player -> getX() + TANK_SIZE)
            if(y + TANK_SIZE > player -> getY() && y < player -> getY() + TANK_SIZE )
                collision = true;
    }


    for(short j=0; j<ENEMIES && !collision; j++)
    {
        if(!enemy[j] -> getDead())
        {
            if(x > enemy[j] -> getX() - OBSTACLE_SIZE && x < enemy[j] -> getX() + TANK_SIZE)
                if(y + TANK_SIZE > enemy[j] -> getY() && y < enemy[j] -> getY() + TANK_SIZE)
                {
                    collision = true;
                    break;
                }
        }
    }

    if (collision)
        return false;
    else
        return true;
};
short GiveWallID(Wall **wall)
{
    short temp=0;
    for(short i=0; i<OBSTACLES; i++)
    {
        if(!wall[i]->getVisible())
        {
            temp=i;
            break;
        }
    }
    return temp;
};

short CheckExistsWalls(Wall **wall)
{
    short temp=0;
    for(short i=0; i<OBSTACLES; i++)
    {
        if(wall[i]->getVisible())
        {
            temp++;
        }
    }
    return temp;
}

void SetImmortallWallsVisible(Wall **wall)
{
    for (short i=0; i<OBSTACLES ; i++)
    {
        if(wall[i]->getVisible() && wall[i]->getDestroyable() == false)
        {
            for(short j = wall[i] -> getY() ; j <= wall[i] -> getY() + OBSTACLE_SIZE; j++)
            {
                for(short k = wall[i] -> getX() ; k <= wall[i] -> getX() + OBSTACLE_SIZE; k++)
                {
                    if(k < 0 || j < 0)
                        continue;

                    Enemy::isPlayer[k][j] = 4;
                }
            }
        }
    }
}
