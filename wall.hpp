#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include <stdint.h>

class Player;
class Enemy;

class Wall
{
private:
    bool destroyable;
    bool base;

protected:
    short x;
    short y;
    short life;
    bool visible;

public:

    Wall():
        base(false) {}

    static short respawnTimer;
    static short baseID;
    static bool baseExist;

    short getX();
    void setX( short _x);

    short getY();
    void setY( short _y);

    short getLife();
    void setLife( short _life);

    bool getDestroyable();
    void setDestroyable( bool _destroyable);

    bool getVisible();
    void setVisible( bool _visible);

    bool getBase();
    void setBase( bool _base);

    bool checkPlace(Wall **wall, Player * player, Enemy **enemy);
    void create(Wall ** wall, Player * player, Enemy ** enemy, short _x, short _y, bool _destroyable, short _life, bool _base);

};

short GiveWallID(Wall **wall);
void SetBaseID(Wall ** wall);
void ClearWall(Wall ** wall);
short CheckExistsWalls(Wall **wall);
void WallCampaingInitialize(Wall **wall, Player * player, Enemy ** enemy, short currentLevel, bool respawn);
void SetImmortallWallsVisible(Wall **wall);

#endif
