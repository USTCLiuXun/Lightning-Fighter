#ifndef FIGHTER_H
#define FIGHTER_H

#include <iostream>

typedef struct _fighter_place{
    int x;
    int y;
}fighter_place;

typedef struct _fighter_state{
    int w;
    int h;
}fighter_state;

class MyFighter
{
private:
    int blood;
    int killpoint;
    fighter_place place;
    fighter_state state;
public:
    MyFighter();
    ~MyFighter();

    bool if_dead();
    bool if_injured(int x,int y);
    void blooddown(int num);
    void addkillpoint(int points);
    int showpoint() const;
    int showblood() const;
    void restart();
    fighter_place showplace() const;
    fighter_state showstate() const;
    void place_up();
    void place_down();
    void place_left();
    void place_right();
};

class MyBullet
{
private:
    fighter_place place;
    int radius;
public:
    MyBullet();
    MyBullet(int init_x, int init_y);
    ~MyBullet();
    void place_up();
    void place_down();
    void place_left();
    void place_right();
    bool if_in_map();
    fighter_place showplace() const;
    int showradius() const;
};

class EnemyFighter
{
private:
    int blood;
    fighter_place place;
    fighter_state state;
public:
    EnemyFighter();
    EnemyFighter(int init_x);
    ~EnemyFighter();

    bool if_dead();
    bool if_injured(int x,int y);
    bool if_in_map();
    void blooddown(int num);
    fighter_place showplace() const;
    fighter_state showstate() const;
    void place_up();
    void place_down();
    void place_left();
    void place_right();
};

class EnemyBullet
{
private:
    fighter_place place;
    int radius;
    int direction;
public:
    EnemyBullet();
    EnemyBullet(int init_x, int init_y,int d);
    ~EnemyBullet();
    void place_up();
    void place_down();
    void place_left();
    void place_right();
    bool if_in_map();
    fighter_place showplace() const;
    int showradius() const;
    int showdirection() const;
};

class EnemyBoss
{
private:
    int blood;
    fighter_place place;
    fighter_state state;
public:
    EnemyBoss();
    ~EnemyBoss();
    bool if_dead();
    bool if_injured(int x,int y);
    void restart();
    void blooddown(int num);
    int showblood() const;
    fighter_place showplace() const;
    fighter_state showstate() const;
    void place_up();
    void place_down();
    void place_left();
    void place_right();
};

#endif // FIGHTER_H
