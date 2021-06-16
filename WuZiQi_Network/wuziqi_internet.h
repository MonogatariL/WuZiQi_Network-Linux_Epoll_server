#ifndef WUZIQI_INTERNET_H
#define WUZIQI_INTERNET_H

#include <QWidget>
#include <QLabel>
#include <QStack>
#include<QPaintEvent>
#include<QPainter>
#include"internet.h"
#include<QMouseEvent>
#include<QDebug>
#include<QMessageBox>
#include<stdio.h>
#include<stdlib.h>
#include<QTimer>
namespace Ui {
class wuziqi_internet;
}

class wuziqi_internet : public QWidget
{
    Q_OBJECT

public:
    explicit wuziqi_internet(QWidget *parent = nullptr){};
    wuziqi_internet(int x,int y,internet *client_,QString room_name,QWidget *parent = nullptr);
    ~wuziqi_internet();

    internet *client;
private:
    Ui::wuziqi_internet *ui;

    int square;//用于保存窗口除以格子后的平均值，便于使用。目前已经是历史遗留问题了

    QPixmap white_chess;//保存白棋的主题
    QPixmap black_chess;//保存黑棋的主题
    QPixmap background;//保存背景主题

    QVector<QVector<QPair<QRect,int>>>press_board;//核心，存储了棋盘的点击范围、当前位置是否已有子等信息。
    QStack<QPair<int,int>>back;//存放每一步的位置，用于悔棋

    bool wait;//用于游戏运行中，一方发出悔棋、新游戏的请求后发出方持续的状态，这个状态下发出方将只等待处理对方的回应信息
    bool turn;//用于游戏运行中，你的回合，为你的回合时才能下棋，但此时，依然可以点击悔棋、新游戏等按钮
    int timerId1;
    int color;//颜色，先后手，0为白棋，1为黑棋，其他值为游戏尚未开始
    bool running;//游戏运行与否，为false则代表游戏处于等待状态，需要两个玩家，并且都准备
    bool prepare;//存放准备按钮的值，0为未准备，1为准备。
    bool ban_mouse;

public:
    void initialization();
    void take_chess(int ,int );
    void win(char x,char y);//判断胜利条件
    void go_back();
    void get_prepare_information();
    void wait_over();
protected:
      void closeEvent(QCloseEvent *event);
      void paintEvent(QPaintEvent *);
      void mousePressEvent(QMouseEvent *event);
      void timerEvent(QTimerEvent* event);
      void keyPressEvent(QKeyEvent * event);

signals:
      void game_over();
private slots:
      void on_Button_exit_room_clicked();
      void on_Button_prepare_clicked();
      void on_Button_black_clicked();
      void on_Button_white_clicked();
      void on_Button_exiting_clicked();
      void on_Button_back_clicked();
      void on_Button_agreen_clicked();
      void on_Button_refuse_clicked();
      void on_Button_send_clicked();
      void on_Button_back_surrender_clicked();
};

#endif // WUZIQI_INTERNET_H
