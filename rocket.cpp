#include "rocket.hpp"
#include "config.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "enemy.hpp"
#include "explosion.hpp"
#include "bonus.hpp"
#include "player.hpp"
#include "wall.hpp"
#include "main.hpp"

extern ALLEGRO_SAMPLE *sound[SOUNDS];

extern bool gameover;
extern unsigned short gameMode;
extern short enemiesKilled;
extern bool youDied;
extern bool baseDestroyed;

short Rocket::getX()
{
    return x;
};

void Rocket::setX(short _x)
{
    x = _x;
};

short Rocket::getY()
{
    return y;
};

void Rocket::setY(short _y)
{
    y = _y;
};

short Rocket::getDirection()
{
    return direction;
};

void Rocket::setDirection(short _direction)
{
    direction = _direction;
};

bool Rocket::getTeam()
{
    return team;
};

void Rocket::setTeam( bool _team)
{
    team = _team;
};

bool Rocket::getVisible()
{
    return visible;
};

void Rocket::setVisible( bool _visible)
{
    visible = _visible;
};

short Rocket::getSpeed()
{
    return speed;
};

void Rocket::setSpeed( short _speed)
{
    speed = _speed;
};

void Rocket::rocketOff()
{
    if(team == true) //player
    {
        Rocket::rocketsCounter[0]--;
        if(Rocket::rocketsCounter[0] < 0)
            Rocket::rocketsCounter[0] = 0;
    }
    else
    {
        Rocket::rocketsCounter[1]--;
        if(Rocket::rocketsCounter[1] < 0)
            Rocket::rocketsCounter[1] = 0;
    }
};

void Rocket::createSmallExplosion(Explosion ** explosion)
{
    short choice=GiveExplosionID(explosion);
    explosion[choice] -> setX(x);
    explosion[choice] -> setY(y);
    if(direction == 2)
        explosion[choice] -> setX(x-5);
    else if(direction == 3)
        explosion[choice] -> setX(x-10);
    else if (direction == 1 || direction == 0)
        explosion[choice] -> setY(y-5);

    explosion[choice] -> setSmall(true);
    explosion[choice] -> setVisible(true);

    explosion[choice] -> setLife(SMALL_EXPLOSION_TIME);
    explosion[choice] -> createExplosion();
    al_play_sample(sound[4], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

void Rocket::createBigExplosion(Explosion ** explosion, short _x, short _y)
{
    short choice=GiveExplosionID(explosion);
    explosion[choice] -> setX(_x);
    explosion[choice] -> setY(_y);
    explosion[choice] -> setSmall(false);
    explosion[choice] -> setVisible(true);
    explosion[choice] -> setLife(BIG_EXPLOSION_TIME);
    explosion[choice] -> createExplosion();
    al_play_sample(sound[2], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
}

void Rocket::move(Rocket ** rocket, Wall ** sciany, Player *player, Enemy ** enemy, Explosion ** explosion, Bonus ** bonus)
{
    this -> checkColision(rocket, sciany, player, enemy, explosion, bonus);

    if(visible && !gameover)
    {
        switch(direction)
        {
        case 0:
        {
            x += speed;

            if(x > REAL_BATTLEFIELD_WIDTH)
            {
                visible = false;
                this -> rocketOff();
                this -> createSmallExplosion(explosion);
            }

            break;
        }
        case 1:
        {
            x -= speed;

            if(x < 0)
            {
                visible = false;
                this -> rocketOff();
                this -> createSmallExplosion(explosion);
            }
            break;
        }
        case 2:
        {
            y += speed;

            if(y > REAL_BATTLEFIELD_HEIGHT)
            {
                visible = false;
                this -> rocketOff();
                this -> createSmallExplosion(explosion);
            }
            break;
        }
        case 3:
        {
            y -= speed;

            if(y < 0)
            {
                visible = false;
                this -> rocketOff();
                this -> createSmallExplosion(explosion);
            }
            break;
        }
        }

        this -> checkColision(rocket, sciany, player, enemy, explosion, bonus);
    }
};

void Rocket::shoot(Player * player)
{
    Player::ammoTimer = 0;

    switch(player -> getDirection())
    {
    case 0:
    {
        x = player -> getX() + 51;
        y = player -> getY() + 21;
        direction = 0;
        break; //right
    }
    case 1:
    {
        x = player -> getX() - 16;
        y = player -> getY() + 21;
        direction = 1;
        break; //left
    }
    case 2:
    {
        x = player -> getX() + 21;
        y = player -> getY() + 60;
        direction = 2;
        break; //down
    }
    case 3:
    {
        x = player -> getX() + 29;
        y = player -> getY() - 14;
        direction = 3;
        break; //up
    }
    }
    Rocket::rocketsCounter[0]++;
    visible = true;
    team = true;
    speed = player -> getAmmoSpeed();

    al_play_sample(sound[0], 0.7, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
};

void Rocket::hitWall(Wall ** sciany, short choice)
{
    visible = false;
    this -> rocketOff();
    if(sciany[choice] -> getDestroyable())
    {
        sciany[choice] -> setLife(sciany[choice] -> getLife() - 1);
        if(sciany[choice] -> getLife() == 0)
            sciany[choice] -> setVisible(false);
    }
}

void Rocket::hitPlayer(Player * player)
{
    visible = false;
    player -> setLife(player -> getLife() - 1);

    //simulate damage
    if(player -> getShoots() > 1)
        player -> setShoots(player -> getShoots() - 1);
    else if(player -> getAmmoSpeed() > AMMO_SPEED - 1)
        player -> setAmmoSpeed(player -> getAmmoSpeed() - 1);
    else if(player -> getAmmoTimer() < 60)
        player -> setAmmoSpeed(player -> getAmmoSpeed() + 10);

    this -> rocketOff();
}

void Rocket::hitEnemy(Enemy ** enemy, Player * player, short choice)
{
    visible = false;
    enemy[choice] -> setLife(enemy[choice] -> getLife() - 1);

    if(enemy[choice] -> getLife() == 0 )
    {
        enemy[choice] -> setDead(true);
        enemy[choice] -> setRespawnDelayTimer(1); //1 to start counting
        if(this -> getTeam())
        {
            player -> setPoints(player -> getPoints() +((enemy[choice] -> getDifficulty()+1) * POINTS_FOR_KILL ));
            player -> setKills(player -> getKills() + 1);
        }
    }
    this -> rocketOff();
}

void Rocket::hitRocket(Rocket ** rocket, short choice)
{
    visible = false;
    rocket[choice] -> setVisible(false);
    this -> rocketOff();
    rocket[choice] -> rocketOff();
}

void Rocket::checkColision(Rocket ** rocket, Wall ** sciany, Player *player, Enemy ** enemy, Explosion ** explosion, Bonus ** bonus)
{
    bool hit=false;//only one hit
    for (short i=0; i < OBSTACLES && !hit; i++)
    {
        if(sciany[i] -> getVisible())
        {
            switch(direction)
            {
            case 0:
            {
                if(x + ROCKET_X >= sciany[i] -> getX() && x <= sciany[i] -> getX() + OBSTACLE_SIZE  && y >= sciany[i] -> getY() - ROCKET_Y  && y <= sciany[i] -> getY() +OBSTACLE_SIZE)
                {
                    this -> hitWall(sciany, i);
                    hit=true;
                }
                break;
            }
            case 1:
            {
                if(x >= sciany[i] -> getX() && x <= sciany[i] -> getX() +OBSTACLE_SIZE && y >= sciany[i] -> getY() - ROCKET_Y  && y <= sciany[i] -> getY() +OBSTACLE_SIZE)
                {
                    hit=true;
                    this -> hitWall(sciany, i);
                }
                break;
            }
            case 2:
            {
                if(x >= sciany[i] -> getX() - ROCKET_Y && x <= sciany[i] -> getX() + OBSTACLE_SIZE && y + ROCKET_X >= sciany[i] -> getY() && y + ROCKET_X <= sciany[i] -> getY() +OBSTACLE_SIZE)
                {
                    hit=true;
                    this -> hitWall(sciany, i);
                }
                break;
            }
            case 3:
            {
                if(x + ROCKET_Y >= sciany[i] -> getX() && x - ROCKET_Y <= sciany[i] -> getX() + OBSTACLE_SIZE && y <= sciany[i] -> getY() + OBSTACLE_SIZE && y >= sciany[i] -> getY())
                {
                    hit=true;
                    this -> hitWall(sciany, i);
                }
                break;
            }
            }

            if(!sciany[i] -> getVisible())
            {
                this -> createBigExplosion(explosion, sciany[i] -> getX(), sciany[i] -> getY());

                if(sciany[i] -> getBase())
                {
                    if(!baseDestroyed && !youDied)
                        baseDestroyed = true;

                    Enemy::hasBase = false;
                }


                ModeGuardian();
            }
            else if(hit && sciany[i] -> getVisible())
                this -> createSmallExplosion(explosion);
        }
    }

    if(player -> getActive() && !hit)
    {
        switch(direction)
        {
        case 0:
        {
            if(x + ROCKET_X >= player -> getX() && x <= player -> getX() + TANK_SIZE  && y >= player -> getY() - ROCKET_Y  && y <= player -> getY() +TANK_SIZE)
            {
                hit=true;
                this -> hitPlayer(player);
            }
            break;
        }
        case 1:
        {
            if(x >= player -> getX() && x <= player -> getX() +TANK_SIZE && y >= player -> getY() - ROCKET_Y  && y <= player -> getY() +TANK_SIZE)
            {
                hit=true;
                this -> hitPlayer(player);
            }
            break;
        }
        case 2:
        {
            if(x >= player -> getX() - ROCKET_Y && x <= player -> getX() + TANK_SIZE && y + ROCKET_X >= player -> getY() && y + ROCKET_X <= player -> getY() +TANK_SIZE)
            {
                hit=true;
                this -> hitPlayer(player);
            }
            break;
        }
        case 3:
        {
            if(x + ROCKET_Y >= player -> getX() && x - ROCKET_Y <= player -> getX() + TANK_SIZE && y <= player -> getY() + TANK_SIZE && y >= player -> getY())
            {
                hit=true;
                this -> hitPlayer(player);
            }
            break;
        }
        }

        if(hit)
        {
            if(player -> getLife() == 0)
            {
                this -> createBigExplosion(explosion, player -> getX(), player -> getY());
                if(!youDied && !youDied)
                    youDied = true;

                player -> setActive(false);
                Enemy::hasPlayer = false;
                ClearPlayerArray(sciany);
            }
            else if(player -> getLife() != 0)
            {
                this -> createSmallExplosion(explosion);
            }
        }
    }

    for(short h = 0; h < ENEMIES && !hit; h++)
    {
        if(!enemy[h] -> getDead())
        {
            switch(direction)
            {
            case 0:
            {
                if(x + ROCKET_X >= enemy[h] -> getX() && x <= enemy[h] -> getX() + TANK_SIZE  && y >= enemy[h] -> getY() - ROCKET_Y  && y <= enemy[h] -> getY() +TANK_SIZE)
                {
                    hit=true;
                    this -> hitEnemy(enemy, player, h);
                }
                break;
            }
            case 1:
            {
                if(x >= enemy[h] -> getX() && x <= enemy[h] -> getX() +TANK_SIZE && y >= enemy[h] -> getY() - ROCKET_Y  && y <= enemy[h] -> getY() +TANK_SIZE)
                {
                    hit=true;
                    this -> hitEnemy(enemy, player, h);
                }
                break;
            }
            case 2:
            {
                if(x >= enemy[h] -> getX() - ROCKET_Y && x <= enemy[h] -> getX() + TANK_SIZE && y + ROCKET_X >= enemy[h] -> getY() && y + ROCKET_X <= enemy[h] -> getY() +TANK_SIZE)
                {
                    hit=true;
                    this -> hitEnemy(enemy, player, h);
                }
                break;
            }
            case 3:
            {
                if(x + ROCKET_Y >= enemy[h] -> getX() && x - ROCKET_Y <= enemy[h] -> getX() + TANK_SIZE && y <= enemy[h] -> getY() + TANK_SIZE && y >= enemy[h] -> getY())
                {
                    hit=true;
                    this -> hitEnemy(enemy, player, h);
                }
                break;
            }
            }

            if(enemy[h] -> getDead())
            {
                this -> createBigExplosion(explosion, enemy[h] -> getX(), enemy[h] -> getY());

                if(rand()%100 < BONUS_CHANCE)
                {
                    short choice=GiveBonusID(bonus);
                    bonus[choice] -> setX(enemy[h] -> getX());
                    bonus[choice] -> setY(enemy[h] -> getY());
                    bonus[choice] -> setVisible(true);
                }

                if(gameMode == 2)
                    enemiesKilled++;

                ModeGuardian();
            }
            else if(hit && !enemy[h] -> getDead())
            {
                this -> createSmallExplosion(explosion);

                short playerDirection = 0; //turn around if enemy get hitted by rocket

                if (direction == 1 || direction == 3)
                    playerDirection = direction - 1;
                else if(direction == 0 || direction == 2)
                    playerDirection = direction + 1;

                if(enemy[h] -> getDirection() != playerDirection)
                {
                    enemy[h] -> setTempDirection(playerDirection);
                    enemy[h] -> setDirection(playerDirection);
                    enemy[h] -> setDirectionCounter(1);
                    enemy[h] -> setTargetAhead(true);
                }
                else
                    enemy[h] -> setTargetAhead(true);
            }
        }
    }

    for(short h = 0; h < ROCKETS && !hit; h++)
    {
        if(rocket[h] -> getVisible() && rocket[h] != this && rocket[h] -> getX() > 0 && rocket[h] -> getY() > 0)
        {
            switch(direction)
            {
            case 0:
            {
                //1 horizontal rocket
                //2 vertical rocket

                if(rocket[h] -> getDirection() < 2)
                {
                    if(x + ROCKET_X >= rocket[h] -> getX()  && x + ROCKET_X <= rocket[h] -> getX() + ROCKET_X )
                        if((y >= rocket[h] -> getY() && y <= rocket[h] -> getY() + ROCKET_Y) || (y <= rocket[h] -> getY() && y + ROCKET_Y >= rocket[h] -> getY()))
                        {
                            hit=true;
                            this -> hitRocket(rocket, h);
                        }
                }
                else
                {
                    if(x + ROCKET_X >= rocket[h] -> getX()  && x + ROCKET_X <= rocket[h] -> getX() + ROCKET_Y )
                        if((y >= rocket[h] -> getY() && y <= rocket[h] -> getY() + ROCKET_X) || (y <= rocket[h] -> getY() && y + ROCKET_Y >= rocket[h] -> getY()))
                        {
                            hit=true;
                            this -> hitRocket(rocket, h);
                        }
                }

                break;
            }
            case 1:
            {
                if(rocket[h] -> getDirection() < 2)
                {
                    if(x + ROCKET_X <= rocket[h] -> getX() + ROCKET_X && x >= rocket[h] -> getX() )
                        if((y >= rocket[h] -> getY() && y <= rocket[h] -> getY() + ROCKET_Y) || (y <= rocket[h] -> getY() && y + ROCKET_Y >= rocket[h] -> getY()))
                        {
                            hit=true;
                            this -> hitRocket(rocket, h);
                        }
                }
                else
                {
                    if(x <= rocket[h] -> getX() + ROCKET_Y && x >= rocket[h] -> getX())
                        if((y >= rocket[h] -> getY() && y <= rocket[h] -> getY() + ROCKET_X) || (y <= rocket[h] -> getY() && y + ROCKET_Y >= rocket[h] -> getY()))
                        {
                            hit=true;
                            this -> hitRocket(rocket, h);
                        }
                }
                break;
            }
            case 2:
            {
                if(rocket[h] -> getDirection() < 2)
                {
                    if(y + ROCKET_X >= rocket[h] -> getY()  && y + ROCKET_X <= rocket[h] -> getY() + ROCKET_Y )
                        if((x >= rocket[h] -> getX() && x <= rocket[h] -> getX() + ROCKET_X) || (x <= rocket[h] -> getX() && x + ROCKET_Y >= rocket[h] -> getX()))
                        {
                            hit=true;
                            this -> hitRocket(rocket, h);
                        }
                }
                else
                {
                    if(y + ROCKET_X >= rocket[h] -> getY()  && y + ROCKET_X <= rocket[h] -> getY() + ROCKET_X )
                        if((x >= rocket[h] -> getX() && x <= rocket[h] -> getX() + ROCKET_Y) || (x <= rocket[h] -> getX() && x + ROCKET_Y >= rocket[h] -> getX()))
                        {
                            hit=true;
                            this -> hitRocket(rocket, h);
                        }
                }
                break;
            }
            case 3:
            {
                if(rocket[h] -> getDirection() < 2)
                {
                    if(y <= rocket[h] -> getY() + ROCKET_Y && y >= rocket[h] -> getY() )
                        if((x >= rocket[h] -> getX() && x <= rocket[h] -> getX() + ROCKET_X) || (x <= rocket[h] -> getX() && x + ROCKET_Y >= rocket[h] -> getX()))
                        {
                            hit=true;
                            this -> hitRocket(rocket, h);
                        }
                }
                else
                {
                    if(y + ROCKET_X <= rocket[h] -> getY()  && y >= rocket[h] -> getY() )
                        if((x >= rocket[h] -> getX() && x <= rocket[h] -> getX() + ROCKET_Y) || (x <= rocket[h] -> getX() && x + ROCKET_Y >= rocket[h] -> getX()))
                        {
                            hit=true;
                            this -> hitRocket(rocket, h);
                        }
                }
                break;
            }
            }

            if(hit)
                this -> createSmallExplosion(explosion);
        }
    }
};

short GiveRocketID(Rocket **rocket)
{
    short temp=0;
    for(short i=0; i<ROCKETS; i++)
    {
        if(!rocket[i]->getVisible())
        {
            temp=i;
            break;
        }
    }
    return temp;
};

void ClearRocket(Rocket ** rocket)
{
    Player::ammoTimer = 0;

    for(short i=0; i<ROCKETS; i++)
    {
        rocket[i] -> setX(0);
        rocket[i] -> setY(0);
        rocket[i] -> setDirection(0);
        rocket[i] -> setVisible(false);
        rocket[i] -> setTeam(true);
        rocket[i] -> setSpeed(0);
    }

    Rocket::rocketsCounter[0] = 0;
    Rocket::rocketsCounter[1] = 0;
}
