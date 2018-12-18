#include "fighter.h"

#define DISTANCE_UNIT 15
#define BULLET_DISTANCE_UNIT 5
#define ENEMY_DISTANCE_UNIT 1.5
#define BOSS_DISTANCE_UNIT 1
#define MAP_WIDTH 600
#define MAP_HEIGHT 840

/**************************MyFighter*****************************/

MyFighter::MyFighter()
{
    place.x = 300;
    place.y = 780;
    state.w = 30;
    state.h = 30;
    blood = 100;
    killpoint = 0;
}

MyFighter::~MyFighter()
{

}

bool MyFighter::if_dead()
{
    return !(blood > 0);
}

bool MyFighter::if_injured(int x,int y)
{
    return ((x >= place.x)&&(x <= place.x + state.w)&&(y >= place.y)&&(y <= place.y + state.h));
}

void MyFighter::blooddown(int num)
{
    blood -= num;
    return;
}

void MyFighter::addkillpoint(int points)
{
    killpoint += points;
    return;
}

int MyFighter::showpoint() const
{
    return killpoint;
}

int MyFighter::showblood() const
{
    if(blood <= 0)
        return 0;
    else
    {
        int b = blood;
        return b;
    }
}

fighter_place MyFighter::showplace() const
{
    fighter_place p = place;
    return p;
}

fighter_state MyFighter::showstate() const
{
    fighter_state s = state;
    return s;
}

void MyFighter::place_up()
{
    if(place.y < 0)
        place.y = 0;
    else
        place.y -= DISTANCE_UNIT;
    return;
}

void MyFighter::place_down()
{
    if(place.y > (MAP_HEIGHT - state.h))
        place.y = MAP_HEIGHT - state.h;
    else
        place.y += DISTANCE_UNIT;
    return;
}

void MyFighter::place_left()
{
    if(place.x < 0)
        place.x = 0;
    else
       place.x -= DISTANCE_UNIT;
    return;
}

void MyFighter::place_right()
{
    if(place.x > (MAP_WIDTH - state.w))
        place.x = MAP_WIDTH - state.w;
    else
        place.x += DISTANCE_UNIT;
    return;
}

void MyFighter::restart()
{
    blood = 100;
    killpoint = 0;
    place.x = 300;
    place.y = 780;
}

/***************************MyBullet*******************************/

#define BULLET_RADIUS 10
#define BULLET_INJURE 50

MyBullet::MyBullet()
{
    place.x = 0;
    place.y = 0;
    radius = BULLET_RADIUS;
}

MyBullet::MyBullet(int init_x,int init_y)
{
    place.x = init_x;
    place.y = init_y;
    radius = BULLET_RADIUS;
}

MyBullet::~MyBullet()
{

}

void MyBullet::place_up()
{
    place.y -= BULLET_DISTANCE_UNIT;
}

void MyBullet::place_down()
{
    place.y += BULLET_DISTANCE_UNIT;
}

void MyBullet::place_left()
{
    place.x -= BULLET_DISTANCE_UNIT;
}

void MyBullet::place_right()
{
    place.x += BULLET_DISTANCE_UNIT;
}

bool MyBullet::if_in_map()
{
    return ((place.x >= 0)&&(place.x <= MAP_WIDTH)&&(place.y >= 0)&&(place.y <= MAP_HEIGHT));
}

fighter_place MyBullet::showplace() const
{
    fighter_place p = place;
    return p;
}

int MyBullet::showradius() const
{
    int r = radius;
    return r;
}

/************************EnemyFighter**********************************/

#define random(x) rand()%x

int init_enemyfighterplace()
{
    srand(time(nullptr));
    return random(MAP_WIDTH - 25);
}

EnemyFighter::EnemyFighter()
{
    place.x = init_enemyfighterplace();
    place.y = 0;
    state.w = 25;
    state.h = 25;
    blood = 100;
}

EnemyFighter::EnemyFighter(int init_x)
{
    place.x = init_x;
    place.y = 0;
    state.w = 25;
    state.h = 25;
    blood = 100;
}

EnemyFighter::~EnemyFighter()
{

}

bool EnemyFighter::if_dead()
{
    return !(blood > 0);
}

bool EnemyFighter::if_injured(int x,int y)
{
    return ((x >= place.x)&&(x <= place.x + state.w)&&(y >= place.y)&&(y <= place.y + state.h));
}

bool EnemyFighter::if_in_map()
{
    return ((place.x >= 0)&&(place.x <= MAP_WIDTH)&&(place.y >= 0)&&(place.y <= MAP_HEIGHT));
}

void EnemyFighter::blooddown(int num)
{
    blood -= num;
    return;
}

fighter_place EnemyFighter::showplace() const
{
    fighter_place p = place;
    return p;
}

fighter_state EnemyFighter::showstate() const
{
    fighter_state s = state;
    return s;
}

void EnemyFighter::place_up()
{
    place.y -= ENEMY_DISTANCE_UNIT;
    return;
}

void EnemyFighter::place_down()
{
    place.y += ENEMY_DISTANCE_UNIT;
    return;
}

void EnemyFighter::place_left()
{
    place.x -= ENEMY_DISTANCE_UNIT;
    return;
}

void EnemyFighter::place_right()
{
    place.x += ENEMY_DISTANCE_UNIT;
    return;
}

/*************************EnemyBullet****************************************/

EnemyBullet::EnemyBullet()
{
    place.x = 0;
    place.y = 0;
    direction = 0;
    radius = BULLET_RADIUS;
}

EnemyBullet::EnemyBullet(int init_x,int init_y,int d)
{
    place.x = init_x;
    place.y = init_y;
    direction = d;
    radius = BULLET_RADIUS;
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::place_up()
{
    place.y -= BULLET_DISTANCE_UNIT;
}

void EnemyBullet::place_down()
{
    place.y += BULLET_DISTANCE_UNIT;
}

void EnemyBullet::place_left()
{
    place.x -= BULLET_DISTANCE_UNIT;
}

void EnemyBullet::place_right()
{
    place.x += BULLET_DISTANCE_UNIT;
}

bool EnemyBullet::if_in_map()
{
    return ((place.x >= 0)&&(place.x <= MAP_WIDTH)&&(place.y >= 0)&&(place.y <= MAP_HEIGHT));
}

fighter_place EnemyBullet::showplace() const
{
    fighter_place p = place;
    return p;
}

int EnemyBullet::showradius() const
{
    int r = radius;
    return r;
}

int EnemyBullet::showdirection() const
{
    int d = direction;
    return d;
}

/************************************EnemyBoss********************************************/

EnemyBoss::EnemyBoss()
{
    place.x = 225;
    place.y = 0;
    state.w = 150;
    state.h = 150;
    blood = 1000;
}

EnemyBoss::~EnemyBoss()
{

}

bool EnemyBoss::if_dead()
{
    return !(blood > 0);
}

bool EnemyBoss::if_injured(int x,int y)
{
    return ((x >= place.x)&&(x <= place.x + state.w)&&(y >= place.y)&&(y <= place.y + state.h));
}

void EnemyBoss::restart()
{
    place.x = 225;
    place.y = 0;
    state.w = 150;
    state.h = 150;
    blood = 1000;
}

void EnemyBoss::blooddown(int num)
{
    blood -= num;
    return;
}

fighter_place EnemyBoss::showplace() const
{
    fighter_place p = place;
    return p;
}

fighter_state EnemyBoss::showstate() const
{
    fighter_state s = state;
    return s;
}

int EnemyBoss::showblood() const
{
    int b = blood;
    return b;
}

void EnemyBoss::place_up()
{
    if(place.y < 0)
        place.y = 0;
    else
        place.y -= BOSS_DISTANCE_UNIT;
    return;
}

void EnemyBoss::place_down()
{
    if(place.y > (MAP_HEIGHT - state.h))
        place.y = MAP_HEIGHT - state.h;
    else
        place.y += BOSS_DISTANCE_UNIT;
    return;
}

void EnemyBoss::place_left()
{
    if(place.x < 0)
        place.x = 0;
    else
       place.x -= BOSS_DISTANCE_UNIT;
    return;
}

void EnemyBoss::place_right()
{
    if(place.x > (MAP_WIDTH - state.w))
        place.x = MAP_WIDTH - state.w;
    else
        place.x += BOSS_DISTANCE_UNIT;
    return;
}


