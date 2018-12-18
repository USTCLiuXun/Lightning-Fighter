#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QPushButton>
#include <QLayout>
#include <QKeyEvent>
#include <QLabel>
#include <vector>
#include <unistd.h>
#include <time.h>
#include "fighter.h"

using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void BootInterface();
    void GameInterface();
    void EndInterface();
    void PaintMyFighter();
    void PaintMyBullet();
    void PaintEnemyFighter();
    void PaintEnemyBullet();
    void PaintEnemyBoss();
    void CheckKill();
    void CheckEnemyKill();
public slots:
    void GameStart();
    void GameRestart();
    void MyBulletUpdate();
    void EnemyBulletUpdate();
    void EnemyFighterUpdate();
    void EndPictureChange();
private:
    Ui::MainWindow *ui;
    QPushButton *Button_start;
    QPushButton *Button_quit;
    QPushButton *Button_restart;
    QPushButton *Button_end;
    QLabel *Label_killpoint;
    QLabel *Label_youblood;
    QLabel *Label_bossblood;
    QLabel *Label_endfail;
    QLabel *Label_endwin;
    QLabel *Label_help;
    QLabel *Label_Author;
    MyFighter Myfighter;
    EnemyBoss Boss;
    vector <MyBullet> MyBulletQueue;
    vector <EnemyFighter> EnemyFighterQuene;
    vector <EnemyBullet> EnemyBulletQuene;
};

#endif // MAINWINDOW_H
