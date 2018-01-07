#include "bonus.hpp"
#include "explosion.hpp"


extern ALLEGRO_BITMAP *explosionBitmap;
extern ALLEGRO_BITMAP *smallExplosionBitmap;
extern ALLEGRO_BITMAP *baseBitmap;
extern ALLEGRO_BITMAP *baseDamageBitmap;
extern ALLEGRO_BITMAP *bonusBitmap;
extern ALLEGRO_BITMAP *background;
extern ALLEGRO_FONT * font30;
extern ALLEGRO_FONT * font60;
extern ALLEGRO_FONT * hudFont;
extern ALLEGRO_FONT * pauseFont;
extern ALLEGRO_FONT * campaignFont;



ALLEGRO_THREAD *FPSThread = NULL;


Bonus ** bonus = new Bonus*[BONUSES];
Explosion ** explosion = new Explosion*[EXPLOSIONS];

Player * playerCampaign = new Player;


bool pause = false;


short levels = 0;
short currentLevel = 0;
short enemiesAtOnce = 0;
short enemies = 0;
short enemiesKilled = 0;

bool levelComplete = false;
bool campaignFinish = false;
bool youDied = false;
bool baseDestroyed = false;


void RandomBonus()
{
    short number=rand()%100;
    if(Wall::baseExist)
    {
        if(number <= 18)
        {
            if(player -> getShoots() < 4)
                player -> setShoots(player -> getShoots() + 1);
        }
        else if(number >= 19 && number <= 39)
        {
            player -> setLife(player -> getLife() + 1);
        }
        else if(number >= 40 && number <= 52)
        {
            if(player -> getAmmoSpeed() < 1 + AMMO_SPEED)
                player -> setAmmoSpeed(player -> getAmmoSpeed() + 1);
        }
        else if(number >= 53 && number <= 70)
        {
            Airstrike(enemy, explosion, bonus, player);
        }
        else if(number >= 71 && number <= 86)
        {
            wall[Wall::baseID] -> setLife(wall[Wall::baseID] -> getLife() + 1);
        }
        else if(number >= 87)
        {
            if(player -> getAmmoTimer() > 30)
                player -> setAmmoTimer(player -> getAmmoTimer() - 10);
        }
    }
    else
    {
        if(number <= 20)
        {
            if(player -> getShoots() < 4)
                player -> setShoots(player -> getShoots() + 1);
        }
        else if(number >= 21 && number <= 40)
        {
            player -> setLife(player -> getLife() + 1);
        }
        else if(number >= 41 && number <= 54)
        {
            if(player -> getAmmoSpeed() < 1 + AMMO_SPEED)
                player -> setAmmoSpeed(player -> getAmmoSpeed() + 1);
        }
        else if(number >= 55 && number <= 79)
        {
            Airstrike(enemy, explosion, bonus, player);
        }
        else if(number >= 80)
        {
            if(player -> getAmmoTimer() > 30)
                player -> setAmmoTimer(player -> getAmmoTimer() - 10);
        }
    }
};

static void *FPScounter(ALLEGRO_THREAD *thread, void * Args)
{
    while(1)
    {
        al_rest(1.0);
        FPS1s=FPS;
        FPS=0;
    }

    return NULL;
};

void CampaignMapCreate()
{
    if(levels == 0)
    {
        iniFile = al_load_config_file("level1.tank");
        if(!iniFile)
            ShowError("level1.tank", 0);

        levels = atoi(al_get_config_value(iniFile, "options", "levels"));
        if(levels == 0)
            ShowError("error", 3);

        al_destroy_config(iniFile);
    }
    enemiesKilled = 0;
    currentLevel ++;
    player -> campaingInitialize(currentLevel);
    WallCampaingInitialize(wall, player, enemy, currentLevel, false);
    EnemycampaingInitialize(enemy, currentLevel, wall, player);
}

void Play()
{
    if(DEBUG && gameMode != 2)
    {
        player -> initialize(200,500,15,2,1,AMMO_SPEED - 1, 0, 1, 30);

        short choice = GiveWallID(wall);
        wall[choice] -> create(wall, player, enemy, 300,50,true,2,false);
        if(gameMode == 1)
            wall[choice+1] -> create(wall, player, enemy, 300,100,true,3,true);

        wall[choice+2] -> create(wall, player, enemy, 300,150,true,2,false);
        wall[choice+3] -> create(wall, player, enemy, 300,200,true,2,false);
        wall[choice+4] -> create(wall, player, enemy, 300,250,true,2,false);
        wall[choice+5] -> create(wall, player, enemy, 300,300,true,2,false);
        wall[choice+6] -> create(wall, player, enemy, 300,350,true,2,false);
        wall[choice+7] -> create(wall, player, enemy, 300,400,true,2,false);
        wall[choice+8] -> create(wall, player, enemy, 300,450,true,2,false);
        wall[choice+9] -> create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+10] -> create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+11] -> create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+12] -> create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+13] -> create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+14] -> create(wall, player, enemy, 100,100,true,2,false);
        wall[choice+21] -> create(wall, player, enemy, 200,400,false,2,false);
        for(short i=1 ; i<8 ; i++)
        {
            wall[choice+21+i] -> create(wall, player, enemy, 100,100,false,2,false);
        }
        enemy[0] -> spawn(450,50,2,AMMO_SPEED, 0, 80, 0, wall, player, enemy);
        enemy[1] -> spawn(800,500,2,AMMO_SPEED, 0,80, 1, wall, player, enemy);
    }
    else if(!DEBUG && gameMode == 0)
    {
        player -> initialize(10,10,3,1,0,AMMO_SPEED - 1, 0, 0, 60);
        enemy[0] -> spawn(500,50,2,AMMO_SPEED, 0, 80, 0, wall, player, enemy);
        enemy[1] -> spawn(500,500,2,AMMO_SPEED + 1, 1,50, 2, wall, player, enemy);
        enemy[2] -> spawn(700,350,2,AMMO_SPEED, 0,60, 1, wall, player, enemy);

        short choice = GiveWallID(wall);
        for(short i=1 ; i<30 ; i++)
        {
            wall[choice+i] -> create(wall, player, enemy, 100,100,true,2,false);
        }

        choice = GiveWallID(wall);
        for(short i=1 ; i<10 ; i++)
        {
            wall[choice+i] -> create(wall, player, enemy, 100,100,false,2,false);
        }
    }
    else if(!DEBUG && gameMode == 1)
    {
        player -> initialize(10,10,3,1,0,AMMO_SPEED - 1, 0, 0, 60);
        enemy[0] -> spawn(500,50,2,AMMO_SPEED, 0, 80, 0, wall, player, enemy);
        enemy[1] -> spawn(500,500,2,AMMO_SPEED + 1, 1,50, 2, wall, player, enemy);
        enemy[2] -> spawn(700,350,3,AMMO_SPEED, 0,60, 1, wall, player, enemy);

        short choice = GiveWallID(wall);
        wall[choice] -> create(wall, player, enemy, 0,300,true,3,true);
        wall[choice+1] -> create(wall, player, enemy, 0,250,true,2,false);
        wall[choice+2] -> create(wall, player, enemy, 50,250,true,2,false);
        wall[choice+3] -> create(wall, player, enemy, 50,300,true,2,false);
        wall[choice+4] -> create(wall, player, enemy, 50,350,true,2,false);
        wall[choice+5] -> create(wall, player, enemy, 0,350,true,2,false);
        choice = GiveWallID(wall);
        for(short i=1 ; i<35 ; i++)
        {
            wall[choice+i] -> create(wall, player, enemy, 100,100,true,2,false);
        }
        choice = GiveWallID(wall);
        for(short i=1 ; i<10 ; i++)
        {
            wall[choice+i] -> create(wall, player, enemy, 100,100,false,2,false);
        }
    }

    if(gameMode == 2)
        CampaignMapCreate();

    SetBaseID(wall);
    SetImmortallWallsVisible(wall);

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT ev;
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(FPSTimer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(FPSTimer);
    while(!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE) && !gameover)
    {
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE && pause )
                break;

            if(ev.keyboard.keycode == ALLEGRO_KEY_P && pause && counterComunicat == 0)
            {
                pause = false;
                al_flush_event_queue(event_queue);
                al_start_timer(FPSTimer);
            }
            else if(ev.keyboard.keycode == ALLEGRO_KEY_P && !pause && counterComunicat == 0)
            {
                pause = true;
                al_stop_timer(FPSTimer);
                al_flush_event_queue(event_queue);
                al_draw_textf( pauseFont, al_map_rgb(255,255,255), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "PAUSED");
                al_flip_display();
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_R && DEBUG)
            {
                Airstrike(enemy, explosion, bonus, player);
            }
        }

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_get_keyboard_state(&keyboard);

            al_clear_to_color(al_map_rgb( 0, 0, 0));
            al_draw_bitmap (background, 960, 0, 0);
            al_draw_textf( hudFont, HUD_COLOR, 1120, 60, ALLEGRO_ALIGN_CENTER, "Points: %i",player -> getPoints());
            al_draw_textf( hudFont, HUD_COLOR, 1120, 110, ALLEGRO_ALIGN_CENTER, "Kills: %i",player -> getKills());
            al_draw_textf( hudFont, HUD_COLOR, 1120, 160, ALLEGRO_ALIGN_CENTER, "Lifes: %i",player -> getLife());
            al_draw_textf( hudFont, HUD_COLOR, 1120, 210, ALLEGRO_ALIGN_CENTER, "Ammo Speed: %i / 3",player -> getAmmoSpeed() - AMMO_SPEED + 2);
            al_draw_textf( hudFont, HUD_COLOR, 1120, 260, ALLEGRO_ALIGN_CENTER, "Rockets: %i / 4",player -> getShoots());
            al_draw_textf( hudFont, HUD_COLOR, 1120, 310, ALLEGRO_ALIGN_CENTER, "Reload Speed: %i",player -> getAmmoTimer());

            if(Wall::baseExist == true && gameMode != 2)
                al_draw_textf( hudFont, HUD_COLOR, 1120, 360, ALLEGRO_ALIGN_CENTER, "Base: %i",wall[Wall::baseID] -> getLife());
            else if(gameMode == 2 && Wall::baseExist == false)
            {
                al_draw_textf( hudFont, HUD_COLOR, 1120, 10, ALLEGRO_ALIGN_CENTER, "Level: %i/%i",currentLevel, levels);
                al_draw_textf( hudFont, HUD_COLOR, 1120, 360, ALLEGRO_ALIGN_CENTER, "Progress: %i/%i",enemiesKilled, enemies);
            }
            else if(gameMode == 2 && Wall::baseExist == true)
            {
                al_draw_textf( hudFont, HUD_COLOR, 1120, 360, ALLEGRO_ALIGN_CENTER, "Base: %i",wall[Wall::baseID] -> getLife());
                al_draw_textf( hudFont, HUD_COLOR, 1120, 10, ALLEGRO_ALIGN_CENTER, "Level: %i/%i",currentLevel, levels);
                al_draw_textf( hudFont, HUD_COLOR, 1120, 410, ALLEGRO_ALIGN_CENTER, "Progress: %i/%i",enemiesKilled, enemies);
            }
			
			if(FPS_COUNTER)
				al_draw_textf( font30, HUD_COLOR, 1100, 480, ALLEGRO_ALIGN_CENTER, "FPS %i ",FPS1s);
			
            if(DEBUG)
            {
                al_draw_textf( font30, HUD_COLOR, 1110, 510, ALLEGRO_ALIGN_CENTER, "Target %i x %i, Dest %i x %i",enemy[0] -> getDestinationX(),   enemy[0] -> getDestinationY(), enemy[0] -> getTempDestinationX(), enemy[0] -> getTempDestinationY());
                al_draw_textf( font30, HUD_COLOR, 1100, 540, ALLEGRO_ALIGN_CENTER, "E0 %i x %i D %i BASE: %i",enemy[0] -> getX(),   enemy[0] -> getY(), enemy[0] -> getTempDirection(), Enemy::attackBase[0]);
                al_draw_textf( font30, HUD_COLOR, 1100, 570, ALLEGRO_ALIGN_CENTER, "Player %i x %i See %s",player -> getX(),   player -> getY(), Enemy::hasPlayer ? "true" : "false");
                if(Wall::baseExist == true)
                    al_draw_textf( font30, HUD_COLOR, 1100, 600, ALLEGRO_ALIGN_CENTER, "Base %i x %i See %s",wall[Wall::baseID] -> getX(),   wall[Wall::baseID] -> getY(), Enemy::hasBase ? "true" : "false");
            }

            for(short t = 0; t < OBSTACLES; t++)
            {
                if(wall[t] -> getVisible())
                {
                    if(!wall[t] -> getDestroyable())
                        al_draw_bitmap (wallBitmap,wall[t] -> getX(),wall[t] -> getY(),0);
                    else
                    {
                        if(!wall[t] -> getBase())
                            al_draw_bitmap (immortalWallBitmap,wall[t] -> getX(),wall[t] -> getY(),0);
                        else
                        {
                            if(wall[t] -> getLife() == 1)
                                al_draw_bitmap (baseDamageBitmap,wall[t] -> getX(),wall[t] -> getY(),0);
                            else
                                al_draw_bitmap (baseBitmap,wall[t] -> getX(),wall[t] -> getY(),0);
                        }
                    }
                }
            }

            for(short t = 0; t < BONUSES; t++)
            {
                if(bonus[t] -> getVisible())
                    al_draw_bitmap (bonusBitmap,bonus[t] -> getX(),bonus[t] -> getY(), 0);
            }

            for(short t = 0; t < EXPLOSIONS; t++)
            {
                if(explosion[t] -> getVisible())
                {
                    if(explosion[t] -> getSmall())
                    {
                        short which = explosion[t] -> getLife() % 4;

                        if(which == 0)
                        {
                            explosion[t] -> setAnimationWidth(explosion[t] -> getAnimationWidth() + 1);
                            if(explosion[t] -> getAnimationWidth() == 4)
                            {
                                explosion[t] -> setAnimationWidth(0);
                                explosion[t] -> setAnimationHeight(explosion[t] -> getAnimationHeight()+ 1);
                            }
                        }

                        al_draw_bitmap_region(smallExplosionBitmap, explosion[t] -> getAnimationWidth() * SMALL_ANIMATION_SIZE,  explosion[t] -> getAnimationHeight() * SMALL_ANIMATION_SIZE, SMALL_ANIMATION_SIZE, SMALL_ANIMATION_SIZE, explosion[t] -> getX(), explosion[t] -> getY(), 0);
                    }
                    else
                    {
                        short which = explosion[t] -> getLife() % 4;

                        if(which == 0)
                        {
                            explosion[t] -> setAnimationWidth(explosion[t] -> getAnimationWidth() + 1);
                            if(explosion[t] -> getAnimationWidth() == 4)
                            {
                                explosion[t] -> setAnimationWidth(0);
                                explosion[t] -> setAnimationHeight(explosion[t] -> getAnimationHeight()+ 1);
                            }
                        }

                        al_draw_bitmap_region(explosionBitmap, explosion[t] -> getAnimationWidth() * BIG_ANIMATION_SIZE,  explosion[t] -> getAnimationHeight() * BIG_ANIMATION_SIZE, BIG_ANIMATION_SIZE, BIG_ANIMATION_SIZE, explosion[t] -> getX(), explosion[t] -> getY(), 0);
                    }

                    explosion[t] -> setLife(explosion[t] -> getLife() - 1);

                    if(explosion[t] -> getLife() == 0)
                    {
                        explosion[t] -> setVisible(false);
                        explosion[t] -> setAnimationHeight(0);
                        explosion[t] -> setAnimationWidth(0);
                    }
                }
            }

            if(player -> getActive())
            {
                if(al_key_down(&keyboard, ALLEGRO_KEY_RIGHT))
                    player -> move(0);
                if(al_key_down(&keyboard, ALLEGRO_KEY_LEFT))
                    player -> move(1);
                if(al_key_down(&keyboard, ALLEGRO_KEY_DOWN))
                    player -> move(2);
                if(al_key_down(&keyboard, ALLEGRO_KEY_UP))
                    player -> move(3);

                player -> checkColision(wall, enemy, bonus);

                switch(player -> getDirection())
                {
                case 0:
                    al_draw_rotated_bitmap(playerTank, 0, 0,  player -> getX(), player -> getY(), 0, ALLEGRO_FLIP_HORIZONTAL);
                    break; //right
                case 1:
                    al_draw_rotated_bitmap(playerTank, 0, 0,  player -> getX(), player -> getY(), 0, 0);
                    break; //left
                case 2:
                    al_draw_rotated_bitmap(playerTank, 0, 0,  player -> getX(), player -> getY() +50, 3*ALLEGRO_PI/2, 0);
                    break; //down
                case 3:
                    al_draw_rotated_bitmap(playerTank, 0, 0,  player -> getX() +50, player -> getY(), ALLEGRO_PI/2, 0);
                    break; //up
                }

                if(al_key_down(&keyboard, ALLEGRO_KEY_SPACE) && Rocket::rocketsCounter[0] < player -> getShoots() && Player::ammoTimer > player -> getAmmoTimer())
                {
                    short choice = GiveRocketID(rocket);
                    rocket[choice] -> shoot(player);
                }
            }

            for(short u = 0; u < ENEMIES; u++)
            {
                if(!enemy[u] -> getDead())
                {
                    enemy[u] -> enemyAI(wall, enemy, player, bonus, rocket);
                    if(enemy[u] -> getDifficulty() == 0)
                        enemyTankBitmap = enemyNormalTank;
                    else if(enemy[u] -> getDifficulty() == 1)
                        enemyTankBitmap = enemyFastTank;
                    else if(enemy[u] -> getDifficulty() == 2)
                        enemyTankBitmap = enemyMidTank;
                    else if(enemy[u] -> getDifficulty() == 3)
                        enemyTankBitmap = enemyHeavyTank;

                    switch(enemy[u] -> getDirection())
                    {
                    case 0:
                        al_draw_rotated_bitmap(enemyTankBitmap, 0, 0,  enemy[u] -> getX(), enemy[u] -> getY(), 0, ALLEGRO_FLIP_HORIZONTAL);
                        break; //right
                    case 1:
                        al_draw_rotated_bitmap(enemyTankBitmap, 0, 0,  enemy[u] -> getX(), enemy[u] -> getY(), 0, 0);
                        break; //left
                    case 2:
                        al_draw_rotated_bitmap(enemyTankBitmap, 0, 0,  enemy[u] -> getX(), enemy[u] -> getY() +50, 3*ALLEGRO_PI/2, 0);
                        break; //down
                    case 3:
                        al_draw_rotated_bitmap(enemyTankBitmap, 0, 0,  enemy[u] -> getX() +50, enemy[u] -> getY(), ALLEGRO_PI/2, 0);
                        break; //up
                    }
                }
            }

            for(short g = 0; g < ROCKETS; g++)
            {
                if(rocket[g] -> getVisible())
                {
                    rocket[g] -> move(rocket, wall, player, enemy, explosion, bonus);

                    switch(rocket[g] -> getDirection())
                    {
                    case 0:
                        al_draw_rotated_bitmap(ammoBitmap, 0, 0,  rocket[g] -> getX(), rocket[g] -> getY(), 0, ALLEGRO_FLIP_HORIZONTAL);
                        break;
                    case 1:
                        al_draw_rotated_bitmap(ammoBitmap, 0, 0,  rocket[g] -> getX(), rocket[g] -> getY(), 0, 0);
                        break;
                    case 2:
                        al_draw_rotated_bitmap(ammoBitmap, 0, 0,  rocket[g] -> getX(), rocket[g] -> getY(), 3*ALLEGRO_PI/2, 0);
                        break;
                    case 3:
                        al_draw_rotated_bitmap(ammoBitmap, 0, 0,  rocket[g] -> getX(), rocket[g] -> getY(), ALLEGRO_PI/2, 0);
                        break;
                    }
                }
            }

            if(levelComplete)
            {
                al_draw_textf( campaignFont, al_map_rgb(255,51,51), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "LEVEL %i COMPLETE", currentLevel);
                counterComunicat++;
            }
            else if(campaignFinish)
            {
                al_draw_textf( campaignFont, al_map_rgb(255,51,51), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "CONGRATULATIONS YOU WON");
                counterComunicat++;
            }
            else if(youDied)
            {
                al_draw_textf( campaignFont, al_map_rgb(255,51,51), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "You Died !");
                counterComunicat++;
            }
            else if(baseDestroyed)
            {
                al_draw_textf( campaignFont, al_map_rgb(255,51,51), BATTLEFIELD_WIDTH/2, BATTLEFIELD_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Base was destroyed !");
                counterComunicat++;
            }

            al_flip_display();
            FPS++;

            if(counterComunicat == 2 * FRAMERATE)
            {
                if(levelComplete)
                {
                    *playerCampaign = *player;
                    levelComplete = false;
                    pause = false;
                    al_flush_event_queue(event_queue);
                    al_stop_timer(FPSTimer);
                    al_rest(1.0);
                    ClearVariables();
                    CampaignMapCreate();
                    al_start_timer(FPSTimer);
                }
                if(campaignFinish)
                {
                    al_stop_timer(FPSTimer);
                    pause = false;
                    al_flush_event_queue(event_queue);
                    al_rest(1.0);
                    gameover = true;
                }
                if(youDied || baseDestroyed)
                {
                    al_stop_timer(FPSTimer);
                    pause = false;
                    al_flush_event_queue(event_queue);
                    al_rest(1.0);
                    gameover=true;
                }
            }

            if(Player::ammoTimer <= player -> getAmmoTimer())
                Player::ammoTimer++;

            for(short u = 0; u < ENEMIES; u++)
            {
                if(enemy[u] -> getDead())
                {
                    if(enemy[u] -> getRespawnDelayTimer() == RESPAWN_TIMER)
                    {
                        enemy[u] -> setRespawnDelayTimer(-1);
                        ModeGuardian();
                    }
                    else if(enemy[u] -> getRespawnDelayTimer() >= 1)
                        enemy[u] -> setRespawnDelayTimer(enemy[u] -> getRespawnDelayTimer() + 1);

                }
                else
                {
                    if(enemy[u] -> getAmmoTimer() == enemy[u] -> getAmmoDelay())
                    {
                        enemy[u] -> setAmmoTimer(-1);
                        enemy[u] -> setCanShoot(true);
                    }

                    if(enemy[u] -> getAmmoTimer() >= 1)
                        enemy[u] -> setAmmoTimer(enemy[u] -> getAmmoTimer() + 1);
                }
            }

            if(Wall::respawnTimer == RESPAWN_TIMER)
                ModeGuardian();

            if(Wall::respawnTimer >= 1)
                Wall::respawnTimer++;

            if(Enemy::hasPlayer)
                Enemy::playerTimer++;

            if(Enemy::playerTimer == 200)
            {
                Enemy::playerTimer = 0;
                Enemy::hasPlayer = false;
                ClearPlayerArray(wall);
            }

        }
    }
    al_destroy_event_queue(event_queue);
    al_destroy_timer(FPSTimer);

    gameover = true;
};

void ClearVariables()
{
    ClearBonus(bonus);
    ClearExplosion(explosion);

    levelComplete = false;
    campaignFinish = false;
    youDied = false;
    baseDestroyed = false;
    SetTarget(enemy, player);
}

void InitializeVariables()
{
    for (short i = 0; i < BONUSES; i++)
    {
        bonus[i] = new Bonus;
    }

    for (short i = 0; i < EXPLOSIONS; i++)
    {
        explosion[i] = new Explosion;
    }
}

void InitializeGame()
{
    FontsInitialize();
    HighscoreLoad();
    SoundInitialize();
}

void GameMenu()
{
    while(1)
    {
        levels = 0;
        currentLevel = 0;

        HighscoreSave(gameMode, player);
    }
}

void ModeGuardian()
{
    switch(gameMode)
    {
    case 0:
    {
        short enemyAlive = CheckEnemyAlive(enemy);
        short wallExist = CheckExistsWalls(wall);

        if(enemyAlive == 0)
            Enemy::hasPlayer = false;

        if(wallExist < 12)
        {
            if(Wall::respawnTimer == RESPAWN_TIMER)
            {
                Wall::respawnTimer = -1;
                for(short i=1 ; i<10 ; i++)
                {
                    short choice = GiveWallID(wall);
                    wall[choice] -> create(wall, player, enemy, 100,100,true,2,false);
                }
            }
            else if(Wall::respawnTimer <= 0)
                Wall::respawnTimer = 1;
        }

        if(enemyAlive < ENEMY_SIMULTANEOUSLY)
        {
            SetTarget(enemy, player);
            for(short i=0 ; i<ENEMY_SIMULTANEOUSLY ; i++)
            {
                if(enemy[i] -> getDead() && enemy[i] -> getRespawnDelayTimer() == -1)
                {
                    short _x = rand()%400 + 500;
                    short _y = rand()%(BATTLEFIELD_HEIGHT);
                    short _difficulty = rand()%4;
                    switch(_difficulty)
                    {
                    case 0:
                    {
                        enemy[i] -> spawn(_x,_y, 2, AMMO_SPEED + 1, 1, 80, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 1:
                    {
                        enemy[i] -> spawn(_x,_y, 3, AMMO_SPEED, 1, 60, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 2:
                    {
                        enemy[i] -> spawn(_x,_y, 2, AMMO_SPEED + 1, 1, 50, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 3:
                    {
                        enemy[i] -> spawn(_x,_y, 4, AMMO_SPEED + 1, 1, 60, _difficulty, wall, player, enemy);
                        break;
                    }
                    }
                }
            }
        }
        break;
    }
    case 1:
    {
        short enemyAlive = CheckEnemyAlive(enemy);
        short wallExist = CheckExistsWalls(wall);

        if(enemyAlive == 0)
        {
            Enemy::hasPlayer = false;
            Enemy::hasBase = false;
        }

        if(wallExist < 12)
        {
            if(Wall::respawnTimer == RESPAWN_TIMER)
            {
                Wall::respawnTimer = -1;
                for(short i=1 ; i<10 ; i++)
                {
                    short choice = GiveWallID(wall);
                    wall[choice] -> create(wall, player, enemy, 100,100,true,2,false);
                }
            }
            else if(Wall::respawnTimer <= 0)
                Wall::respawnTimer = 1;
        }
        if(enemyAlive < ENEMY_SIMULTANEOUSLY)
        {
            SetTarget(enemy, player);
            for(short i=0 ; i<ENEMY_SIMULTANEOUSLY ; i++)
            {
                if(enemy[i] -> getDead() && enemy[i] -> getRespawnDelayTimer() == -1)
                {
                    short _x = rand()%400 + 500;
                    short _y = rand()%(BATTLEFIELD_HEIGHT);
                    short _difficulty = rand()%4;
                    switch(_difficulty)
                    {
                    case 0:
                    {
                        enemy[i] -> spawn(_x,_y, 2, AMMO_SPEED, 1, 80, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 1:
                    {
                        enemy[i] -> spawn(_x,_y, 3, AMMO_SPEED, 1, 60, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 2:
                    {
                        enemy[i] -> spawn(_x,_y, 2, AMMO_SPEED + 1, 1, 50, _difficulty, wall, player, enemy);
                        break;
                    }
                    case 3:
                    {
                        enemy[i] -> spawn(_x,_y, 4, AMMO_SPEED + 1, 1, 60, _difficulty, wall, player, enemy);
                        break;
                    }
                    }
                }
            }
        }

        break;
    }
    case 2:
    {
        short enemyAlive = CheckEnemyAlive(enemy);

        if(enemyAlive == 0)
        {
            Enemy::hasPlayer = false;
            if(Wall::baseExist)
                Enemy::hasBase = false;
        }

        if(enemyAlive == 0 && enemies - enemiesKilled == 0)
        {
            if(currentLevel == levels)
            {
                if(!campaignFinish)
                    campaignFinish = true;
            }
            else
            {
                if(!levelComplete)
                    levelComplete = true;
            }
        }

        else if(enemyAlive < enemiesAtOnce && enemies - enemiesKilled - enemyAlive > 0)
        {
            SetTarget(enemy, player);
            for(short i=0 ; i<ENEMIES ; i++)
            {
                if(enemy[i] -> getDead() && enemy[i] -> getRespawnDelayTimer() == -1)
                {
                    EnemyCampaignDrop(enemy, currentLevel, wall, player);
                }
            }
        }
        short wallExist = CheckExistsWalls(wall);
        if(wallExist < 12)
        {
            if(Wall::respawnTimer == RESPAWN_TIMER)
            {
                Wall::respawnTimer = -1;
                WallCampaingInitialize(wall, player, enemy, currentLevel, true);
            }
            else if(Wall::respawnTimer <= 0)
                Wall::respawnTimer = 1;
        }

        break;
    }
    }
}

int main()
{
    InitializeVariables();
    InitializeGame();
    GameMenu();

    return 0;
};
