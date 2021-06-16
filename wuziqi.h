#ifndef WUZIQI_H
#define WUZIQI_H

#include <QWidget>
#include <QLabel>
#include <QStack>
#include<QPaintEvent>
#include<QPainter>
#include"internet.h"
#include<QMouseEvent>
#include<QDebug>
#include<QMessageBox>
namespace Ui {
class wuziqi;
}

class wuziqi : public QWidget
{
    Q_OBJECT

public:
    explicit wuziqi(QWidget *parent = nullptr);
    //wuziqi(internet *client_,QWidget *parent = nullptr);
    ~wuziqi();

public:
    //internet *client;


private:
    Ui::wuziqi *ui;
    int square;//用于保存窗口除以格子后的平均值，便于使用。目前已经是历史遗留问题了

    QPixmap white_chess;//保存白棋的主题
    QPixmap black_chess;//保存黑棋的主题
    QPixmap background;//保存背景主题

    QVector<QVector<QPair<QRect,int>>>press_board;//核心，存储了棋盘的点击范围、当前位置是否已有子等信息。
    QStack<QPair<int,int>>back;

    bool black=true;
    bool running;
public:
    void initialization();//初始化，用于重新游戏
    void win(int x,int y);//判断胜利条件
    void take_chess(int ,int );
    //void go_back();
protected:
      void closeEvent(QCloseEvent *event);
      void paintEvent(QPaintEvent *);
      void mousePressEvent(QMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event);

private slots:
      void on_Button_back_clicked();
      void on_Button_new_clicked();
      void on_Button_exit_clicked();
signals:
      void game_over();
};

#endif // WUZIQI_H
