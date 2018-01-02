#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "player.hpp"
#include "rocket.hpp"
#include "config.hpp"
#include <cstring>
#include <stdint.h>

class Enemy : public Player
{
private:
    bool dead;
    bool colision;
    short tempDirection;
    short directionCounter;
    short destinationX;
    short destinationY;
    short tempDestinationX;
    short tempDestinationY;
    bool canShoot;
    bool targetAhead;
    short ammoTimer;
    short ammoDelay;
    short respawnDelayTimer;
    short difficulty; // 0 - Normal 1 - Mid 2- Fast 3-heavy
    bool stop;
    short wallID;
    bool wallAtPath;
    bool firstmovement;
    bool attack;
    short id;

public:
    Enemy(short _id):
        dead(1),
        directionCounter(0),
        destinationX(0),
        destinationY(0),
        tempDestinationX(0),
        tempDestinationY(0),
        canShoot(true),
        targetAhead(false),
        ammoTimer(0),
        ammoDelay(0),
        respawnDelayTimer(0),
        difficulty(0),
        stop(false),
        wallID(0),
        wallAtPath(false),
        firstmovement(false),
        attack(false)
    {
        id = _id;
    }

    static uint8_t isPlayer[REAL_BATTLEFIELD_WIDTH+TANK_SIZE+1][REAL_BATTLEFIELD_HEIGHT+TANK_SIZE+1];
    static bool hasPlayer ;
    static bool hasBase ;
    static short baseCoord[2];
    static short playerTimer;
    static short playerDirection;
    static bool attackBase[3];
    static short lostPlayerTimer;

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

    bool getDead();
    void setDead( bool _dead);

    short getWallID();
    void setWallID( short _wallID);

    bool getFirstmovement();
    void setFirstmovement( bool _firstmovement);

    bool getColision();
    void setColision( bool _colision);

    bool getCanShoot();
    void setCanShoot( bool _canShoot);

    short getAmmoSpeed();
    void setAmmoSpeed( short _ammoSpeed);

    short getTempDirection();
    void setTempDirection( short _tempDirection);

    short getDirectionCounter();
    void setDirectionCounter( short _directionCounter);

    short getDestinationX();
    void setDestinationX(short _destinationX);

    short getDestinationY();
    void setDestinationY( short _destinationY);

    short getTempDestinationX();
    void setTempDestinationX(short _tempDestinationX);

    short getTempDestinationY();
    void setTempDestinationY( short _tempDestinationY);

    bool getTargetAhead();
    void setTargetAhead( bool _targetAhead);

    short getAmmoTimer();
    void setAmmoTimer( short _ammoTimer);

    short getAmmoDelay();
    void setAmmoDelay( short _ammoDelay);

    short getRespawnDelayTimer();
    void setRespawnDelayTimer( short _respawnDelayTimer);

    short getDifficulty();
    void setDifficulty( short _difficulty);

    bool getStop();
    void setStop( bool _stop);

    bool getWallAtPath();
    void setWallAtPath( bool _wallAtPath);

    bool getAttack();
    void setAttack( bool _attack);

    void setPlayerCoord(Enemy **enemy, Player * player);
    void checkPlace(Wall **wall, Player * player, Enemy **enemy);
    short checkCollision(Wall **wall, Player * player, Enemy **enemy, Bonus **bonus);
    void spawn(short _x, short _y, short _life, short _ammoSpeed, short _direction, short _ammoDelay, short _difficulty, Wall **wall, Player * player, Enemy **enemy);
    bool checkAimWall(Wall **wall, Enemy ** enemy);
    bool checkAimImmortallWall(Wall **wall, short _x, short _y);
    bool checkAimPlayer(Player *player, Enemy ** enemy, Wall ** wall);
    bool checkAimBase(Wall **wall, short id, Enemy ** enemy);
    bool checkAimEnemy(Enemy **enemy, short _x, short _y);
    bool searchForDirection();
    void checkForBase(Wall ** wall, Enemy ** enemy);
    void checkForPlayer(Player *player, Enemy **enemy);
    bool checkDirection(short direction, Wall ** wall, Enemy ** enemy, Player *player, short moves);
    void shoot(Rocket ** rocket);
    void checkNearbyArea(Wall ** wall, Enemy ** enemy, Player * player);
    bool checkPlayerFuture(short direction, Player *player, short moves);
    void checkDestination(Wall ** wall);
    void fightCoord(Player *player, Wall ** wall, Enemy **enemy);
    short enemyPilot(Enemy **enemy, Wall **wall, Player *player, bool fight);
    void moveCorrection(Wall **wall, Player *player, Enemy **enemy, Bonus **bonus);
    void moveAI(Wall **wall, Player *player, Enemy **enemy, Bonus **bonus);
    void enemyAI(Wall **wall, Enemy **enemy, Player *player, Bonus **bonus, Rocket **rocket);
};

short GiveEnemyID(Enemy **enemy);
void ClearPlayerArray(Wall ** wall);
void ClearWallArray();
void ClearEnemy(Enemy **enemy);
short CheckEnemyAlive(Enemy **enemy);
void SetBaseCoord(Enemy ** enemy, Wall **wall, short choice);
void EnemycampaingInitialize(Enemy ** enemy, short currentLevel, Wall **wall, Player *player);
void EnemyCampaignDrop(Enemy ** enemy, short currentLevel, Wall **wall, Player *player);
void SetTarget(Enemy **enemy, Player *player);

#endif
