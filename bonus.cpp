#include "bonus.hpp"
#include "config.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "enemy.hpp"
#include "main.hpp"
#include "explosion.hpp"

extern short enemiesKilled;
extern unsigned short gameMode;

extern ALLEGRO_SAMPLE *sound[SOUNDS];

short Bonus::getX()
{
    return x;
};

void Bonus::setX( short _x)
{
    x = _x;
};

short Bonus::getY()
{
    return y;
};

void Bonus::setY( short _y)
{
    y = _y;
};

bool Bonus::getVisible()
{
    return visible;
};

void Bonus::setVisible( bool _visible)
{
    visible = _visible;
};

short GiveBonusID(Bonus ** bonus)
{
    short countBonuses = 0;
    for(short i=0; i < BONUSES; i++)
    {
        if(!bonus[i] -> getVisible())
        {
            countBonuses = i;
            break;
        }
    }
    return countBonuses;
};

void Airstrike(Enemy ** enemy, Explosion ** explosion, Bonus ** bonus, Player *player)
{
    short alive = CheckEnemyAlive(enemy);

    for(short i = 0; i < ENEMIES; i++)
    {
        if(!enemy[i] -> getDead())
        {
            enemy[i] -> setDead(true);
            enemy[i] -> setRespawnDelayTimer(1); //1 to start counting to respawn

            short choice = GiveExplosionID(explosion);
            explosion[choice] -> setX(enemy[i] -> getX());
            explosion[choice] -> setY(enemy[i] -> getY());
            explosion[choice] -> setSmall(false);
            explosion[choice] -> setVisible(true);
            explosion[choice] -> setLife(BIG_EXPLOSION_TIME);
            explosion[choice] -> createExplosion();

            if(rand()%100 <= BONUS_CHANCE)
            {
                choice = GiveBonusID(bonus);
                bonus[choice] -> setX(enemy[i] -> getX());
                bonus[choice] -> setY(enemy[i] -> getY());
                bonus[choice] -> setVisible(true);
            }

            if(gameMode == 2)
                enemiesKilled++;

            player -> setPoints(player -> getPoints() +((enemy[i] -> getDifficulty()+1) * POINTS_FOR_KILL ));
            player -> setKills(player -> getKills() + 1);
        }
    }
    if(alive > 0)
    {
        al_play_sample(sound[1], 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        ModeGuardian();
    }
};

void ClearBonus(Bonus ** bonus)
{
    for(short i=0; i < BONUSES; i++)
    {
        bonus[i] -> setX(0);
        bonus[i] -> setY(0);
        bonus[i] -> setVisible(false);
    }
}
