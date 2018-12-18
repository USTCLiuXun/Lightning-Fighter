#include "mainwindow.h"
#include "ui_mainwindow.h"

bool IF_GAME_START;
bool IF_BULLET_EMPTY;
bool IF_YOU_LIVE;
bool IF_YOU_WIN;
bool IF_BOSS_TIME;
bool PICTURE_CHANGE_MARK;

#define ATTACK_TO_BOSS 50
#define ATTACK_TO_ENEMY 200
#define ATTACK_TO_YOU 5
#define GAME_LEVEL 15

#define random(x) rand()%x

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    IF_GAME_START = false;
    IF_BULLET_EMPTY = false;
    IF_YOU_LIVE = true;
    IF_YOU_WIN = false;
    IF_BOSS_TIME = false;
    PICTURE_CHANGE_MARK = false;

    this->setFixedWidth(600);
    this->setFixedHeight(840);
    this->setWindowTitle("Lightning Fighter");

    QFont font("Microsoft YaHei", 20, 35);
    QFont fontend("Microsoft YaHei", 20, 35);
    QFont fonthelp("Microsoft YaHei", 15, 30);

    Label_killpoint = new QLabel(this);
    Label_killpoint->resize(150,50);
    Label_killpoint->setText("Points: " + QString::number(Myfighter.showpoint()));
    Label_killpoint->setAlignment(Qt::AlignCenter);
    Label_killpoint->setFont(font);
    Label_killpoint->move(0,700);

    Label_youblood = new QLabel(this);
    Label_youblood->resize(150,50);
    Label_youblood->setText("Blood: " + QString::number(Myfighter.showblood()));
    Label_youblood->setAlignment(Qt::AlignCenter);
    Label_youblood->setFont(font);
    Label_youblood->move(450,750);

    Label_bossblood = new QLabel(this);
    Label_bossblood->resize(150,50);
    Label_bossblood->setText("Boss: " + QString::number(Boss.showblood()));
    Label_bossblood->setAlignment(Qt::AlignCenter);
    Label_bossblood->setFont(font);
    Label_bossblood->move(0,750);

    Label_endfail = new QLabel(this);
    Label_endfail->resize(280,100);
    Label_endfail->setText("你太弱了，真挫");
    Label_endfail->setAlignment(Qt::AlignCenter);
    Label_endfail->setFont(fontend);
    Label_endfail->move(160,600);

    Label_endwin = new QLabel(this);
    Label_endwin->resize(280,100);
    Label_endwin->setText("大佬我错了...");
    Label_endwin->setAlignment(Qt::AlignCenter);
    Label_endwin->setFont(fontend);
    Label_endwin->move(160,600);

    Label_help = new QLabel(this);
    Label_help->resize(250,50);
    Label_help->setText("方向键：WASD 攻击：K");
    Label_help->setAlignment(Qt::AlignCenter);
    Label_help->setFont(fonthelp);
    Label_help->move(0,760);

    Label_Author = new QLabel(this);
    Label_Author->resize(250,50);
    Label_Author->setText("Author:LiuXun");
    //Label_Author->setAlignment(Qt::AlignCenter);
    Label_Author->setFont(fonthelp);
    Label_Author->move(20,790);

    Button_start = new QPushButton(this);
    Button_start->setText("开始");
    Button_start->resize(150,30);
    Button_start->setStyleSheet("QPushButton::pressed{background-color: rgb(87,250,255);border-radius:5px;border-style:inset;}");
    Button_start->move(230,650);

    Button_quit = new QPushButton(this);
    Button_quit->setText("退出");
    Button_quit->resize(150,30);
    Button_quit->setStyleSheet("QPushButton::pressed{background-color: rgb(87,250,255);border-radius:5px;border-style:inset;}");
    Button_quit->move(230,700);

    Button_restart = new QPushButton(this);
    Button_restart->setText("重新开始");
    Button_restart->resize(150,30);
    Button_restart->setStyleSheet("QPushButton::pressed{background-color: rgb(87,250,255);border-radius:5px;border-style:inset;}");
    Button_restart->move(215,700);

    Button_end = new QPushButton(this);
    Button_end->setText("小火汁你说什么？");
    Button_end->resize(150,30);
    Button_end->setStyleSheet("QPushButton::pressed{background-color: rgb(87,250,255);border-radius:5px;border-style:inset;}");
    Button_end->move(215,720);

    connect(Button_quit, &QPushButton::released, this, &MainWindow::close);
    connect(Button_start, SIGNAL(clicked()), this, SLOT(GameStart()));
    connect(Button_restart, SIGNAL(clicked()), this, SLOT(GameRestart()));
    connect(Button_end,SIGNAL(clicked()), this, SLOT(EndPictureChange()));

    QTimer *timer = new QTimer(this);
    timer->start(100);

    QTimer *bullettimer = new QTimer(this);
    bullettimer->setSingleShot(false);
    connect(bullettimer, SIGNAL(timeout()),this,SLOT(MyBulletUpdate()));
    bullettimer->start(200);

    QTimer *enemytimer = new QTimer(this);
    enemytimer->setSingleShot(false);
    connect(enemytimer, SIGNAL(timeout()),this,SLOT(EnemyFighterUpdate()));
    enemytimer->start(1500);

    QTimer *enemybullettimer = new QTimer(this);
    enemybullettimer->setSingleShot(false);
    connect(enemybullettimer, SIGNAL(timeout()),this,SLOT(EnemyBulletUpdate()));
    enemybullettimer->start(800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if(!IF_GAME_START)
        BootInterface();
    else if((IF_GAME_START)&&(IF_YOU_LIVE))
        GameInterface();
    else
        EndInterface();
    update();
    return;
}

void MainWindow::BootInterface()
{
    QPainter painter(this);
    QBrush brush;
    brush.setTextureImage(QImage("/home/liuxun/C++/bigproject/material/boot3.jpg"));

    painter.setBrush(brush);
    painter.drawRoundedRect(this->rect(),1,1);

    Button_quit->move(230,700);

    IF_YOU_LIVE = true;
    IF_YOU_WIN = false;
    IF_BULLET_EMPTY = false;
    IF_BOSS_TIME = false;
    IF_GAME_START = false;
    PICTURE_CHANGE_MARK = false;
    Boss.restart();

    Button_start->show();
    Button_quit->show();
    Button_restart->hide();
    Button_end->hide();
    Label_killpoint->hide();
    Label_youblood->hide();
    Label_endfail->hide();
    Label_endwin->hide();
    Label_bossblood->hide();
    Label_help->show();
    Label_Author->show();
}

void MainWindow::GameInterface()
{
    QPainter painter(this);
    QBrush brush;
    brush.setTextureImage(QImage("/home/liuxun/C++/bigproject/material/game2.jpeg"));
    painter.setBrush(brush);
    painter.drawRoundedRect(this->rect(),1,1);
    Label_killpoint->setText("Points: " + QString::number(Myfighter.showpoint()));
    Label_youblood->setText("Blood: " + QString::number(Myfighter.showblood()));
    Label_bossblood->setText("Boss: " + QString::number(Boss.showblood()));


    CheckKill();
    CheckEnemyKill();
    PaintMyFighter();
    PaintMyBullet();
    PaintEnemyFighter();
    PaintEnemyBullet();

    if(IF_BOSS_TIME)
    {
        EnemyFighterQuene.clear();
        PaintEnemyBoss();
    }
}

void MainWindow::EndInterface()
{
    Label_killpoint->setText("Points: " + QString::number(Myfighter.showpoint()));
    Label_youblood->setText("Blood: " + QString::number(Myfighter.showblood()));
    Label_bossblood->setText("Boss: " + QString::number(Boss.showblood()));

    IF_BOSS_TIME = false;

    QPainter painter(this);
    QPixmap imagewin, imagefail;
    imagewin.load("/home/liuxun/C++/bigproject/material/endwin.jpeg");
    imagefail.load("/home/liuxun/C++/bigproject/material/endfail.jpeg");

    painter.drawPixmap(0,0,600,600,imagefail);
    //Button_restart->show();
    Label_endfail->show();
    Button_quit->move(215,760);
    if(!IF_YOU_WIN)
    {
        Button_quit->show();
        Button_restart->show();
    }
    if(IF_YOU_WIN)
    {
        Button_end->show();
        //Button_restart->hide();
        if(PICTURE_CHANGE_MARK)
        {
            painter.drawPixmap(0,0,600,600,imagewin);
            Button_end->hide();
            Label_endfail->hide();
            Button_restart->show();
            Label_endwin->show();
            Button_quit->show();
        }
    }
}

void MainWindow::GameStart()
{
    Button_start->hide();
    Button_quit->hide();
    Button_restart->hide();
    Label_killpoint->show();
    Label_youblood->show();
    Label_endfail->hide();
    Label_endwin->hide();
    Label_bossblood->show();
    Label_help->hide();
    Label_Author->hide();

    Myfighter.restart();
    MyBulletQueue.clear();
    EnemyBulletQuene.clear();
    EnemyFighterQuene.clear();

    IF_GAME_START = true;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!IF_GAME_START)
    {
        return;
    }
    else
    {
        if(event->key() == Qt::Key_W)
            Myfighter.place_up();
        else if(event->key() == Qt::Key_S)
            Myfighter.place_down();
        else if(event->key() == Qt::Key_A)
            Myfighter.place_left();
        else if(event->key() == Qt::Key_D)
            Myfighter.place_right();
        else if((event->key() == Qt::Key_K)&&(!IF_BULLET_EMPTY))
        {
            MyBullet newBullet(Myfighter.showplace().x + Myfighter.showstate().w/2,Myfighter.showplace().y);
            MyBulletQueue.push_back(newBullet);
            IF_BULLET_EMPTY = true;
        }
        else if(event->key() == Qt::Key_Escape)
            IF_GAME_START = false;
        else;
    }
    return;
}

void MainWindow::PaintMyFighter()
{
    QPainter painter(this);
    QPixmap myfighterimage;
    myfighterimage.load("/home/liuxun/C++/bigproject/material/you.png");
    painter.drawPixmap(Myfighter.showplace().x,Myfighter.showplace().y,Myfighter.showstate().w,Myfighter.showstate().h,myfighterimage);
    return;
}

void MainWindow::PaintMyBullet()
{
    QPainter painter(this);
    QBrush brush;
    painter.setBrush(Qt::yellow);

    if(MyBulletQueue.empty())
        return;
    int i;
    for(i = 0;i < MyBulletQueue.size();i++)
    {
        MyBulletQueue.at(i).place_up();
        painter.drawEllipse(MyBulletQueue.at(i).showplace().x,MyBulletQueue.at(i).showplace().y,
                               MyBulletQueue.at(i).showradius(), MyBulletQueue.at(i).showradius());
    }
    return;
}

void MainWindow::PaintEnemyFighter()
{
    QPainter painter(this);
    //QBrush brush;
    //brush.setTextureImage(QImage("/home/liuxun/C++/bigproject/material/enemy.png"));
    //painter.setBrush(brush);

    QPixmap enemyimage;
    enemyimage.load("/home/liuxun/C++/bigproject/material/enemy.png");

    if(EnemyFighterQuene.empty())
        return;
    int i;
    for(i = 0;i < EnemyFighterQuene.size();i++)
    {
        EnemyFighterQuene.at(i).place_down();
        //painter.drawRect(EnemyFighterQuene.at(i).showplace().x,EnemyFighterQuene.at(i).showplace().y,
                               //EnemyFighterQuene.at(i).showstate().w, EnemyFighterQuene.at(i).showstate().h);
        painter.drawPixmap(EnemyFighterQuene.at(i).showplace().x,EnemyFighterQuene.at(i).showplace().y,
                           EnemyFighterQuene.at(i).showstate().w, EnemyFighterQuene.at(i).showstate().h,enemyimage);
    }
    return;
}

void MainWindow::MyBulletUpdate()
{
    IF_BULLET_EMPTY = false;

    int i;
    for(i = 0;i < MyBulletQueue.size();i++)
    {
        if(!MyBulletQueue.at(i).if_in_map())
            MyBulletQueue.erase(MyBulletQueue.begin() + i);
    }
    return;
}

void MainWindow::EnemyFighterUpdate()
{
    if((!IF_GAME_START)||(IF_BOSS_TIME))
        return;
    EnemyFighter NewEnemy;
    EnemyFighterQuene.push_back(NewEnemy);

    int i;
    for(i = 0;i < EnemyFighterQuene.size();i++)
    {
        if((!EnemyFighterQuene.at(i).if_in_map())||(EnemyFighterQuene.at(i).if_dead()))
           EnemyFighterQuene.erase(EnemyFighterQuene.begin() + i);
    }
    return;
}

void MainWindow::CheckKill()
{
    int i,j;
    for(i = 0;i < EnemyFighterQuene.size();i++)
    {
        for(j = 0;j < MyBulletQueue.size();j++)
        {
            if((MyBulletQueue.at(j).showplace().x > EnemyFighterQuene.at(i).showplace().x)&&
                    (MyBulletQueue.at(j).showplace().x < EnemyFighterQuene.at(i).showplace().x + EnemyFighterQuene.at(i).showstate().w)&&
                    (MyBulletQueue.at(j).showplace().y > EnemyFighterQuene.at(i).showplace().y)&&
                    (MyBulletQueue.at(j).showplace().y < EnemyFighterQuene.at(i).showplace().y + EnemyFighterQuene.at(i).showstate().h))
            {
                MyBulletQueue.erase(MyBulletQueue.begin() + j);
                EnemyFighterQuene.at(i).blooddown(ATTACK_TO_ENEMY);
                Myfighter.addkillpoint(1);
                if(Myfighter.showpoint() >= GAME_LEVEL)
                    IF_BOSS_TIME = true;
            }
        }
        if(EnemyFighterQuene.at(i).if_dead())
            EnemyFighterQuene.erase(EnemyFighterQuene.begin() + i);

    }

    if(IF_BOSS_TIME)
    {
        for(i = 0;i < MyBulletQueue.size();i++)
        {
            //if(Boss.if_injured(MyBulletQueue.at(i).showplace().x, MyBulletQueue.at(i).showplace().y))
            if((MyBulletQueue.at(i).showplace().x > Boss.showplace().x)&&
                    (MyBulletQueue.at(i).showplace().x < Boss.showplace().x + Boss.showstate().w)&&
                    (MyBulletQueue.at(i).showplace().y > Boss.showplace().y)&&
                    (MyBulletQueue.at(i).showplace().y < Boss.showplace().y + Boss.showstate().h))
            {
                MyBulletQueue.erase(MyBulletQueue.begin() + i);
                Boss.blooddown(ATTACK_TO_BOSS);
                if(Boss.if_dead())
                {
                    IF_YOU_LIVE = false;
                    IF_YOU_WIN = true;
                }
            }
        }
    }

    return;
}

void MainWindow::EnemyBulletUpdate()
{
    int i;

    for(i = 0;i < EnemyFighterQuene.size();i++)
    {
        srand(time(nullptr));
        EnemyBullet NewEnemyBullet1 = EnemyBullet(EnemyFighterQuene.at(i).showplace().x + EnemyFighterQuene.at(i).showstate().w/2,
                                                 EnemyFighterQuene.at(i).showplace().y + EnemyFighterQuene.at(i).showstate().h,random(3) - 1);
        EnemyBullet NewEnemyBullet2 = EnemyBullet(EnemyFighterQuene.at(i).showplace().x + EnemyFighterQuene.at(i).showstate().w/2,
                                                 EnemyFighterQuene.at(i).showplace().y + EnemyFighterQuene.at(i).showstate().h,random(3) - 1);
        EnemyBulletQuene.push_back(NewEnemyBullet1);
        EnemyBulletQuene.push_back(NewEnemyBullet2);
    }

    if(IF_BOSS_TIME)
    {
        srand(time(nullptr));

        EnemyBullet NewBossBullet1 = EnemyBullet(Boss.showplace().x, Boss.showplace().y + Boss.showstate().h,random(3) - 1);
        EnemyBullet NewBossBullet2 = EnemyBullet(Boss.showplace().x + Boss.showstate().w/5,Boss.showplace().y + Boss.showstate().h,random(3) - 1);
        EnemyBullet NewBossBullet3 = EnemyBullet(Boss.showplace().x + Boss.showstate().w/5.0*2,Boss.showplace().y + Boss.showstate().h,random(3) - 1);
        EnemyBullet NewBossBullet4 = EnemyBullet(Boss.showplace().x + Boss.showstate().w/5.0*3,Boss.showplace().y + Boss.showstate().h,random(3) - 1);
        EnemyBullet NewBossBullet5 = EnemyBullet(Boss.showplace().x + Boss.showstate().w/5.0*4,Boss.showplace().y + Boss.showstate().h,random(3) - 1);
        EnemyBullet NewBossBullet6 = EnemyBullet(Boss.showplace().x + Boss.showstate().w,Boss.showplace().y + Boss.showstate().h,random(3) - 1);

        EnemyBulletQuene.push_back(NewBossBullet1);
        EnemyBulletQuene.push_back(NewBossBullet2);
        EnemyBulletQuene.push_back(NewBossBullet3);
        EnemyBulletQuene.push_back(NewBossBullet4);
        EnemyBulletQuene.push_back(NewBossBullet5);
        EnemyBulletQuene.push_back(NewBossBullet6);
    }

    for(i = 0;i < EnemyBulletQuene.size();i++)
    {
        if(!EnemyBulletQuene.at(i).if_in_map())
            EnemyBulletQuene.erase(EnemyBulletQuene.begin() + i);
    }

    return;
}

void MainWindow::PaintEnemyBullet()
{
    QPainter painter(this);
    QBrush brush;
    painter.setBrush(Qt::red);

    if(EnemyBulletQuene.empty())
        return;
    int i;
    for(i = 0;i < EnemyBulletQuene.size();i++)
    {
        EnemyBulletQuene.at(i).place_down();
        if(EnemyBulletQuene.at(i).showdirection() == -1)
            EnemyBulletQuene.at(i).place_left();
        else if(EnemyBulletQuene.at(i).showdirection() == 1)
            EnemyBulletQuene.at(i).place_right();
        else;
        painter.drawEllipse(EnemyBulletQuene.at(i).showplace().x,EnemyBulletQuene.at(i).showplace().y,
                               EnemyBulletQuene.at(i).showradius(), EnemyBulletQuene.at(i).showradius());
    }
    return;
}

void MainWindow::CheckEnemyKill()
{
    int i;
    for(i = 0;i < EnemyBulletQuene.size();i++)
    {
        if((EnemyBulletQuene.at(i).showplace().x > Myfighter.showplace().x)&&
                (EnemyBulletQuene.at(i).showplace().x < Myfighter.showplace().x + Myfighter.showstate().w)&&
                (EnemyBulletQuene.at(i).showplace().y > Myfighter.showplace().y)&&
                (EnemyBulletQuene.at(i).showplace().y < Myfighter.showplace().y + Myfighter.showstate().h))
        {
            EnemyBulletQuene.erase(EnemyBulletQuene.begin() + i);
            Myfighter.blooddown(ATTACK_TO_YOU);
        }
        if(Myfighter.if_dead())
        {
            IF_YOU_LIVE = false;
        }
    }
    return;
}

void MainWindow::GameRestart()
{
    IF_GAME_START = false;
}

void MainWindow::PaintEnemyBoss()
{
    QPainter painter(this);
    QPixmap bossimage;
    bossimage.load("/home/liuxun/C++/bigproject/material/boss4.png");

    srand(time(nullptr));
    int k = random(4);
    if(k == 0)
        Boss.place_up();
    else if(k == 1)
        Boss.place_down();
    else if(k == 2)
        Boss.place_left();
    else
        Boss.place_right();

    painter.drawPixmap(Boss.showplace().x,Boss.showplace().y,Boss.showstate().w,Boss.showstate().h,bossimage);
}

void MainWindow::EndPictureChange()
{
    PICTURE_CHANGE_MARK = true;
}
